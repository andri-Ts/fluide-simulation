#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#include "config.h"
#include "render.h"
#include "fluide.h"

// Cell grid[ROWS][COLUMNS];

// Variables globales SDL
static SDL_Window *window = NULL; // Pointeur vers la fenêtre SDL
static SDL_Renderer *renderer = NULL; // Pointeur vers le renderer

// Foncitons d'initalisation
void init_sdl(void);
void cleanup(void);

// -------------------------------------------------------------------

int main(int argc, char* argv[])
{

    init_sdl();
    init_grid();

    SDL_bool program_running = SDL_TRUE;
    SDL_Event event; // capte tous les event
    SDL_bool delete_mode = SDL_FALSE;

    while(program_running)
    {
        // ---- HANDLE EVENT ----
        while(SDL_PollEvent(&event)) // Boucle qui vide la file d'événements
        {
            switch(event.type) // Switch pour traiter chaque type d'evenements
            {
                case SDL_QUIT:
                    program_running = SDL_FALSE; // pour fermer le programme
                    break;

                case SDL_KEYDOWN:
                    if(event.key.keysym.sym == SDLK_SPACE)
                        delete_mode = !delete_mode;
                    break;

                case SDL_MOUSEMOTION:
                    int cellX = event.motion.x / CELL_SIZE;  // si souris à 120px, posX_cellule = posX_souris / size_cell (120px / 12px) = 10e colonne (index de la cellule)
                    int cellY = event.motion.y / CELL_SIZE; // index (ligne) de la cellule (ex: 5e ligne)

                    if(cellX >= 0 && cellX < COLUMNS && cellY >= 0 && cellY < ROWS) // sécurité
                    {
                        if(delete_mode)
                        {
                            grid[cellY][cellX].type = EMPTY_TYPE;
                            grid[cellY][cellX].fill_level = 0;
                        }
                        // click gauche -> solide (blanc)
                        if(event.motion.state & SDL_BUTTON(SDL_BUTTON_LEFT)) // “Est-ce que le bit du bouton gauche est actif ?”
                        {
                            grid[cellY][cellX].type = SOLID_TYPE;
                        }
                        // click droite -> eau (bleu)
                        else if(event.motion.state & SDL_BUTTON(SDL_BUTTON_RIGHT))
                        {
                            grid[cellY][cellX].type = WATER_TYPE;
                            grid[cellY][cellX].fill_level = 1.0f;
                        }
                    }
                    break;

                default:
                    break;
            }
        }

        // ---- UPDATE ---- Logique du programme
        simulation_step();

        // ---- RENDER ----
        render_frame(renderer);



    }

    cleanup();

    return 0;
}

// -------------------------------------------------------------------

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
        cleanup();

    }
}

// -------------------------------------------------------------------

void cleanup(void)
{
    if (renderer) SDL_DestroyRenderer(renderer);
    if (window) SDL_DestroyWindow(window);
    SDL_Quit();
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
