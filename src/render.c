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

void color_cell(SDL_Renderer *renderer, int cellX, int cellY)
{
    // Caractéristiques du rectangle
    SDL_Rect cell_colored = {
        cellX * CELL_SIZE, // coordoné x du pixel: coordX de la cellule * taille d'une cellule
        cellY * CELL_SIZE, // coordonné Y du nouveau rect
        CELL_SIZE,
        CELL_SIZE
    };
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE); // determiner la courleur: en blanc
    SDL_RenderFillRect(renderer, &cell_colored); // dessiner le rectangle
}
