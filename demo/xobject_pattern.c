/*
 * `libBeresta`
 *
 * xobject_pattern.c - Создание и отображение узора внутри XObject Form
 * =================
 *
 * Copyright (c) 2025 Dmitry Solomennikov
 *
 * Текст лиценции смотри в файле `ЛИЦЕНЗИЯ`
 */

/** en
  \par XObject Form with pattern creation and usage

  XObject Form object created, filled with drawing commands,
  including pattern fill and then object is shown multiple times.
*/

/** ru
  \par Создание и отображение узора внутри XObject Form

  Создается объект XObject, наполняется командами рисования,
  включающие в себя формирование узора.
  после чего объект многократно отображается, в том числе
  на разных страницах.
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
    BRST_Page_SetSize(page, BRST_PAGE_SIZE_A4, BRST_PAGE_ORIENTATION_LANDSCAPE);

    // Подготовка положения объекта
    BRST_REAL width = BRST_Page_Width(page);
    BRST_REAL height = BRST_Page_Height(page);

    // Создание XObject Form
    BRST_XObject xobj = BRST_Doc_XObject_Create(pdf, 100, 100, 1, 1);

    // Матрица преобразований для узора
    BRST_Matrix matrix = BRST_Doc_Matrix_Scale(pdf, BRST_Doc_Matrix_Identity(pdf), 0.5, 0.5);

    // Создание узора
    BRST_Pattern pattern = BRST_Doc_Pattern_Tiling_Create(pdf, 0, 0, 10, 10, 10, 10, matrix);

    // Поток узора (нужен для записи графических команд
    BRST_Stream pattern_stream = BRST_Doc_Pattern_Stream(pattern);

    // Графические команды узора
    BRST_Stream_SetLineWidth(pattern_stream, 0.49814);
    BRST_Stream_MoveTo(pattern_stream, -1,  4);
    BRST_Stream_LineTo(pattern_stream,  6, 11);
    BRST_Stream_MoveTo(pattern_stream,  4, -1);
    BRST_Stream_LineTo(pattern_stream, 11,  6);
    BRST_Stream_Stroke(pattern_stream);

    // Получение и наполнение потока XObject
    BRST_Stream stream = BRST_XObject_Stream(xobj);

    // Команда выбора узора составная,
    // в ней указывается color space, цвет (для non-coloured patterns)
    // и имя узора. Функция BRST_Doc_Dict_RGBPatternFill_Select() как
    // раз и выполняет всю указанную работу.
    BRST_Doc_Dict_RGBPatternFill_Select(pdf, xobj, 1, 0, 0, pattern);

    // Отрисовка прямоугольника внутри XObject
    BRST_Stream_Rectangle(stream, 20, 20, 80, 80);
    BRST_Stream_Fill(stream);
    
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
