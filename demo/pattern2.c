/*
 * `libBeresta`
 *
 * pattern2.c - Несколько узоров на странице
 * ==========
 *
 * Copyright (c) 2025 Dmitry Solomennikov
 *
 * Текст лиценции смотри в файле `ЛИЦЕНЗИЯ`
 */

/** en
  \par Multiple patterns per page demo

*/

/** ru
  \par Демонстрация использования нескольких узоров на одной странице.

*/

#include "brst.h"
#include "handler.h"
#include <setjmp.h>
#include <stdio.h>
#include <string.h>

BRST_Pattern createPattern(BRST_Doc pdf, BRST_Page page, BRST_REAL degrees, BRST_REAL scale) {
    // Подготовка матрицы преобразования
    BRST_Matrix matrix = BRST_Doc_Matrix_RotateDeg(pdf, BRST_Doc_Matrix_Scale(pdf, BRST_Doc_Matrix_Identity(pdf), scale, scale), degrees);

    // Создание узора
    BRST_Pattern pattern = BRST_Doc_Page_Pattern_Tiling_Create(pdf, page, 0, 0, 10, 10, 10, 10, matrix);
    BRST_Stream stream = BRST_Doc_Page_Pattern_Stream(pattern);

    // Наполнение узора
    BRST_Stream_SetLineWidth(stream, 0.49814);
    BRST_Stream_MoveTo(stream, -1,  4);
    BRST_Stream_LineTo(stream,  6, 11);
    BRST_Stream_MoveTo(stream,  4, -1);
    BRST_Stream_LineTo(stream, 11,  6);
    BRST_Stream_Stroke(stream);

    return pattern;
}

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

    // Расчет заливаемых прямоугольников
    BRST_REAL width = BRST_Page_Width(page);
    BRST_REAL height = BRST_Page_Height(page);

    BRST_REAL margin = 15*BRST_MM;

    BRST_REAL rectWidth = ((width - margin * 2) / 3);
    BRST_REAL rectHeight = (height - margin * 2);

    // Подготовка узоров (разный масштаб и наклон)
    BRST_Pattern p1 = createPattern(pdf, page,  0, 1.0);
    BRST_Pattern p2 = createPattern(pdf, page,  0, 0.2);
    BRST_Pattern p3 = createPattern(pdf, page, 70, 1.7);

    // Отрисовка отдельных прямоугольников с заливкой узорами
    BRST_Page_GSave(page);
    BRST_Doc_Page_RGBPatternFill_Select(pdf, page, 1, 0, 0, p1);
    BRST_Page_Rectangle (page, margin, margin, rectWidth, margin + rectHeight);
    BRST_Page_Fill(page);
    BRST_Page_GRestore(page);

    BRST_Page_GSave(page);
    BRST_Doc_Page_RGBPatternFill_Select(pdf, page, 0, 1, 0, p2);
    BRST_Page_Rectangle (page, margin + rectWidth, margin, rectWidth, margin + rectHeight);
    BRST_Page_Fill(page);
    BRST_Page_GRestore(page);

    BRST_Page_GSave(page);
    BRST_Doc_Page_RGBPatternFill_Select(pdf, page, 0, 0, 1, p3);
    BRST_Page_Rectangle (page, margin + rectWidth * 2, margin, rectWidth, margin + rectHeight);
    BRST_Page_Fill(page);
    BRST_Page_GRestore(page);

    // Сохранение документа в файл
    BRST_Doc_SaveToFile(pdf, fname);

    // Очистка
    BRST_Doc_Free(pdf);

    return 0;
}
