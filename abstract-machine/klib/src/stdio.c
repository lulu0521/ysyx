#include <am.h>
#include <klib.h>
#include <klib-macros.h>
#include <stdarg.h>

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)
char str[11];
char* putnum(int num) {
  int i=0;
  int len=0;
  for(i=1;num/i!=0;i*=10)
    len++;
  str[len] = '\0';
  for(len--;len>=0;len--){
    str[len] = (num % 10 + '0');
    num = num / 10;
  }
  return str;
}

int printf(const char *fmt, ...) {
  va_list ap;
  va_start(ap,fmt);
  while(*fmt!='\0'){
    if(*fmt=='%'){
      fmt++;
      switch(*fmt){
        case'c':{
          char ch = (char)va_arg(ap,int);
          putch(ch);
          fmt++;
          break;
        }
        case's':{
          char* s = NULL;
          s = va_arg(ap,char*);
          fmt++;
          while(*s!='\0'){
            putch(*s);
            s++;
          }
          break;
        }
        case'd':{
          int i = va_arg(ap,int);
          char *num_str = putnum(i);
          while(*num_str!='\0'){
            putch(*num_str);
            num_str++;
            i++;
          }
          fmt++;
          break;
        }
        case'%':{
          putch(*fmt);
          fmt++;
          break;
        }
      }
    } 
    else {
      putch(*fmt);
      fmt++;
    }
  }
  va_end(ap);
  return 0;
}

int vsprintf(char *out, const char *fmt, va_list ap) {
  panic("Not implemented");
}

int sprintf(char *out, const char *fmt, ...) {
  assert(out!=NULL);
  va_list ap;
  va_start(ap,fmt);
  while(*fmt!='\0'){
    if(*fmt=='%'){
      fmt++;
      switch(*fmt){
        case'c':{
          *out = va_arg(ap,int);
          fmt++;
          out++;
          break;
        }
        case's':{
          char* str= va_arg(ap,char*);
          while(*str!='\0'){
            *out = *str;
            out++;
            str++; 
          }
          fmt++;
          break;
        }
        case'd':{
          int num = va_arg(ap,int);
          char* str_num = putnum(num);
          while(*str_num!='\0'){
            *out = *str_num;
            out++;
            str_num++; 
          }
          fmt++;
          break;
        }
        case'%':{
          *out = *fmt;
          out++;
          fmt++;
          break;
        }
      }
    }
    else{
      *out = *fmt;
      out++;
      fmt++;
    }
  }
  *out ='\0';
  va_end(ap);
  return 0;
}

int snprintf(char *out, size_t n, const char *fmt, ...) {
  panic("Not implemented");
}

int vsnprintf(char *out, size_t n, const char *fmt, va_list ap) {
  panic("Not implemented");
}

#endif
