#include <stdio.h>
#include <SDL2/SDL.h>
#include "../include/render.h"
// #include "../include/config.h"

void draw_grid(SDL_Renderer *renderer, int grid[ROWS][COLUMNS])
{
    // on "dessine" tous les cellules
    for(int y = 0; y < ROWS; y++)
    {
        for(int x = 0; x < COLUMNS; x++)
        {
            if(grid[y][x] == 0)
            {
                // 1- DEFINIR LA COULEUR
                SDL_SetRenderDrawColor(renderer, 52, 58, 64, SDL_ALPHA_OPAQUE);
                // 2- DEFINIR LE RECTANGLE
                SDL_Rect cell = {
                    x * CELL_SIZE,
                    y * CELL_SIZE,
                    CELL_SIZE,
                    CELL_SIZE
                };
                // 3- DESSINER LE RECTANGLE
                SDL_RenderDrawRect(renderer, &cell); // contour de chque rectangle
            }
        }
    }
}

void draw_cell(SDL_Renderer *renderer, int grid[ROWS][COLUMNS])
{
    for(int y = 0; y < ROWS; y++) // parcours les lignes (0 -> ROWS)
    {
        for (int x = 0; x < COLUMNS; x++) // parcours les colonnes (0 à COLUMNS)
        {
            if(grid[y][x] == 1)
            {
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE); // determiner la couleur
                SDL_Rect cell = {
                    x * CELL_SIZE,
                    y * CELL_SIZE,
                    CELL_SIZE,
                    CELL_SIZE
                };
                SDL_RenderFillRect(renderer, &cell);
            }
        }
    }
}
