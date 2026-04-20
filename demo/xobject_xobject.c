/*
 * `libBeresta`
 *
 * xobject_xobject.c - Создание и отображение 
 * вложенных объектов XObject Form
 * =================
 *
 * Copyright (c) 2025 Dmitry Solomennikov
 *
 * Текст лиценции смотри в файле `ЛИЦЕНЗИЯ`
 */

/** en
  \par Nested XObject Form creation and usage

  XObject Form object created, filled with drawing commands.
  Another one XObject Form is created and first one get called
  multiple times inside new one.

  Then second object is called within a page.
*/

/** ru
  \par Создание и отображение вложенных объектов XObject Form.

  Создается объект XObject, наполняется командами рисования,
  после этого создается второй объект, в котором первый многократно 
  вызывается. Второй объект уже отображается на странице.
*/

#include "brst.h"
#include <stdio.h>
#include <string.h>
#include "cli.h"

int main(int argc, char** argv)
{
    BRST_Doc pdf;
    BRST_Page page;

    char* fname = prepare_output(argc, argv);
    if (fname == NULL) {
        // Сообщение будет выведено в функции
        return 1;
    }

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

    // Подготовка положения объектов
    BRST_REAL width = BRST_Page_Width(page);
    BRST_REAL height = BRST_Page_Height(page);

    // Создание XObject Form
    BRST_XObject xobj = BRST_Doc_XObject_Create(pdf, 100, 100, 1, 1);

    // Получение и наполнение потока XObject (вложенный объект)
    BRST_Stream stream = BRST_XObject_Stream(xobj);
    BRST_Stream_Rectangle(stream, 0, 0, 100, 100);
    BRST_Stream_Stroke(stream);

    // Получение и наполнение потока XObject (внешний объект)
    BRST_XObject gxobj = BRST_Doc_XObject_Create(pdf, 200, 200, 1, 1);
    BRST_Stream gstream = BRST_XObject_Stream(gxobj);
    BRST_Dict_XObject_Execute(gxobj, xobj);
    BRST_Stream_Translate(gstream, 100, 100);
    BRST_Dict_XObject_Execute(gxobj, xobj);

    // Позиционирование и отображение внешнего XObject
    BRST_Page_Translate(page, width / 2 - 100, height / 2 - 100);
    BRST_Page_XObject_Execute(page, gxobj);

    // Позиционирование и отображение внешнего XObject на новой странице
    page = BRST_Doc_Page_Add(pdf);
    BRST_Page_SetSize(page, BRST_PAGE_SIZE_A4, BRST_PAGE_ORIENTATION_LANDSCAPE);
    BRST_Page_Translate(page, width / 2, height / 2);
    BRST_Page_RotateDeg(page, -45);
    BRST_Page_Translate(page, -100, -100);
    BRST_Page_XObject_Execute(page, gxobj);

    // Сохранение документа в файл
    BRST_Doc_SaveToFile(pdf, fname);

    // Очистка
    BRST_Doc_Free(pdf);

    return 0;
}
