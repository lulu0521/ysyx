#include <am.h>
#include <klib.h>
#include <klib-macros.h>

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)
static unsigned long int next = 1;

int rand(void) {
  // RAND_MAX assumed to be 32767
  next = next * 1103515245 + 12345;
  return (unsigned int)(next/65536) % 32768;
}

void srand(unsigned int seed) {
  next = seed;
}

int abs(int x) {
  return (x < 0 ? -x : x);
}

int atoi(const char* nptr) {
  int x = 0;
  while (*nptr == ' ') { nptr ++; }
  while (*nptr >= '0' && *nptr <= '9') {
    x = x * 10 + *nptr - '0';
    nptr ++;
  }
  return x;
}

static struct{
  void *ptr;
  size_t size;
}old={.ptr = NULL, .size = 0};

void *malloc(size_t size) {
  // On native, malloc() will be called during initializaion of C runtime.
  // Therefore do not call panic() here, else it will yield a dead recursion:
  //   panic() -> putchar() -> (glibc) -> malloc() -> panic()
  if(old.ptr==NULL){
    old.ptr = heap.start;
  }
  size = ROUNDUP(size,sizeof(uintptr_t));
  old.ptr += old.size;
  assert((uintptr_t)heap.start <= (uintptr_t)old.ptr && (uintptr_t)old.ptr < (uintptr_t)heap.end);
  char *ret = old.ptr;
  old.size = size;
  return ret;

#if !(defined(__ISA_NATIVE__) && defined(__NATIVE_USE_KLIB__))
  panic("Not implemented");
#endif
  
}

void free(void *ptr) {
  if(ptr==old.ptr){
    old.size = 0;
  }
}

#endif
