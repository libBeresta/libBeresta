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
#include "brst_page.h"
#include "private/brst_page.h"
#include "brst_geometry_defines.h"
#include "private/brst_pages.h"
#include "private/brst_gstate.h"
#include "private/brst_page_attr.h"
#include "private/brst_encrypt_dict.h"
#include "brst_outline.h"
#include "private/brst_catalog.h"
#include "private/brst_c.h"
#include "brst_stream_geometry.h"

static BRST_STATUS
InternalArc(BRST_Page page,
    BRST_REAL x,
    BRST_REAL y,
    BRST_REAL ray,
    BRST_REAL ang1,
    BRST_REAL ang2,
    BRST_BOOL cont_flg);

/* ri --not implemented yet */
/* cs --not implemented yet */
/* CS --not implemented yet */
/* sc --not implemented yet */
/* scn --not implemented yet */
/* SC --not implemented yet */
/* SCN --not implemented yet */
/* sh --not implemented yet */
/* BI --not implemented yet */
/* ID --not implemented yet */
/* EI --not implemented yet */
/* BMC --not implemented yet */
/* BDC --not implemented yet */
/* EMC --not implemented yet */
/* MP --not implemented yet */
/* DP --not implemented yet */
/* BX --not implemented yet */
/* EX --not implemented yet */

static const BRST_REAL KAPPA = 0.552F;

static char*
QuarterCircleA(char* pbuf,
    char* eptr,
    BRST_REAL x,
    BRST_REAL y,
    BRST_REAL ray)
{
    pbuf    = BRST_FToA(pbuf, x - ray, eptr);
    *pbuf++ = ' ';
    pbuf    = BRST_FToA(pbuf, y + ray * KAPPA, eptr);
    *pbuf++ = ' ';
    pbuf    = BRST_FToA(pbuf, x - ray * KAPPA, eptr);
    *pbuf++ = ' ';
    pbuf    = BRST_FToA(pbuf, y + ray, eptr);
    *pbuf++ = ' ';
    pbuf    = BRST_FToA(pbuf, x, eptr);
    *pbuf++ = ' ';
    pbuf    = BRST_FToA(pbuf, y + ray, eptr);
    return (char*)BRST_StrCpy(pbuf, " c\012", eptr);
}

static char*
QuarterCircleB(char* pbuf,
    char* eptr,
    BRST_REAL x,
    BRST_REAL y,
    BRST_REAL ray)
{
    pbuf    = BRST_FToA(pbuf, x + ray * KAPPA, eptr);
    *pbuf++ = ' ';
    pbuf    = BRST_FToA(pbuf, y + ray, eptr);
    *pbuf++ = ' ';
    pbuf    = BRST_FToA(pbuf, x + ray, eptr);
    *pbuf++ = ' ';
    pbuf    = BRST_FToA(pbuf, y + ray * KAPPA, eptr);
    *pbuf++ = ' ';
    pbuf    = BRST_FToA(pbuf, x + ray, eptr);
    *pbuf++ = ' ';
    pbuf    = BRST_FToA(pbuf, y, eptr);
    return (char*)BRST_StrCpy(pbuf, " c\012", eptr);
}

static char*
QuarterCircleC(char* pbuf,
    char* eptr,
    BRST_REAL x,
    BRST_REAL y,
    BRST_REAL ray)
{
    pbuf    = BRST_FToA(pbuf, x + ray, eptr);
    *pbuf++ = ' ';
    pbuf    = BRST_FToA(pbuf, y - ray * KAPPA, eptr);
    *pbuf++ = ' ';
    pbuf    = BRST_FToA(pbuf, x + ray * KAPPA, eptr);
    *pbuf++ = ' ';
    pbuf    = BRST_FToA(pbuf, y - ray, eptr);
    *pbuf++ = ' ';
    pbuf    = BRST_FToA(pbuf, x, eptr);
    *pbuf++ = ' ';
    pbuf    = BRST_FToA(pbuf, y - ray, eptr);
    return (char*)BRST_StrCpy(pbuf, " c\012", eptr);
}

static char*
QuarterCircleD(char* pbuf,
    char* eptr,
    BRST_REAL x,
    BRST_REAL y,
    BRST_REAL ray)
{
    pbuf    = BRST_FToA(pbuf, x - ray * KAPPA, eptr);
    *pbuf++ = ' ';
    pbuf    = BRST_FToA(pbuf, y - ray, eptr);
    *pbuf++ = ' ';
    pbuf    = BRST_FToA(pbuf, x - ray, eptr);
    *pbuf++ = ' ';
    pbuf    = BRST_FToA(pbuf, y - ray * KAPPA, eptr);
    *pbuf++ = ' ';
    pbuf    = BRST_FToA(pbuf, x - ray, eptr);
    *pbuf++ = ' ';
    pbuf    = BRST_FToA(pbuf, y, eptr);
    return (char*)BRST_StrCpy(pbuf, " c\012", eptr);
}

static char*
QuarterEllipseA(char* pbuf,
    char* eptr,
    BRST_REAL x,
    BRST_REAL y,
    BRST_REAL xray,
    BRST_REAL yray)
{
    pbuf    = BRST_FToA(pbuf, x - xray, eptr);
    *pbuf++ = ' ';
    pbuf    = BRST_FToA(pbuf, y + yray * KAPPA, eptr);
    *pbuf++ = ' ';
    pbuf    = BRST_FToA(pbuf, x - xray * KAPPA, eptr);
    *pbuf++ = ' ';
    pbuf    = BRST_FToA(pbuf, y + yray, eptr);
    *pbuf++ = ' ';
    pbuf    = BRST_FToA(pbuf, x, eptr);
    *pbuf++ = ' ';
    pbuf    = BRST_FToA(pbuf, y + yray, eptr);
    return (char*)BRST_StrCpy(pbuf, " c\012", eptr);
}

static char*
QuarterEllipseB(char* pbuf,
    char* eptr,
    BRST_REAL x,
    BRST_REAL y,
    BRST_REAL xray,
    BRST_REAL yray)
{
    pbuf    = BRST_FToA(pbuf, x + xray * KAPPA, eptr);
    *pbuf++ = ' ';
    pbuf    = BRST_FToA(pbuf, y + yray, eptr);
    *pbuf++ = ' ';
    pbuf    = BRST_FToA(pbuf, x + xray, eptr);
    *pbuf++ = ' ';
    pbuf    = BRST_FToA(pbuf, y + yray * KAPPA, eptr);
    *pbuf++ = ' ';
    pbuf    = BRST_FToA(pbuf, x + xray, eptr);
    *pbuf++ = ' ';
    pbuf    = BRST_FToA(pbuf, y, eptr);
    return (char*)BRST_StrCpy(pbuf, " c\012", eptr);
}

static char*
QuarterEllipseC(char* pbuf,
    char* eptr,
    BRST_REAL x,
    BRST_REAL y,
    BRST_REAL xray,
    BRST_REAL yray)
{
    pbuf    = BRST_FToA(pbuf, x + xray, eptr);
    *pbuf++ = ' ';
    pbuf    = BRST_FToA(pbuf, y - yray * KAPPA, eptr);
    *pbuf++ = ' ';
    pbuf    = BRST_FToA(pbuf, x + xray * KAPPA, eptr);
    *pbuf++ = ' ';
    pbuf    = BRST_FToA(pbuf, y - yray, eptr);
    *pbuf++ = ' ';
    pbuf    = BRST_FToA(pbuf, x, eptr);
    *pbuf++ = ' ';
    pbuf    = BRST_FToA(pbuf, y - yray, eptr);
    return (char*)BRST_StrCpy(pbuf, " c\012", eptr);
}

static char*
QuarterEllipseD(char* pbuf,
    char* eptr,
    BRST_REAL x,
    BRST_REAL y,
    BRST_REAL xray,
    BRST_REAL yray)
{
    pbuf    = BRST_FToA(pbuf, x - xray * KAPPA, eptr);
    *pbuf++ = ' ';
    pbuf    = BRST_FToA(pbuf, y - yray, eptr);
    *pbuf++ = ' ';
    pbuf    = BRST_FToA(pbuf, x - xray, eptr);
    *pbuf++ = ' ';
    pbuf    = BRST_FToA(pbuf, y - yray * KAPPA, eptr);
    *pbuf++ = ' ';
    pbuf    = BRST_FToA(pbuf, x - xray, eptr);
    *pbuf++ = ' ';
    pbuf    = BRST_FToA(pbuf, y, eptr);
    return (char*)BRST_StrCpy(pbuf, " c\012", eptr);
}

static BRST_STATUS
InternalArc(BRST_Page page,
    BRST_REAL x,
    BRST_REAL y,
    BRST_REAL ray,
    BRST_REAL ang1,
    BRST_REAL ang2,
    BRST_BOOL cont_flg)
{
    char buf[BRST_TMP_BUF_SIZE];
    char* pbuf = buf;
    char* eptr = buf + BRST_TMP_BUF_SIZE - 1;
    BRST_PageAttr attr;
    BRST_STATUS ret;

    BRST_DOUBLE rx0, ry0, rx1, ry1, rx2, ry2, rx3, ry3;
    BRST_DOUBLE x0, y0, x1, y1, x2, y2, x3, y3;
    BRST_DOUBLE delta_angle;
    BRST_DOUBLE new_angle;

    BRST_PTRACE(" BRST_Page_InternalArc\n");

    attr = (BRST_PageAttr)page->attr;

    BRST_MemSet(buf, 0, BRST_TMP_BUF_SIZE);

    delta_angle = (90 - (BRST_DOUBLE)(ang1 + ang2) / 2) / 180 * BRST_PI;
    new_angle   = (BRST_DOUBLE)(ang2 - ang1) / 2 / 180 * BRST_PI;

    rx0 = ray * BRST_COS(new_angle);
    ry0 = ray * BRST_SIN(new_angle);
    rx2 = (ray * 4.0 - rx0) / 3.0;
    ry2 = ((ray * 1.0 - rx0) * (rx0 - ray * 3.0)) / (3.0 * ry0);
    rx1 = rx2;
    ry1 = -ry2;
    rx3 = rx0;
    ry3 = -ry0;

    x0 = rx0 * BRST_COS(delta_angle) - ry0 * BRST_SIN(delta_angle) + x;
    y0 = rx0 * BRST_SIN(delta_angle) + ry0 * BRST_COS(delta_angle) + y;
    x1 = rx1 * BRST_COS(delta_angle) - ry1 * BRST_SIN(delta_angle) + x;
    y1 = rx1 * BRST_SIN(delta_angle) + ry1 * BRST_COS(delta_angle) + y;
    x2 = rx2 * BRST_COS(delta_angle) - ry2 * BRST_SIN(delta_angle) + x;
    y2 = rx2 * BRST_SIN(delta_angle) + ry2 * BRST_COS(delta_angle) + y;
    x3 = rx3 * BRST_COS(delta_angle) - ry3 * BRST_SIN(delta_angle) + x;
    y3 = rx3 * BRST_SIN(delta_angle) + ry3 * BRST_COS(delta_angle) + y;

    if (!cont_flg) {
        pbuf    = BRST_FToA(pbuf, (BRST_REAL)x0, eptr);
        *pbuf++ = ' ';
        pbuf    = BRST_FToA(pbuf, (BRST_REAL)y0, eptr);

        if (attr->gmode == BRST_GMODE_PATH_OBJECT)
            pbuf = (char*)BRST_StrCpy(pbuf, " l\012", eptr);
        else
            pbuf = (char*)BRST_StrCpy(pbuf, " m\012", eptr);
    }

    pbuf    = BRST_FToA(pbuf, (BRST_REAL)x1, eptr);
    *pbuf++ = ' ';
    pbuf    = BRST_FToA(pbuf, (BRST_REAL)y1, eptr);
    *pbuf++ = ' ';
    pbuf    = BRST_FToA(pbuf, (BRST_REAL)x2, eptr);
    *pbuf++ = ' ';
    pbuf    = BRST_FToA(pbuf, (BRST_REAL)y2, eptr);
    *pbuf++ = ' ';
    pbuf    = BRST_FToA(pbuf, (BRST_REAL)x3, eptr);
    *pbuf++ = ' ';
    pbuf    = BRST_FToA(pbuf, (BRST_REAL)y3, eptr);
    BRST_StrCpy(pbuf, " c\012", eptr);

    if ((ret = BRST_Stream_WriteStr(attr->stream, buf)) != BRST_OK)
        return BRST_Error_Check(attr->stream->error);

    attr->cur_pos.x = (BRST_REAL)x3;
    attr->cur_pos.y = (BRST_REAL)y3;
    attr->str_pos   = attr->cur_pos;
    attr->gmode     = BRST_GMODE_PATH_OBJECT;

    return ret;
}

/* q */
BRST_EXPORT(BRST_STATUS)
BRST_Page_GSave(BRST_Page page)
{
    BRST_GState new_gstate;
    BRST_PageAttr attr;
    BRST_STATUS ret = BRST_Page_CheckState(page, BRST_GMODE_PAGE_DESCRIPTION);

    BRST_PTRACE(" BRST_Page_GSave\n");

    if (ret != BRST_OK)
        return ret;

    attr = (BRST_PageAttr)page->attr;

    new_gstate = BRST_GState_New(page->mmgr, attr->gstate);
    if (!new_gstate)
        return BRST_Error_Check(page->error);

    if (BRST_Stream_WriteStr(attr->stream, "q\012") != BRST_OK)
        return BRST_Error_Check(page->error);

    attr->gstate = new_gstate;

    return ret;
}

/* Q */
BRST_EXPORT(BRST_STATUS)
BRST_Page_GRestore(BRST_Page page)
{
    BRST_GState new_gstate;
    BRST_PageAttr attr;
    BRST_STATUS ret = BRST_Page_CheckState(page, BRST_GMODE_PAGE_DESCRIPTION);

    BRST_PTRACE(" BRST_Page_GRestore\n");

    if (ret != BRST_OK)
        return ret;

    attr = (BRST_PageAttr)page->attr;

    if (!attr->gstate->prev)
        return BRST_Error_Raise(page->error, BRST_PAGE_CANNOT_RESTORE_GSTATE,
            0);

    new_gstate = BRST_GState_Free(page->mmgr, attr->gstate);

    attr->gstate = new_gstate;

    if (BRST_Stream_WriteStr(attr->stream, "Q\012") != BRST_OK)
        return BRST_Error_Check(page->error);

    return ret;
}

/* cm */
BRST_EXPORT(BRST_STATUS)
BRST_Page_Concat(BRST_Page page,
    BRST_REAL a,
    BRST_REAL b,
    BRST_REAL c,
    BRST_REAL d,
    BRST_REAL x,
    BRST_REAL y)
{
    BRST_STATUS ret = BRST_Page_CheckState(page, BRST_GMODE_PAGE_DESCRIPTION);

    BRST_PageAttr attr;
    BRST_TransMatrix tm;

    BRST_PTRACE(" BRST_Page_Concat\n");

    if (ret != BRST_OK)
        return ret;

    attr = (BRST_PageAttr)page->attr;

    if (BRST_Stream_Concat(attr->stream, a, b, c, d, x, y) != BRST_OK) {
        BRST_Error_Copy(page->error, attr->stream->error);
        return BRST_Error_Check(page->error);
    }

    tm = attr->gstate->trans_matrix;
    /*
    | ta tb 0 |   | a b |   | ta*a+tb*c   ta*b+tb*d   |
    | tc td 0 | x | c d | = | tc*a+td*c   tc*b+td*d   |
    | tx ty 1 |   | x y |   | tx*a+ty*c+x tx*b+ty*d+y |
    */
    attr->gstate->trans_matrix.a = tm.a * a + tm.b * c;
    attr->gstate->trans_matrix.b = tm.a * b + tm.b * d;
    attr->gstate->trans_matrix.c = tm.c * a + tm.d * c;
    attr->gstate->trans_matrix.d = tm.c * b + tm.d * d;
    attr->gstate->trans_matrix.x = tm.x * a + tm.y * c + x;
    attr->gstate->trans_matrix.y = tm.x * b + tm.y * d + y;

    return ret;
}

BRST_EXPORT(BRST_STATUS)
BRST_Page_Translate(BRST_Page page,
    BRST_REAL dx,
    BRST_REAL dy)
{
    BRST_PTRACE(" BRST_Page_Translate\n");
    return BRST_Page_Concat(page, 1, 0, 0, 1, dx, dy);
}

BRST_EXPORT(BRST_STATUS)
BRST_Page_Scale(BRST_Page page,
    BRST_REAL sx,
    BRST_REAL sy)
{
    BRST_PTRACE(" BRST_Page_Scale\n");
    return BRST_Page_Concat(page, sx, 0, 0, sy, 0, 0);
}

BRST_EXPORT(BRST_STATUS)
BRST_Page_Rotate(BRST_Page page,
    BRST_REAL a)
{
    BRST_PTRACE(" BRST_Page_Rotate\n");
    return BRST_Page_Concat(page, cos(a), sin(a), -sin(a), cos(a), 0, 0);
}

BRST_EXPORT(BRST_STATUS)
BRST_Page_RotateDeg(BRST_Page page,
    BRST_REAL degrees)
{
    BRST_PTRACE(" BRST_Page_RotateDeg\n");
    BRST_REAL a = degrees * BRST_PI / 180.0;
    return BRST_Page_Concat(page, cos(a), sin(a), -sin(a), cos(a), 0, 0);
}

BRST_EXPORT(BRST_STATUS)
BRST_Page_Skew(BRST_Page page,
    BRST_REAL a,
    BRST_REAL b)
{
    BRST_PTRACE(" BRST_Page_Skew\n");
    return BRST_Page_Concat(page, 1, tan(a), tan(b), 1, 0, 0);
}

BRST_EXPORT(BRST_STATUS)
BRST_Page_Circle(BRST_Page page,
    BRST_REAL x,
    BRST_REAL y,
    BRST_REAL ray)
{
    BRST_STATUS ret = BRST_Page_CheckState(page, BRST_GMODE_PAGE_DESCRIPTION | BRST_GMODE_PATH_OBJECT);
    char buf[BRST_TMP_BUF_SIZE * 2];
    char* pbuf = buf;
    char* eptr = buf + BRST_TMP_BUF_SIZE - 1;
    BRST_PageAttr attr;

    BRST_PTRACE(" BRST_Page_Circle\n");

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
BRST_Page_Ellipse(BRST_Page page,
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

    BRST_PTRACE(" BRST_Page_Ellipse\n");

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

/*
 * this function is based on the code which is contributed by Riccardo Cohen.
 *
 * from http://www.tinaja.com/glib/bezarc1.pdf coming from
 * http://www.whizkidtech.redprince.net/bezier/circle/
 */
BRST_EXPORT(BRST_STATUS)
BRST_Page_Arc(BRST_Page page,
    BRST_REAL x,
    BRST_REAL y,
    BRST_REAL ray,
    BRST_REAL ang1,
    BRST_REAL ang2)
{
    BRST_BOOL cont_flg = BRST_FALSE;

    BRST_STATUS ret = BRST_Page_CheckState(page, BRST_GMODE_PAGE_DESCRIPTION | BRST_GMODE_PATH_OBJECT);

    BRST_PTRACE(" BRST_Page_Arc\n");

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

/* g */
BRST_EXPORT(BRST_STATUS)
BRST_Page_SetGrayFill(BRST_Page page,
    BRST_REAL gray)
{
    BRST_STATUS ret = BRST_Page_CheckState(page, BRST_GMODE_PAGE_DESCRIPTION | BRST_GMODE_TEXT_OBJECT);
    BRST_PageAttr attr;

    BRST_PTRACE(" BRST_Page_SetGrayFill\n");

    if (ret != BRST_OK)
        return ret;

    attr = (BRST_PageAttr)page->attr;

    if (BRST_Stream_SetGrayFill(attr->stream, gray) != BRST_OK) {
        BRST_Error_Copy(page->error, attr->stream->error);
        return BRST_Error_Check(page->error);
    }

    attr->gstate->gray_fill = gray;
    attr->gstate->cs_fill   = BRST_CS_DEVICE_GRAY;

    return ret;
}

/* G */
BRST_EXPORT(BRST_STATUS)
BRST_Page_SetGrayStroke(BRST_Page page,
    BRST_REAL gray)
{
    BRST_STATUS ret = BRST_Page_CheckState(page, BRST_GMODE_PAGE_DESCRIPTION | BRST_GMODE_TEXT_OBJECT);
    BRST_PageAttr attr;

    BRST_PTRACE(" BRST_Page_SetGrayStroke\n");

    if (ret != BRST_OK)
        return ret;

    attr = (BRST_PageAttr)page->attr;

    if (BRST_Stream_SetGrayStroke(attr->stream, gray) != BRST_OK) {
        BRST_Error_Copy(page->error, attr->stream->error);
        return BRST_Error_Check(page->error);
    }

    attr->gstate->gray_stroke = gray;
    attr->gstate->cs_stroke   = BRST_CS_DEVICE_GRAY;

    return ret;
}

/* rg */
BRST_EXPORT(BRST_STATUS)
BRST_Page_SetRGBFill(BRST_Page page,
    BRST_REAL r,
    BRST_REAL g,
    BRST_REAL b)
{
    BRST_STATUS ret = BRST_Page_CheckState(page, BRST_GMODE_TEXT_OBJECT | BRST_GMODE_PAGE_DESCRIPTION);

    BRST_PTRACE(" BRST_Page_SetRGBFill\n");

    if (ret != BRST_OK)
        return ret;

    BRST_PageAttr attr = (BRST_PageAttr)page->attr;

    if (BRST_Stream_SetRGBFill(attr->stream, r, g, b) != BRST_OK) {
        BRST_Error_Copy(page->error, attr->stream->error);
        return BRST_Error_Check(page->error);
    }

    attr->gstate->rgb_fill.r = r;
    attr->gstate->rgb_fill.g = g;
    attr->gstate->rgb_fill.b = b;
    attr->gstate->cs_fill    = BRST_CS_DEVICE_RGB;

    return ret;
}

/* RG */
BRST_EXPORT(BRST_STATUS)
BRST_Page_SetRGBStroke(BRST_Page page,
    BRST_REAL r,
    BRST_REAL g,
    BRST_REAL b)
{
    BRST_STATUS ret = BRST_Page_CheckState(page, BRST_GMODE_TEXT_OBJECT | BRST_GMODE_PAGE_DESCRIPTION);

    BRST_PTRACE(" BRST_Page_SetRGBStroke\n");

    if (ret != BRST_OK)
        return ret;

    BRST_PageAttr attr = (BRST_PageAttr)page->attr;

    if (BRST_Stream_SetRGBStroke(attr->stream, r, g, b) != BRST_OK) {
        BRST_Error_Copy(page->error, attr->stream->error);
        return BRST_Error_Check(page->error);
    }

    attr->gstate->rgb_stroke.r = r;
    attr->gstate->rgb_stroke.g = g;
    attr->gstate->rgb_stroke.b = b;
    attr->gstate->cs_stroke    = BRST_CS_DEVICE_RGB;

    return ret;
}

BRST_EXPORT(BRST_STATUS)
BRST_Page_SetRGBStrokeUint(BRST_Page page,
    BRST_UINT8 r,
    BRST_UINT8 g,
    BRST_UINT8 b)
{
    BRST_REAL rr = (BRST_REAL)r / 255.0;
    BRST_REAL rg = (BRST_REAL)g / 255.0;
    BRST_REAL rb = (BRST_REAL)b / 255.0;

    return BRST_Page_SetRGBStroke(page, rr, rg, rb);
}

BRST_EXPORT(BRST_STATUS)
BRST_Page_SetRGBStrokeHex(BRST_Page page, BRST_UINT32 rgb)
{
    return BRST_Page_SetRGBStrokeUint(page, (rgb >> 16) & 0xFF, (rgb >> 8) & 0xFF, rgb & 0xFF);
}

BRST_EXPORT(BRST_STATUS)
BRST_Page_SetRGBFillUint(BRST_Page page,
    BRST_UINT8 r,
    BRST_UINT8 g,
    BRST_UINT8 b)
{
    BRST_REAL rr = (BRST_REAL)r / 255.0;
    BRST_REAL rg = (BRST_REAL)g / 255.0;
    BRST_REAL rb = (BRST_REAL)b / 255.0;

    return BRST_Page_SetRGBFill(page, rr, rg, rb);
}

BRST_EXPORT(BRST_STATUS)
BRST_Page_SetRGBFillHex(BRST_Page page, BRST_UINT32 rgb)
{
    return BRST_Page_SetRGBFillUint(page, (rgb >> 16) & 0xFF, (rgb >> 8) & 0xFF, rgb & 0xFF);
}

/* k */
BRST_EXPORT(BRST_STATUS)
BRST_Page_SetCMYKFill(BRST_Page page,
    BRST_REAL c,
    BRST_REAL m,
    BRST_REAL y,
    BRST_REAL k)
{
    BRST_STATUS ret = BRST_Page_CheckState(page, BRST_GMODE_TEXT_OBJECT | BRST_GMODE_PAGE_DESCRIPTION);

    BRST_PTRACE(" BRST_Page_SetCMYKFill\n");

    if (ret != BRST_OK)
        return ret;

    BRST_PageAttr attr = (BRST_PageAttr)page->attr;

    if (BRST_Stream_SetCMYKFill(attr->stream, c, m, y, k) != BRST_OK) {
        BRST_Error_Copy(page->error, attr->stream->error);
        return BRST_Error_Check(page->error);
    }

    attr->gstate->cmyk_fill.c = c;
    attr->gstate->cmyk_fill.m = m;
    attr->gstate->cmyk_fill.y = y;
    attr->gstate->cmyk_fill.k = k;
    attr->gstate->cs_fill     = BRST_CS_DEVICE_CMYK;

    return ret;
}

/* K */
BRST_EXPORT(BRST_STATUS)
BRST_Page_SetCMYKStroke(BRST_Page page,
    BRST_REAL c,
    BRST_REAL m,
    BRST_REAL y,
    BRST_REAL k)
{
    BRST_STATUS ret = BRST_Page_CheckState(page, BRST_GMODE_TEXT_OBJECT | BRST_GMODE_PAGE_DESCRIPTION);

    BRST_PTRACE(" BRST_Page_SetCMYKStroke\n");

    if (ret != BRST_OK)
        return ret;

    BRST_PageAttr attr = (BRST_PageAttr)page->attr;

    if (BRST_Stream_SetCMYKStroke(attr->stream, c, m, y, k) != BRST_OK) {
        BRST_Error_Copy(page->error, attr->stream->error);
        return BRST_Error_Check(page->error);
    }

    attr->gstate->cmyk_stroke.c = c;
    attr->gstate->cmyk_stroke.m = m;
    attr->gstate->cmyk_stroke.y = y;
    attr->gstate->cmyk_stroke.k = k;
    attr->gstate->cs_stroke     = BRST_CS_DEVICE_CMYK;

    return ret;
}

/* W */
BRST_EXPORT(BRST_STATUS)
BRST_Page_Clip(BRST_Page page)
{
    BRST_STATUS ret = BRST_Page_CheckState(page, BRST_GMODE_PATH_OBJECT);

    BRST_PTRACE(" BRST_Page_Clip\n");

    if (ret != BRST_OK)
        return ret;

    BRST_PageAttr attr = (BRST_PageAttr)page->attr;

    if (BRST_Stream_Clip(attr->stream) != BRST_OK) {
        BRST_Error_Copy(page->error, attr->stream->error);
        return BRST_Error_Check(page->error);
    }

    attr->gmode = BRST_GMODE_CLIPPING_PATH;

    return ret;
}

/* W* */
BRST_EXPORT(BRST_STATUS)
BRST_Page_Eoclip(BRST_Page page)
{
    BRST_STATUS ret = BRST_Page_CheckState(page, BRST_GMODE_PATH_OBJECT);

    BRST_PTRACE(" BRST_Page_Eoclip\n");

    if (ret != BRST_OK)
        return ret;

    BRST_PageAttr attr = (BRST_PageAttr)page->attr;

    if (BRST_Stream_Eoclip(attr->stream) != BRST_OK) {
        BRST_Error_Copy(page->error, attr->stream->error);
        return BRST_Error_Check(page->error);
    }

    attr->gmode = BRST_GMODE_CLIPPING_PATH;

    return ret;
}

/* S */
BRST_EXPORT(BRST_STATUS)
BRST_Page_Stroke(BRST_Page page)
{
    BRST_STATUS ret = BRST_Page_CheckState(page, BRST_GMODE_PATH_OBJECT | BRST_GMODE_CLIPPING_PATH);

    BRST_PTRACE(" BRST_Page_Stroke\n");

    if (ret != BRST_OK)
        return ret;

    BRST_PageAttr attr = (BRST_PageAttr)page->attr;

    if (BRST_Stream_Stroke(attr->stream) != BRST_OK) {
        BRST_Error_Copy(page->error, attr->stream->error);
        return BRST_Error_Check(page->error);
    }

    attr->gmode   = BRST_GMODE_PAGE_DESCRIPTION;
    attr->cur_pos = INIT_POS;

    return ret;
}

/* s */
BRST_EXPORT(BRST_STATUS)
BRST_Page_ClosePathStroke(BRST_Page page)
{
    BRST_STATUS ret = BRST_Page_CheckState(page, BRST_GMODE_PATH_OBJECT | BRST_GMODE_CLIPPING_PATH);

    BRST_PTRACE(" BRST_Page_ClosePathStroke\n");

    if (ret != BRST_OK)
        return ret;

    BRST_PageAttr attr = (BRST_PageAttr)page->attr;

    if (BRST_Stream_ClosePathStroke(attr->stream) != BRST_OK) {
        BRST_Error_Copy(page->error, attr->stream->error);
        return BRST_Error_Check(page->error);
    }

    attr->gmode   = BRST_GMODE_PAGE_DESCRIPTION;
    attr->cur_pos = INIT_POS;

    return ret;
}

/* f */
BRST_EXPORT(BRST_STATUS)
BRST_Page_Fill(BRST_Page page)
{
    BRST_STATUS ret = BRST_Page_CheckState(page, BRST_GMODE_PATH_OBJECT | BRST_GMODE_CLIPPING_PATH);

    BRST_PTRACE(" BRST_Page_Fill\n");

    if (ret != BRST_OK)
        return ret;

    BRST_PageAttr attr = (BRST_PageAttr)page->attr;

    if (BRST_Stream_Fill(attr->stream) != BRST_OK) {
        BRST_Error_Copy(page->error, attr->stream->error);
        return BRST_Error_Check(page->error);
    }

    attr->gmode   = BRST_GMODE_PAGE_DESCRIPTION;
    attr->cur_pos = INIT_POS;

    return ret;
}

/* f* */
BRST_EXPORT(BRST_STATUS)
BRST_Page_Eofill(BRST_Page page)
{
    BRST_STATUS ret = BRST_Page_CheckState(page, BRST_GMODE_PATH_OBJECT | BRST_GMODE_CLIPPING_PATH);

    BRST_PTRACE(" BRST_Page_Eofill\n");

    if (ret != BRST_OK)
        return ret;

    BRST_PageAttr attr = (BRST_PageAttr)page->attr;

    if (BRST_Stream_Eofill(attr->stream) != BRST_OK) {
        BRST_Error_Copy(page->error, attr->stream->error);
        return BRST_Error_Check(page->error);
    }

    attr->gmode   = BRST_GMODE_PAGE_DESCRIPTION;
    attr->cur_pos = INIT_POS;

    return ret;
}

/* B */
BRST_EXPORT(BRST_STATUS)
BRST_Page_FillStroke(BRST_Page page)
{
    BRST_STATUS ret = BRST_Page_CheckState(page, BRST_GMODE_PATH_OBJECT | BRST_GMODE_CLIPPING_PATH);

    BRST_PTRACE(" BRST_Page_FillStroke\n");

    if (ret != BRST_OK)
        return ret;

    BRST_PageAttr attr = (BRST_PageAttr)page->attr;

    if (BRST_Stream_FillStroke(attr->stream) != BRST_OK) {
        BRST_Error_Copy(page->error, attr->stream->error);
        return BRST_Error_Check(page->error);
    }

    attr->gmode   = BRST_GMODE_PAGE_DESCRIPTION;
    attr->cur_pos = INIT_POS;

    return ret;
}

/* B* */
BRST_EXPORT(BRST_STATUS)
BRST_Page_EofillStroke(BRST_Page page)
{
    BRST_STATUS ret = BRST_Page_CheckState(page, BRST_GMODE_PATH_OBJECT | BRST_GMODE_CLIPPING_PATH);

    BRST_PTRACE(" BRST_Page_EofillStroke\n");

    if (ret != BRST_OK)
        return ret;

    BRST_PageAttr attr = (BRST_PageAttr)page->attr;

    if (BRST_Stream_EofillStroke(attr->stream) != BRST_OK) {
        BRST_Error_Copy(page->error, attr->stream->error);
        return BRST_Error_Check(page->error);
    }
    attr->gmode = BRST_GMODE_PAGE_DESCRIPTION;

    return ret;
}

/* b */
BRST_EXPORT(BRST_STATUS)
BRST_Page_ClosePathFillStroke(BRST_Page page)
{
    BRST_STATUS ret = BRST_Page_CheckState(page, BRST_GMODE_PATH_OBJECT | BRST_GMODE_CLIPPING_PATH);

    BRST_PTRACE(" BRST_Page_ClosePathFillStroke\n");

    if (ret != BRST_OK)
        return ret;

    BRST_PageAttr attr = (BRST_PageAttr)page->attr;

    if (BRST_Stream_ClosePathFillStroke(attr->stream) != BRST_OK) {
        BRST_Error_Copy(page->error, attr->stream->error);
        return BRST_Error_Check(page->error);
    }

    attr->gmode   = BRST_GMODE_PAGE_DESCRIPTION;
    attr->cur_pos = INIT_POS;

    return ret;
}

/* b* */
BRST_EXPORT(BRST_STATUS)
BRST_Page_ClosePathEofillStroke(BRST_Page page)
{
    BRST_STATUS ret = BRST_Page_CheckState(page, BRST_GMODE_PATH_OBJECT | BRST_GMODE_CLIPPING_PATH);

    BRST_PTRACE(" BRST_Page_ClosePathEofillStroke\n");

    if (ret != BRST_OK)
        return ret;

    BRST_PageAttr attr = (BRST_PageAttr)page->attr;

    if (BRST_Stream_ClosePathEofillStroke(attr->stream) != BRST_OK) {
        BRST_Error_Copy(page->error, attr->stream->error);
        return BRST_Error_Check(page->error);
    }

    attr->gmode   = BRST_GMODE_PAGE_DESCRIPTION;
    attr->cur_pos = INIT_POS;

    return ret;
}

/* n */
BRST_EXPORT(BRST_STATUS)
BRST_Page_EndPath(BRST_Page page)
{
    BRST_STATUS ret = BRST_Page_CheckState(page, BRST_GMODE_PATH_OBJECT | BRST_GMODE_CLIPPING_PATH);

    BRST_PTRACE(" BRST_PageEndPath\n");

    if (ret != BRST_OK)
        return ret;

    BRST_PageAttr attr = (BRST_PageAttr)page->attr;

    if (BRST_Stream_EndPath(attr->stream) != BRST_OK) {
        BRST_Error_Copy(page->error, attr->stream->error);
        return BRST_Error_Check(page->error);
    }

    attr->gmode   = BRST_GMODE_PAGE_DESCRIPTION;
    attr->cur_pos = INIT_POS;

    return ret;
}

/* m */
BRST_EXPORT(BRST_STATUS)
BRST_Page_MoveTo(BRST_Page page,
    BRST_REAL x,
    BRST_REAL y)
{
    BRST_STATUS ret = BRST_Page_CheckState(page, BRST_GMODE_PAGE_DESCRIPTION | BRST_GMODE_PATH_OBJECT);

    BRST_PTRACE(" BRST_Page_MoveTo\n");

    if (ret != BRST_OK)
        return ret;

    BRST_PageAttr attr = (BRST_PageAttr)page->attr;

    if (BRST_Stream_MoveTo(attr->stream, x, y) != BRST_OK) {
        BRST_Error_Copy(page->error, attr->stream->error);
        return BRST_Error_Check(page->error);
    }

    attr->cur_pos.x = x;
    attr->cur_pos.y = y;
    attr->str_pos   = attr->cur_pos;
    attr->gmode     = BRST_GMODE_PATH_OBJECT;

    return ret;
}

/* l */
BRST_EXPORT(BRST_STATUS)
BRST_Page_LineTo(BRST_Page page,
    BRST_REAL x,
    BRST_REAL y)
{
    BRST_STATUS ret = BRST_Page_CheckState(page, BRST_GMODE_PATH_OBJECT);

    BRST_PTRACE(" BRST_Page_LineTo\n");

    if (ret != BRST_OK)
        return ret;

    BRST_PageAttr attr = (BRST_PageAttr)page->attr;

    if (BRST_Stream_LineTo(attr->stream, x, y) != BRST_OK) {
        BRST_Error_Copy(page->error, attr->stream->error);
        return BRST_Error_Check(page->error);
    }

    attr->cur_pos.x = x;
    attr->cur_pos.y = y;

    return ret;
}

/* c */
BRST_EXPORT(BRST_STATUS)
BRST_Page_CurveTo(BRST_Page page,
    BRST_REAL x1,
    BRST_REAL y1,
    BRST_REAL x2,
    BRST_REAL y2,
    BRST_REAL x3,
    BRST_REAL y3)
{
    BRST_STATUS ret = BRST_Page_CheckState(page, BRST_GMODE_PATH_OBJECT);

    BRST_PTRACE(" BRST_Page_CurveTo\n");

    if (ret != BRST_OK)
        return ret;

    BRST_PageAttr attr = (BRST_PageAttr)page->attr;

    if (BRST_Stream_CurveTo(attr->stream, x1, y1, x2, y2, x3, y3) != BRST_OK) {
        BRST_Error_Copy(page->error, attr->stream->error);
        return BRST_Error_Check(page->error);
    }

    attr->cur_pos.x = x3;
    attr->cur_pos.y = y3;

    return ret;
}

/* v */
BRST_EXPORT(BRST_STATUS)
BRST_Page_CurveTo2(BRST_Page page,
    BRST_REAL x2,
    BRST_REAL y2,
    BRST_REAL x3,
    BRST_REAL y3)
{
    BRST_STATUS ret = BRST_Page_CheckState(page, BRST_GMODE_PATH_OBJECT);

    BRST_PTRACE(" BRST_Page_CurveTo2\n");

    if (ret != BRST_OK)
        return ret;

    BRST_PageAttr attr = (BRST_PageAttr)page->attr;

    if (BRST_Stream_CurveTo2(attr->stream, x2, y2, x3, y3) != BRST_OK) {
        BRST_Error_Copy(page->error, attr->stream->error);
        return BRST_Error_Check(page->error);
    }

    attr->cur_pos.x = x3;
    attr->cur_pos.y = y3;

    return ret;
}

/* y */
BRST_EXPORT(BRST_STATUS)
BRST_Page_CurveTo3(BRST_Page page,
    BRST_REAL x1,
    BRST_REAL y1,
    BRST_REAL x3,
    BRST_REAL y3)
{
    BRST_STATUS ret = BRST_Page_CheckState(page, BRST_GMODE_PATH_OBJECT);

    BRST_PTRACE(" BRST_Page_CurveTo3\n");

    if (ret != BRST_OK)
        return ret;

    BRST_PageAttr attr = (BRST_PageAttr)page->attr;

    if (BRST_Stream_CurveTo3(attr->stream, x1, y1, x3, y3) != BRST_OK) {
        BRST_Error_Copy(page->error, attr->stream->error);
        return BRST_Error_Check(page->error);
    }

    attr->cur_pos.x = x3;
    attr->cur_pos.y = y3;

    return ret;
}

/* h */
BRST_EXPORT(BRST_STATUS)
BRST_Page_ClosePath(BRST_Page page)
{
    BRST_STATUS ret = BRST_Page_CheckState(page, BRST_GMODE_PATH_OBJECT);

    BRST_PTRACE(" BRST_Page_ClosePath\n");

    if (ret != BRST_OK)
        return ret;

    BRST_PageAttr attr = (BRST_PageAttr)page->attr;

    if (BRST_Stream_ClosePath(attr->stream) != BRST_OK) {
        BRST_Error_Copy(page->error, attr->stream->error);
        return BRST_Error_Check(page->error);
    }

    attr->cur_pos = attr->str_pos;

    return ret;
}

/* re */
BRST_EXPORT(BRST_STATUS)
BRST_Page_Rectangle(BRST_Page page,
    BRST_REAL x,
    BRST_REAL y,
    BRST_REAL width,
    BRST_REAL height)
{
    BRST_STATUS ret = BRST_Page_CheckState(page, BRST_GMODE_PAGE_DESCRIPTION | BRST_GMODE_PATH_OBJECT);

    BRST_PTRACE(" BRST_Page_Rectangle\n");

    if (ret != BRST_OK)
        return ret;

    BRST_PageAttr attr = (BRST_PageAttr)page->attr;

    if (BRST_Stream_Rectangle(attr->stream, x, y, width, height) != BRST_OK) {
        BRST_Error_Copy(page->error, attr->stream->error);
        return BRST_Error_Check(page->error);
    }

    attr->cur_pos.x = x;
    attr->cur_pos.y = y;
    attr->str_pos   = attr->cur_pos;
    attr->gmode     = BRST_GMODE_PATH_OBJECT;

    return ret;
}

/* w */
BRST_EXPORT(BRST_STATUS)
BRST_Page_SetLineWidth(BRST_Page page,
    BRST_REAL line_width)
{
    BRST_STATUS ret = BRST_Page_CheckState(page, BRST_GMODE_PAGE_DESCRIPTION | BRST_GMODE_TEXT_OBJECT);

    BRST_PTRACE(" BRST_Page_SetLineWidth\n");

    if (ret != BRST_OK)
        return ret;

    BRST_PageAttr attr = (BRST_PageAttr)page->attr;

    if (BRST_Stream_SetLineWidth(attr->stream, line_width) != BRST_OK) {
        BRST_Error_Copy(page->error, attr->stream->error);
        return BRST_Error_Check(page->error);
    }

    attr->gstate->line_width = line_width;

    return ret;
}

/* J */
BRST_EXPORT(BRST_STATUS)
BRST_Page_SetLineCap(BRST_Page page,
    BRST_LineCap line_cap)
{
    BRST_STATUS ret = BRST_Page_CheckState(page, BRST_GMODE_PAGE_DESCRIPTION | BRST_GMODE_TEXT_OBJECT);

    BRST_PTRACE(" BRST_Page_SetLineCap\n");

    if (ret != BRST_OK)
        return ret;

    BRST_PageAttr attr = (BRST_PageAttr)page->attr;

    if (BRST_Stream_SetLineCap(attr->stream, line_cap) != BRST_OK) {
        BRST_Error_Copy(page->error, attr->stream->error);
        return BRST_Error_Check(page->error);
    }

    attr->gstate->line_cap = line_cap;

    return ret;
}

/* j */
BRST_EXPORT(BRST_STATUS)
BRST_Page_SetLineJoin(BRST_Page page,
    BRST_LineJoin line_join)
{
    BRST_STATUS ret = BRST_Page_CheckState(page, BRST_GMODE_PAGE_DESCRIPTION | BRST_GMODE_TEXT_OBJECT);

    BRST_PTRACE(" BRST_Page_SetLineJoin\n");

    if (ret != BRST_OK)
        return ret;

    BRST_PageAttr attr = (BRST_PageAttr)page->attr;

    if (BRST_Stream_SetLineJoin(attr->stream, line_join) != BRST_OK) {
        BRST_Error_Copy(page->error, attr->stream->error);
        return BRST_Error_Check(page->error);
    }

    attr->gstate->line_join = line_join;

    return ret;
}

/* M */
BRST_EXPORT(BRST_STATUS)
BRST_Page_SetMiterLimit(BRST_Page page,
    BRST_REAL miter_limit)
{
    BRST_STATUS ret = BRST_Page_CheckState(page, BRST_GMODE_PAGE_DESCRIPTION | BRST_GMODE_TEXT_OBJECT);

    BRST_PTRACE(" BRST_Page_SetMitterLimit\n");

    if (ret != BRST_OK)
        return ret;

    BRST_PageAttr attr = (BRST_PageAttr)page->attr;

    if (BRST_Stream_SetMiterLimit(attr->stream, miter_limit) != BRST_OK) {
        BRST_Error_Copy(page->error, attr->stream->error);
        return BRST_Error_Check(page->error);
    }

    attr->gstate->miter_limit = miter_limit;

    return ret;
}

/* d */
BRST_EXPORT(BRST_STATUS)
BRST_Page_SetDash(BRST_Page page,
    BRST_DASH_PATTERN dash_ptn,
    BRST_UINT num_param,
    BRST_REAL phase)
{
    BRST_STATUS ret = BRST_Page_CheckState(page, BRST_GMODE_PAGE_DESCRIPTION | BRST_GMODE_TEXT_OBJECT);

    BRST_PTRACE(" BRST_Page_SetDash\n");

    if (ret != BRST_OK)
        return ret;

    BRST_PageAttr attr = (BRST_PageAttr)page->attr;

    if (BRST_Stream_SetDash(attr->stream, dash_ptn, num_param, phase) != BRST_OK) {
        BRST_Error_Copy(page->error, attr->stream->error);
        return BRST_Error_Check(page->error);
    }

    attr->gstate->dash_mode         = INIT_MODE;
    attr->gstate->dash_mode.num_ptn = num_param;
    attr->gstate->dash_mode.phase   = phase;

    BRST_DASH_PATTERN pdash_ptn = dash_ptn;
    for (int i = 0; i < num_param; i++) {
        attr->gstate->dash_mode.ptn[i] = *pdash_ptn;
        pdash_ptn++;
    }

    return ret;
}

/* i */
BRST_EXPORT(BRST_STATUS)
BRST_Page_SetFlat(BRST_Page page,
    BRST_REAL flatness)
{
    BRST_STATUS ret = BRST_Page_CheckState(page, BRST_GMODE_PAGE_DESCRIPTION | BRST_GMODE_TEXT_OBJECT);

    BRST_PTRACE(" BRST_Page_SetFlat\n");

    if (ret != BRST_OK)
        return ret;

    BRST_PageAttr attr = (BRST_PageAttr)page->attr;

    if (BRST_Stream_SetFlat(attr->stream, flatness) != BRST_OK) {
        BRST_Error_Copy(page->error, attr->stream->error);
        return BRST_Error_Check(page->error);
    }

    attr->gstate->flatness = flatness;

    return ret;
}

BRST_EXPORT(BRST_RGBColor)
BRST_Page_RGBFill(BRST_Page page)
{
    BRST_PTRACE(" BRST_Page_RGBFill\n");

    if (BRST_Page_Validate(page)) {
        BRST_PageAttr attr = (BRST_PageAttr)page->attr;

        if (attr->gstate->cs_fill == BRST_CS_DEVICE_RGB)
            return attr->gstate->rgb_fill;
    }

    return DEF_RGB_COLOR;
}

BRST_EXPORT(BRST_RGBColor)
BRST_Page_RGBStroke(BRST_Page page)
{
    BRST_PTRACE(" BRST_Page_RGBStroke\n");

    if (BRST_Page_Validate(page)) {
        BRST_PageAttr attr = (BRST_PageAttr)page->attr;

        if (attr->gstate->cs_stroke == BRST_CS_DEVICE_RGB)
            return attr->gstate->rgb_stroke;
    }

    return DEF_RGB_COLOR;
}

BRST_EXPORT(BRST_CMYKColor)
BRST_Page_CMYKFill(BRST_Page page)
{
    BRST_PTRACE(" BRST_Page_CMYKFill\n");

    if (BRST_Page_Validate(page)) {
        BRST_PageAttr attr = (BRST_PageAttr)page->attr;

        if (attr->gstate->cs_fill == BRST_CS_DEVICE_CMYK)
            return attr->gstate->cmyk_fill;
    }

    return DEF_CMYK_COLOR;
}

BRST_EXPORT(BRST_CMYKColor)
BRST_Page_CMYKStroke(BRST_Page page)
{
    BRST_PTRACE(" BRST_Page_CMYKStroke\n");

    if (BRST_Page_Validate(page)) {
        BRST_PageAttr attr = (BRST_PageAttr)page->attr;

        if (attr->gstate->cs_stroke == BRST_CS_DEVICE_CMYK)
            return attr->gstate->cmyk_stroke;
    }

    return DEF_CMYK_COLOR;
}

BRST_EXPORT(BRST_REAL)
BRST_Page_GrayFill(BRST_Page page)
{
    BRST_PTRACE(" BRST_Page_GrayFill\n");

    if (BRST_Page_Validate(page)) {
        BRST_PageAttr attr = (BRST_PageAttr)page->attr;

        if (attr->gstate->cs_fill == BRST_CS_DEVICE_GRAY)
            return attr->gstate->gray_fill;
    }

    return 0;
}

BRST_EXPORT(BRST_REAL)
BRST_Page_GrayStroke(BRST_Page page)
{
    BRST_PTRACE(" BRST_Page_GrayStroke\n");

    if (BRST_Page_Validate(page)) {
        BRST_PageAttr attr = (BRST_PageAttr)page->attr;

        if (attr->gstate->cs_stroke == BRST_CS_DEVICE_GRAY)
            return attr->gstate->gray_stroke;
    }

    return 0;
}

BRST_EXPORT(BRST_ColorSpace)
BRST_Page_StrokeColorSpace(BRST_Page page)
{
    BRST_PTRACE(" BRST_Page_StrokeColorSpace\n");

    if (BRST_Page_Validate(page))
        return ((BRST_PageAttr)page->attr)->gstate->cs_stroke;

    return BRST_CS_EOF;
}

BRST_EXPORT(BRST_ColorSpace)
BRST_Page_FillColorSpace(BRST_Page page)
{
    BRST_PTRACE(" BRST_Page_FillColorSpace\n");

    if (BRST_Page_Validate(page))
        return ((BRST_PageAttr)page->attr)->gstate->cs_fill;

    return BRST_CS_EOF;
}

BRST_EXPORT(BRST_REAL)
BRST_Page_LineWidth(BRST_Page page)
{
    BRST_PTRACE(" BRST_Page_LineWidth\n");

    if (BRST_Page_Validate(page)) {
        BRST_PageAttr attr = (BRST_PageAttr)page->attr;

        return attr->gstate->line_width;
    } else
        return BRST_DEF_LINEWIDTH;
}

BRST_EXPORT(BRST_LineCap)
BRST_Page_LineCap(BRST_Page page)
{
    BRST_PTRACE(" BRST_Page_LineCap\n");

    if (BRST_Page_Validate(page)) {
        BRST_PageAttr attr = (BRST_PageAttr)page->attr;

        return attr->gstate->line_cap;
    } else
        return BRST_DEF_LINECAP;
}

BRST_EXPORT(BRST_LineJoin)
BRST_Page_LineJoin(BRST_Page page)
{
    BRST_PTRACE(" BRST_Page_LineJoin\n");

    if (BRST_Page_Validate(page)) {
        BRST_PageAttr attr = (BRST_PageAttr)page->attr;

        return attr->gstate->line_join;
    } else
        return BRST_DEF_LINEJOIN;
}

BRST_EXPORT(BRST_REAL)
BRST_Page_MiterLimit(BRST_Page page)
{
    BRST_PTRACE(" BRST_Page_MiterLimit\n");

    if (BRST_Page_Validate(page)) {
        BRST_PageAttr attr = (BRST_PageAttr)page->attr;

        return attr->gstate->miter_limit;
    } else
        return BRST_DEF_MITERLIMIT;
}

BRST_EXPORT(BRST_DashMode)
BRST_Page_Dash(BRST_Page page)
{
    BRST_DashMode mode = { { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f }, 0, 0.0f };

    BRST_PTRACE(" BRST_Page_Dash\n");

    if (BRST_Page_Validate(page)) {
        BRST_PageAttr attr = (BRST_PageAttr)page->attr;

        mode = attr->gstate->dash_mode;
    }

    return mode;
}

BRST_EXPORT(BRST_REAL)
BRST_Page_Flat(BRST_Page page)
{
    BRST_PTRACE(" BRST_Page_Flat\n");

    if (BRST_Page_Validate(page)) {
        BRST_PageAttr attr = (BRST_PageAttr)page->attr;

        return attr->gstate->flatness;
    } else
        return BRST_DEF_FLATNESS;
}

BRST_EXPORT(BRST_TransMatrix)
BRST_Page_TransMatrix(BRST_Page page)
{
    BRST_TransMatrix DEF_MATRIX = { 1, 0, 0, 1, 0, 0 };

    BRST_PTRACE(" BRST_Page_GetTransMatrix\n");
    if (BRST_Page_Validate(page)) {
        BRST_PageAttr attr = (BRST_PageAttr)page->attr;

        return attr->gstate->trans_matrix;
    } else
        return DEF_MATRIX;
}

/* sh */
BRST_EXPORT(BRST_STATUS)
BRST_Page_SetShading(BRST_Page page,
    BRST_Shading shading)
{
    BRST_STATUS ret = BRST_Page_CheckState(page, BRST_GMODE_PAGE_DESCRIPTION);
    BRST_PageAttr attr;
    const char* local_name;

    BRST_PTRACE(" BRST_Page_SetShading\n");

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
