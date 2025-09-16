/*
 * `libBeresta`
 *
 * minimal.c - Минимально возможный пример
 * =========
 *
 * Copyright (c) 2025 Dmitry Solomennikov
 *
 * Текст лицензии смотри в файле `ЛИЦЕНЗИЯ`
 */

/** en
  \par Multi-byte UTF-8 example.

  This is an UTF-8 example for multi-byte encoded text.
  It is important to have font with appropriate characters (Chinese in this example).
  <a href="https://fonts.google.com/noto/specimen/Noto+Sans">Noto Sans</a> font is used here.
*/

/** ru
  \par Пример многобайтного UTF-8 текста.

  Это пример использование многобайтного текста в кодировке UTF-8.
  Важно отметить, что в примере используется шрифт, содержащий все требуемые символы
  (в данном случае китайские и испанские).
  Используется шрифт <a href="https://fonts.google.com/noto/specimen/Noto+Sans">Noto Sans</a>.
*/
#include <stdio.h>
#include <string.h>
#include <setjmp.h>
#include "brst.h"
#include "handler.h"
#include "grid_sheet.h"

int
main (int argc, char **argv)
{
    BRST_Doc pdf;
    BRST_Page page;
    BRST_ExtGState gstate;
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

    // Подготовка миллиметровой бумаги
    print_grid(pdf, page, BRST_ROSE_LINE);

    BRST_Font font;
    const char *font_name;

    BRST_Doc_UseUTFEncodings(pdf);
    BRST_Doc_Encoder_SetCurrent(pdf, "UTF-8");
    font_name = BRST_Doc_TTFont_LoadFromFile(pdf, "../../data/fonts/PT/PT/PT-Astra-Serif/pt-astra-serif_regular.ttf", BRST_TRUE);
    font = BRST_Doc_Font(pdf, font_name, "UTF-8");
    BRST_Page_SetFontAndSize(page, font, 36);


    BRST_Page_GSave(page);
    gstate = BRST_Doc_Create_ExtGState(pdf);
    BRST_ExtGState_SetAlphaFill(gstate, 0.7);
    BRST_Page_SetExtGState(page, gstate);
    BRST_Page_SetRGBFillHex(page, 0x49A52C);

    BRST_Page_BeginText(page);

    BRST_Page_MoveTextPos(page, 100, BRST_Page_Height (page) - 100);
    BRST_Page_ShowText(page, "Привет, мир!");
    BRST_Page_MoveTextPos(page, 0, -100);
    BRST_Page_ShowText(page, "Peña, ¿cómo va, mundo?");

    // Ниже текст на китайском языке в кодировке UTF-8
    // Для его отображения необходимо использовать шрифт,
    // включающий соответствующие символы.
    // Например, Noto Sans.
    // Самостоятельно скачайте файл TTF шрифта со страницы
    // https://fonts.google.com/noto/specimen/Noto+Sans,
    // затем измените путь до TTF-файла в вызове функции
    // BRST_Doc_TTFont_LoadFromFile() выше в этом файле.

    // BRST_Page_MoveTextPos(page, 0, -100);
    // BRST_Page_ShowText(page, "你好，世界！");

    BRST_Page_EndText(page);
    BRST_Page_GRestore (page);

    // Сохранение документа в файл
    BRST_Doc_SaveToFile(pdf, fname);

    // Очистка
    BRST_Doc_Free(pdf);

    return 0;
}
