#include <stdio.h>
#include <SDL2/SDL.h>
#include "render.h"
#include "fluide.h"
#include "sdl.h"

void render_frame(void)
{
    SDL_Renderer *renderer = get_renderer();

    // Nettoyer l'écran
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Dessiner la grille
    draw_grid(renderer);

    for(int y = 0; y < ROWS; y++)
    {
        for(int x = 0; x < COLUMNS; x++)
        {
            Cell c = get_cell(y, x);
            if(c.type == EMPTY_TYPE) continue;

            SDL_Rect rect = { x * CELL_SIZE, y * CELL_SIZE, CELL_SIZE, CELL_SIZE };

            if(c.type == SOLID_TYPE)
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
            else if(c.type == WATER_TYPE)
            {
                SDL_SetRenderDrawColor(renderer, 0, 180, 216, SDL_ALPHA_OPAQUE);
                rect.y += CELL_SIZE - (CELL_SIZE * c.fill_level);
                rect.h = CELL_SIZE * c.fill_level;
            }

            SDL_RenderFillRect(renderer, &rect);
        }
    }

    SDL_RenderPresent(renderer);
}

// ----------------------------------------------------------------------------------------

void draw_grid(SDL_Renderer *renderer)
{
    // on "dessine" tous les cellules
    // 1- DEFINIR LA COULEUR
    SDL_SetRenderDrawColor(renderer, 40, 40, 40, SDL_ALPHA_OPAQUE); // gris discret

    // lignes verticales
    for(int x = 0; x <= COLUMNS; x++)
    {
        // 2 - DEFINIR LA FIGURE
        int posX = x * CELL_SIZE;
        //// 3- DESSINER LA FIGURE (sur celle-ci, definition et dessin en même tmps)
        SDL_RenderDrawLine(renderer, posX, 0, posX, ROWS * CELL_SIZE); // (xStart, yStart, xEnd, yeND[coordoné du dernier pixel du bas])
    }

    // ligne horizontales
    for (int y = 0; y < ROWS; y++)
    {
        int posY = y * CELL_SIZE;
        SDL_RenderDrawLine(renderer, 0, posY, COLUMNS * CELL_SIZE, posY);
    }
}
