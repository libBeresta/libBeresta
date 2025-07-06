/*
 * `libBeresta`
 *
 * grid_sheet.c - Вспомогательный файл для примеров
 * ============
 *
 * Copyright (c) 2025 Dmitry Solomennikov
 *
 * Текст лиценции смотри в файле `ЛИЦЕНЗИЯ`
 */

#include "grid_sheet.h"
#include "brst.h"
#include "utils.h"
#include <setjmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_grid(BRST_Doc pdf, BRST_Page page, BRST_UINT32 page_lines_color)
{
    // Рисуем миллиметровую сетку для листа формата A4 портретной ориентации.
    BRST_Page_SetSize(page, BRST_PAGE_SIZE_A4, BRST_PAGE_PORTRAIT);

    BRST_REAL l01mm = 0.04 * BRST_MM;
    BRST_REAL l05mm = 0.10 * BRST_MM;
    BRST_REAL l10mm = 0.15 * BRST_MM;
    BRST_REAL l50mm = 0.30 * BRST_MM;

    BRST_UINT i = 0;

    // Сохранение состояния для сдвига
    BRST_Page_GSave(page);

    BRST_REAL w = BRST_Page_Width(page);
    BRST_REAL h = BRST_Page_Height(page);

    BRST_Page_Translate(page, (w - 190 * BRST_MM) / 2, (h - 280 * BRST_MM) / 2);

    // Цвета линий миллиметровой бумаги
    BRST_Page_SetRGBStrokeHex(page, page_lines_color);

    // Горизонтальные линии
    // ====================

    // Шаг в 1 миллиметр
    BRST_Page_SetLineWidth(page, l01mm);
    while (i < 280) {
        if ((i % 5 != 0) && (i % 10 != 0) && (i % 50 != 0)) {
            BRST_Page_MoveTo(page, 0 * BRST_MM, (280 - i) * BRST_MM);
            BRST_Page_LineTo(page, 190 * BRST_MM, (280 - i) * BRST_MM);
        }
        i++;
    }
    BRST_Page_Stroke(page);

    // Шаг в 5 миллиметров
    BRST_Page_SetLineWidth(page, l05mm);
    i = 0;
    while (i < 280) {
        if ((i % 10 != 0) && (i % 50 != 0)) {
            BRST_Page_MoveTo(page, 0 * BRST_MM, (280 - i) * BRST_MM);
            BRST_Page_LineTo(page, 190 * BRST_MM, (280 - i) * BRST_MM);
        }
        i += 5;
    }
    BRST_Page_Stroke(page);

    // Шаг в 10 миллиметров
    BRST_Page_SetLineWidth(page, l10mm);
    i = 0;
    while (i < 280) {
        if (i % 50 != 0) {
            BRST_Page_MoveTo(page, 0 * BRST_MM, (280 - i) * BRST_MM);
            BRST_Page_LineTo(page, 190 * BRST_MM, (280 - i) * BRST_MM);
        }
        i += 10;
    }
    BRST_Page_Stroke(page);

    // Шаг в 50 миллиметров
    BRST_Page_SetLineWidth(page, l50mm);
    i = 0;
    while (i < 280) {
        BRST_Page_MoveTo(page, 0 * BRST_MM, (280 - i) * BRST_MM);
        BRST_Page_LineTo(page, 190 * BRST_MM, (280 - i) * BRST_MM);
        i += 50;
    }
    BRST_Page_Stroke(page);

    // Вертикальные линии
    // ==================

    // Шаг в 1 миллиметр
    BRST_Page_SetLineWidth(page, l01mm);
    i = 0;
    while (i < 190) {
        if ((i % 5 != 0) && (i % 10 != 0) && (i % 50 != 0)) {
            BRST_Page_MoveTo(page, i * BRST_MM, 0 * BRST_MM);
            BRST_Page_LineTo(page, i * BRST_MM, 280 * BRST_MM);
        }
        i++;
    }
    BRST_Page_Stroke(page);

    // Шаг в 5 миллиметров
    BRST_Page_SetLineWidth(page, l05mm);
    i = 0;
    while (i < 190) {
        if ((i % 10 != 0) && (i % 50 != 0)) {
            BRST_Page_MoveTo(page, i * BRST_MM, 0 * BRST_MM);
            BRST_Page_LineTo(page, i * BRST_MM, 280 * BRST_MM);
        }
        i += 5;
    }
    BRST_Page_Stroke(page);

    // Шаг в 10 миллиметров
    BRST_Page_SetLineWidth(page, l10mm);
    i = 0;
    while (i < 190) {
        if (i % 50 != 0) {
            BRST_Page_MoveTo(page, i * BRST_MM, 0 * BRST_MM);
            BRST_Page_LineTo(page, i * BRST_MM, 280 * BRST_MM);
        }
        i += 10;
    }
    BRST_Page_Stroke(page);

    // Шаг в 50 миллиметров
    BRST_Page_SetLineWidth(page, l50mm);
    i = 0;
    while (i < 190) {
        BRST_Page_MoveTo(page, i * BRST_MM, 0 * BRST_MM);
        BRST_Page_LineTo(page, i * BRST_MM, 280 * BRST_MM);
        i += 50;
    }
    BRST_Page_Stroke(page);

    // Прямоугольник вокруг миллимитровой сетки
    BRST_Page_Rectangle(page, 0, 0, 190 * BRST_MM, 280 * BRST_MM);
    BRST_Page_Stroke(page);

    // Отображение текста версии библиотеки
    // Подготовка шрифта для отображения текста версии библиотеки
    BRST_Font font = BRST_Doc_Font(pdf, "Helvetica", NULL);

    // Вход в текстовый режим
    BRST_Page_BeginText(page);

    // Установка выбранного шрифта и размера для текста
    BRST_Page_SetFontAndSize(page, font, 4);

    // Подготовка буфера для строки версии
    char buf[256];
    BRST_snprintf(buf, 256, "%s %s", BRST_LIBRARY_NAME, BRST_VERSION_TEXT);

    // Цвет текста версии библиотеки
    BRST_Page_SetRGBFillHex(page, page_lines_color);

    // Отображение текста версии библиотеки
    BRST_Page_TextRect(page,
        0, 0, 190 * BRST_MM, -10 * BRST_MM,
        buf, BRST_TALIGN_RIGHT, NULL);

    // Выход из текстового режима
    BRST_Page_EndText(page);

    // Восстановление состояния после после сдвига
    BRST_Page_GRestore(page);
}
