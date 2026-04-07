#ifndef SDL_HELPER_H
#define SDL_HELPER_H

#include <SDL2/SDL.h>

void init_sdl(void);
void cleanup(void);
SDL_Renderer* get_renderer(void);

#endif
