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
            {
                continue;
            }
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

                    default:
                        break;
                }
            }
        }
    }
}

// void simulation_step(void)
// {
//     for(int y = ROWS - 2; y >= 0; y--)
//     {
//         for(int x = 0; x < COLUMNS; x++)
//         {
//             switch(grid[y][x].type)
//             {
//                 case EMPTY_TYPE:
//                     break;

//                 case WATER_TYPE: // je suis une cellule d'eau
//                     if(grid[y+1][x].type == EMPTY_TYPE) // si la cellule de dessous est vide
//                     {
//                         grid[y+1][x].type = WATER_TYPE; // elle reçoit mon eau
//                         grid[y+1][x].fill_level = grid[y][x].fill_level; // avec la meme quantité

//                         grid[y][x].type = EMPTY_TYPE;  // moi je me vide
//                         grid[y][x].fill_level = 0.0f;

//                     }
//                     break;

//                 default:
//                     break;
//             }
//         }
//     }
// }

// void simulation_step(void)
// {
//     for(int y = ROWS - 2; y >= 0; y--) // -2 : car on regarde la cellule d'en dessous
//     {
//         for(int x = 0; x < COLUMNS; x++)
//         {
//             if(grid[y][x].type == WATER_TYPE) // je suis une cellule d'eau
//             {
//                 // on agis directement sur la cellule et non une copie (facilite la tache aulieu de faire grid[y][x] à chque fois)
//                 Cell *current_c = &grid[y][x];
//                 Cell *below_c = &grid[y+1][x];

//                 switch(current_c->type)
//                 {
//                     case EMPTY_TYPE: // si la cellule de dessous est vide, j'y met ma quantité d'eau et je me vide
//                         below_c->type = WATER_TYPE;
//                         below_c->fill_level = current_c->fill_level;
//                         current_c->type = EMPTY_TYPE;
//                         current_c->fill_level = 0.0f;
//                         break;

//                         // grid[y+1][x].type = WATER_TYPE;
//                         // grid[y+1][x].fill_level = grid[y][x].fill_level;
//                         // grid[y][x].type = EMPTY_TYPE;
//                         // grid[y][x].fill_level = 0.0f;
//                         // break;

//                     case WATER_TYPE:
//                     {
//                         // float below_capacity = 1.0 - below_c->fill_level; // Combien peut recevoir la cellule du dessous
//                         // float current_available = current_c->fill_level; // Combien peut donner la cellule du dessus

//                         // // La quantité réel transmis vers le bas est le minimum entre ce que le bas peut recevoir et ce que le haut peut donner
//                         // // Si below_capacity = 0; transfer = 0 => belew_c ne peut plus recevoir de flux
//                         // float transfert = (below_capacity < current_available) ? below_capacity : current_available;
//                         // if(transfert > 0.0f) //on ne transfère que si c'est positif()
//                         // {
//                         //     below_c->fill_level += transfert;
//                         //     current_c->fill_level -= transfert; // on retire ce qui a été pu transféré au dessous

//                         //     if(current_c->fill_level == 0.0f) // si la cellule courante est vide après transfert, on la marque comme vide
//                         //     {
//                         //         current_c->type = EMPTY_TYPE;
//                         //         current_c->fill_level = 0.0f;
//                         //     }
//                         // }

//                         // below_c->fill_level += current_c->fill_level;  // ajouter une partie de l'eau de dessous selon la disponibilté
//                         // current_c->fill_level -= below_capacity; // retiré cette partie d'eau à celui d'au dessous

//                         // double availability = 1 - grid[y+1][x].fill_level; // calculer le reste qu'il peut recevoir
//                         // grid[y+1][x].fill_level = grid[y+1][x].fill_level + availability; // // ajouter une partie de l'eau de dessous selon la disponibilté
//                         // grid[y][x].fill_level = grid[y][x].fill_level - availability; // retiré cette partie d'eau à celui d'au dessous
//                         // break;

//                         break;
//                     }

//                     default:
//                         break;
//                 }
//             }
//         }
//     }
// }

// void simulation_step(void)
// {
//     for(int y = ROWS - 2; y >= 0; y--)
//     {
//         for(int x = 0; x < COLUMNS; x++)
//         {
//             if(grid[y][x].type != WATER_TYPE)
//                 continue;

//             // Si la cellule du dessous est solide → bloqué
//             if(grid[y+1][x].type == SOLID_TYPE)
//                 continue;

//             // Assure que la cellule du dessous est de l'eau
//             if(grid[y+1][x].type == EMPTY_TYPE)
//             {
//                 grid[y+1][x].type = WATER_TYPE;
//                 grid[y+1][x].fill_level = 0.0f;
//             }

//             float current = grid[y][x].fill_level;
//             float below   = grid[y+1][x].fill_level;

//             // Calcul de la différence
//             float diff = current - below;

//             if(diff <= 0.0f)
//                 continue;

//             // Quantité à transférer (fraction)
//             float flow = diff * 0.5f;

//             // Limiter pour ne pas dépasser la capacité du dessous
//             float capacity = 1.0f - below;
//             if(flow > capacity)
//                 flow = capacity;

//             // Appliquer le transfert
//             grid[y][x].fill_level     -= flow;
//             grid[y+1][x].fill_level   += flow;

//             // Nettoyage si cellule vide
//             if(grid[y][x].fill_level <= 0.0f)
//             {
//                 grid[y][x].type = EMPTY_TYPE;
//                 grid[y][x].fill_level = 0.0f;
//             }
//         }
//     }
// }

// void simulation_step(void)
// {
//     // On parcourt la grille de bas en haut pour que l'eau tombe correctement
//     for(int y = ROWS - 2; y >= 0; y--) // -2 car on regarde la cellule juste en dessous
//     {
//         for(int x = 0; x < COLUMNS; x++)
//         {
//             // On ne s'intéresse qu'aux cellules contenant de l'eau
//             if(grid[y][x].type == WATER_TYPE)
//             {
//                 // On regarde la cellule du dessous
//                 Cell *current = &grid[y][x];
//                 Cell *below   = &grid[y+1][x];

//                 if(below->type == EMPTY_TYPE)
//                 {
//                     // Si la cellule en dessous est vide, on y met l'eau entière
//                     below->type = WATER_TYPE;
//                     below->fill_level = current->fill_level;

//                     current->type = EMPTY_TYPE;
//                     current->fill_level = 0.0f;
//                 }
//                 else if(below->type == WATER_TYPE)
//                 {
//                     // Si la cellule du dessous contient déjà de l'eau
//                     // Calculer la différence de niveau d'eau
//                     double diff = current->fill_level - below->fill_level;

//                     // Si le niveau du bas est plus élevé ou égal, pas de transfert
//                     if(diff <= 0.0f)
//                         continue;

//                     // Transférer **une partie seulement** de la différence pour la stabilité
//                     double flow = diff * 0.5; // facteur 0.5 = correction stable, pas d'oscillation

//                     // Ajuster les niveaux
//                     current->fill_level -= flow;
//                     below->fill_level   += flow;
//                 }

//                 // Les autres types (SOLID) ne reçoivent pas d'eau
//             }
//         }
//     }
// }

// void simulation_step(void)
// {
//     for(int y = ROWS - 2; y >= 0; y--) // -2 : car on regarde la cellule d'en dessous
//     {
//         for(int x = 0; x < COLUMNS; x++)
//         {
//             if(grid[y][x].type == WATER_TYPE) // je suis une cellule d'eau
//             {
//                 // on agis directement sur la cellule et non une copie (facilite la tache aulieu de faire grid[y][x] à chque fois)
//                 Cell *current_c = &grid[y][x];
//                 Cell *below_c = &grid[y+1][x];

//                 switch(grid[y][x].type)
//                 {
//                     case EMPTY_TYPE: // si la cellule de dessous es vide, j'y met ma quantité d'eau et je me vide
//                         grid[y+1][x].type = WATER_TYPE;
//                         grid[y+1][x].fill_level = grid[y][x].fill_level;
//                         grid[y][x].type = EMPTY_TYPE;
//                         grid[y][x].fill_level = 0.0f;
//                         break;

//                     case WATER_TYPE:
//                         double availability = 1 - grid[y+1][x].fill_level; // calculer le reste qu'il peut recevoir
//                         grid[y+1][x].fill_level = grid[y+1][x].fill_level + availability; // // ajouter une partie de l'eau de dessous selon la disponibilté
//                         grid[y][x].fill_level = grid[y][x].fill_level - availability; // retiré cette partie d'eau à celui d'au dessous
//                         break;

//                     default:
//                         break;
//                 }
//             }
//         }
//     }
// }


// ----------------------------------------------------------------------------------------

void water_cell(int x, int y)
{
    if(x < 0 || x >= COLUMNS || y < 0 || y >= ROWS) return;
    grid[y][x].type = WATER_TYPE;
    grid[y][x].fill_level = 1.0;
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
