#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <setjmp.h>
#include "brst.h"
#include "grid_sheet.h"
#include "handler.h"
#include "cli.h"

int
main (int argc, char **argv)
{
    BRST_Doc  pdf;
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
    BRST_Page_SetSize(page, BRST_PAGE_SIZE_A4, BRST_PAGE_ORIENTATION_PORTRAIT);

    // Подготовка миллиметровой бумаги
    print_grid(pdf, page, BRST_GREEN_LINE);

    // Сохранение документа в файл
    BRST_Doc_SaveToFile(pdf, fname);

    // Очистка
    BRST_Doc_Free(pdf);

    return 0;
}
