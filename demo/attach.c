/**
  \par Attach demo

  This demo shows HPDF_AttachFile() function and ability to include files into resulting PDF document.
  Application expects file `pngsuite/basn3p08.png` next to binary.

  One can see attachment in Adobe Reader or in Firefox browser.
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <setjmp.h>
#include "brst.h"
#include "handler.h"

const char *text = "This PDF should have an attachment named basn3p08.png";

int
main (int argc, char **argv)
{
    BRST_Doc  pdf;
    BRST_Page page;
    char fname[256];

    strcpy(fname, argv[0]);
    strcat(fname, ".pdf");

    pdf = BRST_Doc_New(demo_error_handler, NULL);
    if (!pdf) {
        printf ("error: cannot create PdfDoc object\n");
        return 1;
    }

    if (setjmp(env)) {
        BRST_Doc_Free(pdf);
        return 1;
    }

    // Подготовка шрифта для отображения текста о вложении
    BRST_Font font = BRST_Doc_Font(pdf, "Helvetica", NULL);

    // Добавление страницы
    page = BRST_Doc_Page_Add(pdf);

    BRST_Page_SetSize(page, BRST_PAGE_SIZE_A4, BRST_PAGE_ORIENTATION_PORTRAIT);

    BRST_Page_BeginText(page);
    BRST_Page_SetFontAndSize(page, font, 20);
    BRST_REAL tw = BRST_Page_TextWidth(page, text);
    BRST_Page_MoveTextPos(page, 
        (BRST_Page_Width(page) - tw) / 2,
        (BRST_Page_Height(page) - 20) / 2);
    BRST_Page_ShowText(page, text);
    BRST_Page_EndText(page);

    /* Вложение файла в документ */
    BRST_Doc_AttachFile(pdf, "../../data/images/pngsuite/basn3p08.png");

    // Сохранение документа в файл
    BRST_Doc_SaveToFile(pdf, fname);

    // Очистка
    BRST_Doc_Free(pdf);

    return 0;
}
