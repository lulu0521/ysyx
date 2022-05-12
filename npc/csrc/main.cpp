#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <nvboard.h>
#include <VSW_C.h>

static TOP_NAME dut;
void nvboard_bind_all_pins(VSW_C* top);

static void single_cycle() {
  //int a = rand() & 1;
  //int b = rand() & 1;
  //dut->a = a;
  //dut->b = b;
  dut.clk = 0; dut.eval();
  dut.clk = 1; dut.eval();
 
}

static void reset(int n) {
  dut.rst = 1;
  while (n -- > 0) single_cycle();
  dut.rst = 0;
}

int main() {
  nvboard_bind_all_pins(&dut);
  nvboard_init();


  reset(10);

  while(1) {
    nvboard_update();
    single_cycle();
  }
}

