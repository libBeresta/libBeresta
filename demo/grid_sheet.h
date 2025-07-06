#ifndef __GRID_SHEET_H
#define __GRID_SHEET_H

#include "brst.h"

void print_grid(BRST_Doc pdf,
    BRST_Page page, BRST_UINT32 page_lines_color);

// Цвет линий оранжевой миллимитровой бумаги
#define BRST_ORANGE_LINE 0xFFB836

// Цвет линий синей миллимитровой бумаги
#define BRST_BLUE_LINE 0x77DDE7

// Цвет линий зеленой миллимитровой бумаги
#define BRST_GREEN_LINE 0x00FF7F

// Цвет линий коричневой миллимитровой бумаги
#define BRST_BROWN_LINE 0x734222

// Цвет линий черной миллимитровой бумаги
#define BRST_BLACK_LINE 0x181513

#endif /* __GRID_SHEET_H */
