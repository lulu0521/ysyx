#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include <fcntl.h>


#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
static int evtdev = -1;
static int fbdev = -1;
static int screen_w = 0, screen_h = 0;
//struct timeval st;
static int dpdev=-1;

uint32_t NDL_GetTicks() {
  struct timeval et;
  gettimeofday(&et,NULL);
  uint32_t tms = et.tv_sec*1000 +et.tv_usec/1000;
  return tms;
}

int NDL_PollEvent(char *buf, int len) {
  int fd;
  int rl=0;
  //evtdev = open("/dev/events",0,0);
  rl = read(evtdev,buf,len);
  //close(evtdev);
  return rl;
}

void NDL_OpenCanvas(int *w, int *h) {

  char buf[32];
  //dpdev = open("/proc/dispinfo",0,0);
  read(dpdev,buf,32);
  
  int i;
  int flag = 0;
  int a[2];//a[1] is height; a[0] ia the width
  int m = 0;
  int k;
  int sum = 0;
  char *buf_ = buf;
  for(i=0;i<=strlen(buf_);i++){
    if(buf[i]>='0' && buf[i]<='9'){
      flag = 1;
      k = buf[i] - '0';
      sum *= 10;
      sum += k;
    }else{
      if(flag==1){
        a[m] = sum;
        m++;
      }
      sum = 0;
      flag = 0;
    }
  }
  if(*w > a[0] || *w ==0)
    *w = a[0];
  if(*h > a[1] || *h ==0)
    *h = a[1];
  screen_w = a[0];
  screen_h = a[1];

  if (getenv("NWM_APP")) {
    int fbctl = 4;
    fbdev = 5;
    screen_w = *w; screen_h = *h;
    char buf[64];
    int len = sprintf(buf, "%d %d", screen_w, screen_h);
    // let NWM resize the window and create the frame buffer
    write(fbctl, buf, len);
    while (1) {
      // 3 = evtdev
      int nread = read(3, buf, sizeof(buf) - 1);
      if (nread <= 0) continue;
      buf[nread] = '\0';
      if (strcmp(buf, "mmap ok") == 0) break;
    }
    close(fbctl);
  }
}
/*
void NDL_DrawRect(uint32_t *pixels, int x, int y, int w, int h)
{

  //居中
  //x += (screen_w - canvas_w) / 2;
  //y += (screen_h - canvas_h) / 2;

  int fb = open("/dev/fb", 0, 0);

  //printf("NDL x:%d, y:%d, w:%d, h:%d\n",x,y,w,h); 

  for(int i = 0; i < h; i++){
    lseek(fb, (x + (y + i) * screen_w) * 4, SEEK_SET);
    write(fb, pixels, w * 4);
    pixels += w;
  }
   
}
*/
void NDL_DrawRect(uint32_t *pixels, int x, int y, int w, int h) {
  int fd;
  int i;
  size_t offset;
  //printf("222222\n");
  //fbdev = open("/dev/fb",0,0);
  for(i=0;i<h;i++){
    offset = lseek(fbdev,((y+i)*screen_w+x)*4,SEEK_SET);
    write(fbdev,pixels+i*w,w*4);
  }
  //close(fbdev);
}

void NDL_OpenAudio(int freq, int channels, int samples) {
}

void NDL_CloseAudio() {
}

int NDL_PlayAudio(void *buf, int len) {
  return 0;
}

int NDL_QueryAudio() {
  return 0;
}

int NDL_Init(uint32_t flags) {
  //gettimeofday(&st,NULL);
  if (getenv("NWM_APP")) {
    evtdev = 3;
  }
  evtdev=open("/dev/events",0);
  dpdev=open("/proc/dispinfo",0);
  fbdev=open("/dev/fb",0);
  return 0;
}

void NDL_Quit() {
  close(evtdev);
  close(fbdev);
  close(dpdev);
}




