#include <common.h>
#include <utils.h>

void init_monitor(int, char *[]);
void am_init_monitor();
void engine_start();
int is_exit_status_bad();
word_t expr(char *e, bool *success); 

int main(int argc, char *argv[]) {
  /* Initialize the monitor. */
#ifdef CONFIG_TARGET_AM
  am_init_monitor();
#else
  init_monitor(argc, argv);
#endif
 
#if 0

  FILE* fp = fopen("/home/majianlu/ysyx-workbench/nemu/tools/gen-expr/input","r");
  char str_s[65536];
  char str_cpy[65536];
  char *p;
  char *num_str;
  unsigned int  num;
  char expr_test[65536];
  bool *success = malloc(sizeof(bool));
    
    while((p = fgets(str_s,65536,fp))!=NULL){
      *success = true;
      p = strchr(p,'\n');
      strcpy(str_cpy,p+1);
      strcpy(p,str_cpy);

      p = str_s;
      p = strchr(p,' ');
      strcpy(expr_test,p+1);

      p= str_s;
      num_str = strtok(p," ");
      num = atoi(num_str);
      
      unsigned int my = expr(expr_test, success);
      if(my != num){
        printf(ANSI_FG_RED "Failed : %s success=%d, my=%u num=%u \n" ANSI_NONE,
                expr_test, *success, my, num);
      } 
      //else {
      //  printf(ANSI_FG_GREEN "PASS! \n" ANSI_NONE);
      //}
        
    }
  free (success);
#endif
  /* Start engine. */
 
  engine_start();
 
 
  return is_exit_status_bad();
}
