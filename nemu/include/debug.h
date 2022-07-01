#ifndef __DEBUG_H__
#define __DEBUG_H__

#include <common.h>
#include <stdio.h>
#include <utils.h>

#define Log(format, ...) \
    _Log(ANSI_FMT("[%s:%d %s] " format, ANSI_FG_BLUE) "\n", \
        __FILE__, __LINE__, __func__, ## __VA_ARGS__)

/*
void f(){
Log("%d\n",123)
}

_Log(ANSI_FMT("[%s:%d %s] " "%d\n", ANSI_FG_BLUE) "\n", \
        __FILE__, __LINE__, __func__, ## 123)

#define ANSI_FMT(str, fmt) fmt str ANSI_NONE

_Log(ANSI_FMT("[%s:%d %s] " "%d\n", ANSI_FG_BLUE) "\n", \
        __FILE__, __LINE__, __func__, ## 123)

_Log(ANSI_FG_BLUE "[%s:%d %s] " "%d\n" ANSI_NONE " \n", \
        __FILE__, __LINE__, __func__, ## 123)       

do { \
    printf(ANSI_FMT("[%s:%d %s] " "%d\n", ANSI_FG_BLUE) "\n", \
        __FILE__, __LINE__, __func__, ## 123); \
    log_write(ANSI_FMT("[%s:%d %s] " "%d\n", ANSI_FG_BLUE) "\n", \
        __FILE__, __LINE__, "__func__", ## 123); \
  } while (0)
  
ANSI_FG_BLUE "[%s:%d %s] " "%d\n" ANSI_NONE "\n", \
        __FILE__, __LINE__, __func__, ## 123

ANSI_FG_BLUE "[%s:%d %s] " "%d\n" ANSI_NONE "\n", \
        "debug.h", 29, "f", 123

do { \
    printf(ANSI_FG_BLUE "[%s:%d %s] " "%d\n" ANSI_NONE "\n", \
        "debug.h", 29, "f", 123); \
    log_write(ANSI_FG_BLUE "[%s:%d %s] " "%d\n" ANSI_NONE "\n", \
        "debug.h", 29, "f", 123); \
  } while (0)
*/

#define Assert(cond, format, ...) \
  do { \
    if (!(cond)) { \
      MUXDEF(CONFIG_TARGET_AM, printf(ANSI_FMT(format, ANSI_FG_RED) "\n", ## __VA_ARGS__), \
        (fflush(stdout), fprintf(stderr, ANSI_FMT(format, ANSI_FG_RED) "\n", ##  __VA_ARGS__))); \
      IFNDEF(CONFIG_TARGET_AM, extern FILE* log_fp; fflush(log_fp)); \
      extern void assert_fail_msg(); \
      assert_fail_msg(); \
      assert(cond); \
    } \
  } while (0)

#define panic(format, ...) Assert(0, format, ## __VA_ARGS__)

#define TODO() panic("please implement me")


volatile static int dummy=0;
#endif
