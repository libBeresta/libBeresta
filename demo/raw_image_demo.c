#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "brst.h"
#include "handler.h"

const BRST_BYTE RAW_IMAGE_DATA[128] = {
    0xff, 0xff, 0xff, 0xfe, 0xff, 0xff, 0xff, 0xfc,
    0xff, 0xff, 0xff, 0xf8, 0xff, 0xff, 0xff, 0xf0,
    0xf3, 0xf3, 0xff, 0xe0, 0xf3, 0xf3, 0xff, 0xc0,
    0xf3, 0xf3, 0xff, 0x80, 0xf3, 0x33, 0xff, 0x00,
    0xf3, 0x33, 0xfe, 0x00, 0xf3, 0x33, 0xfc, 0x00,
    0xf8, 0x07, 0xf8, 0x00, 0xf8, 0x07, 0xf0, 0x00,
    0xfc, 0xcf, 0xe0, 0x00, 0xfc, 0xcf, 0xc0, 0x00,
    0xff, 0xff, 0x80, 0x00, 0xff, 0xff, 0x00, 0x00,
    0xff, 0xfe, 0x00, 0x00, 0xff, 0xfc, 0x00, 0x00,
    0xff, 0xf8, 0x0f, 0xe0, 0xff, 0xf0, 0x0f, 0xe0,
    0xff, 0xe0, 0x0c, 0x30, 0xff, 0xc0, 0x0c, 0x30,
    0xff, 0x80, 0x0f, 0xe0, 0xff, 0x00, 0x0f, 0xe0,
    0xfe, 0x00, 0x0c, 0x30, 0xfc, 0x00, 0x0c, 0x30,
    0xf8, 0x00, 0x0f, 0xe0, 0xf0, 0x00, 0x0f, 0xe0,
    0xe0, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00,
    0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

int main(int argc, char **argv)
{
    BRST_Doc  pdf;
    BRST_Font font;
    BRST_Page page;
    char fname[256];
    BRST_Image image;

    BRST_REAL x, y;

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

    BRST_Doc_SetCompressionMode(pdf, BRST_COMP_ALL);

    // Подготовка шрифта для отображения текста примера
    font = BRST_Doc_Font(pdf, "Helvetica", NULL);

    // Добавление страницы
    page = BRST_Doc_Page_Add(pdf);

    // Настройка размера и ориентации страницы
    BRST_Page_SetSize(page, BRST_PAGE_SIZE_A4, BRST_PAGE_ORIENTATION_PORTRAIT);

    BRST_Page_BeginText(page);
    BRST_Page_SetFontAndSize(page, font, 20);
    BRST_Page_MoveTextPos(page, 220, BRST_Page_Height(page) - 70);
    BRST_Page_ShowText(page, "Raw Image Demo");
    BRST_Page_EndText(page);

    // Загрузка RGB изображений из файлов
    #ifndef __WIN32__
    image = BRST_Doc_Image_Raw_LoadFromFile(pdf, "rawimage/32_32_rgb.dat",
            32, 32, BRST_CS_DEVICE_RGB);
    #else
    image = BRST_Doc_Image_Raw_LoadFromFile(pdf, "rawimage\\32_32_rgb.dat",
            32, 32, BRST_CS_DEVICE_RGB);
    #endif

    x = 20;
    y = 20;

    // Отображение изображения на холсте
    BRST_Page_DrawImage(page, image, x, y, 32, 32);

    // Загрузка полутонового изображения из файла
    #ifndef __WIN32__
    image = BRST_Doc_Image_Raw_LoadFromFile(pdf, "rawimage/32_32_gray.dat",
            32, 32, BRST_CS_DEVICE_GRAY);
    #else
    image = BRST_Doc_Image_Raw_LoadFromFile(pdf, "rawimage\\32_32_gray.dat",
            32, 32, BRST_CS_DEVICE_GRAY);
    #endif

    x = 70;
    y = 20;

    // Отображение изображения на холсте
    BRST_Page_DrawImage(page, image, x, y, 32, 32);

    // Загрузка полутонового одно-битного изображения из памяти
    image = BRST_Doc_Image_Raw_LoadFromMem(pdf, RAW_IMAGE_DATA, 32, 32,
                BRST_CS_DEVICE_GRAY, 1);

    x = 120;
    y = 20;

    // Отображение изображения на холсте
    BRST_Page_DrawImage(page, image, x, y, 32, 32);

    // Сохранение документа в файл
    BRST_Doc_SaveToFile(pdf, fname);

    // Очистка
    BRST_Doc_Free(pdf);

    return 0;
}


