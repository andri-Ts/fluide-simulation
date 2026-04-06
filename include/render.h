#ifndef RENDER_H
#define RENDER_H

#include <SDL2/SDL.h>
#include "config.h"

void render_frame(SDL_Renderer *renderer);
void init_grid(void);
void draw_grid(SDL_Renderer *renderer);
void draw_cell(SDL_Renderer *renderer);

#endif
