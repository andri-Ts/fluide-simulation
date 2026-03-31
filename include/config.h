#ifndef CONFIG_H
#define CONFIG_H

#define SCREEN_WIDTH 900
#define SCREEN_HEIGHT 600

#define CELL_SIZE 12 // 12px
#define COLUMNS (SCREEN_WIDTH / CELL_SIZE) // nbr de colonne
#define ROWS (SCREEN_HEIGHT / CELL_SIZE)
#define LINE_WIDTH 2 //

#define EMPTY_TYPE -1
#define WATER_TYPE 0
#define SOLID_TYPE 1

#endif
