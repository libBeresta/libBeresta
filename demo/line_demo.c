/*
 * << Haru Free PDF Library 2.0.0 >> -- line_demo.c
 *
 * Copyright (c) 1999-2006 Takeshi Kanno <takeshi_kanno@est.hi-ho.ne.jp>
 *
 * Permission to use, copy, modify, distribute and sell this software
 * and its documentation for any purpose is hereby granted without fee,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear
 * in supporting documentation.
 * It is provided "as is" without express or implied warranty.
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "brst.h"
#include "handler.h"

void
draw_line  (BRST_Page    page,
            float        x,
            float        y,
            const char  *label)
{
    BRST_Page_BeginText (page);
    BRST_Page_MoveTextPos (page, x, y - 10);
    BRST_Page_ShowText (page, label);
    BRST_Page_EndText (page);

    BRST_Page_MoveTo (page, x, y - 15);
    BRST_Page_LineTo (page, x + 220, y - 15);
    BRST_Page_Stroke (page);
}

void
draw_line2  (BRST_Page    page,
             float       x,
             float       y,
             const char  *label)
{
    BRST_Page_BeginText (page);
    BRST_Page_MoveTextPos (page, x, y);
    BRST_Page_ShowText (page, label);
    BRST_Page_EndText (page);

    BRST_Page_MoveTo (page, x + 30, y - 25);
    BRST_Page_LineTo (page, x + 160, y - 25);
    BRST_Page_Stroke (page);
}

void
draw_rect (BRST_Page     page,
           double        x,
           double        y,
           const char   *label)
{
    BRST_Page_BeginText (page);
    BRST_Page_MoveTextPos (page, x, y - 10);
    BRST_Page_ShowText (page, label);
    BRST_Page_EndText (page);

    BRST_Page_Rectangle(page, x, y - 40, 220, 25);
}

int main (int argc, char **argv)
{
    const char* page_title = "Line Example";

    BRST_Doc  pdf;
    BRST_Font font;
    BRST_Page page;
    char fname[256];

    const BRST_REAL DASH_MODE1[] = {3};
    const BRST_REAL DASH_MODE2[] = {3, 7};
    const BRST_REAL DASH_MODE3[] = {8, 7, 2, 7};

    double x;
    double y;
    double x1;
    double y1;
    double x2;
    double y2;
    double x3;
    double y3;

    float tw;

    strcpy (fname, argv[0]);
    strcat (fname, ".pdf");

    pdf = BRST_New (demo_error_handler, NULL);
    pdf = BRST_Doc_New (demo_error_handler, NULL);
    if (!pdf) {
        printf ("error: cannot create PdfDoc object\n");
        return 1;
    }

    if (setjmp(env)) {
        BRST_Doc_Free(pdf);
        return 1;
    }

    /* create default-font */
    font = BRST_Doc_Font (pdf, "Helvetica", NULL);

    /* add a new page object. */
    page = BRST_Doc_Page_Add(pdf);

    /* print the lines of the page. */
    BRST_Page_SetLineWidth(page, 1);
    BRST_Page_Rectangle(page, 50, 50, BRST_Page_Width(page) - 100,
                BRST_Page_Height(page) - 110);
    BRST_Page_Stroke(page);

    /* print the title of the page (with positioning center). */
    BRST_Page_SetFontAndSize(page, font, 24);
    tw = BRST_Page_TextWidth(page, page_title);
    BRST_Page_BeginText(page);
    BRST_Page_MoveTextPos(page, (BRST_Page_Width(page) - tw) / 2,
                BRST_Page_Height(page) - 50);
    BRST_Page_ShowText(page, page_title);
    BRST_Page_EndText(page);

    BRST_Page_SetFontAndSize(page, font, 10);

    /* Draw various widths of lines. */
    BRST_Page_SetLineWidth(page, 0);
    draw_line(page, 60, 770, "line width = 0");

    BRST_Page_SetLineWidth(page, 1.0);
    draw_line(page, 60, 740, "line width = 1.0");

    BRST_Page_SetLineWidth(page, 2.0);
    draw_line(page, 60, 710, "line width = 2.0");

    /* Line dash pattern */
    BRST_Page_SetLineWidth(page, 1.0);

    BRST_Page_SetDash(page, DASH_MODE1, 1, 1.0);
    draw_line(page, 60, 680, "dash_ptn=[3], phase=1 -- "
                "2 on, 3 off, 3 on...");

    BRST_Page_SetDash(page, DASH_MODE2, 2, 2.0);
    draw_line(page, 60, 650, "dash_ptn=[7, 3], phase=2 -- "
                "5 on 3 off, 7 on,...");

    BRST_Page_SetDash(page, DASH_MODE3, 4, 0.0);
    draw_line(page, 60, 620, "dash_ptn=[8, 7, 2, 7], phase=0");

    BRST_Page_SetDash(page, NULL, 0, 0.0);

    BRST_Page_SetLineWidth(page, 30);
    BRST_Page_SetRGBStroke(page, 0.0, 0.5, 0.0);

    /* Line Cap Style */
    BRST_Page_SetLineCap(page, BRST_BUTT_END);
    draw_line2(page, 60, 570, "PDF_BUTT_END");

    BRST_Page_SetLineCap(page, BRST_ROUND_END);
    draw_line2(page, 60, 505, "PDF_ROUND_END");

    BRST_Page_SetLineCap(page, BRST_PROJECTING_SQUARE_END);
    draw_line2(page, 60, 440, "PDF_PROJECTING_SCUARE_END");

    /* Line Join Style */
    BRST_Page_SetLineWidth(page, 30);
    BRST_Page_SetRGBStroke(page, 0.0, 0.0, 0.5);

    BRST_Page_SetLineJoin(page, BRST_MITER_JOIN);
    BRST_Page_MoveTo(page, 120, 300);
    BRST_Page_LineTo(page, 160, 340);
    BRST_Page_LineTo(page, 200, 300);
    BRST_Page_Stroke(page);

    BRST_Page_BeginText(page);
    BRST_Page_MoveTextPos(page, 60, 360);
    BRST_Page_ShowText(page, "PDF_MITER_JOIN");
    BRST_Page_EndText(page);

    BRST_Page_SetLineJoin(page, BRST_ROUND_JOIN);
    BRST_Page_MoveTo(page, 120, 195);
    BRST_Page_LineTo(page, 160, 235);
    BRST_Page_LineTo(page, 200, 195);
    BRST_Page_Stroke(page);

    BRST_Page_BeginText(page);
    BRST_Page_MoveTextPos(page, 60, 255);
    BRST_Page_ShowText(page, "PDF_ROUND_JOIN");
    BRST_Page_EndText(page);

    BRST_Page_SetLineJoin(page, BRST_BEVEL_JOIN);
    BRST_Page_MoveTo(page, 120, 90);
    BRST_Page_LineTo(page, 160, 130);
    BRST_Page_LineTo(page, 200, 90);
    BRST_Page_Stroke(page);

    BRST_Page_BeginText(page);
    BRST_Page_MoveTextPos(page, 60, 150);
    BRST_Page_ShowText(page, "PDF_BEVEL_JOIN");
    BRST_Page_EndText(page);

    /* Draw Rectangle */
    BRST_Page_SetLineWidth(page, 2);
    BRST_Page_SetRGBStroke(page, 0, 0, 0);
    BRST_Page_SetRGBFill(page, 0.75, 0.0, 0.0);

    draw_rect(page, 300, 770, "Stroke");
    BRST_Page_Stroke(page);

    draw_rect(page, 300, 720, "Fill");
    BRST_Page_Fill(page);

    draw_rect(page, 300, 670, "Fill then Stroke");
    BRST_Page_FillStroke(page);

    /* Clip Rect */
    BRST_Page_GSave(page);  /* Save the current graphic state */
    draw_rect(page, 300, 620, "Clip Rectangle");
    BRST_Page_Clip(page);
    BRST_Page_Stroke(page);
    BRST_Page_SetFontAndSize(page, font, 13);

    BRST_Page_BeginText(page);
    BRST_Page_MoveTextPos(page, 290, 600);
    BRST_Page_SetTextLeading(page, 12);
    BRST_Page_ShowText(page,
                "Clip Clip Clip Clip Clip Clipi Clip Clip Clip");
    BRST_Page_ShowTextNextLine(page,
                "Clip Clip Clip Clip Clip Clip Clip Clip Clip");
    BRST_Page_ShowTextNextLine(page,
                "Clip Clip Clip Clip Clip Clip Clip Clip Clip");
    BRST_Page_EndText(page);
    BRST_Page_GRestore(page);

    /* Curve Example(CurveTo2) */
    x = 330;
    y = 440;
    x1 = 430;
    y1 = 530;
    x2 = 480;
    y2 = 470;
    x3 = 480;
    y3 = 90;

    BRST_Page_SetRGBFill(page, 0, 0, 0);

    BRST_Page_BeginText(page);
    BRST_Page_MoveTextPos(page, 300, 540);
    BRST_Page_ShowText(page, "CurveTo2(x1, y1, x2. y2)");
    BRST_Page_EndText(page);

    BRST_Page_BeginText(page);
    BRST_Page_MoveTextPos(page, x + 5, y - 5);
    BRST_Page_ShowText(page, "Current point");
    BRST_Page_MoveTextPos(page, x1 - x, y1 - y);
    BRST_Page_ShowText(page, "(x1, y1)");
    BRST_Page_MoveTextPos(page, x2 - x1, y2 - y1);
    BRST_Page_ShowText(page, "(x2, y2)");
    BRST_Page_EndText(page);

    BRST_Page_SetDash(page, DASH_MODE1, 1, 0.0);

    BRST_Page_SetLineWidth(page, 0.5);
    BRST_Page_MoveTo(page, x1, y1);
    BRST_Page_LineTo(page, x2, y2);
    BRST_Page_Stroke(page);

    BRST_Page_SetDash(page, NULL, 0, 0.0);

    BRST_Page_SetLineWidth(page, 1.5);

    BRST_Page_MoveTo(page, x, y);
    BRST_Page_CurveTo2(page, x1, y1, x2, y2);
    BRST_Page_Stroke(page);

    /* Curve Example(CurveTo3) */
    y -= 150;
    y1 -= 150;
    y2 -= 150;

    BRST_Page_BeginText(page);
    BRST_Page_MoveTextPos(page, 300, 390);
    BRST_Page_ShowText(page, "CurveTo3(x1, y1, x2. y2)");
    BRST_Page_EndText(page);

    BRST_Page_BeginText(page);
    BRST_Page_MoveTextPos(page, x + 5, y - 5);
    BRST_Page_ShowText(page, "Current point");
    BRST_Page_MoveTextPos(page, x1 - x, y1 - y);
    BRST_Page_ShowText(page, "(x1, y1)");
    BRST_Page_MoveTextPos(page, x2 - x1, y2 - y1);
    BRST_Page_ShowText(page, "(x2, y2)");
    BRST_Page_EndText(page);

    BRST_Page_SetDash(page, DASH_MODE1, 1, 0.0);

    BRST_Page_SetLineWidth(page, 0.5);
    BRST_Page_MoveTo(page, x, y);
    BRST_Page_LineTo(page, x1, y1);
    BRST_Page_Stroke(page);

    BRST_Page_SetDash(page, NULL, 0, 0.0);

    BRST_Page_SetLineWidth(page, 1.5);
    BRST_Page_MoveTo(page, x, y);
    BRST_Page_CurveTo3(page, x1, y1, x2, y2);
    BRST_Page_Stroke(page);

    /* Curve Example(CurveTo) */
    y -= 150;
    y1 -= 160;
    y2 -= 130;
    x2 += 10;

    BRST_Page_BeginText(page);
    BRST_Page_MoveTextPos(page, 300, 240);
    BRST_Page_ShowText(page, "CurveTo(x1, y1, x2. y2, x3, y3)");
    BRST_Page_EndText(page);

    BRST_Page_BeginText(page);
    BRST_Page_MoveTextPos(page, x + 5, y - 5);
    BRST_Page_ShowText(page, "Current point");
    BRST_Page_MoveTextPos(page, x1 - x, y1 - y);
    BRST_Page_ShowText(page, "(x1, y1)");
    BRST_Page_MoveTextPos(page, x2 - x1, y2 - y1);
    BRST_Page_ShowText(page, "(x2, y2)");
    BRST_Page_MoveTextPos(page, x3 - x2, y3 - y2);
    BRST_Page_ShowText(page, "(x3, y3)");
    BRST_Page_EndText(page);

    BRST_Page_SetDash(page, DASH_MODE1, 1, 0.0);

    BRST_Page_SetLineWidth(page, 0.5);
    BRST_Page_MoveTo(page, x, y);
    BRST_Page_LineTo(page, x1, y1);
    BRST_Page_Stroke(page);
    BRST_Page_MoveTo(page, x2, y2);
    BRST_Page_LineTo(page, x3, y3);
    BRST_Page_Stroke(page);

    BRST_Page_SetDash(page, NULL, 0, 0.0);

    BRST_Page_SetLineWidth(page, 1.5);
    BRST_Page_MoveTo(page, x, y);
    BRST_Page_CurveTo(page, x1, y1, x2, y2, x3, y3);
    BRST_Page_Stroke(page);

    /* save the document to a file */
    BRST_Doc_SaveToFile (pdf, fname);

    /* clean up */
    BRST_Doc_Free(pdf);

    return 0;
}

