#include "input.h"
#include "config.h"
#include "fluide.h"

void handle_events(SDL_bool *running, SDL_bool *delete_mode)
{
    SDL_Event event; // capte tous les event

    while(SDL_PollEvent(&event))
    {
        switch(event.type)
        {
            case SDL_QUIT:
                *running = SDL_FALSE;
                break;

            case SDL_KEYDOWN:
                if(event.key.keysym.sym == SDLK_SPACE)
                    *delete_mode = !(*delete_mode);
                break;

            case SDL_MOUSEMOTION:
                int cellX = event.motion.x / CELL_SIZE;
                int cellY = event.motion.y / CELL_SIZE;

                if(cellX < 0 || cellX >= COLUMNS || cellY < 0 || cellY >= ROWS)
                    break;

                if(*delete_mode)
                    remove_cell(cellX, cellY);
                else if(event.motion.state & SDL_BUTTON(SDL_BUTTON_LEFT))
                    solid_cell(cellX, cellY);
                else if(event.motion.state & SDL_BUTTON(SDL_BUTTON_RIGHT))
                    water_cell(cellX, cellY);

                break;

            default:
                break;
        }
    }
}
