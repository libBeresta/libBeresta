/*
 * `libBeresta`
 *
 * properties.c - Метаданные документа
 * ============
 *
 * Copyright (c) 2025 Dmitry Solomennikov
 *
 * Текст лицензии смотри в файле `ЛИЦЕНЗИЯ`
 */

/** en
  \par Document metadata setup

  In this example metadata fields are set:
  - Author
  - Creator
  - Producer
  - Title
  - Subject
  - Keywords

  In order to use encoded text in metadata fields one has to 
  turn on encoder usage with BRST_Doc_Use*() functions.

*/

/** ru
  \par Настройка метаданных документа

  В примере устанавливаются метаданные PDF-документа:
  - Author
  - Creator
  - Producer
  - Title
  - Subject
  - Keywords

  Для корректного отображения свойств необходимо включить использование кодировки,
  что делается вызовом функций BRST_Doc_Use*().

*/

#include "brst.h"
#include "handler.h"
#include <setjmp.h>
#include <stdio.h>
#include <string.h>

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

    BRST_Doc_UseUTFEncodings(pdf);
    BRST_Doc_Encoder_SetCurrent(pdf, "UTF-8");
    // Установка свойств документа
    BRST_Doc_SetInfoAttr(pdf, BRST_INFO_AUTHOR, "Автор / Author / Autor");
    BRST_Doc_SetInfoAttr(pdf, BRST_INFO_CREATOR, "Разработчик / Creator / Creador");
    BRST_Doc_SetInfoAttr(pdf, BRST_INFO_PRODUCER, "Продюсер / Producer / Productor");
    BRST_Doc_SetInfoAttr(pdf, BRST_INFO_TITLE, "Заголовок / Title / Título");
    BRST_Doc_SetInfoAttr(pdf, BRST_INFO_SUBJECT, "Тема / Subject / Asunto");
    BRST_Doc_SetInfoAttr(pdf, BRST_INFO_KEYWORDS, "Ключевые слова, Keywords, Palabras clave");

    // Сохранение документа в файл
    BRST_Doc_SaveToFile(pdf, fname);

    // Очистка
    BRST_Doc_Free(pdf);

    return 0;
}
