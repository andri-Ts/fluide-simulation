#include "fluide.h"

// définition réelle de la grille
static Cell grid[ROWS][COLUMNS]; // visible uniquement dans ce fichier

// ----------------------------------------------------------------------------------------

Cell get_cell(int y, int x)
{
    if(x < 0 || x >= COLUMNS || y < 0 || y >= ROWS)
        return (Cell){0, 0, EMPTY_TYPE, 0.0f}; // renvoie une cellule vide neutre si on dépasse les limites (évite le crash)

    return grid[y][x];
}

// ----------------------------------------------------------------------------------------

void init_grid(void)
{
    for(int y = 0; y < ROWS; y++) // Le premier indice (grid[y][…]) correspond à la ligne → l’axe vertical (Y)
    {
        for(int x = 0; x < COLUMNS; x++) // Le second indice (grid[…][x]) correspond à la colonne → l’axe horizontal (X)
        {
            grid[y][x].x = x;
            grid[y][x].y = y;
            grid[y][x].type = EMPTY_TYPE;
            grid[y][x].fill_level = 0.0f;
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

// ----------------------------------------------------------------------------------------

void add_water(int x, int y)
{
    if(x < 0 || x >= COLUMNS || y < 0 || y >= ROWS) return;
    grid[y][x].type = WATER_TYPE;
    grid[y][x].fill_level = 1.0f;
}

void add_solid(int x, int y)
{
    if(x < 0 || x >= COLUMNS || y < 0 || y >= ROWS) return;
    grid[y][x].type = SOLID_TYPE;
}

void remove_cell(int x, int y)
{
    if(x < 0 || x >= COLUMNS || y < 0 || y >= ROWS) return;
    grid[y][x].type = EMPTY_TYPE;
    grid[y][x].fill_level = 0.0f;
}
