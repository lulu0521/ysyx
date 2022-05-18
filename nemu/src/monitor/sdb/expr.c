#include <isa.h>
#include <stdlib.h>
/* We use the POSIX regex functions to process regular expressions.
 * Type 'man regex' for more information about POSIX regex functions.
 */
#include <regex.h>
#include "utils.h"

enum {
  TK_NOTYPE = 256, TK_EQ,NUM
  /* TODO: Add more token types */
};

static struct rule {
  const char *regex;
  int token_type;
} rules[] = {
  /* TODO: Add more rules.
   * Pay attention to the precedence level of different rules.
   */
  {" +", TK_NOTYPE},       // spaces
  {"==", TK_EQ},           // equal
  {"([1-9][0-9]{0,9}|0)",NUM},   //num
  {"\\(",'('},
  {"\\)",')'},            //brackets
  {"\\+", '+' },          // plus
  {"\\-",'-' },             //sub
  {"\\*",'*' },          //mul
  {"\\/",'/' }             //div
};

#define NR_REGEX ((sizeof(rules) / sizeof(rules[0])))

static regex_t re[NR_REGEX] = {};

void init_regex() {
  int i;
  char error_msg[128];
  int ret;

  for (i = 0; i < NR_REGEX; i ++) {
    ret = regcomp(&re[i], rules[i].regex, REG_EXTENDED);
    if (ret != 0) {
      regerror(ret, &re[i], error_msg, 128);
      panic("regex compilation failed: %s\n%s", error_msg, rules[i].regex);
    }
  }
}



typedef struct token {
  int type;
  char str[256];
} Token;

#define NUM_TOKENS 65536

static Token tokens[NUM_TOKENS] __attribute__((used)) = {};
static int nr_token __attribute__((used))  = 0;


static bool make_token(char *e) {
  int position = 0;
  int i;
  regmatch_t pmatch;

  nr_token = 0;

  while (e[position] != '\0') {
    /* Try all rules one by one. */
    for (i = 0; i < NR_REGEX; i ++) 
    {
      if (regexec(&re[i], e + position, 1, &pmatch, 0) == 0 && pmatch.rm_so == 0) {
        char *substr_start = e + position;
        int substr_len = pmatch.rm_eo;

       // Log("match rules[%d] = \"%s\" at position %d with len %d: %.*s",
        //    i, rules[i].regex, position, substr_len, substr_len, substr_start);

        position += substr_len;

        /* TODO: Now a new token is recognized with rules[i]. Add codes
         * to record the token in the array `tokens'. For certain types
         * of tokens, some extra actions should be performed.
         */
        assert(substr_len <= 256);
        assert(nr_token < NUM_TOKENS);

        switch (rules[i].token_type) {
          case TK_NOTYPE : break;
          case NUM : sprintf(tokens[nr_token].str,"%.*s",substr_len, substr_start);
          
          default  : {tokens[nr_token].type = rules[i].token_type;
                      nr_token ++;
                      break;
          }
          //default: TODO();
        }
       break;
      }
    }

    if (i == NR_REGEX) {
      printf("no match at position %d\n%s\n%*.s^\n", position, e, position, "");
      return false;
    }
  }
  return true;
}

int bra_token[5000];
/*======find matched brackets==========*/

int match_bra(int start,int end){
  
  int bra_mark = 0;
  int stack_bra[NUM_TOKENS];
  int stack_top = 0;
  int bra_num = 0;
  int i;

  for(i=start;i<=end;i++){
    switch(tokens[i].type){
      case '(':{
        bra_num++;
        bra_mark++;
        bra_token[i] = bra_mark;
        stack_bra[stack_top++] = bra_mark;
        break;
      }
      case ')':{
        bra_num--;
        if(bra_num < 0){
          return -1;
        }
        bra_token[i] = stack_bra[--stack_top];
        break;
      }
      default:bra_token[i] = 0;
      break;
    }
  }
  return 0;
}


int priority(int token_type){
  switch(token_type){
    case '+':
    case '-': return 0;
    case '*':
    case '/': return 1;
    default:assert(0);
  }
}

/*find dominated operation and matched brackets*/
int domi_op(int p,int q,bool *success){
  int bra_num = 0;
  int i;
  int domi_s = -1;

  for(i=p;i<q;i++){
    switch(tokens[i].type){
      case NUM: break;
      case '(':
        bra_num++;
        break;
      case ')':
        bra_num--;
        break;
      default:{
        if(bra_num==0){
          if(domi_s==-1 ||
          priority(tokens[domi_s].type)-priority(tokens[i].type)>0||
          priority(tokens[domi_s].type)-priority(tokens[i].type)==0){
          domi_s = i;
          }
        }
      }
    }

  }
  if (domi_s == -1){
    *success = false;
  }
  else{
    *success = true;
  }
  return domi_s;
} 

int eval(int p, int q, bool *success){
  if(p > q){
    *success = false;
    return 0;
  }

  else if(p == q){
    uint32_t num;
    num = atoi(tokens[p].str);
    *success = true;
    return num;
  }
  
  else if(bra_token[p]==bra_token[q] &&
          bra_token[p]!= 0           &&
          bra_token[q]!=0){
    return eval(p+1,q-1,success);
  }

  else{
    int domi_s = domi_op(p,q,success);

    uint32_t val1 = eval(p, domi_s - 1, success);
    if (!*success) { return 0; }

    uint32_t val2 = eval(domi_s + 1, q, success);
    if (!*success) { return 0; }

    switch(tokens[domi_s].type){
      case '+':return val1 + val2; 
      case '-':return val1 - val2; 
      case '*':return val1 * val2; 
      case '/':return val1 / val2; 
      default://printf("%d\n",domi_s);
      assert(0);
    }
  }

}

word_t expr(char *e, bool *success) {
  if (!make_token(e)) {
    *success = false;
    return 0;
  }
  if(match_bra(0,nr_token-1)<0){
    *success = false;
    return 0;
  }
  /* TODO: Insert codes to evaluate the expression. */

  return eval(0,nr_token-1,success);
}
