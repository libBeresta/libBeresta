/*
 * `libBeresta`
 *
 * circle.c - Построение окружности
 * ========
 *
 * Copyright (c) 2025 Dmitry Solomennikov
 *
 * Текст лиценции смотри в файле `ЛИЦЕНЗИЯ`
 */

/** en
  \par Circle construction from several Bézier curves. 
*/

/** ru
  \par Построение окружности с помощью кривых Безье.
  За основу взято предварительно рассчитанное значение положения контрольных точек на кривой.
*/

#include "brst.h"
#include <stdio.h>
#include <string.h>

void circle(BRST_Page page, BRST_REAL x, BRST_REAL y, BRST_REAL radius) {
    BRST_REAL a = 0.552284749830793 * radius;

    BRST_REAL xpr = x + radius;
    BRST_REAL ypr = y + radius;
    BRST_REAL xmr = x - radius;
    BRST_REAL ymr = y - radius;

    BRST_REAL xpa = x + a;
    BRST_REAL ypa = y + a;
    BRST_REAL xma = x - a;
    BRST_REAL yma = y - a;

    BRST_Page_MoveTo(page,  xpr, y);
    BRST_Page_CurveTo(page, xpr, ypa, xpa, ypr, x, ypr);
    BRST_Page_CurveTo(page, xma, ypr, xmr, ypa, xmr, y);
    BRST_Page_CurveTo(page, xmr, yma, xma, ymr, x, ymr);
    BRST_Page_CurveTo(page, xpa, ymr, xpr, yma, xpr, y);
    BRST_Page_ClosePath(page);
} 

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
    BRST_Page_SetSize(page, BRST_PAGE_SIZE_A4, BRST_PAGE_ORIENTATION_LANDSCAPE);

    BRST_REAL width = BRST_Page_Width(page);
    BRST_REAL height = BRST_Page_Height(page);

    // Отрисовка окружности с помощью расчета
    circle(page, width/2, height/2, height/6);
    BRST_Page_Stroke(page);

    BRST_Page_SetRGBStrokeHex(page, 0xFF00FF);
    // Отрисовка окружности с помощью готовой функции
    // (внутри там тот же самый расчет, но это уже часть библиотеки)
    BRST_Page_Circle(page, width/2, height/2, height/3);
    BRST_Page_LineTo(page, 300, 500);
    BRST_Page_Stroke(page);

    // Сохранение документа в файл
    BRST_Doc_SaveToFile(pdf, fname);

    // Очистка
    BRST_Doc_Free(pdf);

    return 0;
}
