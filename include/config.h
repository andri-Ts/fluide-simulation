#ifndef CONFIG_H
#define CONFIG_H

#define SCREEN_WIDTH 900
#define SCREEN_HEIGHT 600

#define CELL_SIZE 50 // 15px
#define COLUMNS (SCREEN_WIDTH / CELL_SIZE) // nbr de colonne 900 / 15 = 60 col
#define ROWS (SCREEN_HEIGHT / CELL_SIZE)
#define LINE_WIDTH 2 //

typedef enum
{
    EMPTY_TYPE,
    WATER_TYPE,
    SOLID_TYPE
} CellType;

typedef struct Cell
{
    CellType type;
    float fill_level; // 0 à 1
    int x, y;
} Cell;

#endif
