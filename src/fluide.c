#include <stdio.h>
#include <SDL2/SDL.h>
#include "../include/fluide.h"
#include "../include/config.h"

void draw_grid(SDL_Renderer *renderer)
{
    // Je créer chaque colonne (donc verticale)
    for(int i = 0; i < COLUMNS; i++)
    {
        SDL_Rect column = {
            i * CELL_SIZE, // chaque rectangle est décalé à droite par CELL_WIDTH * son index i
            0,              // tous les rectangles commencent en haut de la fenêtre.
            LINE_WIDTH,     // largeur de chaque colonne (épaisseur d'un carré)
            SCREEN_HEIGHT     // hauteur de la colonne.
        };
        SDL_SetRenderDrawColor(renderer, 52, 58, 64, SDL_ALPHA_OPAQUE);
        SDL_RenderFillRect(renderer, &column);
    }

    // Je créer chauqe colonne (donc horizontale)
    for(int j = 0; j < ROWS; j++)
    {
        SDL_Rect row = {
            0,
            j * CELL_SIZE,
            SCREEN_WIDTH,
            LINE_WIDTH
        };
        SDL_SetRenderDrawColor(renderer, 52, 58, 64, SDL_ALPHA_OPAQUE);
        SDL_RenderFillRect(renderer, &row);
    }
}
