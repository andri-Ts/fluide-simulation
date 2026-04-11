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
    memset(next_grid, 0, sizeof(next_grid)); // (grid à afficher pour le prochain frame) on le veut vide

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


            // float current_quantity = current->fill_level;
            // Cell *next_current = &next_grid[y][x];
            float current_quantity = current->fill_level; // Quantité d'eau dans la cellule courante
            float down_flow = 0.0f; // flux de descente
            float left_flow = 0.0f; // flux de vers la gauche
            float right_flow = 0.0f; //

            // ==================================
            // RULE 1: flow down (gravité)
            // ==================================
            if(y + 1 < ROWS) // sécurité pour ne pas sortir de la fenêtre window
            {
                Cell *below = &grid[y+1][x];

                if(below->type != SOLID_TYPE)
                {
                    down_flow = current_quantity;
                    float capacity = 1.0f - next_grid[y+1][x].fill_level; // on utilise next_grid car plrs cellules peuvent déjà avoir ajouté de l'eau à cette case pendant cette frame

                    if(down_flow > capacity)
                        down_flow = capacity; // évite le surcharge

                    current_quantity -= down_flow;
                }
            }

            // ==================================
            // RULE 2: Horizontal (gauche/droite)
            // ==================================

            float left_quantity = (x > 0) ? grid[y][x-1].fill_level : 0.0f; // si voisin (actuelle) existe, on lit la valeur, sinon o suppose vide
            float right_quantity = (x < COLUMNS - 1) ? grid[y][x+1].fill_level : 0.0f;

            float left_diff = current_quantity - left_quantity; // current est il plus plein que son voisin
            float right_diff = current_quantity - right_quantity;
            float flow_factor = 0.25f; // facteur d'amortissement pour éviter les oscillations

            // -------- LEFT --------------
            if( x > 0 && grid[y][x-1].type != SOLID_TYPE && left_diff > 0.0f)
            {
                left_flow = left_diff * flow_factor;

                float capacity = 1.0f - next_grid[y][x-1].fill_level;
                if(left_flow > capacity)
                    left_flow = capacity; // on ne transfère que ce que voici peut recevoir
            }

            // -------- RIGTH -------------
            if( x < COLUMNS - 1 && grid[y][x+1].type != SOLID_TYPE && right_diff > 0.0f) // ..., si current a plus d'eau que son voisin
            {
                right_flow = right_diff * flow_factor;

                float capacity = 1.0f - next_grid[y][x+1].fill_level;
                if(right_flow > capacity)
                    right_flow = capacity;
            }

            // ==================================
            // NORMALISATION (réduit tout proportionnement)
            // ==================================
            float total_flow = down_flow + left_flow + right_flow;

            // évite création/perte d'eau : répartit l'eau proportionnellement
            if(total_flow > current->fill_level)
            // if(total_flow > current_quantity)
            {
                // float k = current_quantity / total_flow;
                float k = current->fill_level / total_flow;

                down_flow *= k; // on réduit tous les flux proportionnellement
                left_flow *= k;
                right_flow *= k;
            }

            // ==================================
            // Application des flux (envoye des quantités réels d'eau dans les cases voisines)
            // ==================================
            if(down_flow > 0.0f)
            {
                next_grid[y+1][x].fill_level += down_flow;
                next_grid[y+1][x].type = WATER_TYPE;
            }

            if(left_flow > 0.0f)
            {
                next_grid[y][x-1].fill_level += left_flow;
                next_grid[y][x-1].type = WATER_TYPE;
            }

            if(right_flow > 0.0f)
            {
                next_grid[y][x+1].fill_level += right_flow;
                next_grid[y][x+1].type = WATER_TYPE;
            }

            // ==================================
            // Reste dans la cellule actuelle
            // ==================================
             float stay = current->fill_level - (down_flow + left_flow + right_flow); // l'eau qui n'a pas bougé

            if(stay > 0.001f)
            {
                next_grid[y][x].fill_level += stay;
                next_grid[y][x].type = WATER_TYPE;
            }
            else
            {
                next_grid[y][x].type = EMPTY_TYPE;
                next_grid[y][x].fill_level = 0.0f;
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
    grid[y][x].fill_level = 1.0f;
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
