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

void simulation_step()
{
    //  =================================
    // 1. RESET COMPLET DE next_grid
    // ==================================
    memset(next_grid, 0, sizeof(grid)); // (grid à afficher pour le prochain frame) on le veut vide

    //  =================================
    // 2. Parcours de la grille(lecture)
    // ==================================
    for( int y = ROWS - 1; y >= 0; y--) // On parcours l'écran de bas vers le haut (grid LECTURE uniquement)
    {
        for(int x = 0; x < COLUMNS; x++)
        {
            Cell *current = &grid[y][x];

            // =================================
            // 3. Ignorer certainnes conditions
            // ==================================

            // copie des cell solides
            if(current->type == SOLID_TYPE)
            {
                next_grid[y][x] = *current;
                continue; // sort de la boucle for et saute à l'itération suivante
            }

            // Ignorer les cellules vides
            if(current->type != WATER_TYPE)
                continue;

            // Quantité d'eau dans la cellule courante
            float current_quantity = current->fill_level;
            Cell *next_current = &next_grid[y][x];

            // =================================
            // RULE 1: flow down (gravité)
            // ==================================
            if(y + 1 < ROWS) // sécurité pour ne pas sortir de la fenêtre window
            {
                Cell *below = &grid[y+1][x];

                if(below->type != SOLID_TYPE)
                {
                    float below_capacity = 1.0f - below->fill_level;
                    float transfer = current_quantity;

                    if(transfer > below_capacity)
                        transfer = below_capacity; // on ne transfert que ce que below peut contenir, si non on transfert tout

                    // On modifie la cellule d'en bas
                    if(transfer > 0.0f)
                    {
                        current_quantity -= transfer; // on soustrait la quentité d'eau transféré vers le bas à la cellule courante
                        next_grid[y+1][x].fill_level += transfer;
                        next_grid[y+1][x].type = WATER_TYPE;
                    }
                }
            }

            // =================================
            // RULE 2: flow LEFT
            // ==================================
            if(x - 1 >= 0) // Sécurité pour ne pas faire débordé la grid
            {
                Cell *left = &grid[y][x-1];

                if(left->type != SOLID_TYPE)
                {
                    float diff = current_quantity - left->fill_level; // différence de niveau d'eau

                    if(diff > 0) // c-a-d cellule courante contient plus d'eau que cellule de gauche
                    {
                        float transfer = diff * 0.5f;
                        float left_capacity = 1.0f - left->fill_level;

                        // Limite max de transfert par frame
                        if(transfer > 0.25f)
                            transfer = 0.25f; // valeur empirique

                        if(transfer > left_capacity)
                            transfer = left_capacity; // on ne transmet que ce que la cellule de gauche peut recevoir
                        if(transfer > current_quantity)
                            transfer = current_quantity; // emp^che de créer de l'eau, on ne transfert que la quantité possédée par current

                        next_grid[y][x-1].fill_level += transfer;
                        next_grid[y][x-1].type = WATER_TYPE;

                        current_quantity -= transfer; // Calcul le reste

                    }
                }
            }

            //  =================================
            // RULE 2: flow RIGHT
            // ==================================
            if(x + 1 < COLUMNS)
            {
                Cell *right = &grid[y][x+1];

                if(right->type != SOLID_TYPE)
                {
                    float diff = current_quantity - right->fill_level; // le reste de l'eau courant apres regle 1 et regle 2(left) - level right

                    if(diff > 0.0f)
                    {
                        float transfer = diff * 0.5f;
                        float right_capacity = 1 - right->fill_level;

                        if(transfer > right_capacity)
                            transfer = right_capacity;
                        if(transfer > current_quantity)
                            transfer = current_quantity;

                        if(transfer > 0.25f)
                            transfer = 0.25f;

                        next_grid[y][x+1].fill_level += transfer;
                        next_grid[y][x+1].type = WATER_TYPE;

                        current_quantity -= transfer;
                    }
                }
            }

            //  ====================================
            // 3. Mettre à jour la cellule courante
            // =====================================
            next_current->fill_level = current_quantity; // a priori le next_grid level est à 0, donc on ajoute l'eau qui reste
            if(next_current->fill_level > 0.001f)
            {
                next_current->type = WATER_TYPE;
            }
            else
            {
                next_current->type = EMPTY_TYPE;
                next_current->fill_level = 0.0f;
            }
        }
    }

    //  ===================================
    // FINAL: Remplacer grid par next_grid
    // ====================================
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
