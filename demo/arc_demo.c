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

    // Создание объекта документа
    pdf = BRST_Doc_New(demo_error_handler, NULL);
    if (!pdf) {
        printf("Error: cannot create Doc object\n");
        return 1;
    }

    if (setjmp(env)) {
        BRST_Doc_Free(pdf);
        return 1;
    }

    // Добавление страницы
    page = BRST_Doc_Page_Add(pdf);

    // Настройка размера и ориентации страницы
    BRST_Page_SetSize(page, BRST_PAGE_SIZE_A4, BRST_PAGE_ORIENTATION_PORTRAIT);

    // Подготовка миллиметровой бумаги
    print_grid(pdf, page, BRST_ORANGE_LINE);

    // Отображение круговой диаграммы
    // A: 45% Красный
    // B: 25% Синий
    // C: 15% Зеленый
    // D: Другое

    BRST_REAL cx = BRST_Page_Width(page) / 2.0;
    BRST_REAL cy = BRST_Page_Height(page) / 2.0;
    BRST_REAL r  = BRST_Page_Width(page) / 3.0;

    // A
    BRST_Page_SetRGBFillHex(page, 0xC51D34);
    BRST_Page_MoveTo(page, cx, cy);
    BRST_Page_LineTo(page, cx, cx + r);
    BRST_Page_Arc(page, cx, cy, r, 0, 360 * 0.45);
    pos = BRST_Page_CurrentPos(page);
    BRST_Page_LineTo(page, cx, cy);
    BRST_Page_Fill(page);

    // B
    BRST_Page_SetRGBFillHex(page, 0x0047AB);
    BRST_Page_MoveTo(page, cx, cy);
    BRST_Page_LineTo(page, pos.x, pos.y);
    BRST_Page_Arc(page, cx, cy, r, 360 * 0.45, 360 * 0.7);
    pos = BRST_Page_CurrentPos(page);
    BRST_Page_LineTo(page, cx, cy);
    BRST_Page_Fill(page);

    // C
    BRST_Page_SetRGBFillHex(page, 0x20603D);
    BRST_Page_MoveTo(page, cx, cy);
    BRST_Page_LineTo(page, pos.x, pos.y);
    BRST_Page_Arc(page, cx, cy, r, 360 * 0.7, 360 * 0.85);
    pos = BRST_Page_CurrentPos(page);
    BRST_Page_LineTo(page, cx, cy);
    BRST_Page_Fill(page);

    // D
    BRST_Page_SetRGBFillHex(page, 0xFFDC33);
    BRST_Page_MoveTo(page, cx, cy);
    BRST_Page_LineTo(page, pos.x, pos.y);
    BRST_Page_Arc(page, cx, cy, r, 360 * 0.85, 360);
    pos = BRST_Page_CurrentPos(page);
    BRST_Page_LineTo(page, cx, cy);
    BRST_Page_Fill(page);

    // Отображение центральной окружности
    BRST_Page_SetGrayStroke(page, 0);
    BRST_Page_SetRGBFillHex(page, 0xF5FFFA);
    BRST_Page_Circle(page, cx, cy, r / 2.0);
    BRST_Page_Fill(page);

    // Сохранение документа в файл
    BRST_Doc_SaveToFile(pdf, fname);

    // Очистка
    BRST_Doc_Free(pdf);

    return 0;
}
