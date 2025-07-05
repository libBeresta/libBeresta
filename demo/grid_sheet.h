#ifndef __GRID_SHEET_H
#define __GRID_SHEET_H

#include "brst.h"

void print_grid(BRST_Doc pdf,
    BRST_Page page, BRST_UINT32 page_color, BRST_UINT32 page_lines_color);

// Цвета для оранжевой миллимитровой бумаги
#define BRST_ORANGE_FILL 0xFFDC9C
#define BRST_ORANGE_LINE 0xFFB836

#endif /* __GRID_SHEET_H */
