#define __STDC_WANT_LIB_EXT1__ 1
#include "brst.h"
#include <stdio.h>
#include <string.h>
#include "test_utils.h"

int main(int argc, char** argv)
{
    TEST_NAME("t004: Create circle");
    
    BRST_Doc pdf;
    BRST_Page page;
    char fname[FNAME_SIZE];

    // TODO переработать и убрать в общее место
    int res = strcpy_s(fname, FNAME_SIZE, argv[0]);

    if (res != 0) {
        printf("Error: cannot prepare filename\n");
        return 1;
    }

    res = strcat_s(fname, FNAME_SIZE, ".pdf");
    if (res != 0) {
        printf("Error: cannot append '.pdf' to filename\n");
        return 1;
    }

    // Создание объекта документа
    pdf = BRST_Doc_New_Empty();
    if (!pdf) {
        printf("Error: cannot create Doc object\n");
        return 1;
    }

    // Добавление страницы
    page = BRST_Doc_Page_Add(pdf);

    // Настройка размера и ориентации страницы
    BRST_Page_SetSize(page, BRST_PAGE_SIZE_A4, BRST_PAGE_ORIENTATION_PORTRAIT);

    BRST_REAL width = BRST_Page_Width(page);
    BRST_REAL height = BRST_Page_Height(page);

    BRST_Page_SetRGBStrokeHex(page, 0xFF00FF);
    BRST_Page_Circle(page, width/2, height/2, height/3);
    BRST_Page_Stroke(page);

    // Сохранение документа в файл
    BRST_Doc_SaveToFile(pdf, fname);

    // Очистка
    BRST_Doc_Free(pdf);

    return 0;
}
