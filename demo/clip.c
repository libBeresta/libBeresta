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
#include <stdio.h>
#include <string.h>

#define FNAME_BUFFER_SIZE 256

int main(int argc, char** argv)
{
    BRST_Doc pdf;
    BRST_Page page;

    char fname[FNAME_BUFFER_SIZE];
    char* pbuf = fname;
    char* eptr = fname + FNAME_BUFFER_SIZE - 1;

    pbuf = BRST_StrCopy(pbuf, argv[0], eptr);
    BRST_StrCopy(pbuf, ".pdf",  eptr);

    // Создание объекта документа
    pdf = BRST_Doc_New_Empty();
    if (!pdf) {
        printf("Error: cannot create Doc object\n");
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
