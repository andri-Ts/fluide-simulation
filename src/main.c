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
    // Initialisation du SDL (systeme video/image ici)
    // --------------------------------------------------------
    if(SDL_init(SDL_INIT_VIDEO != 0))
    {
        fprintf(stderr, "Erreur SDL_Init: %s\n", SDL_GetError());
        goto cleanup;
    }

    // --------------------------------------------------------
    // Création de la fenêtre
    // --------------------------------------------------------


// Label pour le nettoyage
cleanup:
    SDL_Quit(); // libère le SDL

    return 0;
}
