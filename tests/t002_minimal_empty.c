#define __STDC_WANT_LIB_EXT1__ 1
#include "brst.h"
#include <stdio.h>
#include <string.h>
#include "test_utils.h"

int main(int argc, char** argv)
{
    TEST_NAME("t002: Create minimal document");
    
    BRST_Doc pdf;
    BRST_Page page;
    char fname[FNAME_SIZE];

    BRST_snprintf(fname, FNAME_SIZE, "%s.pdf", argv[0]);

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

    // Сохранение документа в файл
    BRST_Doc_SaveToFile(pdf, fname);

    // Очистка
    BRST_Doc_Free(pdf);

    return 0;
}
