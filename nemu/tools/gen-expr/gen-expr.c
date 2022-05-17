#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <string.h>


// this should be enough
static char buf[65536] = {};
static char code_buf[65536 + 128] = {}; // a little larger than `buf`

static char *code_format =
"#include <stdio.h>\n"
"int main() { "
"  unsigned result = %s; "
"  printf(\"%%u\", result); "
"  return 0; "
"}";

static char *buf_wend;
#define buf_w(fmt,...) buf_wend += sprintf(buf_wend,fmt,##__VA_ARGS__)

static uint32_t choose(uint32_t max_num){
  return rand() % max_num;
}

void gen_num(){
  buf_w("%uu", rand()%(uint32_t)4294967295);
}

int gen_rand_op(){
  char op[4] = {'+','-','*','/'};
  buf_w("%c" , op[choose(4)]);
}

int gen_space(){
  char *space[3] = {""," ", "   "};
  buf_w("%s" , space[choose(3)]);
}

static int op_cnt;
static void gen_rand_expr() {
  switch (choose(3)) {
    case 0: 
    if(op_cnt==0){
      gen_rand_expr();
      break;
    }
    else{
      gen_num(); 
      break;
    }
    case 1: 
    buf_w("%s","("); 
    gen_rand_expr(); 
    buf_w("%s",")"); 
    break;
    default: 
    if(buf_wend - buf >= sizeof(buf)/2){
      gen_num();
      break;
    }
    else{
      op_cnt ++;
      gen_space();
      gen_rand_expr(); 
      gen_space();
      gen_rand_op(); 
      gen_space();
      gen_rand_expr();
      gen_space();
      break;
    }
  }
}

void remove_u(char *buf){
  while((buf=strchr(buf,'u'))!=NULL){
   
  strcpy(code_buf,buf+1);
  strcpy(buf,code_buf);
  }
}

int main(int argc, char *argv[]) {
  int seed = (uint32_t)time(NULL);
  srand(seed);

  int loop = 1;
  if (argc > 1) {
    sscanf(argv[1], "%d", &loop);
  }

  int i;
  for (i = 0; i < loop; i ++) {
    op_cnt = 0;
    buf_wend = buf;
    gen_rand_expr();

    sprintf(code_buf, code_format, buf);

    FILE *fp = fopen("/tmp/.code.c", "w");
    assert(fp != NULL);
    fputs(code_buf, fp);
    fclose(fp);


    int ret = system("gcc /tmp/.code.c -Werror -o /tmp/.expr");
    if (ret != 0) continue;

    fp = popen("/tmp/.expr", "r");
    assert(fp != NULL);

    uint32_t result;
    fscanf(fp, "%u", &result);
    pclose(fp);

    remove_u(buf);
    printf("%u %s\n\n", result, buf);
  }
  return 0;
}
