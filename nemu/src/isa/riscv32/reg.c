#include <isa.h>
#include "local-include/reg.h"

const char *regs[] = {
  "$0", "ra", "sp", "gp", "tp", "t0", "t1", "t2",
  "s0", "s1", "a0", "a1", "a2", "a3", "a4", "a5",
  "a6", "a7", "s2", "s3", "s4", "s5", "s6", "s7",
  "s8", "s9", "s10", "s11", "t3", "t4", "t5", "t6"
};

const char *regs_num[] = {
  "0", "1", "2", "3", "4", "5", "6", "7",
  "8", "9", "10", "11", "12", "13", "14", "15",
  "16", "17", "18", "19", "20", "21", "22", "23",
  "24", "25", "26", "27", "28", "29", "30", "31"
};

void isa_reg_display() {
  int i;
  for(i=0;i<(sizeof(regs)/sizeof(regs[0]));i++){
    printf("%s  %s  %d\n",regs[i],regs_num[i],gpr(i));
  }
  printf("%s  %d\n","pc",cpu.pc);
  
}

word_t isa_reg_str2val(const char *s, bool *success) {
  int i;
  for(i = 0;i<(sizeof(regs)/sizeof(regs[0]));i++){
    if(strcmp(s,regs[i])==0 ||strcmp(s,regs_num[i])==0){
      *success = true;
      printf("%d\n",gpr(i));
      return gpr(i);
    }
  }
  if(strcmp(s,"pc")==0){
   *success = true;
    return cpu.pc;
  }
  *success = false;
  return 0;
}
