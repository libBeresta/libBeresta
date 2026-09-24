#include "brst.h"

#define HPDF_STATUS BRST_STATUS
#define HPDF_UINT BRST_UINT

#define HPDF_REAL BRST_REAL
#define HPDF_Page BRST_Page
#define HPDF_Font BRST_Font
#define HPDF_Doc  BRST_Doc

#define HPDF_Free                BRST_Doc_Free
#define HPDF_New                 BRST_Doc_New
#define HPDF_AddPage             BRST_Doc_Page_Add
#define HPDF_Page_GetWidth       BRST_Page_Width
#define HPDF_Page_GetHeight      BRST_Page_Height
#define HPDF_Page_SetLineWidth   BRST_Page_SetLineWidth
#define HPDF_Page_Rectangle      BRST_Page_Rectangle
#define HPDF_Page_TextOut        BRST_Page_TextOut
#define HPDF_Page_Stroke         BRST_Page_Stroke
#define HPDF_Page_BeginText      BRST_Page_BeginText
#define HPDF_Page_EndText        BRST_Page_EndText
#define HPDF_Page_ShowText       BRST_Page_ShowText
#define HPDF_GetFont             BRST_Doc_Font
#define HPDF_Page_TextWidth      BRST_Page_TextWidth
#define HPDF_Page_SetFontAndSize BRST_Page_SetFontAndSize
#define HPDF_Page_MoveTextPos    BRST_Page_MoveTextPos
#define HPDF_SaveToFile          BRST_Doc_SaveToFile
