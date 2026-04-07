#include <stdio.h>
#include <stdlib.h>
#include "sdl.h"
#include "config.h"

// Variables globales SDL | static: visible uniquement dans ce fichier
static SDL_Window *window = NULL; // Pointeur vers la fenêtre SDL
static SDL_Renderer *renderer = NULL; // Pointeur vers le renderer

void init_sdl(void)
{
    // Initialisation de SDL (système vidéo ici)
    if(SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        fprintf(stderr, "Erreur SDL_Init: %s\n", SDL_GetError());
        exit(1); // rien à nettoyer, SLD n'est pas initilisé;
    }

    // Création de la fenêtre window
    window = SDL_CreateWindow(
        "Liquide Simulation",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH, SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN);

    if(window == NULL)
    {
        fprintf(stderr, "Erreur SDL_CreateWindow: %s\n", SDL_GetError());
        SDL_Quit(); // SDL est déjà initialisé, on le nettoie
        exit(1);
    }

    // Création du renderer (outils de dessin)
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(renderer == NULL)
    {
        fprintf(stderr, "Erreur SDL_CreateRenderer : %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        exit(1);

    }
}

// ---------------------------------------------------------------------------------------------

void cleanup(void)
{
    if (renderer)
    {
        SDL_DestroyRenderer(renderer);
        renderer == NULL;
    }

    if (window)
    {
        SDL_DestroyWindow(window);
        window == NULL;
    }

    SDL_Quit();
}

// ---------------------------------------------------------------------------------------------

SDL_Renderer* get_renderer(void)
{
    return renderer;
}
