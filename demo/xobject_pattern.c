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
    // Создание XObject Form
    BRST_XObject xobj = BRST_Doc_Page_XObject_Create(pdf, page, 100, 100, 1, 1);

    BRST_Matrix matrix = BRST_Doc_Matrix_Scale(pdf, BRST_Doc_Matrix_Identity(pdf), 0.5, 0.5);

    // Создание узора
    BRST_Pattern pattern = BRST_Doc_Page_Pattern_Tiling_Create(pdf, xobj, 0, 0, 10, 10, 10, 10, matrix);

    BRST_Stream pstream = BRST_Doc_Page_Pattern_Stream(pattern);

    //BRST_Doc_Page_Pattern_EnsureColorSpace(xobj, BRST_CS_DEVICE_RGB);

    BRST_Stream_SetLineWidth(pstream, 0.49814);
    BRST_Stream_MoveTo(pstream, -1,  4);
    BRST_Stream_LineTo(pstream,  6, 11);
    BRST_Stream_MoveTo(pstream,  4, -1);
    BRST_Stream_LineTo(pstream, 11,  6);
    BRST_Stream_Stroke(pstream);

    // Выбор узора для заливки.
    // Команда выбора узора составная, 
    // в ней указывается color space, цвет (для non-coloured patterns)
    // и имя узора. Функция BRST_Doc_Page_RGBPatternFill_Select() как
    // раз и выполняет всю указанную работу.

    // Отрисовка прямоугольника
//    BRST_Page_Rectangle (xobj, margin, margin, width - margin*2, height - margin*2);
    // Поскольку ранее был выбран узор, то заливка
    // прямоугольника будет произведена при помощи узора.
//    BRST_Page_Fill(page);



    // Получение и наполнение потока XObject
    BRST_Stream stream = BRST_XObject_Stream(xobj);

    BRST_Doc_Dict_RGBPatternFill_Select(pdf, xobj, 1, 0, 0, pattern);

    BRST_Stream_Rectangle(stream, 20, 20, 80, 80);
    BRST_Stream_Fill(stream);
    
//    BRST_Stream_MoveTo(stream, 0, 0);
//    BRST_Stream_LineTo(stream, 100, 100);
//    BRST_Stream_Stroke(stream);

    // Позиционирование и отображение XObject
    BRST_Page_Translate(page, 50, 50);
    BRST_Page_XObject_Execute(page, xobj);

    // Позиционирование и отображение XObject на новой странице
    page = BRST_Doc_Page_Add(pdf);
    BRST_Page_SetSize(page, BRST_PAGE_SIZE_A4, BRST_PAGE_ORIENTATION_LANDSCAPE);
    BRST_Page_Translate(page, 200, 110);
    BRST_Page_XObject_Execute(page, xobj);

    // Сохранение документа в файл
    BRST_Doc_SaveToFile(pdf, fname);

    // Очистка
    BRST_Doc_Free(pdf);

    return 0;
}
