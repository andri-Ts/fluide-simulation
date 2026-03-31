#ifndef FLUIDE_H
#define FLUIDE_H

#include "config.h"

typedef struct Cell
{
    int type;
    int fill_level;
    int x;
    int y;
} Cell;

extern Cell grid[ROWS][COLUMNS]; // extern: déclaration → juste dire que la variable existe

#endif
