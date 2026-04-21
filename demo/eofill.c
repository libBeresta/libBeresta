/*
 * `libBeresta`
 *
 * eofill.c - Демонстрация eofill заливки
 * ========
 *
 * Copyright (c) 2025 Dmitry Solomennikov
 *
 * Текст лиценции смотри в файле `ЛИЦЕНЗИЯ`
 */

/** en
  \par Minimal BRST program demo
*/

/** ru
  \par Демонстрация заливки с правилом even-odd.
*/

#include "brst.h"
#include "grid_sheet.h"
#include "handler.h"
#include "cli.h"
#include <setjmp.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char** argv)
{
    BRST_Doc pdf;
    BRST_Page page;

    char* fname = prepare_output(argc, argv);
    if (fname == NULL) {
        print_error("file name too long");
        return 1;
    }

    // Создание объекта документа
    pdf = BRST_Doc_New(demo_error_handler, NULL);
    if (!pdf) {
        print_error("cannot create Doc object");
        return 1;
    }

    if (setjmp(env)) {
        BRST_Doc_Free(pdf);
        return 1;
    }

    // Добавление страницы
    page = BRST_Doc_Page_Add(pdf);

    // Настройка размера и ориентации страницы
//    BRST_Page_SetSize(page, BRST_PAGE_SIZE_A4, BRST_PAGE_ORIENTATION_LANDSCAPE);

    // Подготовка миллиметровой бумаги
    print_grid(pdf, page, BRST_ORANGE_LINE);
    // Подготовка положения объектов
    BRST_REAL width = BRST_Page_Width(page);
    BRST_REAL height = BRST_Page_Height(page);

    // Перемещение того, что создается ниже, на середину страницы
    BRST_Page_Translate(page, 0, height / 2);

    // Размер прямоугольника
    BRST_REAL margin = BRST_MM * 15;

    // Отрисовка большого прямоугольника
    BRST_Page_MoveTo(page, height, 0);
    BRST_Page_LineTo(page, width, 0);
    BRST_Page_LineTo(page, width, margin);
    BRST_Page_LineTo(page, 0, margin);
    BRST_Page_LineTo(page, 0, 0);

    // Отрисовка "отверстия"
    BRST_Page_MoveTo(page, width / 2 - 100, margin / 2 - 10);
    BRST_Page_LineTo(page, width / 2 + 100, margin / 2 - 10);
    BRST_Page_LineTo(page, width / 2 + 100, margin / 2 + 10);
    BRST_Page_LineTo(page, width / 2 - 100, margin / 2 + 10);
    BRST_Page_LineTo(page, width / 2 - 100, margin / 2 - 10);

    BRST_Page_ClosePath(page);

    // Заливка по правилу Even-odd
    BRST_Page_Eofill(page);

    // Сохранение документа в файл
    BRST_Doc_SaveToFile(pdf, fname);

    // Очистка
    BRST_Doc_Free(pdf);

    return 0;
}
