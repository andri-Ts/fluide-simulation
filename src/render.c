#include <stdio.h>
#include <SDL2/SDL.h>
#include "../include/render.h"
#include "../include/fluide.h"

void draw_grid(SDL_Renderer *renderer)
{
    // on "dessine" tous les cellules
    // 1- DEFINIR LA COULEUR
    SDL_SetRenderDrawColor(renderer, 52, 58, 64, SDL_ALPHA_OPAQUE);
    for(int y = 0; y < ROWS; y++)
    {
        for(int x = 0; x < COLUMNS; x++)
        {
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

void draw_cell(SDL_Renderer *renderer)
{
    for(int y = 0; y < ROWS; y++) // parcours les lignes (0 -> ROWS)
    {
        for (int x = 0; x < COLUMNS; x++) // parcours les colonnes (0 à COLUMNS)
        {
            if(grid[y][x].type == SOLID_TYPE)
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE); // determiner la couleur
            else if(grid[y][x].type == WATER_TYPE)
                SDL_SetRenderDrawColor(renderer, 0, 180, 216, SDL_ALPHA_OPAQUE); // eau bleu

            SDL_Rect cell = {
                grid[y][x].x * CELL_SIZE,
                grid[y][x].y * CELL_SIZE,
                CELL_SIZE,
                CELL_SIZE
            };

            SDL_RenderFillRect(renderer, &cell);

        }
    }
}
