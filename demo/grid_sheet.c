/*
 * `libBeresta`
 *
 * grid_sheet.c - Вспомогательный файл для примеров
 * ============
 *
 * Copyright (c) 2025 Dmitry Solomennikov
 *
 * Текст лиценции смотри в файле `ЛИЦЕНЗИЯ`
 */

#include "grid_sheet.h"
#include "brst.h"
#include "utils.h"
#include <setjmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_grid(BRST_Doc pdf, BRST_Page page)
{
    BRST_REAL height = BRST_Page_Height(page);
    BRST_REAL width  = BRST_Page_Width(page);
    BRST_Font font   = BRST_Doc_Font(pdf, "Helvetica", NULL);
    BRST_UINT x, y;

    BRST_Page_SetFontAndSize(page, font, 5);
    BRST_Page_SetGrayFill(page, 0.5);
    BRST_Page_SetGrayStroke(page, 0.8);

    // Добавление горизонтальных линий
    y = 0;
    while (y < height) {
        if (y % 10 == 0)
            BRST_Page_SetLineWidth(page, 0.5);
        else {
            if (BRST_Page_LineWidth(page) != 0.25)
                BRST_Page_SetLineWidth(page, 0.25);
        }

        BRST_Page_MoveTo(page, 0, y);
        BRST_Page_LineTo(page, width, y);
        BRST_Page_Stroke(page);

        if (y % 10 == 0 && y > 0) {
            BRST_Page_SetGrayStroke(page, 0.5);

            BRST_Page_MoveTo(page, 0, y);
            BRST_Page_LineTo(page, 5, y);
            BRST_Page_Stroke(page);

            BRST_Page_SetGrayStroke(page, 0.8);
        }

        y += 5;
    }

    // Добавление вертикальных линий
    x = 0;
    while (x < width) {
        if (x % 10 == 0)
            BRST_Page_SetLineWidth(page, 0.5);
        else {
            if (BRST_Page_LineWidth(page) != 0.25)
                BRST_Page_SetLineWidth(page, 0.25);
        }

        BRST_Page_MoveTo(page, x, 0);
        BRST_Page_LineTo(page, x, height);
        BRST_Page_Stroke(page);

        if (x % 50 == 0 && x > 0) {
            BRST_Page_SetGrayStroke(page, 0.5);

            BRST_Page_MoveTo(page, x, 0);
            BRST_Page_LineTo(page, x, 5);
            BRST_Page_Stroke(page);

            BRST_Page_MoveTo(page, x, height);
            BRST_Page_LineTo(page, x, height - 5);
            BRST_Page_Stroke(page);

            BRST_Page_SetGrayStroke(page, 0.8);
        }

        x += 5;
    }

    // Добавление горизонтальных надписей
    y = 0;
    while (y < height) {
        if (y % 10 == 0 && y > 0) {
            char buf[12];

            BRST_Page_BeginText(page);
            BRST_Page_MoveTextPos(page, 5, y - 2);
            BRST_snprintf(buf, 12, "%u", y);
            BRST_Page_ShowText(page, buf);
            BRST_Page_EndText(page);
        }

        y += 5;
    }

    // Добавление вертикальных надписей
    x = 0;
    while (x < width) {
        if (x % 50 == 0 && x > 0) {
            char buf[12];

            BRST_Page_BeginText(page);
            BRST_Page_MoveTextPos(page, x, 5);
            BRST_snprintf(buf, 12, "%u", x);
            BRST_Page_ShowText(page, buf);
            BRST_Page_EndText(page);

            BRST_Page_BeginText(page);
            BRST_Page_MoveTextPos(page, x, height - 10);
            BRST_Page_ShowText(page, buf);
            BRST_Page_EndText(page);
        }

        x += 5;
    }

    BRST_Page_SetGrayFill(page, 0);
    BRST_Page_SetGrayStroke(page, 0);
}
