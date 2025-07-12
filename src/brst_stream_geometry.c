#include "brst_external.h"
#include "brst_types.h"
#include "brst_mmgr.h"
#include "brst_encrypt.h"
#include "brst_stream.h"
#include "brst_dict.h"
#include "brst_xref.h"
#include "brst_encoder.h"
#include "brst_error.h"
#include "brst_consts.h"
#include "private/brst_utils.h"
#include "brst_ext_gstate.h"
#include "brst_font.h"
#include "brst_shading.h"
#include "private/brst_page.h"
#include "brst_geometry_defines.h"
#include "private/brst_pages.h"
#include "private/brst_gstate.h"
#include "private/brst_page_attr.h"
#include "private/brst_encrypt_dict.h"
#include "brst_outline.h"
#include "private/brst_catalog.h"
#include "private/brst_c.h"


/* q */
BRST_EXPORT(BRST_STATUS)
BRST_Stream_GSave(BRST_Stream stream)
{
    BRST_STATUS ret =  BRST_Stream_Validate(stream);

    BRST_PTRACE((" BRST_Stream_GSave\n"));

    if (ret != BRST_OK)
        return ret;

    if (BRST_Stream_WriteStr(stream, "q\012") != BRST_OK)
        return BRST_Error_Check(stream->error);

    return ret;
}

/* Q */
BRST_EXPORT(BRST_STATUS)
BRST_Stream_GRestore(BRST_Stream stream)
{
    BRST_STATUS ret =  BRST_Stream_Validate(stream);

    BRST_PTRACE((" BRST_Stream_GRestore\n"));

    if (ret != BRST_OK)
        return ret;

    if (BRST_Stream_WriteStr(stream, "Q\012") != BRST_OK)
        return BRST_Error_Check(stream->error);

    return ret;
}

/* cm */
BRST_EXPORT(BRST_STATUS)
BRST_Stream_Concat(BRST_Stream stream,
    BRST_REAL a,
    BRST_REAL b,
    BRST_REAL c,
    BRST_REAL d,
    BRST_REAL x,
    BRST_REAL y)
{
    BRST_STATUS ret =  BRST_Stream_Validate(stream);
    char buf[BRST_TMP_BUF_SIZE];
    char* pbuf = buf;
    char* eptr = buf + BRST_TMP_BUF_SIZE - 1;

    BRST_PTRACE((" BRST_Stream_Concat\n"));

    if (ret != BRST_OK)
        return ret;


    BRST_MemSet(buf, 0, BRST_TMP_BUF_SIZE);

    pbuf    = BRST_FToA(pbuf, a, eptr);
    *pbuf++ = ' ';
    pbuf    = BRST_FToA(pbuf, b, eptr);
    *pbuf++ = ' ';
    pbuf    = BRST_FToA(pbuf, c, eptr);
    *pbuf++ = ' ';
    pbuf    = BRST_FToA(pbuf, d, eptr);
    *pbuf++ = ' ';
    pbuf    = BRST_FToA(pbuf, x, eptr);
    *pbuf++ = ' ';
    pbuf    = BRST_FToA(pbuf, y, eptr);
    BRST_StrCpy(pbuf, " cm\012", eptr);

    if (BRST_Stream_WriteStr(stream, buf) != BRST_OK)
        return BRST_Error_Check(stream->error);

    return ret;
}

BRST_EXPORT(BRST_STATUS)
BRST_Stream_Translate(BRST_Stream stream,
    BRST_REAL dx,
    BRST_REAL dy)
{
    BRST_PTRACE((" BRST_Stream_Translate\n"));
    return BRST_Stream_Concat(stream, 1, 0, 0, 1, dx, dy);
}

BRST_EXPORT(BRST_STATUS)
BRST_Stream_Scale(BRST_Stream stream,
    BRST_REAL sx,
    BRST_REAL sy)
{
    BRST_PTRACE((" BRST_Stream_Scale\n"));
    return BRST_Stream_Concat(stream, sx, 0, 0, sy, 0, 0);
}

BRST_EXPORT(BRST_STATUS)
BRST_Stream_Rotate(BRST_Stream stream,
    BRST_REAL a)
{
    BRST_PTRACE((" BRST_Stream_Rotate\n"));
    return BRST_Stream_Concat(stream, cos(a), sin(a), -sin(a), cos(a), 0, 0);
}

BRST_EXPORT(BRST_STATUS)
BRST_Stream_RotateDeg(BRST_Stream stream,
    BRST_REAL degrees)
{
    BRST_PTRACE((" BRST_Stream_RotateDeg\n"));
    BRST_REAL a = degrees * BRST_PI / 180.0;
    return BRST_Stream_Concat(stream, cos(a), sin(a), -sin(a), cos(a), 0, 0);
}

BRST_EXPORT(BRST_STATUS)
BRST_Stream_Skew(BRST_Stream stream,
    BRST_REAL a,
    BRST_REAL b)
{
    BRST_PTRACE((" BRST_Stream_Skew\n"));
    return BRST_Stream_Concat(stream, 1, tan(a), tan(b), 1, 0, 0);
}

/* 
TODO Эти функции нужно переработать, слишком завязаны на содержимое Page
BRST_EXPORT(BRST_STATUS)
BRST_Stream_Circle(BRST_Stream stream,
    BRST_REAL x,
    BRST_REAL y,
    BRST_REAL ray)
{
    BRST_STATUS ret = BRST_Page_CheckState(page, BRST_GMODE_PAGE_DESCRIPTION | BRST_GMODE_PATH_OBJECT);
    char buf[BRST_TMP_BUF_SIZE * 2];
    char* pbuf = buf;
    char* eptr = buf + BRST_TMP_BUF_SIZE - 1;
    BRST_PageAttr attr;

    BRST_PTRACE((" BRST_Stream_Circle\n"));

    if (ret != BRST_OK)
        return ret;

    attr = (BRST_PageAttr)page->attr;

    BRST_MemSet(buf, 0, BRST_TMP_BUF_SIZE);

    pbuf    = BRST_FToA(pbuf, x - ray, eptr);
    *pbuf++ = ' ';
    pbuf    = BRST_FToA(pbuf, y, eptr);
    pbuf    = (char*)BRST_StrCpy(pbuf, " m\012", eptr);

    pbuf = QuarterCircleA(pbuf, eptr, x, y, ray);
    pbuf = QuarterCircleB(pbuf, eptr, x, y, ray);
    pbuf = QuarterCircleC(pbuf, eptr, x, y, ray);
    QuarterCircleD(pbuf, eptr, x, y, ray);

    if (BRST_Stream_WriteStr(attr->stream, buf) != BRST_OK)
        return BRST_Error_Check(page->error);

    attr->cur_pos.x = x - ray;
    attr->cur_pos.y = y;
    attr->str_pos   = attr->cur_pos;
    attr->gmode     = BRST_GMODE_PATH_OBJECT;

    return ret;
}

BRST_EXPORT(BRST_STATUS)
BRST_Stream_Ellipse(BRST_Page page,
    BRST_REAL x,
    BRST_REAL y,
    BRST_REAL xray,
    BRST_REAL yray)
{
    BRST_STATUS ret = BRST_Page_CheckState(page, BRST_GMODE_PAGE_DESCRIPTION | BRST_GMODE_PATH_OBJECT);
    char buf[BRST_TMP_BUF_SIZE];
    char* pbuf = buf;
    char* eptr = buf + BRST_TMP_BUF_SIZE - 1;
    BRST_PageAttr attr;

    BRST_PTRACE((" BRST_Stream_Ellipse\n"));

    if (ret != BRST_OK)
        return ret;

    attr = (BRST_PageAttr)page->attr;

    BRST_MemSet(buf, 0, BRST_TMP_BUF_SIZE);

    pbuf    = BRST_FToA(pbuf, x - xray, eptr);
    *pbuf++ = ' ';
    pbuf    = BRST_FToA(pbuf, y, eptr);
    pbuf    = (char*)BRST_StrCpy(pbuf, " m\012", eptr);

    pbuf = QuarterEllipseA(pbuf, eptr, x, y, xray, yray);
    pbuf = QuarterEllipseB(pbuf, eptr, x, y, xray, yray);
    pbuf = QuarterEllipseC(pbuf, eptr, x, y, xray, yray);
    QuarterEllipseD(pbuf, eptr, x, y, xray, yray);

    if (BRST_Stream_WriteStr(attr->stream, buf) != BRST_OK)
        return BRST_Error_Check(page->error);

    attr->cur_pos.x = x - xray;
    attr->cur_pos.y = y;
    attr->str_pos   = attr->cur_pos;
    attr->gmode     = BRST_GMODE_PATH_OBJECT;

    return ret;
}
*/
/*
 * this function is based on the code which is contributed by Riccardo Cohen.
 *
 * from http://www.tinaja.com/glib/bezarc1.pdf coming from
 * http://www.whizkidtech.redprince.net/bezier/circle/
 */
/*
BRST_EXPORT(BRST_STATUS)
BRST_Stream_Arc(BRST_Page page,
    BRST_REAL x,
    BRST_REAL y,
    BRST_REAL ray,
    BRST_REAL ang1,
    BRST_REAL ang2)
{
    BRST_BOOL cont_flg = BRST_FALSE;

    BRST_STATUS ret = BRST_Page_CheckState(page, BRST_GMODE_PAGE_DESCRIPTION | BRST_GMODE_PATH_OBJECT);

    BRST_PTRACE((" BRST_Stream_Arc\n"));

    if (fabs(ang2 - ang1) >= 360)
        BRST_Error_Raise(page->error, BRST_PAGE_OUT_OF_RANGE, 0);

    if (ret != BRST_OK)
        return ret;

    while (ang1 < 0 || ang2 < 0) {
        ang1 = ang1 + 360;
        ang2 = ang2 + 360;
    }

    for (;;) {
        if (fabs(ang2 - ang1) <= 90)
            return InternalArc(page, x, y, ray, ang1, ang2, cont_flg);
        else {
            BRST_REAL tmp_ang = (ang2 > ang1 ? ang1 + 90 : ang1 - 90);

            if ((ret = InternalArc(page, x, y, ray, ang1, tmp_ang, cont_flg))
                != BRST_OK)
                return ret;

            ang1 = tmp_ang;
        }

        if (fabs(ang1 - ang2) < 0.1)
            break;

        cont_flg = BRST_TRUE;
    }

    return BRST_OK;
}
*/
/* g */
BRST_EXPORT(BRST_STATUS)
BRST_Stream_SetGrayFill(BRST_Stream stream,
    BRST_REAL gray)
{
    BRST_STATUS ret =  BRST_Stream_Validate(stream);

    BRST_PTRACE((" BRST_Stream_SetGrayFill\n"));

    if (ret != BRST_OK)
        return ret;

    if (gray < 0 || gray > 1)
        return BRST_Error_Raise(stream->error, BRST_PAGE_OUT_OF_RANGE, 0);

    if (BRST_Stream_WriteReal(stream, gray) != BRST_OK)
        return BRST_Error_Check(stream->error);

    if (BRST_Stream_WriteStr(stream, " g\012") != BRST_OK)
        return BRST_Error_Check(stream->error);

    return ret;
}

/* G */
BRST_EXPORT(BRST_STATUS)
BRST_Stream_SetGrayStroke(BRST_Stream stream,
    BRST_REAL gray)
{
    BRST_STATUS ret =  BRST_Stream_Validate(stream);

    BRST_PTRACE((" BRST_Stream_SetGrayStroke\n"));

    if (ret != BRST_OK)
        return ret;

    if (gray < 0 || gray > 1)
        return BRST_Error_Raise(stream->error, BRST_PAGE_OUT_OF_RANGE, 0);

    if (BRST_Stream_WriteReal(stream, gray) != BRST_OK)
        return BRST_Error_Check(stream->error);

    if (BRST_Stream_WriteStr(stream, " G\012") != BRST_OK)
        return BRST_Error_Check(stream->error);

    return ret;
}

/* rg */
BRST_EXPORT(BRST_STATUS)
BRST_Stream_SetRGBFill(BRST_Stream stream,
    BRST_REAL r,
    BRST_REAL g,
    BRST_REAL b)
{
    BRST_STATUS ret =  BRST_Stream_Validate(stream);

    char buf[BRST_TMP_BUF_SIZE];
    char* pbuf = buf;
    char* eptr = buf + BRST_TMP_BUF_SIZE - 1;

    BRST_PTRACE((" BRST_Stream_SetRGBFill\n"));

    if (ret != BRST_OK)
        return ret;

    if (r < 0 || r > 1 || g < 0 || g > 1 || b < 0 || b > 1)
        return BRST_Error_Raise(stream->error, BRST_PAGE_OUT_OF_RANGE, 0);

    BRST_MemSet(buf, 0, BRST_TMP_BUF_SIZE);

    pbuf    = BRST_FToA(pbuf, r, eptr);
    *pbuf++ = ' ';
    pbuf    = BRST_FToA(pbuf, g, eptr);
    *pbuf++ = ' ';
    pbuf    = BRST_FToA(pbuf, b, eptr);
    BRST_StrCpy(pbuf, " rg\012", eptr);

    if (BRST_Stream_WriteStr(attr->stream, buf) != BRST_OK)
        return BRST_Error_Check(page->error);

    return ret;
}

/* RG */
BRST_EXPORT(BRST_STATUS)
BRST_Stream_SetRGBStroke(BRST_Stream stream,
    BRST_REAL r,
    BRST_REAL g,
    BRST_REAL b)
{
    BRST_STATUS ret =  BRST_Stream_Validate(stream);

    char buf[BRST_TMP_BUF_SIZE];
    char* pbuf = buf;
    char* eptr = buf + BRST_TMP_BUF_SIZE - 1;

    BRST_PTRACE((" BRST_Stream_SetRGBStroke\n"));

    if (ret != BRST_OK)
        return ret;

    if (r < 0 || r > 1 || g < 0 || g > 1 || b < 0 || b > 1)
        return BRST_Error_Raise(stream->error, BRST_PAGE_OUT_OF_RANGE, 0);

    BRST_MemSet(buf, 0, BRST_TMP_BUF_SIZE);

    pbuf    = BRST_FToA(pbuf, r, eptr);
    *pbuf++ = ' ';
    pbuf    = BRST_FToA(pbuf, g, eptr);
    *pbuf++ = ' ';
    pbuf    = BRST_FToA(pbuf, b, eptr);
    BRST_StrCpy(pbuf, " RG\012", eptr);

    if (BRST_Stream_WriteStr(stream, buf) != BRST_OK)
        return BRST_Error_Check(stream->error);

    return ret;
}

BRST_EXPORT(BRST_STATUS)
BRST_Stream_SetRGBStrokeHex(BRST_Stream stream,
    BRST_UINT8 r,
    BRST_UINT8 g,
    BRST_UINT8 b)
{
    BRST_REAL rr = (BRST_REAL)r / 255.0;
    BRST_REAL rg = (BRST_REAL)g / 255.0;
    BRST_REAL rb = (BRST_REAL)b / 255.0;

    return BRST_Stream_SetRGBStroke(stream, rr, rg, rb);
}

/* k */
BRST_EXPORT(BRST_STATUS)
BRST_Stream_SetCMYKFill(BRST_Stream stream,
    BRST_REAL c,
    BRST_REAL m,
    BRST_REAL y,
    BRST_REAL k)
{
    BRST_STATUS ret =  BRST_Stream_Validate(stream);

    char buf[BRST_TMP_BUF_SIZE];
    char* pbuf = buf;
    char* eptr = buf + BRST_TMP_BUF_SIZE - 1;

    BRST_PTRACE((" BRST_Stream_SetCMYKFill\n"));

    if (ret != BRST_OK)
        return ret;

    if (c < 0 || c > 1 || m < 0 || m > 1 || y < 0 || y > 1 || k < 0 || k > 1)
        return BRST_Error_Raise(stream->error, BRST_PAGE_OUT_OF_RANGE, 0);

    BRST_MemSet(buf, 0, BRST_TMP_BUF_SIZE);

    pbuf    = BRST_FToA(pbuf, c, eptr);
    *pbuf++ = ' ';
    pbuf    = BRST_FToA(pbuf, m, eptr);
    *pbuf++ = ' ';
    pbuf    = BRST_FToA(pbuf, y, eptr);
    *pbuf++ = ' ';
    pbuf    = BRST_FToA(pbuf, k, eptr);
    BRST_StrCpy(pbuf, " k\012", eptr);

    if (BRST_Stream_WriteStr(stream, buf) != BRST_OK)
        return BRST_Error_Check(stream->error);

    return ret;
}

/* K */
BRST_EXPORT(BRST_STATUS)
BRST_Stream_SetCMYKStroke(BRST_Stream stream,
    BRST_REAL c,
    BRST_REAL m,
    BRST_REAL y,
    BRST_REAL k)
{
    BRST_STATUS ret =  BRST_Stream_Validate(stream);

    char buf[BRST_TMP_BUF_SIZE];
    char* pbuf = buf;
    char* eptr = buf + BRST_TMP_BUF_SIZE - 1;

    BRST_PTRACE((" BRST_Stream_SetCMYKStroke\n"));

    if (ret != BRST_OK)
        return ret;

    if (c < 0 || c > 1 || m < 0 || m > 1 || y < 0 || y > 1 || k < 0 || k > 1)
        return BRST_Error_Raise(stream->error, BRST_PAGE_OUT_OF_RANGE, 0);

    BRST_MemSet(buf, 0, BRST_TMP_BUF_SIZE);

    pbuf    = BRST_FToA(pbuf, c, eptr);
    *pbuf++ = ' ';
    pbuf    = BRST_FToA(pbuf, m, eptr);
    *pbuf++ = ' ';
    pbuf    = BRST_FToA(pbuf, y, eptr);
    *pbuf++ = ' ';
    pbuf    = BRST_FToA(pbuf, k, eptr);
    BRST_StrCpy(pbuf, " K\012", eptr);

    if (BRST_Stream_WriteStr(stream, buf) != BRST_OK)
        return BRST_Error_Check(stream->error);

    return ret;
}

/* W */
BRST_EXPORT(BRST_STATUS)
BRST_Stream_Clip(BRST_Stream stream)
{
    BRST_STATUS ret =  BRST_Stream_Validate(stream);

    BRST_PTRACE((" BRST_Stream_Clip\n"));

    if (ret != BRST_OK)
        return ret;

    if (BRST_Stream_WriteStr(stream, "W\012") != BRST_OK)
        return BRST_Error_Check(stream->error);

    return ret;
}

/* W* */
BRST_EXPORT(BRST_STATUS)
BRST_Stream_Eoclip(BRST_Stream stream)
{
    BRST_STATUS ret =  BRST_Stream_Validate(stream);

    BRST_PTRACE((" BRST_Stream_Eoclip\n"));

    if (ret != BRST_OK)
        return ret;

    if (BRST_Stream_WriteStr(stream, "W*\012") != BRST_OK)
        return BRST_Error_Check(stream->error);

    return ret;
}

/* S */
BRST_EXPORT(BRST_STATUS)
BRST_Stream_Stroke(BRST_Stream stream)
{
    BRST_STATUS ret =  BRST_Stream_Validate(stream);

    BRST_PTRACE((" BRST_Stream_Stroke\n"));

    if (ret != BRST_OK)
        return ret;

    if (BRST_Stream_WriteStr(stream, "S\012") != BRST_OK)
        return BRST_Error_Check(stream->error);

    return ret;
}

/* s */
BRST_EXPORT(BRST_STATUS)
BRST_Stream_ClosePathStroke(BRST_Stream stream)
{
    BRST_STATUS ret =  BRST_Stream_Validate(stream);

    BRST_PTRACE((" BRST_Stream_ClosePathStroke\n"));

    if (ret != BRST_OK)
        return ret;

    if (BRST_Stream_WriteStr(stream, "s\012") != BRST_OK)
        return BRST_Error_Check(stream->error);

    return ret;
}

/* f */
BRST_EXPORT(BRST_STATUS)
BRST_Stream_Fill(BRST_Stream stream)
{
    BRST_STATUS ret =  BRST_Stream_Validate(stream);

    BRST_PTRACE((" BRST_Stream_Fill\n"));

    if (ret != BRST_OK)
        return ret;

    if (BRST_Stream_WriteStr(stream, "f\012") != BRST_OK)
        return BRST_Error_Check(stream->error);

    return ret;
}

/* f* */
BRST_EXPORT(BRST_STATUS)
BRST_Stream_Eofill(BRST_Stream stream)
{
    BRST_STATUS ret =  BRST_Stream_Validate(stream);

    BRST_PTRACE((" BRST_Stream_Eofill\n"));

    if (ret != BRST_OK)
        return ret;

    if (BRST_Stream_WriteStr(stream, "f*\012") != BRST_OK)
        return BRST_Error_Check(stream->error);

    return ret;
}

/* B */
BRST_EXPORT(BRST_STATUS)
BRST_Stream_FillStroke(BRST_Stream stream)
{
    BRST_STATUS ret =  BRST_Stream_Validate(stream);

    BRST_PTRACE((" BRST_Stream_FillStroke\n"));

    if (ret != BRST_OK)
        return ret;

    if (BRST_Stream_WriteStr(attrS->stream, "B\012") != BRST_OK)
        return BRST_Error_Check(page->error);

    return ret;
}

/* B* */
BRST_EXPORT(BRST_STATUS)
BRST_Stream_EofillStroke(BRST_Stream stream)
{
    BRST_STATUS ret =  BRST_Stream_Validate(stream);

    BRST_PTRACE((" BRST_Stream_EofillStroke\n"));

    if (ret != BRST_OK)
        return ret;

    if (BRST_Stream_WriteStr(stream, "B*\012") != BRST_OK)
        return BRST_Error_Check(stream->error);

    return ret;
}

/* b */
BRST_EXPORT(BRST_STATUS)
BRST_Stream_ClosePathFillStroke(BRST_Page page)
{
    BRST_STATUS ret =  BRST_Stream_Validate(stream);

    BRST_PTRACE((" BRST_Stream_ClosePathFillStroke\n"));

    if (ret != BRST_OK)
        return ret;

    if (BRST_Stream_WriteStr(stream, "b\012") != BRST_OK)
        return BRST_Error_Check(stream->error);

    return ret;
}

/* b* */
BRST_EXPORT(BRST_STATUS)
BRST_Stream_ClosePathEofillStroke(BRST_Stream stream)
{
    BRST_STATUS ret =  BRST_Stream_Validate(stream);

    BRST_PTRACE((" BRST_Stream_ClosePathEofillStroke\n"));

    if (ret != BRST_OK)
        return ret;

    if (BRST_Stream_WriteStr(stream, "b*\012") != BRST_OK)
        return BRST_Error_Check(stream->error);

    return ret;
}

/* n */
BRST_EXPORT(BRST_STATUS)
BRST_Stream_EndPath(BRST_Stream stream)
{
    BRST_STATUS ret =  BRST_Stream_Validate(stream);

    BRST_PTRACE((" BRST_PageEndPath\n"));

    if (ret != BRST_OK)
        return ret;

    if (BRST_Stream_WriteStr(stream, "n\012") != BRST_OK)
        return BRST_Error_Check(stream->error);

    return ret;
}

/* m */
BRST_EXPORT(BRST_STATUS)
BRST_Stream_MoveTo(BRST_Stream stream,
    BRST_REAL x,
    BRST_REAL y)
{
    BRST_STATUS ret =  BRST_Stream_Validate(stream);

    char buf[BRST_TMP_BUF_SIZE];
    char* pbuf = buf;
    char* eptr = buf + BRST_TMP_BUF_SIZE - 1;

    BRST_PTRACE((" BRST_Stream_MoveTo\n"));

    if (ret != BRST_OK)
        return ret;

    BRST_MemSet(buf, 0, BRST_TMP_BUF_SIZE);

    pbuf    = BRST_FToA(pbuf, x, eptr);
    *pbuf++ = ' ';
    pbuf    = BRST_FToA(pbuf, y, eptr);
    BRST_StrCpy(pbuf, " m\012", eptr);

    if (BRST_Stream_WriteStr(stream, buf) != BRST_OK)
        return BRST_Error_Check(stream->error);

    return ret;
}

/* l */
BRST_EXPORT(BRST_STATUS)
BRST_Stream_LineTo(BRST_Stream stream,
    BRST_REAL x,
    BRST_REAL y)
{
    BRST_STATUS ret =  BRST_Stream_Validate(stream);

    char buf[BRST_TMP_BUF_SIZE];
    char* pbuf = buf;
    char* eptr = buf + BRST_TMP_BUF_SIZE - 1;

    BRST_PTRACE((" BRST_Stream_LineTo\n"));

    if (ret != BRST_OK)
        return ret;

    BRST_MemSet(buf, 0, BRST_TMP_BUF_SIZE);

    pbuf    = BRST_FToA(pbuf, x, eptr);
    *pbuf++ = ' ';
    pbuf    = BRST_FToA(pbuf, y, eptr);
    BRST_StrCpy(pbuf, " l\012", eptr);

    if (BRST_Stream_WriteStr(stream, buf) != BRST_OK)
        return BRST_Error_Check(stream->error);

    return ret;
}

/* c */
BRST_EXPORT(BRST_STATUS)
BRST_Stream_CurveTo(BRST_Stream stream,
    BRST_REAL x1,
    BRST_REAL y1,
    BRST_REAL x2,
    BRST_REAL y2,
    BRST_REAL x3,
    BRST_REAL y3)
{
    BRST_STATUS ret =  BRST_Stream_Validate(stream);

    char buf[BRST_TMP_BUF_SIZE];
    char* pbuf = buf;
    char* eptr = buf + BRST_TMP_BUF_SIZE - 1;

    BRST_PTRACE((" BRST_Stream_CurveTo\n"));

    if (ret != BRST_OK)
        return ret;

    BRST_MemSet(buf, 0, BRST_TMP_BUF_SIZE);

    pbuf    = BRST_FToA(pbuf, x1, eptr);
    *pbuf++ = ' ';
    pbuf    = BRST_FToA(pbuf, y1, eptr);
    *pbuf++ = ' ';
    pbuf    = BRST_FToA(pbuf, x2, eptr);
    *pbuf++ = ' ';
    pbuf    = BRST_FToA(pbuf, y2, eptr);
    *pbuf++ = ' ';
    pbuf    = BRST_FToA(pbuf, x3, eptr);
    *pbuf++ = ' ';
    pbuf    = BRST_FToA(pbuf, y3, eptr);
    BRST_StrCpy(pbuf, " c\012", eptr);

    if (BRST_Stream_WriteStr(stream, buf) != BRST_OK)
        return BRST_Error_Check(stream->error);

    return ret;
}

/* v */
BRST_EXPORT(BRST_STATUS)
BRST_Stream_CurveTo2(BRST_Stream stream,
    BRST_REAL x2,
    BRST_REAL y2,
    BRST_REAL x3,
    BRST_REAL y3)
{
    BRST_STATUS ret =  BRST_Stream_Validate(stream);

    char buf[BRST_TMP_BUF_SIZE];
    char* pbuf = buf;
    char* eptr = buf + BRST_TMP_BUF_SIZE - 1;

    BRST_PTRACE((" BRST_Stream_CurveTo2\n"));

    if (ret != BRST_OK)
        return ret;

    BRST_MemSet(buf, 0, BRST_TMP_BUF_SIZE);

    pbuf    = BRST_FToA(pbuf, x2, eptr);
    *pbuf++ = ' ';
    pbuf    = BRST_FToA(pbuf, y2, eptr);
    *pbuf++ = ' ';
    pbuf    = BRST_FToA(pbuf, x3, eptr);
    *pbuf++ = ' ';
    pbuf    = BRST_FToA(pbuf, y3, eptr);
    BRST_StrCpy(pbuf, " v\012", eptr);

    if (BRST_Stream_WriteStr(stream, buf) != BRST_OK)
        return BRST_Error_Check(stream->error);

    return ret;
}

/* y */
BRST_EXPORT(BRST_STATUS)
BRST_Stream_CurveTo3(BRST_Page page,
    BRST_REAL x1,
    BRST_REAL y1,
    BRST_REAL x3,
    BRST_REAL y3)
{
    BRST_STATUS ret =  BRST_Stream_Validate(stream);

    char buf[BRST_TMP_BUF_SIZE];
    char* pbuf = buf;
    char* eptr = buf + BRST_TMP_BUF_SIZE - 1;

    BRST_PTRACE((" BRST_Stream_CurveTo3\n"));

    if (ret != BRST_OK)
        return ret;

    BRST_MemSet(buf, 0, BRST_TMP_BUF_SIZE);

    pbuf    = BRST_FToA(pbuf, x1, eptr);
    *pbuf++ = ' ';
    pbuf    = BRST_FToA(pbuf, y1, eptr);
    *pbuf++ = ' ';
    pbuf    = BRST_FToA(pbuf, x3, eptr);
    *pbuf++ = ' ';
    pbuf    = BRST_FToA(pbuf, y3, eptr);
    BRST_StrCpy(pbuf, " y\012", eptr);

    if (BRST_Stream_WriteStr(stream, buf) != BRST_OK)
        return BRST_Error_Check(stream->error);

    return ret;
}

/* h */
BRST_EXPORT(BRST_STATUS)
BRST_Stream_ClosePath(BRST_Stream stream)
{
    BRST_STATUS ret =  BRST_Stream_Validate(stream);

    BRST_PTRACE((" BRST_Stream_ClosePath\n"));

    if (ret != BRST_OK)
        return ret;

    if (BRST_Stream_WriteStr(stream, "h\012") != BRST_OK)
        return BRST_Error_Check(stream->error);

    return ret;
}

/* re */
BRST_EXPORT(BRST_STATUS)
BRST_Stream_Rectangle(BRST_Stream stream,
    BRST_REAL x,
    BRST_REAL y,
    BRST_REAL width,
    BRST_REAL height)
{
    BRST_STATUS ret =  BRST_Stream_Validate(stream);

    char buf[BRST_TMP_BUF_SIZE];
    char* pbuf = buf;
    char* eptr = buf + BRST_TMP_BUF_SIZE - 1;

    BRST_PTRACE((" BRST_Stream_Rectangle\n"));

    if (ret != BRST_OK)
        return ret;

    BRST_MemSet(buf, 0, BRST_TMP_BUF_SIZE);

    pbuf    = BRST_FToA(pbuf, x, eptr);
    *pbuf++ = ' ';
    pbuf    = BRST_FToA(pbuf, y, eptr);
    *pbuf++ = ' ';
    pbuf    = BRST_FToA(pbuf, width, eptr);
    *pbuf++ = ' ';
    pbuf    = BRST_FToA(pbuf, height, eptr);
    BRST_StrCpy(pbuf, " re\012", eptr);

    if (BRST_Stream_WriteStr(stream, buf) != BRST_OK)
        return BRST_Error_Check(stream->error);

    return ret;
}

/* w */
BRST_EXPORT(BRST_STATUS)
BRST_Stream_SetLineWidth(BRST_Stream stream,
    BRST_REAL line_width)
{
    BRST_STATUS ret =  BRST_Stream_Validate(stream);

    BRST_PTRACE((" BRST_Stream_SetLineWidth\n"));

    if (ret != BRST_OK)
        return ret;

    if (line_width < 0)
        return BRST_Error_Raise(stream->error, BRST_PAGE_OUT_OF_RANGE, 0);

    if (BRST_Stream_WriteReal(stream, line_width) != BRST_OK)
        return BRST_Error_Check(stream->error);

    if (BRST_Stream_WriteStr(stream, " w\012") != BRST_OK)
        return BRST_Error_Check(stream->error);

    return ret;
}

/* J */
BRST_EXPORT(BRST_STATUS)
BRST_Stream_SetLineCap(BRST_Stream stream,
    BRST_LineCap line_cap)
{
    BRST_STATUS ret =  BRST_Stream_Validate(stream);

    BRST_PTRACE((" BRST_Stream_SetLineCap\n"));

    if (ret != BRST_OK)
        return ret;

    if (line_cap >= BRST_LINECAP_EOF)
        return BRST_Error_Raise(stream->error, BRST_PAGE_OUT_OF_RANGE,
            (BRST_STATUS)line_cap);

    if ((ret = BRST_Stream_WriteInt(stream,
             (BRST_UINT)line_cap))
        != BRST_OK)
        return ret;

    if ((ret = BRST_Stream_WriteStr(stream,
             " J\012"))
        != BRST_OK)
        return BRST_Error_Check(stream->error);

    return ret;
}

/* j */
BRST_EXPORT(BRST_STATUS)
BRST_Stream_SetLineJoin(BRST_Stream stream,
    BRST_LineJoin line_join)
{
    BRST_STATUS ret =  BRST_Stream_Validate(stream);

    BRST_PTRACE((" BRST_Stream_SetLineJoin\n"));

    if (ret != BRST_OK)
        return ret;

    if (line_join >= BRST_LINEJOIN_EOF)
        return BRST_Error_Raise(stream->error, BRST_PAGE_OUT_OF_RANGE,
            (BRST_STATUS)line_join);

    if (BRST_Stream_WriteInt(stream, (BRST_UINT)line_join) != BRST_OK)
        return BRST_Error_Check(stream->error);

    if (BRST_Stream_WriteStr(stream, " j\012") != BRST_OK)
        return BRST_Error_Check(stream->error);

    return ret;
}

/* M */
BRST_EXPORT(BRST_STATUS)
BRST_Stream_SetMiterLimit(BRST_Stream stream,
    BRST_REAL miter_limit)
{
    BRST_STATUS ret =  BRST_Stream_Validate(stream);

    BRST_PTRACE((" BRST_Stream_SetMitterLimit\n"));

    if (ret != BRST_OK)
        return ret;

    if (miter_limit < 1)
        return BRST_Error_Raise(stream->error, BRST_PAGE_OUT_OF_RANGE, 0);

    if (BRST_Stream_WriteReal(stream, miter_limit) != BRST_OK)
        return BRST_Error_Check(stream->error);

    if (BRST_Stream_WriteStr(stream, " M\012") != BRST_OK)
        return BRST_Error_Check(stream->error);

    return ret;
}

/* d */
BRST_EXPORT(BRST_STATUS)
BRST_Stream_SetDash(BRST_Stream stream,
    const BRST_REAL* dash_ptn,
    BRST_UINT num_param,
    BRST_REAL phase)
{
    BRST_STATUS ret =  BRST_Stream_Validate(stream);

    char buf[BRST_TMP_BUF_SIZE];
    char* pbuf                 = buf;
    char* eptr                 = buf + BRST_TMP_BUF_SIZE - 1;
    const BRST_REAL* pdash_ptn = dash_ptn;

    BRST_UINT i;

    BRST_PTRACE((" BRST_Stream_SetDash\n"));

    if (ret != BRST_OK)
        return ret;

    if (num_param == 0 && phase > 0)
        return BRST_Error_Raise(stream->error, BRST_PAGE_OUT_OF_RANGE, 0);

    if (!dash_ptn && num_param > 0)
        return BRST_Error_Raise(stream->error, BRST_INVALID_PARAMETER, 0);

    BRST_MemSet(buf, 0, BRST_TMP_BUF_SIZE);
    *pbuf++ = '[';

    for (i = 0; i < num_param; i++) {
        if (*pdash_ptn == 0 || *pdash_ptn > BRST_MAX_DASH_PATTERN)
            return BRST_Error_Raise(stream->error, BRST_PAGE_OUT_OF_RANGE, 0);

        pbuf    = BRST_FToA(pbuf, *pdash_ptn, eptr);
        *pbuf++ = ' ';
        pdash_ptn++;
    }

    *pbuf++ = ']';
    *pbuf++ = ' ';

    pbuf = BRST_FToA(pbuf, phase, eptr);
    BRST_StrCpy(pbuf, " d\012", eptr);

    if ((ret = BRST_Stream_WriteStr(stream, buf)) != BRST_OK)
        return BRST_Error_Check(stream->error);

    return ret;
}

/* i */
BRST_EXPORT(BRST_STATUS)
BRST_Stream_SetFlat(BRST_Stream stream,
    BRST_REAL flatness)
{
    BRST_STATUS ret =  BRST_Stream_Validate(stream);

    BRST_PTRACE((" BRST_Stream_SetFlat\n"));

    if (ret != BRST_OK)
        return ret;

    if (flatness > 100 || flatness < 0)
        return BRST_Error_Raise(stream->error, BRST_PAGE_OUT_OF_RANGE, 0);

    if (BRST_Stream_WriteReal(stream, flatness) != BRST_OK)
        return BRST_Error_Check(stream->error);

    if (BRST_Stream_WriteStr(stream, " i\012") != BRST_OK)
        return BRST_Error_Check(stream->error);

    return ret;
}

/* sh */
/*

TODO MMgr?

BRST_EXPORT(BRST_STATUS)
BRST_Stream_SetShading(BRST_Stream stream,
    BRST_Shading shading)
{
    BRST_STATUS ret =  BRST_Stream_Validate(stream);

    const char* local_name;

    BRST_PTRACE((" BRST_Stream_SetShading\n"));

    if (ret != BRST_OK)
        return ret;

    if (page->mmgr != shading->mmgr)
        return BRST_Error_Raise(page->error, BRST_INVALID_OBJECT, 0);

    attr       = (BRST_PageAttr)page->attr;
    local_name = BRST_Page_ShadingName(page, shading);

    if (!local_name)
        return BRST_Error_Check(page->error);

    if (BRST_Stream_WriteEscapeName(attr->stream, local_name) != BRST_OK)
        return BRST_Error_Check(page->error);

    if (BRST_Stream_WriteStr(attr->stream, " sh\012") != BRST_OK)
        return BRST_Error_Check(page->error);

    return ret;
}
*/