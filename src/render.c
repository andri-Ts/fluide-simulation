#include <stdio.h>
#include <SDL2/SDL.h>
#include "../include/render.h"
#include "../include/config.h"

void draw_grid(SDL_Renderer *renderer)
{
    // on "dessine" tous les cellules
    for(int y = 0; y < ROWS; y++)
    {
        for(int x = 0; x < COLUMNS; x++)
        {
            SDL_Rect cell = {
                x * CELL_SIZE,
                y * CELL_SIZE,
                CELL_SIZE,
                CELL_SIZE
            };
            SDL_SetRenderDrawColor(renderer, 52, 58, 64, SDL_ALPHA_OPAQUE);
            SDL_RenderDrawRect(renderer, &cell); // contour de chque rectangle
        }
    }
}
