#ifndef RENDER_H
#define RENDER_H

#include <SDL2/SDL.h>
#include "config.h"

void draw_grid(SDL_Renderer *renderer, int grid[ROWS][COLUMNS]);
void draw_cell(SDL_Renderer *renderer, int grid[ROWS][COLUMNS]);

#endif
