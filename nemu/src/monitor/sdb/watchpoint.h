#include "sdb.h"
#include <common.h>

typedef struct watchpoint {
  int NO;
  struct watchpoint *next;
  char *expr_content;
  word_t New_Val;
  word_t Old_Val;
  /* TODO: Add more members if necessary */
} WP;

void init_wp_pool();
WP* new_wp();
void free_wp(WP *wp);
void recode_expr(char *e);
WP* scan_WP();