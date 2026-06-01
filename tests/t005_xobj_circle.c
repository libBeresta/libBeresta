#include "brst.h"
#include <stdio.h>
#include <string.h>
#include "test_utils.h"

int main(int argc, char** argv)
{
    TEST_NAME("t005: Create circle inside XObject (check stream)");

    BRST_Doc pdf;
    BRST_Page page;
    char fname[256];

    strcpy(fname, argv[0]);
    strcat(fname, ".pdf");

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

    // Подготовка положения объектов
    BRST_REAL width = BRST_Page_Width(page);
    BRST_REAL height = BRST_Page_Height(page);

    // Создание XObject Form
    BRST_XObject xobj = BRST_Doc_XObject_New(pdf, 100, 100, 1, 1);

    // Получение и наполнение потока XObject
    BRST_Stream stream = BRST_XObject_Stream(xobj);
    BRST_Stream_Circle(stream, 50, 50, 49.5);
    BRST_Stream_Stroke(stream);

    // Позиционирование и отображение XObject
    BRST_Page_Translate(page, width / 2 - 50, height / 2 - 50);
    BRST_Page_XObject_Execute(page, xobj);

    // Сохранение документа в файл
    BRST_Doc_SaveToFile(pdf, fname);

    // Очистка
    BRST_Doc_Free(pdf);

    return 0;
}
