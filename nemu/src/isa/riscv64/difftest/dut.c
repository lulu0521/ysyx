#include <isa.h>
#include <cpu/difftest.h>
#include "../local-include/reg.h"

bool isa_difftest_checkregs(CPU_state *ref_r, vaddr_t pc) {
  int i;
  for(i=0; i<32; i++){
    if(ref_r->gpr[i]!=gpr(i) || ref_r->pc!=cpu.pc){
      printf("ref_r->gpr[%d]=%ld\ngpr(%d)=%ld\n",i,ref_r->gpr[i],i,gpr(i));
      printf("ref_r->pc=0x%lx\npc=0x%lx\n",ref_r->pc,pc);
      return false;
    }   
  }
  return true;
}

void isa_difftest_attach() {
}
