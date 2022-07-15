#include <am.h>
#include <nemu.h>
#include <stdio.h>


#define MASK 0x8000
void __am_input_keybrd(AM_INPUT_KEYBRD_T *kbd) {
  int k = inl(KBD_ADDR);
  //printf("===\n");
  kbd->keydown = (k & MASK) ? 1:0;
  kbd->keycode = k & ~MASK;
}