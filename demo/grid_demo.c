#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <setjmp.h>
#include "brst.h"
#include "grid_sheet.h"
#include "handler.h"

int
main (int argc, char **argv)
{
    BRST_Doc  pdf;
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
    BRST_Page_SetSize(page, BRST_PAGE_SIZE_A4, BRST_PAGE_PORTRAIT);

    // Подготовка миллимитровой бумаги
    print_grid(pdf, page, BRST_GREEN_LINE);

    // Сохранение документа в файл
    BRST_Doc_SaveToFile(pdf, fname);

    // Очистка
    BRST_Doc_Free(pdf);

    return 0;
}
