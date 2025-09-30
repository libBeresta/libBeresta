/*
 * `libBeresta`
 *
 * xobject.c - Создание и отображение XObject Form
 * =========
 *
 * Copyright (c) 2025 Dmitry Solomennikov
 *
 * Текст лиценции смотри в файле `ЛИЦЕНЗИЯ`
 */

/** en
  \par XObject Form creation and usage

  XObject Form object created, filled with drawing commands
  and then object is shown multiple times.
*/

/** ru
  \par Создание и отображение XObject Form

  Создается объект XObject, наполняется командами рисования,
  после чего объект многократно отображается, в том числе
  на разных страницах.
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

    // Подготовка положения объектов
    BRST_REAL width = BRST_Page_Width(page);
    BRST_REAL height = BRST_Page_Height(page);

    // Создание XObject Form
    BRST_XObject xobj = BRST_Doc_XObject_Create(pdf, 100, 100, 1, 1);

    // Получение и наполнение потока XObject
    BRST_Stream stream = BRST_XObject_Stream(xobj);
    BRST_Stream_Rectangle(stream, 0, 0, 100, 100);
    BRST_Stream_Stroke(stream);

    // Позиционирование и отображение XObject
    BRST_Page_Translate(page, width / 2 - 50, height / 2 - 50);
    BRST_Page_XObject_Execute(page, xobj);

    // Позиционирование и отображение XObject на новой странице
    page = BRST_Doc_Page_Add(pdf);
    BRST_Page_SetSize(page, BRST_PAGE_SIZE_A4, BRST_PAGE_ORIENTATION_LANDSCAPE);
    BRST_Page_Translate(page, width / 2, height / 2);
    BRST_Page_RotateDeg(page, -45);
    BRST_Page_Translate(page, -50, -50);
    BRST_Page_XObject_Execute(page, xobj);

    // Сохранение документа в файл
    BRST_Doc_SaveToFile(pdf, fname);

    // Очистка
    BRST_Doc_Free(pdf);

    return 0;
}
