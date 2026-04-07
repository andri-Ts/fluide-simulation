#include <stdio.h>
// #include <SDL2/SDL.h>
// #include "../include/render.h"
// #include "../include/fluide.h"

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

// void render_frame(SDL_Renderer *renderer)
// {
//     SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
//     SDL_RenderClear(renderer); // efface TOUT

//     draw_cell(renderer);
//     draw_grid(renderer);

//     // OPTIONS AFFICHAGES
//     SDL_RenderPresent(renderer); // "affiche" tout ce qu'on a dessiné
// }

// // ----------------------------------------------------------------------------------------

// void draw_grid(SDL_Renderer *renderer)
// {
//     // on "dessine" tous les cellules
//     // 1- DEFINIR LA COULEUR
//     SDL_SetRenderDrawColor(renderer, 52, 58, 64, SDL_ALPHA_OPAQUE); // vide : gris
//     for(int y = 0; y < ROWS; y++)
//     {
//         for(int x = 0; x < COLUMNS; x++)
//         {
//              if(grid[y][x].type != EMPTY_TYPE)
//                 continue; // pas de grille sur les cellules colorées

//             // 2- DEFINIR LE RECTANGLE
//             SDL_Rect cell = {
//                 x * CELL_SIZE, // posX = le num du pixel en X * taille d'une cellule en pix (12px)
//                 y * CELL_SIZE,
//                 CELL_SIZE, // longeur d'une cellule c'est 12px, donc posX du proche cellule: 12px * index
//                 CELL_SIZE
//             };
//             // 3- DESSINER LE RECTANGLE
//             SDL_RenderDrawRect(renderer, &cell); // contour de chaque rectangle

//         }
//     }
// }

// // ----------------------------------------------------------------------------------------

// void draw_cell(SDL_Renderer *renderer)
// {
//     for(int y = 0; y < ROWS; y++) // parcours les lignes (0 -> ROWS)
//     {
//         for (int x = 0; x < COLUMNS; x++) // parcours les colonnes (0 à COLUMNS)
//         {
//             if(grid[y][x].type == EMPTY_TYPE)
//                 continue; // cellule vide, on ne dessine rien

//             if(grid[y][x].type == SOLID_TYPE)
//             {
//                 SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE); // determiner la couleur (blanc)
//                 SDL_Rect cell = {
//                     x * CELL_SIZE,
//                     y * CELL_SIZE,
//                     CELL_SIZE,
//                     CELL_SIZE
//                 };
//                 SDL_RenderFillRect(renderer, &cell);
//             }
//             else if(grid[y][x].type == WATER_TYPE)
//             {
//                 SDL_SetRenderDrawColor(renderer, 0, 180, 216, SDL_ALPHA_OPAQUE); // eau bleu
//                 // L'eau doit oller au bas de la cellule
//                 int height_water = CELL_SIZE * grid[y][x].fill_level; // si level = 1, taille de l'eau 12px, si level 0.75, taille de l'eau : 12 * 0.75
//                 int posY_water = grid[y][x].y * CELL_SIZE + (CELL_SIZE - height_water); // y = top of cell + (cellsize - height of water)

//                 SDL_Rect cell = {
//                     grid[y][x].x * CELL_SIZE,
//                     posY_water,
//                     CELL_SIZE,
//                     height_water
//                 };
//                 SDL_RenderFillRect(renderer, &cell);
//             }
//         }
//     }
// }
