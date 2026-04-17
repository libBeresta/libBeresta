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
  \par Minimal text BRST program demo

*/

/** ru
  \par Минимальная программа библиотеки libBeresta для вывода текста.

  Минимально возможная программа для создания PDF-документа.
  Создается \ref BRST_Doc, в него добавляется объект \ref BRST_Page,
  устанавливаются размер и ориентация страницы и документ сохраняется.

  Последним действием все очищается.
*/

#include "brst.h"
#include <stdio.h>
#include <string.h>

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

#if 1
    BRST_Doc_UseUTFEncodings(pdf);
    BRST_Doc_Encoder_SetCurrent(pdf, "UTF-8");

    // Последний параметр отвечает за встраивание шрифта внутрь файла.
    BRST_CSTR font_name = BRST_Doc_TTFont_LoadFromFile(pdf, "../../data/fonts/PT/PT/PT-Astra-Serif/pt-astra-serif_regular.ttf", BRST_TRUE);
    BRST_Font font = BRST_Doc_Font(pdf, font_name, "UTF-8");
#else
    BRST_Font font = BRST_Doc_Font(pdf, "Helvetica", NULL);
#endif

    // Вход в текстовый режим
    BRST_Page_BeginText(page);

    // Установка выбранного шрифта и размера для текста
    BRST_Page_SetFontAndSize(page, font, 20);

    // Отображение одной буквы
    BRST_Page_MoveTextPos(page, 0, 0);
    BRST_Page_ShowText(page, "W");

    // Выход из текстового режима
    BRST_Page_EndText(page);


    // Сохранение документа в файл
    BRST_Doc_SaveToFile(pdf, fname);

    // Очистка
    BRST_Doc_Free(pdf);

    return 0;
}
