#include <NDL.h>
#include <assert.h>
uint32_t s_time;
int SDL_Init(uint32_t flags) {
  s_time = NDL_GetTicks();
  return NDL_Init(flags);
}

void SDL_Quit() {
  NDL_Quit();
}

char *SDL_GetError() {
  return "Navy does not support SDL_GetError()";
}

int SDL_SetError(const char* fmt, ...) {
  //assert(0);
  return -1;
}

int SDL_ShowCursor(int toggle) {
  assert(0);
  return 0;
}

void SDL_WM_SetCaption(const char *title, const char *icon) {
  
}
