#include <isa.h>
#include <stdlib.h>
#include <cpu/cpu.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "sdb.h"
#include "utils.h"
#include "memory/paddr.h"
#include "watchpoint.h"


static int is_batch_mode = false;

void init_regex();
void init_wp_pool();
int delete_wp(int NO);
void info_wp();

/* We use the `readline' library to provide more flexibility to read from stdin. */
static char* rl_gets() {
  static char *line_read = NULL;

  if (line_read) {
    free(line_read);
    line_read = NULL;
  }

  line_read = readline("(nemu) ");

  if (line_read && *line_read) {
    add_history(line_read);
  }

  return line_read;
}

static int cmd_c(char *args) {
  cpu_exec(-1);
  return 0;
}


static int cmd_q(char *args) {
  nemu_state.state = NEMU_QUIT;
  return  -1;
}

static int cmd_help(char *args);

static int cmd_si(char *args){
  char *arg1 = strtok(NULL," ");
  int i;
  if(arg1==NULL){
    cpu_exec(1);
  }
  else{
    i = atoi(arg1);
    cpu_exec(i);
  }
  return 0;
}

static int cmd_info(char *args){
  char *arg1 = strtok(NULL," ");
  
  if(*arg1=='r'){
    isa_reg_display();
    printf("\n");
  }
  else if(*arg1=='w'){
    info_wp();
  }
  else{
    printf("The infomation you entered is invalid\n");
  }
  return 0;
}

static int cmd_x(char *args){
  int i;
  int addr;

  char *arg1 = strtok(NULL," ");
  i = atoi(arg1);

  char *arg2 = strtok(NULL," ");
  addr = strtol(arg2, NULL, 16);

  for(int j=0;j<i;j++){
    word_t val;
    val = paddr_read(addr + 4*j, 4);
    printf("0x""%x ",val);
  }
  printf("\n");
  return 0;
}

static int cmd_d(char *arg){
  char *arg1 = strtok(NULL," ");
  int NO = atoi(arg1);
  delete_wp(NO);
  return 0;
}

static int cmd_w(char *arg){
  recode_expr(arg);
  return 0;
}


static struct {
  const char *name;
  const char *description;
  int (*handler) (char *);
} cmd_table [] = {
  { "help", "Display informations about all supported commands", cmd_help },
  { "c", "Continue the execution of the program", cmd_c },
  { "q", "Exit NEMU", cmd_q },
  { "si", "Continue to execute the program n step", cmd_si},
  { "info", "print register or watchpoint information", cmd_info},
  { "x", "Scan memory", cmd_x},
  { "d", "Delete WP",cmd_d},
  { "w", "Set WP",cmd_w},

  /* TODO: Add more commands */

};

#define NR_CMD ARRLEN(cmd_table)

static int cmd_help(char *args) {
  /* extract the first argument */
  char *arg = strtok(NULL, " ");
  int i;

  if (arg == NULL) {
    /* no argument given */
    for (i = 0; i < NR_CMD; i ++) {
      printf("%s - %s\n", cmd_table[i].name, cmd_table[i].description);
    }
  }
  else {
    for (i = 0; i < NR_CMD; i ++) {
      if (strcmp(arg, cmd_table[i].name) == 0) {
        printf("%s - %s\n", cmd_table[i].name, cmd_table[i].description);
        return 0;
      }
    }
    printf("Unknown command '%s'\n", arg);
  }
  return 0;
}

void sdb_set_batch_mode() {
  is_batch_mode = true;
}

void sdb_mainloop() {
  if (is_batch_mode) {
    cmd_c(NULL);
    return;
  }

  for (char *str; (str = rl_gets()) != NULL; ) {
    char *str_end = str + strlen(str);

    /* extract the first token as the command */
    char *cmd = strtok(str, " ");
    if (cmd == NULL) { continue; }

    /* treat the remaining string as the arguments,
     * which may need further parsing
     */
    char *args = cmd + strlen(cmd) + 1;
    if (args >= str_end) {
      args = NULL;
    }

#ifdef CONFIG_DEVICE
    extern void sdl_clear_event_queue();
    sdl_clear_event_queue();
#endif

    int i;
    for (i = 0; i < NR_CMD; i ++) {
      if (strcmp(cmd, cmd_table[i].name) == 0) {
        if (cmd_table[i].handler(args) < 0) { return; }
        break;
      }
    }

    if (i == NR_CMD) { printf("Unknown command '%s'\n", cmd); }
  }
}

void init_sdb() {
  /* Compile the regular expressions. */
  init_regex();

  /* Initialize the watchpoint pool. */
  init_wp_pool();
}
