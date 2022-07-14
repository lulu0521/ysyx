#include <stdio.h>
#include <assert.h>
#include <NDL.h>
//#include<sys/time.h>
//int gettime_ofday(struct timeval *tv, struct timezone *tz);
//int main(){
//    struct timeval tv;
//    int i = 0;
//    while(1){
//        gettimeofday(&tv,NULL);
//        if(tv.tv_usec%500000==0){
//            i++;
//            printf("this is %d times\n",i);
//        }
//    }
//    return 0; 
//}

int main(){
   uint32_t time_old;
   uint32_t time_new;
   int i = 0;
   uint32_t flags = 0;
   NDL_Init(flags);
   time_old = NDL_GetTicks();
   while(1){
    time_new = NDL_GetTicks();
    if((time_new - time_old)==500){
        time_old = time_new;
        i++;
        printf("this is %d times\n",i);
    }
   }
   return 0;
}
