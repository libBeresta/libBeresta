/*
 * `libBeresta`
 *
 * dates.c - Метаданные документа (дата/время)
 * =========
 *
 * Copyright (c) 2025 Dmitry Solomennikov
 *
 * Текст лицензии смотри в файле `ЛИЦЕНЗИЯ`
 */

/** en
  \par Document date/time metadata setup

  In this example metadata fields are set:
  - Creation date
  - Modification date
*/

/** ru
  \par Настройка метаданных даты/времени документа

  В примере устанавливаются метаданные PDF-документа:
  - Дата создания
  - Дата изменения
*/

#include "brst.h"
#include "handler.h"
#include <setjmp.h>
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
    BRST_Page_SetSize(page, BRST_PAGE_SIZE_A4, BRST_PAGE_ORIENTATION_LANDSCAPE);

    // Создание даты (создания и модификации)
    BRST_Date date = BRST_Date_Now(pdf);

    BRST_Doc_SetInfoDateAttr(pdf, BRST_INFO_CREATION_DATE, date);
    BRST_Doc_SetInfoDateAttr(pdf, BRST_INFO_MOD_DATE, date);

    // Сохранение документа в файл
    BRST_Doc_SaveToFile(pdf, fname);

    // Очистка
    BRST_Doc_Free(pdf);

    return 0;
}
