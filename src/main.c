#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#include "sdl.h"
#include "render.h"
#include "fluide.h"
#include "input.h"

int main(int argc, char* argv[])
{

    init_sdl();
    init_grid();

    SDL_bool program_running = SDL_TRUE;
    // SDL_Event event;
    SDL_bool delete_mode = SDL_FALSE;

    while(program_running)
    {
        // ---- HANDLE EVENT ----
        handle_events(&program_running, &delete_mode);

        // ---- UPDATE ---- Logique du programme
        simulation_step();

        // ---- RENDER ----
        render_frame();

        SDL_Delay(80);
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
