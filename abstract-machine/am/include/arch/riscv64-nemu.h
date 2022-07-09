#ifndef ARCH_H__
#define ARCH_H__

struct Context {
  // TODO: fix the order of these members to match trap.S
  uintptr_t gpr[32],mcause,mstatus,mepc;
  void *pdir;
};

#define GPR1 gpr[17] // a7
#define GPR2 gpr[10]//a0
#define GPR3 gpr[11]//a1
#define GPR4 gpr[12]//a2
#define GPRx gpr[10]//a0
#endif

/*
const char *regs[] = {
  "$0", "ra", "sp", "gp", "tp", "t0", "t1", "t2",//8
  "s0", "s1", "a0", "a1", "a2", "a3", "a4", "a5",
  "a6", "a7", "s2", "s3", "s4", "s5", "s6", "s7",
  "s8", "s9", "s10", "s11", "t3", "t4", "t5", "t6"
};
*/ 