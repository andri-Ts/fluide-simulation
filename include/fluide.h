#ifndef FLUIDE_H
#define FLUIDE_H

#include "config.h"

void init_grid(void);
void simulation_step(void);

// Acces au grid via API
Cell get_cell(int y, int x);
// void set_cell(int y, int x, Cell c);

//Foncitons pour manipueler les cellules
void water_cell(int x, int y);
void solid_cell(int x, int y);
void remove_cell(int x, int y);

#endif
