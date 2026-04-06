#include "input.h"
#include "config.h"
#include "fluide.h"

void handle_events(SDL_Event *event, SDL_bool *running, SDL_bool *delete_mode)
{
    while(SDL_PollEvent(event))
    {
        switch(event->type)
        {
            case SDL_QUIT:
                *running = SDL_FALSE;
                break;

            case SDL_KEYDOWN:
                if(event->key.keysym.sym == SDLK_SPACE)
                    *delete_mode = !(*delete_mode);
                break;

            case SDL_MOUSEMOTION:
                int cellX = event->motion.x / CELL_SIZE;
                int cellY = event->motion.y / CELL_SIZE;

                if(cellX >= 0 && cellX < COLUMNS && cellY >= 0 && cellY < ROWS)
                {
                    if(*delete_mode)
                    {
                        grid[cellY][cellX].type = EMPTY_TYPE;
                        grid[cellY][cellX].fill_level = 0;
                    }
                    if(event->motion.state & SDL_BUTTON(SDL_BUTTON_LEFT))
                        grid[cellY][cellX].type = SOLID_TYPE;
                    else if(event->motion.state & SDL_BUTTON(SDL_BUTTON_RIGHT))
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
}
