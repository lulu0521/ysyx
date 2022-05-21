#include "sdb.h"

#define NR_WP 32

typedef struct watchpoint {
  int NO;
  struct watchpoint *next;
  char *expr_content;
  word_t New_Val;
  word_t Old_Val;
  /* TODO: Add more members if necessary */
} WP;

static WP wp_pool[NR_WP] = {};
static WP *head = NULL, *free_ = NULL;
bool *success;

void init_wp_pool(){
  int i;
  for (i = 0; i < NR_WP; i ++) {
    wp_pool[i].NO = i;
    wp_pool[i].next = (i == NR_WP - 1 ? NULL : &wp_pool[i + 1]);
  }

  head = NULL;
  free_ = wp_pool;
}

WP* new_wp(){
  if(free_){
    //take one WP from free_ list
    WP* p = free_;
    free_ = free_->next;
    //add in head list
    p->next = head->next;
    head->next = p;
    return p;
  }
  else {
    assert(free_ != NULL);
    return 0;
  }
}

void free_wp(WP *wp){
  //delete from head list
  WP *p = wp->next;
  wp->expr_content = p->expr_content;
  wp->next = p->next;
  //add in free_
  p->next = free_->next;
  free_->next = p;
}

/* TODO: Implement the functionality of watchpoint */

void recode_expr(char *e){
  WP *p = new_wp();
  p->expr_content = e;
  p->Old_Val = expr(e,success);
}

WP* scan_WP(){
  WP *p = head->next;
  while(p){
    p->New_Val = expr(p->expr_content,success);
    if(p->New_Val != p->Old_Val){
      return p;
    }
    else {
      return NULL;
    }
    p = p->next;
  }
  return 0;
}

void info_wp(){
  WP *p = head->next;
  while(p){
    printf("NMU:%d Type:hw watchpoint Disp:keep Enb:y What:%s\n",p->NO,p->expr_content);
    p = p->next;
  }
}

int delete_wp(int NO){
  if(NO>=0 && NO<NR_WP){
    WP *p = head->next;
    while(p){
      if(p->NO==NO){
        free_wp(p);
        return 0;
      }
      else {
        p= p->next;
      }
    }
    printf("The WP %d you entered is invalid" ,NO);
    return 0;
  }
  else{
    printf("The WP %d you entered doesn't exist\n",NO);
    assert(0);
  }
}