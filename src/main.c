#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#include "config.h"
#include "render.h"
#include "fluide.h"
#include "input.h"




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
        handle_events(&event, &program_running, & delete_mode);

        // ---- UPDATE ---- Logique du programme
        simulation_step();

        // ---- RENDER ----
        render_frame(renderer);

        SDL_Delay(16);
    }

    cleanup();

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
