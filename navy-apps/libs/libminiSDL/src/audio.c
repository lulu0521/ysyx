#include <NDL.h>
#include <SDL.h>
#include <assert.h>
int SDL_OpenAudio(SDL_AudioSpec *desired, SDL_AudioSpec *obtained) {
  return 0;
}

void SDL_CloseAudio() {
  assert(0);
}

void SDL_PauseAudio(int pause_on) {
  
}

void SDL_MixAudio(uint8_t *dst, uint8_t *src, uint32_t len, int volume) {
  assert(0);
}

SDL_AudioSpec *SDL_LoadWAV(const char *file, SDL_AudioSpec *spec, uint8_t **audio_buf, uint32_t *audio_len) {
  
  return NULL;

}

void SDL_FreeWAV(uint8_t *audio_buf) {
  assert(0);
}

void SDL_LockAudio() {
  
}

void SDL_UnlockAudio() {
  
}
