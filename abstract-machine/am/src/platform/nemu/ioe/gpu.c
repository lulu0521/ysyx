#include <am.h>
#include <nemu.h>

#define SYNC_ADDR (VGACTL_ADDR + 4)


void __am_gpu_init() {
#if 0
  int i;
  int w = io_read(AM_GPU_CONFIG).width;  // TODO: get the correct width
  int h = io_read(AM_GPU_CONFIG).height;  // TODO: get the correct height
  uint32_t *fb = (uint32_t *)(uintptr_t)FB_ADDR;
  for (i = 0; i < w * h; i ++) fb[i] = i;
  outl(SYNC_ADDR, 1);
#endif
}


void __am_gpu_config(AM_GPU_CONFIG_T *cfg) {
  uint32_t num = inl(VGACTL_ADDR);
  *cfg = (AM_GPU_CONFIG_T) {
    .present = true, .has_accel = false,
    .width = num>>16, .height = num & 0xffff,
    .vmemsz = 0
  };
}
//io_write(AM_GPU_FBDRAW, x * w, y * h, color_buf, w, h, false);
//int x, y; void *pixels; int w, h; bool sync

void __am_gpu_fbdraw(AM_GPU_FBDRAW_T *ctl) {
 // printf("8888888888\n");
  uint32_t *p = (uint32_t *) ctl->pixels;
  uint32_t *fb = (uint32_t *)(uintptr_t)FB_ADDR;
  int w = io_read(AM_GPU_CONFIG).width;
  int i,j;
  for(i=0; i<ctl->h; i++){
    for(j=0; j<ctl->w; j++){
      fb[(ctl->y+i)*w+ctl->x+j] = p[i*ctl->w+j];
    }
  }
  if (ctl->sync) {
    outl(SYNC_ADDR, 1);
  }
}

void __am_gpu_status(AM_GPU_STATUS_T *status) {
  status->ready = true;
}
