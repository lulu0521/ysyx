#include <klib.h>
#include <klib-macros.h>
#include <stdint.h>

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)

size_t strlen(const char *s) {
  size_t i = 0;
  while(s[i]!='\0'&&s!=NULL){
    i++;
  }
  return i;
}

char *strcpy(char *dst, const char *src) {
  int i = 0;
  assert(!(dst>=src && dst<=src+strlen(src)));
  while(src[i]!='\0'&&src!=NULL){
    dst[i] = src[i];
    i++;
  }
  dst[i] = src[i];
  return dst;
}

char *strncpy(char *dst, const char *src, size_t n) {
  int i = 0;
  assert(!(dst>=src && dst<=src+strlen(src)));
  while(i!=n && src[i]!='\0'){
    dst[i] = src[i];
    i++;
  }
  if(src[i]=='\0'){
    dst[i] = src[i];
  }else{
    dst[i] = '\0';
  }
  return dst;
}

char *strcat(char *dst, const char *src) {
  char *dst_ = dst;
  size_t len = strlen(dst);
  int i = 0;
  while(src[i]!='\0'&&src!=NULL){
    dst[len+i] = src[i];
    i++;
  }
  dst[len+i] = src[i];
  return dst_;
}

int strcmp(const char *s1, const char *s2) {
  int i = 0;
  char *s1_ = (char *)s1;
  char *s2_ = (char *)s2;
  while(s1_[i]!='\0'&&s2_[i]!='\0'&&s1_[i]==s2_[i]){
      i++;
  }
  if(s1_[i]==s2_[i]){
      return 0;
    }
  else if(s1_[i]<s2_[i]){
      return -1;
    }
  else if(s1_[i]>s2_[i]){
      return 1;
    }
    return 0;
}

int strncmp(const char *s1, const char *s2, size_t n) {
  int i=0;
   while(s1[i]!='\0'&&s2[i]!='\0'&&s1[i]==s2[i]&&i<n){
      i++;
  }
    if(s1[i]==s2[i] || i==n){
      return 0;
    }
    else if(s1[i]<s2[i]){
      return -1;
    }
    else if(s1[i]>s2[i]){
      return 1;
    }
  return 0;
}

void *memset(void *s, int c, size_t n) {
  assert(s!=NULL);
  char *s_ = (char*)s;
  for(int i=0;i<n;i++){
    s_[i] = (unsigned char)c;
  }
  return s;
}

void *memmove(void *dst, const void *src, size_t n) {
  assert(dst!=NULL);
  assert(src!=NULL);
  char src_cpy[strlen(src)+1];
  char *str_cpy_ = src_cpy;
  strcpy(str_cpy_,src);
  char* dst_ = (char*)dst;
  while(n!=0 ){
    *dst_ = *str_cpy_;
    dst_++;
    str_cpy_++;
    n--;
  }
  return dst;
}

void *memcpy(void *out, const void *in, size_t n) {
  assert(out!=NULL);
  assert(in!=NULL);
  char *out_ = (char *)out;
  char *in_ = (char *)in;
  while(n!=0){
    *out_ = *in_;
    out_++;
    in_++;
    n--;
  }
  return out;
}

int memcmp(const void *s1, const void *s2, size_t n) {
  assert(s1!=NULL);
  assert(s2!=NULL);
  char* s1_ = (char*)s1;
  char* s2_ = (char*)s2;
  while(n!=0){
    if(*s1_==*s2_){
      s1_++;
      s2_++;
      n--;
    }
    else if(*s1_<*s2_){
      return -1;
    }
    else{
      return 1;
    }
  }
  return 0;
}

#endif
