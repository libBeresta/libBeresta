/*
 * `libBeresta`
 *
 * pattern.c - Демонстрация работы с узорами
 * =========
 *
 * Copyright (c) 2025 Dmitry Solomennikov
 *
 * Текст лиценции смотри в файле `ЛИЦЕНЗИЯ`
 */

/** en
  \par Pattern usage demo

  Patterns are important part of PDF.
  This demo shows pattern creation and selection.

  Pattern must have transformation matrix affecting 
  its appearance.
*/

/** ru
  \par Демонстрация работы с узорами libBeresta.

  Узоры (pattern) &ndash; важная часть работы с PDF.
  Пример показывает возможность создания и использования
  узоров в программе.
  При создании узора указывается матрица преобразования,
  влияющая на то, как узор будет в конечном итоге выглядеть.
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

    // Создание матрицы преобразования для узора
    BRST_Matrix matrix = BRST_Doc_Matrix_Scale(pdf, BRST_Doc_Matrix_Identity(pdf), 0.5, 0.5);

    // Создание узора
    BRST_Pattern pattern = BRST_Doc_Page_Pattern_Tiling_Create(pdf, page, 0, 0, 10, 10, 10, 10, matrix);
    // Получение потока, в который записываются графические команды
    // Здесь графические команды записываются не на страницу,
    // а в узор.
    BRST_Stream stream = BRST_Doc_Page_Pattern_Stream(pattern);

    BRST_Stream_SetLineWidth(stream, 0.49814);
    BRST_Stream_MoveTo(stream, -1,  4);
    BRST_Stream_LineTo(stream,  6, 11);
    BRST_Stream_MoveTo(stream,  4, -1);
    BRST_Stream_LineTo(stream, 11,  6);
    BRST_Stream_Stroke(stream);

    // Выбор узора для заливки.
    // Команда выбора узора составная, 
    // в ней указывается color space, цвет (для non-coloured patterns)
    // и имя узора. Функция BRST_Doc_Page_RGBPatternFill_Select() как
    // раз и выполняет всю указанную работу.
    BRST_Doc_Page_RGBPatternFill_Select(pdf, page, 1, 0, 0, pattern);

    // Расчет заливаемого прямоугольника
    BRST_REAL width = BRST_Page_Width(page);
    BRST_REAL height = BRST_Page_Height(page);

    BRST_REAL margin = 15*BRST_MM;

    // Отрисовка прямоугольника
    BRST_Page_Rectangle (page, margin, margin, width - margin*2, height - margin*2);
    // Поскольку ранее был выбран узор, то заливка
    // прямоугольника будет произведена при помощи узора.
    BRST_Page_Fill(page);

    // Удаление ранее созданной матрицы преобразования.
    // Технически это не требуется, финальная очистка высвободит
    // память, занимаемую матрицей, но мы можем "помочь" и высвободить
    // память раньше.
    BRST_Doc_Matrix_Free(matrix);

    // Сохранение документа в файл
    BRST_Doc_SaveToFile(pdf, fname);

    // Очистка
    BRST_Doc_Free(pdf);

    return 0;
}
