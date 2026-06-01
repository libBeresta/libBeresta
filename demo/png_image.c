/*
 * `libBeresta`
 *
 * png_image.c - загрузка PNG изображения
 * ===========
 *
 * Copyright (c) 2026 Dmitry Solomennikov
 *
 * Текст лиценции смотри в файле `ЛИЦЕНЗИЯ`
 */

/** en
  \par PNG image load demo
*/

/** ru
  \par Демонстрация загрузки изображения формата PNG.
*/

#include "brst.h"
#include "handler.h"
#include "cli.h"
#include <setjmp.h>
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
    pdf = BRST_Doc_New(demo_error_handler, NULL);
    if (!pdf) {
        print_error("cannot create Doc object");
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

    #ifndef __WIN32__
    BRST_Image image = BRST_Doc_Image_Png_LoadFromFile(pdf, "../../img/beresta.png");
    #else
    BRST_Image image = BRST_Doc_Image_Png_LoadFromFile(pdf, "..\\..\\img\\beresta.png");
    #endif // __WIN32__

    double iw = BRST_Image_Width(image);
    double ih = BRST_Image_Height(image);

    // Отображение изображения на холсте
    BRST_Page_Image_Draw(page, image, 20*BRST_MM, 20*BRST_MM, iw, ih);

    // Сохранение документа в файл
    BRST_Doc_SaveToFile(pdf, fname);

    // Очистка
    BRST_Doc_Free(pdf);

    return 0;
}
