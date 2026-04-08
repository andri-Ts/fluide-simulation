#include "fluide.h"
#include <stdio.h>
#include <string.h>

// définition réelle de la grille
static Cell grid[ROWS][COLUMNS]; // visible uniquement dans ce fichier
static Cell next_grid[ROWS][COLUMNS]; // Etat suivant de la grid

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
    // 1.Copier l'état actuel du grid dans next_grid
    memcpy(next_grid, grid, sizeof(grid));

    // 2.On parcours l'écran de bas vers le haut (grid LECTURE uniquement)
    for(int y = ROWS - 2; y >= 0; y--)
    {
        for(int x = 0; x < COLUMNS; x++)
        {
            Cell *current_cell = &grid[y][x];
            Cell *below_cell = &grid[y+1][x];

            // On écirit dans next_grid (copie de la grid)
            Cell *c_current_cell = &next_grid[y][x];
            Cell *c_below_cell = &next_grid[y+1][x];

            if(current_cell->type != WATER_TYPE)
                continue;

            switch(below_cell->type)
            {
                case EMPTY_TYPE:
                {
                    // L'eau tombe complètement
                    c_below_cell->type = WATER_TYPE;
                    c_below_cell->fill_level = current_cell->fill_level;

                    c_current_cell->type = EMPTY_TYPE;
                    c_current_cell->fill_level = 0.0f;

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

                    c_below_cell->fill_level += transfer;
                    c_current_cell->fill_level -= transfer;

                    // Nettoyage float (important) ET // remettre la cellule current comme vide si c'est le cas
                    if(c_current_cell->fill_level < 0.0001f)
                    {
                        c_current_cell->type = EMPTY_TYPE;
                        c_current_cell->fill_level = 0.0f;
                    }

                    if(c_below_cell->fill_level > 1.0f)
                        c_below_cell->fill_level = 1.0f;

                    break;
                }

                default:
                    break;
            }

        }
    }

    // 3.Appliquer le résultat au vrai grid
    memcpy(grid, next_grid, sizeof(grid));
}

// ----------------------------------------------------------------------------------------

void water_cell(int x, int y)
{
    if(x < 0 || x >= COLUMNS || y < 0 || y >= ROWS) return;
    grid[y][x].type = WATER_TYPE;
    grid[y][x].fill_level = 0.5f;
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
