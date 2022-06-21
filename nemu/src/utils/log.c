#include <common.h>
#include <stdio.h>

extern uint64_t g_nr_guest_inst;
FILE *log_fp = NULL;
FILE *ftrace_fp = NULL;

void init_log(const char *log_file) {
  log_fp = stdout;
  if (log_file != NULL) {
    FILE *fp = fopen(log_file, "w");
    Assert(fp, "Can not log open '%s'", log_file);
    log_fp = fp;
  }
  Log("Log is written to %s", log_file ? log_file : "stdout");
}

void init_ftrace_fp(const char *ftrace_file) {
  if (ftrace_file) {
    FILE *fp = fopen(ftrace_file, "w");
    Assert(fp, "Can not ftrace log open '%s'", ftrace_file);
    ftrace_fp = fp;
  } else {
    ftrace_fp = stdout;
  }
}

bool log_enable() {
  return MUXDEF(CONFIG_TRACE, (g_nr_guest_inst >= CONFIG_TRACE_START) &&
         (g_nr_guest_inst <= CONFIG_TRACE_END), false);
}
