#include <cpu/cpu.h>
#include <cpu/decode.h>
#include <cpu/difftest.h>
#include <locale.h>
#include "../monitor/sdb/watchpoint.h"
#include "../monitor/sdb/sdb.h"
#include <elf.h>
#include <device/map.h>

/* The assembly code of instructions executed is only output to the screen
 * when the number of instructions executed is less than this value.
 * This is useful when you use the `si' command.
 * You can modify this value as you want.
 */
#define MAX_INST_TO_PRINT 10
#define RB_LEN 32

CPU_state cpu = {};
uint64_t g_nr_guest_inst = 0;
static uint64_t g_timer = 0; // unit: us
static bool g_print_step = false;
char iringbuf[RB_LEN][128];
/*==========iringbuf arg==============*/
int tail = 0;
int g_inst_num = 0;
/*========mtrace arg=========*/
char g_mem_info[256];
char *g_mem_ = g_mem_info;
char *g_mem = g_mem_info;
char **g_mem_p = &g_mem;
/*===========ftrace arg==============*/
int j_flag = 0;
char g_ftrace_info[128];
char *g_ftrace = g_ftrace_info;
/*===========dtrace arg==========*/
vaddr_t data_addr = 0;
int data_flag=0;
int dtrace_flag = 0;
char g_dtrace_info[128];
char* g_dtrace = g_dtrace_info;
/*===========etrace arg==========*/
int etrace_flag=0;

void device_update();

void ringbuf_dispaly(){
  int i;
  for(i=0;i<g_inst_num;i++){
    if(i==tail){
      printf("---->%s\n",iringbuf[i]);
    }
    printf("%s\n",iringbuf[i]);
  }
}


static void trace_and_difftest(Decode *_this, vaddr_t dnpc) {
#ifdef CONFIG_ITRACE_COND
//itrace print infomation of instruction 
  if (ITRACE_COND) { log_write("%s\n", _this->logbuf); }
  sprintf(iringbuf[tail],"%s",_this->logbuf);
  tail = (tail+1)%RB_LEN;
  if(g_inst_num<RB_LEN)
    ++g_inst_num;
#endif
  if (g_print_step) { IFDEF(CONFIG_ITRACE, puts(_this->logbuf)); }

#ifdef CONFIG_MTRACE_COND
  if (CONFIG_MTRACE_COND) { log_write("%s\n", g_mem_); }
#endif

  IFDEF(CONFIG_DIFFTEST, difftest_step(_this->pc, dnpc));

#ifdef CONFIG_FTRACE
  if(j_flag==1){
    j_flag = 0;
    ftrace_write("%s\n",g_ftrace);
  }
#endif

#ifdef CONFIG_DTRACE
  if(data_flag == 1 ){
    if(dtrace_flag==1){
      data_flag = 0;
      dtrace_flag=0;
    dtrace_write("%s\n", g_dtrace);
  }else{
    data_flag = 0;
  }
 }   
  
#endif

#if 0
  WP *p = scan_WP();
  if(p != NULL){
    nemu_state.state = NEMU_STOP;
    printf("watchpoint triggered\n");
    sdb_mainloop();
  }
#endif
}

#if defined(CONFIG_ITRACE) || defined(CONFIG_MTRACE) 
void trace_once(Decode *s,char** info_p,char *start_p, size_t psize){
  *info_p += snprintf(*info_p,start_p + psize - *info_p, FMT_WORD ":", s->pc);
  int ilen = s->snpc - s->pc;
  int i;
  uint8_t *inst = (uint8_t *)&s->isa.inst.val;
  for (i = ilen-1; i >= 0; i --) {
    *info_p += snprintf(*info_p, 4, " %02x", inst[i]);
  }
  int ilen_max = MUXDEF(CONFIG_ISA_x86, 8, 4);
  int space_len = ilen_max - ilen;
  if (space_len < 0) space_len = 0;
  space_len = space_len * 3 + 1;
  memset(*info_p, ' ', space_len);
  *info_p += space_len;
  void disassemble(char *str, int size, uint64_t pc, uint8_t *code, int nbyte);
  disassemble(*info_p, start_p + psize - *info_p,
      MUXDEF(CONFIG_ISA_x86, s->snpc, s->pc), (uint8_t *)&s->isa.inst.val, ilen);
  * info_p = g_mem_;
}
#endif

#ifdef CONFIG_FTRACE
void ftrace(Decode *s,char* info_p){
  extern int symtab_num;
  extern Elf32_Sym *symtab;
  extern char *strtab;
  int i;
  // printf("%d",symtab_num); 
  for(i=0;i<symtab_num;i++){
   
      if(symtab[i].st_info%16==STT_FUNC){  
        if(s->dnpc>=symtab[i].st_value && s->dnpc<symtab[i].st_value+symtab[i].st_size){
          if(s->dnpc==symtab[i].st_value){
          sprintf(info_p,"0x%x: call[ %s @0x%x ]\n",s->pc,strtab+symtab[i].st_name,s->dnpc);
          }
          else{
          sprintf(info_p,"0x%x: ret[ %s ]\n",s->pc,strtab+symtab[i].st_name);
        }
        }   
      }
    }
}
#endif

#ifdef CONFIG_DTRACE
  void dtrace(Decode *s){
    int i;
    extern int nr_map;
    extern IOMap maps[NR_MAP];
    for(i=0;i<nr_map;i++){
       dtrace_flag = map_inside(&maps[i],data_addr);
      if(dtrace_flag ==1){
        sprintf(g_dtrace,"0x%lx  %s\n",s->pc,maps[i].name );
        //printf("%s",g_dtrace);
        return;
      }
    }
  }
#endif
static void exec_once(Decode *s, vaddr_t pc) {
  s->pc = pc;
  s->snpc = pc;
  isa_exec_once(s);
  cpu.pc = s->dnpc;
#ifdef CONFIG_ITRACE
  char *p = s->logbuf;
//trace once instruction
  trace_once(s,&p,p, sizeof(s->logbuf));
#endif
#ifdef CONFIG_MTRACE
//trace once instruction
  trace_once(s,g_mem_p,g_mem_, sizeof(g_mem_info));
#endif
#ifdef CONFIG_FTRACE
  if(j_flag==1){
    ftrace(s,g_ftrace);
  } 
#endif
#ifdef CONFIG_DTRACE
  if(data_flag==1){
    dtrace(s);
  }
#endif
#ifdef CONFIG_ETRACE
  if(etrace_flag==1){
    if(cpu.mcause>-1&&cpu.mcause<20){
      printf("STRACE:%ld\n",cpu.mcause);
    }else{
      printf("ETRACE:%ld\n",cpu.mcause);
    }
    etrace_flag=0;
  }
#endif
}

static void execute(uint64_t n) {
  Decode s;
  for (;n > 0; n --) {
    exec_once(&s, cpu.pc);
    g_nr_guest_inst ++;
    trace_and_difftest(&s, cpu.pc);
    if (nemu_state.state != NEMU_RUNNING) break;
    IFDEF(CONFIG_DEVICE, device_update());
  }
}

static void statistic() {
  IFNDEF(CONFIG_TARGET_AM, setlocale(LC_NUMERIC, ""));
#define NUMBERIC_FMT MUXDEF(CONFIG_TARGET_AM, "%ld", "%'ld")
  Log("host time spent = " NUMBERIC_FMT " us", g_timer);
  Log("total guest instructions = " NUMBERIC_FMT, g_nr_guest_inst);
  if (g_timer > 0) Log("simulation frequency = " NUMBERIC_FMT " inst/s", g_nr_guest_inst * 1000000 / g_timer);
  else Log("Finish running in less than 1 us and can not calculate the simulation frequency");
}


//if program run error,print register infomation and so on
void assert_fail_msg() {
  isa_reg_display();
  statistic();
}

/* Simulate how the CPU works. */
void cpu_exec(uint64_t n) {
  g_print_step = (n < MAX_INST_TO_PRINT);
  switch (nemu_state.state) {
    case NEMU_END: case NEMU_ABORT:
      printf("Program execution has ended. To restart the program, exit NEMU and run again.\n");
      return;
    default: nemu_state.state = NEMU_RUNNING;
  }

  uint64_t timer_start = get_time();
  execute(n);

  uint64_t timer_end = get_time();
  g_timer += timer_end - timer_start;

  switch (nemu_state.state) {
    case NEMU_RUNNING: nemu_state.state = NEMU_STOP; break;
    case NEMU_END: case NEMU_ABORT:
      Log("nemu: %s at pc = " FMT_WORD,
          (nemu_state.state == NEMU_ABORT ? ANSI_FMT("ABORT", ANSI_FG_RED) :
           (nemu_state.halt_ret == 0 ? ANSI_FMT("HIT GOOD TRAP", ANSI_FG_GREEN) :
            ANSI_FMT("HIT BAD TRAP", ANSI_FG_RED))),
          nemu_state.halt_pc);
        if(nemu_state.state != NEMU_ABORT && nemu_state.halt_ret != 0){
          ringbuf_dispaly();
        }
      // fall through
    case NEMU_QUIT: statistic();
  }
}
