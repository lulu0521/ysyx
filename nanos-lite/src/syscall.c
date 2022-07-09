#include <common.h>
#include "syscall.h"


size_t write(int fd, const void *buf, size_t count){
  int i=0;
  char* buf_= (char*)buf;
  if(fd==1 || fd==2){
    for(i=0;i<count&&buf_!=NULL;i++){
      if(*buf_ !='\0'){
        putch(*buf_);
        buf_ +=1;
      }
    }
  }
  return i;
}

void do_syscall(Context *c) {
  uintptr_t a[4];
  a[0] = c->GPR1;
  switch (a[0]) {
    case SYS_exit: halt(0);break;
    case SYS_yield: yield();c->GPRx = 0;break;
    //case SYS_open:break;
    //case SYS_read:break;
    case SYS_write: c->GPRx=write(c->GPR2,(const void *)c->GPR3,c->GPR4);break;
    //case SYS_kill:break;
    //case SYS_getpid:break;
    //case SYS_close:break;
    //case SYS_lseek:break;
    case SYS_brk:break;
    //case SYS_fstat:break;
    //case SYS_time:break;
    //case SYS_signal:break;
    //case SYS_execve:break;
    //case SYS_fork:break;
    //case SYS_link:break;
    //case SYS_unlink:break;
    //case SYS_wait:break;
    //case SYS_times:break;
    //case SYS_gettimeofday:break;
    default: panic("Unhandled syscall ID = %d", a[0]);
  }
}
