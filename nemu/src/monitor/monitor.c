#include <isa.h>
#include <memory/paddr.h>
#include <elf.h>
#include <time.h>
void init_rand();
void init_log(const char *log_file);
void init_ftrace_fp(const char *log_file);
void init_mem();
void init_difftest(char *ref_so_file, long img_size, int port);
void init_device();
void init_sdb();
void init_disasm(const char *triple);

static void welcome() {
  Log("Trace: %s", MUXDEF(CONFIG_TRACE, ANSI_FMT("ON", ANSI_FG_GREEN), ANSI_FMT("OFF", ANSI_FG_RED)));
  IFDEF(CONFIG_TRACE, Log("If trace is enabled, a log file will be generated "
        "to record the trace. This may lead to a large log file. "
        "If it is not necessary, you can disable it in menuconfig"));
  Log("Build time: %s, %s", __TIME__, __DATE__);
  printf("Welcome to %s-NEMU!\n", ANSI_FMT(str(__GUEST_ISA__), ANSI_FG_YELLOW ANSI_BG_RED));
  printf("For help, type \"help\"\n");
 // Log("Exercise: Please remove me in the source code and compile NEMU again.");
 // assert(0);
}

#ifndef CONFIG_TARGET_AM
#include <getopt.h>
void sdb_set_batch_mode();

static char *log_file = NULL;
static char *diff_so_file = NULL;
static char *img_file = NULL;
static char *elf_file =NULL;
static char *ftrace_file =NULL;
static int difftest_port = 1234;
/*
typedef struct {
  uint32_t      st_name;
  Elf32_Addr    st_value;
  uint32_t      st_size;
  unsigned char st_info;
  unsigned char st_other;
  uint16_t      st_shndx;
} Elf32_Sym;*/
int symtab_num = 0;
Elf32_Sym *symtab;
char *strtab;

static long load_img() {
  if (img_file == NULL) {
    if (elf_file == NULL) {
      Log("No image is given. Use the default build-in image.");
      return 4096; // built-in image size
    } else {
      // TODO Load the ELF image
      typedef struct {
               uint32_t   p_type;
               Elf32_Off  p_offset;
               Elf32_Addr p_vaddr;
               Elf32_Addr p_paddr;
               uint32_t   p_filesz;
               uint32_t   p_memsz;
               uint32_t   p_flags;
               uint32_t   p_align;
      } Elf32_Phdr;//PT_LOAD

      long size_elf = 0;
      uint32_t prog_header_tab_off;
      uint16_t prog_header_tab_num;
      uint16_t prog_header_tab_len;
      int size_;
      FILE *fp_elf = fopen(elf_file, "rb");
      Assert(fp_elf, "Can not open '%s'", elf_file);
      fseek(fp_elf,28,SEEK_SET);
      size_ = fread(&prog_header_tab_off,4,1,fp_elf);
      assert(size_ == 1);
      fseek(fp_elf,44,SEEK_SET);
      size_ = fread(&prog_header_tab_num,2,1,fp_elf);
      assert(size_ == 1);
      fseek(fp_elf,42,SEEK_SET);
      size_ = fread(&prog_header_tab_len,2,1,fp_elf);
      assert(size_ == 1);
      Elf32_Phdr *prog_header = malloc(prog_header_tab_len*prog_header_tab_num);
      for(int i=0;i<prog_header_tab_num;i++){
        fseek(fp_elf,prog_header_tab_off+i*prog_header_tab_len,SEEK_SET);
        size_ = fread(&prog_header[i],sizeof(Elf32_Phdr),1,fp_elf);
        assert(size_ == 1);
      }
      for(int i=0;i<prog_header_tab_num;i++){
        if(prog_header[i].p_type==PT_LOAD){
          fseek(fp_elf, prog_header[i].p_offset, SEEK_SET);
          size_ = fread(guest_to_host(prog_header[i].p_vaddr), prog_header[i].p_filesz, 1, fp_elf);
          assert(size_ == 1);
          size_elf += prog_header[i].p_filesz;
        }
      }
      //printf("%lx",size_elf);
      return size_elf;
      
    }
  }

  FILE *fp = fopen(img_file, "rb");
  Assert(fp, "Can not open '%s'", img_file);

  fseek(fp, 0, SEEK_END);
  long size = ftell(fp);

  Log("The image is %s, size = %ld", img_file, size);

  fseek(fp, 0, SEEK_SET);
  int ret = fread(guest_to_host(RESET_VECTOR), size, 1, fp);
  assert(ret == 1);

  fclose(fp);
  return size;
}

#ifdef CONFIG_FTRACE
static void init_ftrace(){
  uint32_t section_header_tab_off;
  uint16_t section_header_len;
  uint16_t shstrtab_index;
  size_t size;
typedef struct{
    uint32_t   sh_name;
    uint32_t   sh_type;
    uint32_t   sh_flags;
    Elf32_Addr sh_addr;
    Elf32_Off  sh_offset;
    uint32_t   sh_size;
    uint32_t   sh_link;
    uint32_t   sh_info;
    uint32_t   sh_addralign;
    uint32_t   sh_entsize;
}Elf32_Shdr;
  Elf32_Shdr strtab_section;
  Elf32_Shdr symtab_section;

  if (!elf_file) {
    Log("ftrace is unsupported when no ELF file!\n");
    return;
  }
extern bool log_enable();
extern FILE* log_fp;
  printf("%d %p\n", log_enable(), log_fp);
  log_write("Current time %lu\n",  time(0));

  FILE* fp = fopen(elf_file,"rb");
  Assert(fp, "Can not open elf '%s'", elf_file);
//the offset of section_header_tab in ELF
  fseek(fp,32,SEEK_SET);
  size = fread(&section_header_tab_off,4,1,fp);
  assert(size == 1);
//the length of one section_header
  fseek(fp,46,SEEK_SET);
  size = fread(&section_header_len,2,1,fp);
  assert(size == 1);
//the index of shstrtab 
  fseek(fp,50,SEEK_SET);
  size = fread(&shstrtab_index,2,1,fp);
  assert(size == 1);
//get the infomation of strtab_section
  fseek(fp,section_header_tab_off+(shstrtab_index-1)*section_header_len,SEEK_SET);
  size = fread(&strtab_section,section_header_len,1,fp);
  assert(size == 1);
//get the infomation of symtab_section
  fseek(fp,section_header_tab_off+(shstrtab_index-2)*section_header_len,SEEK_SET);
  size = fread(&symtab_section,section_header_len,1,fp);
  assert(size == 1);
//put the infomation of strtab in strtab
  fseek(fp,strtab_section.sh_offset,SEEK_SET);
  strtab = (char*)malloc(strtab_section.sh_size);
  size = fread(strtab,strtab_section.sh_size,1,fp);
  assert(size == 1);
//put the infomation of strtab in symtab
  fseek(fp,symtab_section.sh_offset,SEEK_SET);
  symtab =(Elf32_Sym*) malloc(symtab_section.sh_size);
  symtab_num = symtab_section.sh_size/sizeof(Elf32_Sym);
  for(int i=0;i<symtab_num;i++){
    size = fread(&symtab[i],sizeof(Elf32_Sym),1,fp);
    assert(size == 1);
  }
  
  fclose(fp);
}

#endif
static int parse_args(int argc, char *argv[]) {
  const struct option table[] = {
    {"batch"    , no_argument      , NULL, 'b'},
    {"log"      , required_argument, NULL, 'l'},
    {"diff"     , required_argument, NULL, 'd'},
    {"port"     , required_argument, NULL, 'p'},
    {"help"     , no_argument      , NULL, 'h'},
    {"elf"      , required_argument, NULL, 'e'},
    {"ftrace"   , required_argument, NULL, 'f'},
    {0          , 0                , NULL,  0 },
  };
  int o;
  while ( (o = getopt_long(argc, argv, "-bhl:d:p:e:", table, NULL)) != -1) {
    switch (o) {
      case 'b': sdb_set_batch_mode(); break;
      case 'p': sscanf(optarg, "%d", &difftest_port); break;
      case 'l': log_file = optarg; break;
      case 'd': diff_so_file = optarg; break;
      case 'e': elf_file = optarg; break;
      case 'f': ftrace_file = optarg; break;
      case 1: img_file = optarg; return 0;
      default:
        printf("Usage: %s [OPTION...] IMAGE [args]\n\n", argv[0]);
        printf("\t-b,--batch              run with batch mode\n");
        printf("\t-l,--log=FILE           output log to FILE\n");
        printf("\t-d,--diff=REF_SO        run DiffTest with reference REF_SO\n");
        printf("\t-p,--port=PORT          run DiffTest with port PORT\n");
        printf("\t-e,--elf                no .elf file");///////////
        printf("\t-f,--ftrace             output ftrace to ftrace_file");
        printf("\n");
        exit(0);
    }
  }
  return 0;
}

void init_monitor(int argc, char *argv[]) {
  /* Perform some global initialization. */

  /* Parse arguments. */
  parse_args(argc, argv);

  /* Set random seed. */
  init_rand();

  /* Open the log file. */
  init_log(log_file);

  init_ftrace_fp(ftrace_file);
  /* Initialize memory. */
  init_mem();

  /* Initialize ftrace. */
  IFDEF(CONFIG_FTRACE,init_ftrace());

  /* Initialize devices. */
  IFDEF(CONFIG_DEVICE, init_device());

  /* Perform ISA dependent initialization. */
  init_isa();

  /* Load the image to memory. This will overwrite the built-in image. */
  long img_size = load_img();

  /* Initialize differential testing. */
  init_difftest(diff_so_file, img_size, difftest_port);

  /* Initialize the simple debugger. */
  init_sdb();

  IFDEF(CONFIG_ITRACE, init_disasm(
    MUXDEF(CONFIG_ISA_x86,     "i686",
    MUXDEF(CONFIG_ISA_mips32,  "mipsel",
    MUXDEF(CONFIG_ISA_riscv32, "riscv32",
    MUXDEF(CONFIG_ISA_riscv64, "riscv64", "bad")))) "-pc-linux-gnu"
  ));

  IFDEF(CONFIG_MTRACE, init_disasm(
    MUXDEF(CONFIG_ISA_x86,     "i686",
    MUXDEF(CONFIG_ISA_mips32,  "mipsel",
    MUXDEF(CONFIG_ISA_riscv32, "riscv32",
    MUXDEF(CONFIG_ISA_riscv64, "riscv64", "bad")))) "-pc-linux-gnu"
  ));

  /* Display welcome message. */
  welcome();
}
#else // CONFIG_TARGET_AM
static long load_img() {
  extern char bin_start, bin_end;
  size_t size = &bin_end - &bin_start;
  Log("img size = %ld", size);
  memcpy(guest_to_host(RESET_VECTOR), &bin_start, size);
  return size;
}

void am_init_monitor() {
  init_rand();
  init_mem();
  init_isa();
  load_img();
  IFDEF(CONFIG_DEVICE, init_device());
  welcome();
}
#endif
