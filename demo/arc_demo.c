/*
 * `libBeresta`
 *
 * arc_demo.c - Примеры создания дуг
 * ==========
 *
 * Copyright (c) 2025 Dmitry Solomennikov
 *
 * Текст лиценции смотри в файле `ЛИЦЕНЗИЯ`
 */

/** ru
  \par Демонстрация дуг

  Этот пример показывает использование функций \ref BRST_Page_Arc() and
  BRST_Page_Circle().

  График в виде пирога создается с использованием заполненных сегментов
  окружности и центрального круга.
*/

/** en
  \par Arc demo

  This demo show BRST_Page_Arc() and BRST_Page_Circle() functions usage.

  Pie chart is created using filled circle segments and central circle.
*/

#include "brst.h"
#include "grid_sheet.h"
#include "handler.h"
#include <setjmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv)
{
    BRST_Doc pdf;
    BRST_Page page;
    char fname[256];
    BRST_Point pos;

    strcpy(fname, argv[0]);
    strcat(fname, ".pdf");

    pdf = BRST_Doc_New(demo_error_handler, NULL);
    if (!pdf) {
        printf("error: cannot create PdfDoc object\n");
        return 1;
    }

    if (setjmp(env)) {
        BRST_Doc_Free(pdf);
        return 1;
    }

    /* add a new page object. */
    page = BRST_Doc_Page_Add(pdf);

    BRST_Page_SetHeight(page, 220);
    BRST_Page_SetWidth(page, 200);

    /* draw grid to the page */
    print_grid(pdf, page);

    /* draw pie chart
     *
     *   A: 45% Red
     *   B: 25% Blue
     *   C: 15% green
     *   D: other yellow
     */

    /* A */
    BRST_Page_SetRGBFill(page, 1.0, 0, 0);
    BRST_Page_MoveTo(page, 100, 100);
    BRST_Page_LineTo(page, 100, 180);
    BRST_Page_Arc(page, 100, 100, 80, 0, 360 * 0.45);
    pos = BRST_Page_CurrentPos(page);
    BRST_Page_LineTo(page, 100, 100);
    BRST_Page_Fill(page);

    /* B */
    BRST_Page_SetRGBFill(page, 0, 0, 1.0);
    BRST_Page_MoveTo(page, 100, 100);
    BRST_Page_LineTo(page, pos.x, pos.y);
    BRST_Page_Arc(page, 100, 100, 80, 360 * 0.45, 360 * 0.7);
    pos = BRST_Page_CurrentPos(page);
    BRST_Page_LineTo(page, 100, 100);
    BRST_Page_Fill(page);

    /* C */
    BRST_Page_SetRGBFill(page, 0, 1.0, 0);
    BRST_Page_MoveTo(page, 100, 100);
    BRST_Page_LineTo(page, pos.x, pos.y);
    BRST_Page_Arc(page, 100, 100, 80, 360 * 0.7, 360 * 0.85);
    pos = BRST_Page_CurrentPos(page);
    BRST_Page_LineTo(page, 100, 100);
    BRST_Page_Fill(page);

    /* D */
    BRST_Page_SetRGBFill(page, 1.0, 1.0, 0);
    BRST_Page_MoveTo(page, 100, 100);
    BRST_Page_LineTo(page, pos.x, pos.y);
    BRST_Page_Arc(page, 100, 100, 80, 360 * 0.85, 360);
    pos = BRST_Page_CurrentPos(page);
    BRST_Page_LineTo(page, 100, 100);
    BRST_Page_Fill(page);

    /* draw center circle */
    BRST_Page_SetGrayStroke(page, 0);
    BRST_Page_SetGrayFill(page, 1);
    BRST_Page_Circle(page, 100, 100, 30);
    BRST_Page_Fill(page);

    /* save the document to a file */
    BRST_Doc_SaveToFile(pdf, fname);

    /* clean up */
    BRST_Doc_Free(pdf);

    return 0;
}
