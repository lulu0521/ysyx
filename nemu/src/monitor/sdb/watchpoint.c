#include "sdb.h"
#include <string.h>

#define NR_WP 32

typedef struct watchpoint {
  int NO;
  struct watchpoint *next;
  char expr_content[65536];
  word_t New_Val;
  word_t Old_Val;
  /* TODO: Add more members if necessary */
} WP;

bool success = true;
static WP wp_pool[NR_WP] = {};
static WP *head = NULL, *free_ = NULL;

void init_wp_pool(){
  int i;
  for (i = 0; i < NR_WP; i ++) {
    wp_pool[i].NO = i;
    wp_pool[i].next = (i == NR_WP - 1 ? NULL : &wp_pool[i + 1]);
  }

  head = &wp_pool[0];
  head->next = NULL;
  free_ = &wp_pool[1];
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
  strcpy(wp->expr_content ,p->expr_content);
  wp->next = p->next;
  //add in free_
  p->next = free_->next;
  free_->next = p;
}

/* TODO: Implement the functionality of watchpoint */

void recode_expr(char *e){
  WP *p = new_wp();
  strcpy(p->expr_content,e);
  p->Old_Val = expr(e,&success);
}

WP* scan_WP(){
  WP *p = head->next;
  while(p){
    p->New_Val = expr(p->expr_content,&success);
    if(p->New_Val != p->Old_Val){
      p->Old_Val =  p->New_Val;
      return p;
    }
    p = p->next;
  }
  return NULL;
}

int info_wp(){
  WP *p = head->next;
  while(p){
    printf("NUM:%d     What:%s\n",p->NO,p->expr_content);
    p = p->next;
  }
  return 0;
}

int delete_wp(int NO){
  if(NO>=0 && NO<NR_WP){
    WP *p = head->next;
    while(p){
      if(p->NO==NO){
        free_wp(p);
        return 0;
      }
        p= p->next;
    }
    printf("The WP %d you entered is invalid\n" ,NO);
    return 0;
  }
  else{
    printf("The WP %d you entered doesn't exist\n",NO);
    assert(0);
  }
}

