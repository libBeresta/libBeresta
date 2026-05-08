/*
 * `libBeresta`
 *
 * clip.c - Пример использования отсечения
 * ======
 *
 * Copyright (c) 2025 Dmitry Solomennikov
 *
 * Текст лицензии смотри в файле `ЛИЦЕНЗИЯ`
 */

/** en
  \par Clipping demo program
*/

/** ru
  \par Демонстрация отсечения
  Вызов BRST_Page_EndPath() является обязательным.
*/

#include "brst.h"
#include "grid_sheet.h"
#include "cli.h"
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
    pdf = BRST_Doc_New_Empty();
    if (!pdf) {
        print_error("cannot create Doc object");
        return 1;
    }

    // Добавление страницы
    page = BRST_Doc_Page_Add(pdf);

    // Настройка размера и ориентации страницы
    BRST_Page_SetSize(page, BRST_PAGE_SIZE_A4, BRST_PAGE_ORIENTATION_PORTRAIT);

    // Подготовка положения объектов
    BRST_REAL width = BRST_Page_Width(page);
    BRST_REAL height = BRST_Page_Height(page);
    BRST_REAL margin = BRST_MM * 15;

    // Установка окна отсечения
    BRST_Page_MoveTo(page, 0, height / 2 - margin);
    BRST_Page_LineTo(page, width, height / 2);
    BRST_Page_LineTo(page, width, height / 2 + margin);
    BRST_Page_LineTo(page, 0, height / 2);
    BRST_Page_Clip(page);
    BRST_Page_EndPath(page);

    // Подготовка миллиметровой бумаги
    print_grid(pdf, page, BRST_ORANGE_LINE);

    // Сохранение документа в файл
    BRST_Doc_SaveToFile(pdf, fname);

    // Очистка
    BRST_Doc_Free(pdf);

    return 0;
}
