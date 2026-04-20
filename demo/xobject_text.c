/*
 * `libBeresta`
 *
 * xobject_text.c - Создание и отображение XObject Form
 * ==============
 *
 * Copyright (c) 2025 Dmitry Solomennikov
 *
 * Текст лиценции смотри в файле `ЛИЦЕНЗИЯ`
 */

/** en
  \par XObject Form Text usage


*/

/** ru
  \par Использование текста в XObject Form
*/

#include "brst.h"
#include "cli.h"
#include <stdio.h>
#include <string.h>

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

#if 1
    BRST_Doc_UseUTFEncodings(pdf);
    BRST_Doc_Encoder_SetCurrent(pdf, "UTF-8");
    BRST_CSTR font_name = BRST_Doc_TTFont_LoadFromFile(pdf, "../../data/fonts/PT/PT/PT-Astra-Serif/pt-astra-serif_regular.ttf", BRST_TRUE);
    BRST_Font font = BRST_Doc_Font(pdf, font_name, "UTF-8");
#else
    BRST_Font font = BRST_Doc_Font(pdf, "Helvetica", NULL);
#endif

    // Добавление страницы
    page = BRST_Doc_Page_Add(pdf);

    // Настройка размера и ориентации страницы
    BRST_Page_SetSize(page, BRST_PAGE_SIZE_A4, BRST_PAGE_ORIENTATION_LANDSCAPE);

    // Подготовка положения объектов
    BRST_REAL width = BRST_Page_Width(page);
    BRST_REAL height = BRST_Page_Height(page);

    // Создание XObject Form
    BRST_XObject xobj = BRST_Doc_XObject_Create(pdf, 100, 100, 1, 1);
    BRST_Dict_SetFontAndSize(xobj, font, 24);

    // Получение и наполнение потока XObject
    BRST_Stream stream = BRST_XObject_Stream(xobj);
    BRST_Stream_Rectangle(stream, 0, 0, 100, 100);
    //BRST_Stream_MoveTo(stream, 0, 0);
    //BRST_Stream_LineTo(stream, 100, 100);
    BRST_Stream_Stroke(stream);

    BRST_Stream_BeginText(stream);
                                           
    BRST_Stream_MoveTextPos(stream, 0, 0);
    BRST_Stream_ShowText(stream, font, "Ю");

    BRST_Stream_EndText(stream);

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
