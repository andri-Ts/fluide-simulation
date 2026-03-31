#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#include "config.h"
#include "render.h"

int main(int argc, char* argv[])
{
    // --------------------------------------------------------
    // VARIABLES
    // --------------------------------------------------------
    SDL_Window *window = NULL; // Pointeur vers la fenêtre SDL
    SDL_Renderer *renderer = NULL; // Pointeur vers le renderer

    // --------------------------------------------------------
    // INITIALISATION
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
    // BOUCLE PRINCIPALE
    // --------------------------------------------------------
    SDL_bool program_running = SDL_TRUE;
    SDL_Event event; // capte tous les event

    while(program_running)
    {
        draw_grid(renderer);
        // ---- HANDLE EVENT ----
        while(SDL_PollEvent(&event)) // Boucle qui vide la file d'événements
        {
            switch(event.type) // Switch pour traiter chaque type d'evenements
            {
                case SDL_QUIT:
                    program_running = SDL_FALSE; // pour fermer le programme
                    break;

                case SDL_MOUSEMOTION:
                    int cellX = event.motion.x / CELL_SIZE;  // si souris à 120px, posX_cellule = posX_souris / size_cell (120px / 12px) = 10e colonne (index de la cellule)
                    int cellY = event.motion.y / CELL_SIZE; // index (ligne) de la cellule (ex: 5e ligne)
                    color_cell(renderer, cellX, cellY);
                    break;

                default:
                    break;
            }
        }

        // ---- UPDATE ---- Logique du programme

        // ---- RENDER ----
        // SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // fond noir
        // SDL_RenderClear(renderer); // // Effacer l'écran avec le couleur noir

        // Rectangle blanc
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);  // 1- DEFINIR LA COULEUR
        SDL_Rect rectangle = {50, 50, 100, 50};                             // 2- DEFINIR LE RECTANGLE
        SDL_RenderFillRect(renderer, &rectangle);                           // 3- DESSINER LE RECTANGLE

        // Rectangle bleu ciel
        SDL_SetRenderDrawColor(renderer, 0, 180, 216, SDL_ALPHA_OPAQUE);
        SDL_Rect rectangle_blue = {150, 50, 100, 50};
        SDL_RenderFillRect(renderer, &rectangle_blue);

        // draw_grid(renderer);

        // OPTIONS AFFICHAGES
        SDL_RenderPresent(renderer); // "affiche" tout ce qu'on a dessiné
        SDL_Delay(16);
    }



// --------------------------------------------------------
// Label pour le nettoyage
// --------------------------------------------------------
cleanup:
    if (renderer) SDL_DestroyRenderer(renderer);
    if (window) SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}


/* STRUCTURE :
----------------
init();
while (running)
{
    handle_events();
    update();
    render();
}
cleanup();
*/
