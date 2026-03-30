#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

int main(int argc, char argc[])
{
    // --------------------------------------------------------
    // VARIABLES
    // --------------------------------------------------------
    SDL_Window *window = NULL;

    // --------------------------------------------------------
    // Initialisations
    // --------------------------------------------------------

    // Initialisation de SDL (système vidéo ici)
    if(SDL_init(SDL_INIT_VIDEO != 0))
    {
        fprintf(stderr, "Erreur SDL_Init: %s\n", SDL_GetError());
        goto cleanup;
    }

    // Création de la fenêtre
    // window = SDL_CreateWindow("Liquide Simulation", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED)

// --------------------------------------------------------
// Label pour le nettoyage
// --------------------------------------------------------
cleanup:
    SDL_Quit(); // libère le SDL

    return 0;
}
