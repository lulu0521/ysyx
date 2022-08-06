#include <NDL.h>
#include <SDL.h>
#include <assert.h>
#include <string.h>
#define keyname(k) #k,

static const char *keyname[] = {
  "NONE",
  _KEYS(keyname)
};
//const size_t k_n = sizeof(keyname)/sizeof(keyname[0]);
uint8_t key_state[sizeof(keyname)/sizeof(keyname[0])] = {0};

int SDL_PushEvent(SDL_Event *ev) {
  assert(0);
  return 0;
}

int SDL_PollEvent(SDL_Event *ev) {
  int i;
  char buf[64];
  int len = 64;
  char *type_ = buf +1 ;// ku or kd
  char *k_name = buf+3;//key name
  memset(buf,0,64);
  int k_n = sizeof(keyname)/sizeof(keyname[0]);
  int bv_len = NDL_PollEvent(buf, len);
  buf[bv_len-1] = '\0';
  if(*buf==0){
    return 0;
  }
  if(*type_=='d'){
    ev->type = SDL_KEYDOWN;
    //key_state[i] = 1;
  }
  else if(*type_=='u') {
    ev->type = SDL_KEYUP;
    //key_state[i] = 0;
  }
  else{
    ev->type = SDL_USEREVENT;
  }
  for(i=0;i<k_n;i++){
    if(strcmp(k_name,keyname[i])==0){
      ev->key.keysym.sym = i;
      key_state[i] = (ev->type == SDL_KEYDOWN);
     //key_state[i] = (ev->type != SDL_KEYDOWN);
    }    
  }
  return 1;
}

int SDL_WaitEvent(SDL_Event *event) {
  assert(event);
  while(!SDL_PollEvent(event));
  return 1;
}

int SDL_PeepEvents(SDL_Event *ev, int numevents, int action, uint32_t mask) {
  assert(0);
  return 0;
}

uint8_t* SDL_GetKeyState(int *numkeys) {
  
  return key_state;
}
