#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#include "../include/config.h"

int main(int argc, char* argv[])
{
    // --------------------------------------------------------
    // VARIABLES
    // --------------------------------------------------------
    SDL_Window *window = NULL; // Pointeur vers la fenêtre SDL
    SDL_Renderer *renderer = NULL; // Pointeur vers le renderer

    // --------------------------------------------------------
    // Initialisations
    // --------------------------------------------------------

    // Initialisation de SDL (système vidéo ici)
    if(SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        fprintf(stderr, "Erreur SDL_Init: %s\n", SDL_GetError());
        goto cleanup;
    }

    // Création de la fenêtre
    window = SDL_CreateWindow(
        "Liquide Simulation",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH, SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN);

    if(window == NULL)
    {
        fprintf(stderr, "Erreur SDL_CreateWindow: %s\n", SDL_GetError());
        goto cleanup;
    }

    // Création du renderer (outils de dessin)
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(renderer == NULL)
    {
        fprintf(stderr, "Erreur SDL_CreateRenderer : %s\n", SDL_GetError());
        goto cleanup;
    }

    // --------------------------------------------------------
    // CODES
    // --------------------------------------------------------

    // Nettoyage de l'écran
    SDL_RenderClear(renderer);

    // Rectangle blanc
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);    // 1- DEFINIR LA COULEUR
    SDL_Rect rectangle = {50, 50, 100, 50};                             // 2- DEFINIR LE RECTANGLE
    SDL_RenderFillRect(renderer, &rectangle);          // 3- DESSINER LE RECTANGLE

    // Rectangle bleu ciel
    SDL_SetRenderDrawColor(renderer, 0, 180, 216, SDL_ALPHA_OPAQUE);
    SDL_Rect rectangle_blue = {150, 50, 100, 50};
    SDL_RenderFillRect(renderer, &rectangle_blue);

    // OPTIONS AFFICHAGES
    SDL_RenderPresent(renderer); // "affiche" tout ce qu'on a dessiné
    SDL_Delay(5000);

// --------------------------------------------------------
// Label pour le nettoyage
// --------------------------------------------------------
cleanup:
    if (renderer) SDL_DestroyRenderer(renderer);
    if (window) SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
