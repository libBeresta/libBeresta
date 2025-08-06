/*
 * `libBeresta`
 *
 * minimal.c - Минимально возможный пример
 * =========
 *
 * Copyright (c) 2025 Dmitry Solomennikov
 *
 * Текст лиценции смотри в файле `ЛИЦЕНЗИЯ`
 */

/** en
  \par Minimal BRST program demo

  This is bare minimum program, creating PDF document.
  It creates \ref BRST_Doc object, adds \ref BRST_Page object into it,
  sets added page size and orientation and saves document to a file.

  Last action is to clean up everything.
*/

/** ru
  \par Минимальная демонстрационная программа библиотеки libBeresta.

  Минимально возможная программа для создания PDF-документа.
  Создается \ref BRST_Doc, в него добавляется объект \ref BRST_Page,
  устанавливаются размер и ориентация страницы и документ сохраняется.

  Последним действием все очищается.
*/

#include "brst.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char** argv)
{
    BRST_Doc pdf;
    BRST_Page page;
    char fname[256];

    strcpy(fname, argv[0]);
    strcat(fname, ".pdf");

    // Создание объекта документа
    pdf = BRST_Doc_New_Empty();
    if (!pdf) {
        printf("Error: cannot create Doc object\n");
        return 1;
    }

    // Добавление страницы
    page = BRST_Doc_Page_Add(pdf);

    // Настройка размера и ориентации страницы
    BRST_Page_SetSize(page, BRST_PAGE_SIZE_A4, BRST_PAGE_ORIENTATION_LANDSCAPE);

    // Сохранение документа в файл
    BRST_Doc_SaveToFile(pdf, fname);

    // Очистка
    BRST_Doc_Free(pdf);

    return 0;
}
