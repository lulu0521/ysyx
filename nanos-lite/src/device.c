#include <stdio.h>
#include <common.h>

#if defined(MULTIPROGRAM) && !defined(TIME_SHARING)
# define MULTIPROGRAM_YIELD() yield()
#else
# define MULTIPROGRAM_YIELD()
#endif

#define NAME(key) \
  [AM_KEY_##key] = #key,

static const char *keyname[256] __attribute__((used)) = {
  [AM_KEY_NONE] = "NONE",
  AM_KEYS(NAME)
};

size_t serial_write(const void *buf, size_t offset, size_t len){
   int i=0;
  char* buf_ = (char*)buf;
  for(i=0;i<len && buf_!=NULL;i++){
    if( *buf_ != '\0'){
      putch(*buf_);
      buf_++;
    } 
  }
  return i;
}

size_t events_read(void *buf, size_t offset, size_t len) {
  char* buf_ = (char*)buf;
  AM_INPUT_CONFIG_T has_kbd;
  AM_INPUT_KEYBRD_T kdb;
  int vaild = 0;
  has_kbd  = io_read(AM_INPUT_CONFIG);
  if(has_kbd.present){
    if(vaild<=len){
      kdb = io_read(AM_INPUT_KEYBRD);
      if(kdb.keycode!=AM_KEY_NONE){
        if(kdb.keydown==1){
          sprintf(buf_,"kd %s\n",keyname[kdb.keycode]);
          vaild += strlen(buf_);
        }else{
          sprintf(buf_,"ku %s\n",keyname[kdb.keycode]);
          vaild += strlen(buf_);
        }
      }
    }
  }
  return vaild;
}

size_t dispinfo_read(void *buf, size_t offset, size_t len) {
  return 0;
}

size_t fb_write(const void *buf, size_t offset, size_t len) {
  return 0;
}

void init_device() {
  Log("Initializing devices...");
  ioe_init();
}
