#include <am.h>
#include <klib.h>
#include <klib-macros.h>
#include <stdarg.h>

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)
char str[11];
char tab[16] = {'0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f'};

char *out_num(long num,int base,char leader_m,int minwidth){
  int i=0;
  int len=0;
  long num_;
  //num_ is positive num
  if(num<0){
    num_ = -num;
  }else{
    num_ = num;
  }
  //num_ = 0
  if(num_==0){
    if(minwidth==0){
      str[0] = '0';
      str[1] = '\0';
    } else{
      str[minwidth]   = '\0';
      str[minwidth-1] = '0' ;
      int width = minwidth - 2;
      for(;width>=0;width--){
        str[width] = leader_m;
      }
    }
  }
  //num_ != 0
  else{
    for(i=1;num_/i!=0;i*=base)
    len++;
    if(len<minwidth){
      str[minwidth]   = '\0';
      for(;num_!=0;num_/= base){
        minwidth -= 1;
        str[minwidth] = tab[num_ % base];
      }
      for(minwidth-=1;minwidth!=0;minwidth--){
        str[minwidth] = leader_m;
      }
      if(num>0) str[minwidth] = leader_m;
      else str[minwidth] = '-';
    }else{
      if(num>0){
        str[len] = '\0';
        for(len-=1;len>=0;len--){
          str[len] = tab[num_%base];
          num_ /= base;
        }
      }else{
        str[len+1] = '\0';
        for(;len!=0;len--){
          str[len] = tab[num_%base];
          num_ /= base;
        }
        str[len] = '-';
      }
    }
  }
  return str;
}


int printf(const char *fmt, ...) {
  va_list ap;
  va_start(ap,fmt);
  while(*fmt!='\0'){
    switch(*fmt){
      case '%':{  
        fmt++;
        int minwidth = 0;
        char leader_m = ' ';
        //leader mark
        if(*fmt == '0'){
          leader_m = '0';
          fmt++;
        }
        //the length of data
        while(*fmt>'0' && *fmt<'9'){
          minwidth *= 10;
          minwidth += *fmt -'0';
          fmt++;
        }
        switch(*fmt){
          case'c':{
            putch (va_arg(ap,int));
            fmt++;
            break;
          }
          case's':{
            char* str= va_arg(ap,char*);
            while(*str!='\0' && str!=NULL){
              putch (*str);
              str++; 
            }
            fmt++;
            break;
          }
          case'd':{
            char* str_num = out_num(va_arg(ap,int),10,leader_m, minwidth);
            putch ('=');
            while(*str_num!='\0'){
              putch (*str_num);
              str_num++; 
            }
            fmt++;
            break;
          }
          case'o':{
            char* str_num = out_num(va_arg(ap,unsigned int),8,leader_m, minwidth);
            while(*str_num!='\0'){
              putch (*str_num);
              str_num++; 
            }
            fmt++;
            break;
          }
          case'u':{
            char* str_num = out_num(va_arg(ap,unsigned int),10,leader_m, minwidth);
            while(*str_num!='\0'){
              putch (*str_num);
              str_num++; 
            }
            fmt++;
            break;
          }
          case'x':{
            char* str_num = out_num(va_arg(ap,unsigned int),16,leader_m, minwidth);
            while(*str_num!='\0'){
              putch (*str_num);
              str_num++; 
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
        break;
      } 
      default:{
      putch(*fmt);
      fmt++;
      break;
      }
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
    switch(*fmt){
      case '%':{  
        fmt++;
        int minwidth = 0;
        char leader_m = ' ';
        //leader mark
        if(*fmt == '0'){
          leader_m = '0';
          fmt++;
        }
        //the length of data
        while(*fmt>'0' && *fmt<'9'){
          minwidth *= 10;
          minwidth += *fmt -'0';
          fmt++;
        }
        switch(*fmt){
          case'c':{
            *out = va_arg(ap,int);
            fmt++;
            out++;
            break;
          }
          case's':{
            char* str= va_arg(ap,char*);
            while(*str!='\0'&&str!=NULL){
              *out = *str;
              out++;
              str++; 
            }
            fmt++;
            break;
          }
          case'd':{
            char* str_num = out_num(va_arg(ap,int),10,leader_m, minwidth);
            while(*str_num!='\0'){
              *out = *str_num;
              out++;
              str_num++; 
            }
            fmt++;
            break;
          }
          case'o':{
            char* str_num = out_num(va_arg(ap,unsigned int),8,leader_m, minwidth);
            while(*str_num!='\0'){
              *out = *str_num;
              out++;
              str_num++; 
            }
            fmt++;
            break;
          }
          case'u':{
            char* str_num = out_num(va_arg(ap,unsigned int),10,leader_m, minwidth);
            while(*str_num!='\0'){
              *out = *str_num;
              out++;
              str_num++; 
            }
            fmt++;
            break;
          }
          case'x':{
            char* str_num = out_num(va_arg(ap,unsigned int),16,leader_m, minwidth);
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
        break;
      } 
      default:{
      *out = *fmt;
      out++;
      fmt++;
      break;
      }
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
