/**
  \par Minimal BRST program demo

  This is bare minimum program, creating PDF document.
  It creates \ref BRST_Doc object, adds \ref BRST_Page object into it,
  sets added page size and orientation and saves document to a file.

  Last action is to clean up everything.
*/
#include <stdio.h>
#include <string.h>
#include <setjmp.h>
#include "brst.h"
#include "handler.h"

int main(int argc, char** argv)
{
    BRST_Doc pdf;
    BRST_Page page;
    char fname[256];

    strcpy(fname, argv[0]);
    strcat(fname, ".pdf");

    /* create document object*/
    pdf = BRST_New(demo_error_handler, NULL);
    pdf = BRST_Doc_New(demo_error_handler, NULL);
    if (!pdf) {
        printf("error: cannot create PdfDoc object\n");
        return 1;
    }

    if (setjmp(env)) {
        BRST_Doc_Free(pdf);
        return 1;
    }

    /* add a new page object. */
    page = BRST_Doc_Page_Add(pdf);

    /* set up added page */
    BRST_Page_SetSize(page, BRST_PAGE_SIZE_A4, BRST_PAGE_LANDSCAPE);

    /* save document to a file */
    BRST_Doc_SaveToFile(pdf, fname);

    /* clean up */
    BRST_Doc_Free(pdf);

    return 0;
}
