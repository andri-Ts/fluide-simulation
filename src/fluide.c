#include "fluide.h"

// définition réelle de la grille
Cell grid[ROWS][COLUMNS];

// ----------------------------------------------------------------------------------------

void init_grid(void)
{
    for(int y = 0; y < ROWS; y++)
    {
        for(int x = 0; x < COLUMNS; x++)
        {
            grid[y][x].x = x;
            grid[y][x].y = y;
            grid[y][x].type = EMPTY_TYPE;
            grid[y][x].fill_level = 0;
        }
    }
}

// ----------------------------------------------------------------------------------------

void simulation_step(void)
{
    for(int y = ROWS - 2; y >= 0; y--)
    {
        for(int x = 0; x < COLUMNS; x++)
        {
            switch(grid[y][x].type)
            {
                case EMPTY_TYPE:
                    break;

                case WATER_TYPE: // je suis une cellule d'eau
                    if(grid[y+1][x].type == EMPTY_TYPE) // si la cellule de dessous est vide
                    {
                        grid[y+1][x].type = WATER_TYPE; // elle reçoit mon eau
                        grid[y+1][x].fill_level = grid[y][x].fill_level; // avec la meme quantité

                        grid[y][x].type = EMPTY_TYPE;  // moi je me vide
                        grid[y][x].fill_level = 0.0f;

                    }
                    break;

                default:
                    break;
            }
        }
    }
}
