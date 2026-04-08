#include "fluide.h"
#include <stdio.h>

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
    // On parcours l'écran de bas vers l haut

    for(int y = ROWS - 2; y >= 0; y--)
    {
        for(int x = 0; x < COLUMNS; x++)
        {
            Cell *current_cell = &grid[y][x];
            Cell *below_cell = &grid[y+1][x];

            if(current_cell->type != WATER_TYPE)
                continue;
            else if(current_cell->type == WATER_TYPE)
            {
                switch(below_cell->type)
                {
                    case EMPTY_TYPE:
                    {
                        below_cell->type = WATER_TYPE;
                        below_cell->fill_level = current_cell->fill_level;

                        current_cell->type = EMPTY_TYPE;
                        current_cell->fill_level = 0.0f;

                        break;
                    }

                    case WATER_TYPE:
                    {
                        float below_capacity = 1 - below_cell->fill_level; // quantité que peut recevoir la cellule du dessous
                        float current_quantity = current_cell->fill_level; // quantité d'eau que la cellule possède
                        float transfer = 0.0f; // quantité réél d'eau a transféré vers le bas

                        // La quantité réel transmis vers le bas est le minimum entre ce que le bas peut recevoir et ce que le haut peut donner
                        if( below_capacity >= current_quantity)
                            transfer = current_quantity; // below possede assez de capacité pour contenir tout l'eau de current
                        else
                            transfer = below_capacity;

                        below_cell->fill_level += transfer;
                        current_cell->fill_level -= transfer;

                        // remettre la cellule current comme vide si c'est le cas
                        if(current_cell->fill_level == 0.0f)
                            current_cell->type = EMPTY_TYPE;

                        // Sécurité pour float
                        if(below_cell->fill_level > 1.0f)
                            below_cell->fill_level = 1.0f;
                        if(current_cell->fill_level < 0.0f)
                            current_cell->fill_level = 0.0f;

                        break;
                    }

                    default:
                        break;
                }
            }
        }
    }
}

// ----------------------------------------------------------------------------------------

void water_cell(int x, int y)
{
    if(x < 0 || x >= COLUMNS || y < 0 || y >= ROWS) return;
    grid[y][x].type = WATER_TYPE;
    grid[y][x].fill_level = 0.30;
}

void solid_cell(int x, int y)
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
