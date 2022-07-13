#include <fs.h>

typedef size_t (*ReadFn) (void *buf, size_t offset, size_t len);
typedef size_t (*WriteFn) (const void *buf, size_t offset, size_t len);

typedef struct {
  char *name;
  size_t size;
  size_t disk_offset;
  ReadFn read;
  WriteFn write;
  size_t f_offset;
} Finfo;

enum {FD_STDIN=0, FD_STDOUT, FD_STDERR, FD_FB};

size_t invalid_read(void *buf, size_t offset, size_t len) {
  panic("should not reach here");
  return 0;
}

size_t invalid_write(const void *buf, size_t offset, size_t len) {
  panic("should not reach here");
  return 0;
}

size_t write_std(int fd,const void *buf,size_t len){
  int i=0;
  char* buf_ = (char*)buf;
  if(fd==1 || fd==2){
    for(i=0;i<len && buf_!=NULL;i++){
    if( *buf_ != '\0'){
      putch(*buf_);
      buf_++;
    } 
  }
  }
  return i;
}
/* This is the information about all files in disk. */
static Finfo file_table[] __attribute__((used)) = {
  [FD_STDIN]  = {"stdin", 0, 0, invalid_read, invalid_write},
  [FD_STDOUT] = {"stdout", 0, 0, invalid_read, invalid_write},
  [FD_STDERR] = {"stderr", 0, 0, invalid_read, invalid_write},
#include "files.h"
};

int f_num = sizeof(file_table)/sizeof(file_table[0]);
int fs_open(const char *pathname, int flags, int mode){
  int i;
  int fd = -1;
  for(i=0;i<f_num;i++){
    fd = strcmp(file_table[i].name,pathname);
    if(fd==0){
      file_table[i].f_offset = 0;
      printf("The strace is SYS_open,The open file is %s",file_table[fd].name);
      return i;
    }
  }
  printf("pathname %s is not existing\n",file_table[i].name);
  assert(0);
}

size_t ramdisk_read(void *buf, size_t offset, size_t len);
size_t fs_read(int fd, void *buf, size_t len){
  int len_ = 0;
  if(len==0 || file_table[fd].f_offset>=file_table[fd].size)
    return 0;
  if(file_table[fd].f_offset+len>file_table[fd].size)
    len = file_table[fd].size-file_table[fd].f_offset;
  len_ = ramdisk_read(buf,file_table[fd].disk_offset+file_table[fd].f_offset,len);
  file_table[fd].f_offset += len; 
  return len_;
}

size_t ramdisk_write(const void *buf, size_t offset, size_t len);
size_t fs_write(int fd, const void *buf, size_t len){
  int len_ = len;
    switch(fd){
      case FD_STDOUT:
      case FD_STDERR:len_ = write_std(fd,buf,len_);break;
      default:
      if(len_==0 || file_table[fd].f_offset>=file_table[fd].size)
        assert(0);
      if(file_table[fd].f_offset+len>file_table[fd].size)
        len_ = file_table[fd].size-file_table[fd].f_offset;
      len_ = ramdisk_write(buf,file_table[fd].disk_offset+file_table[fd].f_offset,len_);
      file_table[fd].f_offset += len_; 
      break;
    }
  return len_;
}

int fs_close(int fd){
  return 0;
}

size_t fs_lseek(int fd, size_t offset, int whence){
  switch(whence){
    case SEEK_SET:file_table[fd].f_offset = offset;break;
    case SEEK_CUR:file_table[fd].f_offset += offset;break;
    case SEEK_END:file_table[fd].f_offset = file_table[fd].size+ offset;break;
    default:file_table[fd].f_offset = -1;break;
  }
  if(file_table[fd].f_offset>file_table[fd].size)
    file_table[fd].f_offset = -1;
  return file_table[fd].f_offset;
}

void init_fs() {
  // TODO: initialize the size of /dev/fb
}
