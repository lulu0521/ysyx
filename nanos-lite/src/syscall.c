#include <common.h>
#include "syscall.h"
#include <sys/time.h>
#include <proc.h>
#include <fcntl.h>
#include <unistd.h>
int fs_open(const char *pathname, int flags, int mode);
size_t fs_read(int fd, void *buf, size_t len);
int fs_close(int fd);
size_t fs_write(int fd, const void *buf, size_t len);
size_t fs_lseek(int fd, size_t offset, int whence);
extern uintptr_t *program_break;
void naive_uload(PCB *pcb, const char *filename);

int gettime_ofday(struct timeval *tv, struct timezone *tz){
  AM_TIMER_UPTIME_T time_us;
  time_us.us = io_read(AM_TIMER_UPTIME).us;
  tv->tv_sec = time_us.us/1000000;
  tv->tv_usec = time_us.us%1000000;
  return 0;
}
int execve_(const char *pathname, char *const argv[],char *const envp[]){
  //printf("%s\n",pathname);
  //fs_close("/bin/menu");
  //printf("%s\n",pathname);
  naive_uload(NULL,pathname);
  return -1;
}

void exit(){
  naive_uload(NULL,"/bin/nterm");
  //execve("/bin/menu",NULL,NULL);
}

void do_syscall(Context *c) {
  //printf("&&&&&\n");
  uintptr_t a[4];
  a[0] = c->GPR1;
  a[1] = c->GPR2;
  a[2] = c->GPR3;
  a[3] = c->GPR4;
  switch (a[0]) {
    case SYS_exit: exit();break;
    case SYS_yield: yield();c->GPRx = 0;break;
    case SYS_open:c->GPRx=fs_open((const char*)c->GPR2,c->GPR3,c->GPR4);break;
    case SYS_read:c->GPRx=fs_read(c->GPR2,(void *)c->GPR3,c->GPR4);break;
    case SYS_write:c->GPRx=fs_write(c->GPR2,(const void *)c->GPR3,c->GPR4);break;
    //case SYS_kill:break;
    //case SYS_getpid:break;
    case SYS_close:c->GPRx=fs_close(c->GPR2);break;
    case SYS_lseek:c->GPRx =fs_lseek(c->GPR2,c->GPR3,c->GPR4);break;
    case SYS_brk: c->GPRx = 0;break;
    //case SYS_fstat:break;
    //case SYS_time:break;
    //case SYS_signal:break;
    case SYS_execve: c->GPRx = execve_((const char *)c->GPR2,(char *const*)c->GPR3,(char *const*)c->GPR4);break;
    //case SYS_fork:break;
    //case SYS_link:break;
    //case SYS_unlink:break;
    //case SYS_wait:break;
    //case SYS_times:break;
    case SYS_gettimeofday:c->GPRx = gettime_ofday((struct timeval *)c->GPR2,(struct timezone *)c->GPR3);break;
    default: panic("Unhandled syscall ID = %d", a[0]);
  }
}
