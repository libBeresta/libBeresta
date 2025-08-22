#include "brst_external.h"
#include "brst_types.h"
#include "brst_mmgr.h"
#include "brst_encrypt.h"
#include "brst_stream.h"
#include "brst_dict.h"
#include "brst_xref.h"
#include "brst_array.h"
#include "private/brst_array.h"
#include "private/brst_boolean.h"
#include "private/brst_name.h"
#include "private/brst_proxy.h"
#include "brst_encoder.h"
#include "brst_error.h"
#include "brst_consts.h"
#include "brst_annotation.h"
#include "private/brst_annotation.h"
#include "private/brst_utils.h"
#include "brst_font.h"
#include "brst_shading.h"
#include "brst_doc_info.h"
#include "private/brst_info.h"
#include "brst_ext_gstate.h"
#include "brst_page.h"
#include "private/brst_page.h"
#include "private/brst_pages.h"
#include "private/brst_gstate.h"
#include "private/brst_page_attr.h"
#include "brst_image.h"
#include "brst_page_xobject.h"
#include "private/brst_catalog.h"
#include "private/brst_destination.h"
#include "brst_exdata.h"
#include "brst_javascript.h"

static const char* const BRST_ANNOT_ICON_NAMES_NAMES[] = {
    "Comment",
    "Key",
    "Note",
    "Help",
    "NewParagraph",
    "Paragraph",
    "Insert"
};

static const char* const BRST_ANNOT_INTENT_NAMES[] = {
    "FreeTextCallout",
    "FreeTextTypeWriter",
    "LineArrow",
    "LineDimension",
    "PolygonCloud",
    "PolyLineDimension",
    "PolygonDimension"
};

static const char* const BRST_LINE_ANNOT_ENDING_STYLE_NAMES[] = {
    "None",
    "Square",
    "Circle",
    "Diamond",
    "OpenArrow",
    "ClosedArrow",
    "Butt",
    "ROpenArrow",
    "RClosedArrow",
    "Slash"
};

static const char* const BRST_LINE_ANNOT_CAP_POSITION_NAMES[] = {
    "Inline",
    "Top"
};

BRST_STATUS
AddAnnotation(BRST_Page page,
    BRST_Annotation annot)
{
    BRST_Array array;
    BRST_STATUS ret = BRST_OK;

    BRST_PTRACE(" AddAnnotation\n");

    /* find "Annots" entry */
    array = BRST_Dict_Item(page, "Annots", BRST_OCLASS_ARRAY);

    if (!array) {
        array = BRST_Array_New(page->mmgr);
        if (!array)
            return BRST_Error_Code(page->error);

        ret = BRST_Dict_Add(page, "Annots", array);
        if (ret != BRST_OK)
            return ret;
    }

    if ((ret = BRST_Array_Add(array, annot)) != BRST_OK)
        return ret;

    /* Add Parent to the annotation  */
    ret = BRST_Dict_Add(annot, "P", page);

    return ret;
}

static BRST_BOOL
CheckSubType(BRST_Annotation annot,
    BRST_AnnotType type)
{
    BRST_Name subtype;

    BRST_PTRACE(" BRST_CheckSubType\n");

    if (!BRST_Annotation_Validate(annot))
        return BRST_FALSE;

    subtype = BRST_Dict_Item(annot, "Subtype", BRST_OCLASS_NAME);

    if (!subtype || BRST_StrCmp(BRST_Name_Value(subtype), BRST_ANNOT_TYPE_NAMES[(BRST_INT)type]) != 0) {
        BRST_Error_Raise(annot->error, BRST_INVALID_ANNOTATION, 0);
        return BRST_FALSE;
    }

    return BRST_TRUE;
}

/*----------------------------------------------------------------------------*/
/*------ BRST_Annotation -----------------------------------------------------*/

BRST_EXPORT(BRST_STATUS)
BRST_Annotation_SetBorderStyle(BRST_Annotation annot,
    BRST_BSSubtype subtype,
    BRST_REAL width,
    BRST_UINT16 dash_on,
    BRST_UINT16 dash_off,
    BRST_UINT16 dash_phase)
{
    BRST_Dict bs;
    BRST_Array dash;
    BRST_STATUS ret;

    BRST_PTRACE(" BRST_Annotation_SetBoderStyle\n");

    bs = BRST_Dict_New(annot->mmgr);
    if (!bs)
        return BRST_Error_Code(annot->error);

    if ((ret = BRST_Dict_Add(annot, "BS", bs)) != BRST_OK)
        return ret;

    if (subtype == BRST_BS_DASHED) {
        dash = BRST_Array_New(annot->mmgr);
        if (!dash)
            return BRST_Error_Code(annot->error);

        if ((ret = BRST_Dict_Add(bs, "D", dash)) != BRST_OK)
            return ret;

        ret += BRST_Dict_AddName(bs, "Type", "Border");
        ret += BRST_Array_AddReal(dash, dash_on);
        ret += BRST_Array_AddReal(dash, dash_off);

        if (dash_phase != 0)
            ret += BRST_Array_AddReal(dash, dash_off);
    }

    switch (subtype) {
    case BRST_BS_SOLID:
        ret += BRST_Dict_AddName(bs, "S", "S");
        break;
    case BRST_BS_DASHED:
        ret += BRST_Dict_AddName(bs, "S", "D");
        break;
    case BRST_BS_BEVELED:
        ret += BRST_Dict_AddName(bs, "S", "B");
        break;
    case BRST_BS_INSET:
        ret += BRST_Dict_AddName(bs, "S", "I");
        break;
    case BRST_BS_UNDERLINED:
        ret += BRST_Dict_AddName(bs, "S", "U");
        break;
    default:
        return BRST_Error_Set(annot->error, BRST_ANNOT_INVALID_BORDER_STYLE, 0);
    }

    if (width != BRST_BS_DEF_WIDTH)
        ret += BRST_Dict_AddReal(bs, "W", width);

    if (ret != BRST_OK)
        return BRST_Error_Code(annot->error);

    return BRST_OK;
}

BRST_EXPORT(BRST_STATUS)
BRST_LinkAnnot_SetJavaScript(BRST_Annotation annot, BRST_JavaScript javascript)
{
    BRST_Dict action;
    BRST_STATUS ret;

    BRST_PTRACE(" BRST_LinkAnnot_SetJavaScript\n");

    if (!CheckSubType(annot, BRST_ANNOT_LINK))
        return BRST_INVALID_ANNOTATION;

    /* create action dictionary */
    action = BRST_Dict_New(annot->mmgr);
    if (!action)
        return BRST_Error_Check(annot->error);

    ret = BRST_Dict_Add(annot, "A", action);
    if (ret != BRST_OK)
        return BRST_Error_Check(annot->error);

    ret += BRST_Dict_Add(action, "JS", javascript);
    ret += BRST_Dict_AddName(action, "S", "JavaScript");

    if (ret != BRST_OK)
        return BRST_Error_Check(annot->error);

    return BRST_OK;
}

BRST_EXPORT(BRST_STATUS)
BRST_LinkAnnot_SetBorderStyle(BRST_Annotation annot,
    BRST_REAL width,
    BRST_UINT16 dash_on,
    BRST_UINT16 dash_off)
{
    BRST_Array array;
    BRST_STATUS ret;

    BRST_PTRACE(" BRST_LinkAnnot_SetBorderStyle\n");

    if (!CheckSubType(annot, BRST_ANNOT_LINK))
        return BRST_INVALID_ANNOTATION;

    if (width < 0)
        return BRST_Error_Raise(annot->error, BRST_INVALID_PARAMETER, 0);

    array = BRST_Array_New(annot->mmgr);
    if (!array)
        return BRST_Error_Check(annot->error);

    if ((ret = BRST_Dict_Add(annot, "Border", array)) != BRST_OK)
        return BRST_Error_Check(annot->error);

    ret += BRST_Array_AddNumber(array, 0);
    ret += BRST_Array_AddNumber(array, 0);
    ret += BRST_Array_AddReal(array, width);

    if (ret != BRST_OK)
        return BRST_Error_Check(annot->error);

    if (dash_on && dash_off) {
        BRST_Array dash = BRST_Array_New(annot->mmgr);
        if (!dash)
            return BRST_Error_Check(annot->error);

        if ((ret = BRST_Array_Add(array, dash)) != BRST_OK)
            return BRST_Error_Check(annot->error);

        ret += BRST_Array_AddNumber(dash, dash_on);
        ret += BRST_Array_AddNumber(dash, dash_off);

        if (ret != BRST_OK)
            return BRST_Error_Check(annot->error);
    }

    return BRST_OK;
}

BRST_EXPORT(BRST_STATUS)
BRST_LinkAnnot_SetHighlightMode(BRST_Annotation annot,
    BRST_AnnotHighlightMode mode)
{
    BRST_STATUS ret;

    BRST_PTRACE(" BRST_LinkAnnot_SetHighlightMode\n");

    if (!CheckSubType(annot, BRST_ANNOT_LINK))
        return BRST_INVALID_ANNOTATION;

    switch (mode) {
    case BRST_ANNOT_NO_HIGHLIGHT:
        ret = BRST_Dict_AddName(annot, "H", "N");
        break;
    case BRST_ANNOT_INVERT_BORDER:
        ret = BRST_Dict_AddName(annot, "H", "O");
        break;
    case BRST_ANNOT_DOWN_APPEARANCE:
        ret = BRST_Dict_AddName(annot, "H", "P");
        break;
    default: /* BRST_ANNOT_INVERT_BOX */
        /* default value */
        BRST_Dict_RemoveElement(annot, "H");
        ret = BRST_OK;
    }

    if (ret != BRST_OK)
        return BRST_Error_Check(annot->error);

    return ret;
}

BRST_EXPORT(BRST_STATUS)
BRST_Annot_SetRGBColor(BRST_Annotation annot, BRST_RGBColor color)
{
    BRST_Array cArray;
    BRST_STATUS ret = BRST_OK;

    BRST_PTRACE(" BRST_Annot_SetRGBColor\n");

    cArray = BRST_Array_New(annot->mmgr);
    if (!cArray)
        return BRST_Error_Code(annot->error);

    ret += BRST_Dict_Add(annot, "C", cArray);
    ret += BRST_Array_AddReal(cArray, color.r);
    ret += BRST_Array_AddReal(cArray, color.g);
    ret += BRST_Array_AddReal(cArray, color.b);

    if (ret != BRST_OK)
        return BRST_Error_Code(annot->error);

    return BRST_OK;
}

BRST_EXPORT(BRST_STATUS)
BRST_Annot_SetCMYKColor(BRST_Annotation annot, BRST_CMYKColor color)
{
    BRST_Array cArray;
    BRST_STATUS ret = BRST_OK;

    BRST_PTRACE(" BRST_Annot_SetCMYKColor\n");

    cArray = BRST_Array_New(annot->mmgr);
    if (!cArray)
        return BRST_Error_Code(annot->error);

    // TODO А команда здесь правильная?
    ret += BRST_Dict_Add(annot, "C", cArray);
    ret += BRST_Array_AddReal(cArray, color.c);
    ret += BRST_Array_AddReal(cArray, color.m);
    ret += BRST_Array_AddReal(cArray, color.y);
    ret += BRST_Array_AddReal(cArray, color.k);

    if (ret != BRST_OK)
        return BRST_Error_Code(annot->error);

    return BRST_OK;
}

BRST_EXPORT(BRST_STATUS)
BRST_Annot_SetGrayColor(BRST_Annotation annot, BRST_REAL color)
{
    BRST_Array cArray;
    BRST_STATUS ret = BRST_OK;

    BRST_PTRACE(" BRST_Annot_SetGrayColor\n");

    cArray = BRST_Array_New(annot->mmgr);
    if (!cArray)
        return BRST_Error_Code(annot->error);

    ret += BRST_Dict_Add(annot, "C", cArray);
    ret += BRST_Array_AddReal(cArray, color);

    if (ret != BRST_OK)
        return BRST_Error_Code(annot->error);

    return BRST_OK;
}

BRST_EXPORT(BRST_STATUS)
BRST_Annot_SetNoColor(BRST_Annotation annot)
{
    BRST_Array cArray;
    BRST_STATUS ret = BRST_OK;

    BRST_PTRACE(" BRST_Annot_SetNoColor\n");

    cArray = BRST_Array_New(annot->mmgr);
    if (!cArray)
        return BRST_Error_Code(annot->error);

    ret = BRST_Dict_Add(annot, "C", cArray);

    return ret;
}

BRST_EXPORT(BRST_STATUS)
BRST_TextAnnot_SetIcon(BRST_Annotation annot,
    BRST_AnnotIcon icon)
{
    BRST_PTRACE(" BRST_TextAnnot_SetIcon\n");

    if (!CheckSubType(annot, BRST_ANNOT_TEXT_NOTES))
        return BRST_INVALID_ANNOTATION;

    if (icon >= BRST_ANNOT_ICON_EOF)
        return BRST_Error_Raise(annot->error, BRST_ANNOT_INVALID_ICON,
            (BRST_STATUS)icon);

    if (BRST_Dict_AddName(annot, "Name",
            BRST_ANNOT_ICON_NAMES_NAMES[(BRST_INT)icon])
        != BRST_OK)
        return BRST_Error_Check(annot->error);

    return BRST_OK;
}

BRST_EXPORT(BRST_STATUS)
BRST_TextAnnot_SetOpened(BRST_Annotation annot,
    BRST_BOOL opened)
{
    BRST_Boolean b;

    BRST_PTRACE(" BRST_TextAnnot_SetOpened\n");

    if (!CheckSubType(annot, BRST_ANNOT_TEXT_NOTES))
        return BRST_INVALID_ANNOTATION;

    b = BRST_Boolean_New(annot->mmgr, opened);
    if (!b)
        return BRST_Error_Check(annot->error);

    return BRST_Dict_Add(annot, "Open", b);
}

BRST_EXPORT(BRST_STATUS)
BRST_PopupAnnot_SetOpened(BRST_Annotation annot,
    BRST_BOOL opened)
{
    BRST_Boolean b;

    BRST_PTRACE(" BRST_TextAnnot_SetOpened\n");

    if (!CheckSubType(annot, BRST_ANNOT_POPUP))
        return BRST_INVALID_ANNOTATION;

    b = BRST_Boolean_New(annot->mmgr, opened);
    if (!b)
        return BRST_Error_Check(annot->error);

    return BRST_Dict_Add(annot, "Open", b);
}

BRST_EXPORT(BRST_STATUS)
BRST_MarkupAnnot_SetTitle(BRST_Annotation annot, const char* name)
{
    BRST_PTRACE(" BRST_MarkupAnnot_SetTitle\n");

    return BRST_Dict_Add(annot, "T", BRST_String_New(annot->mmgr, name, NULL));
}

BRST_EXPORT(BRST_STATUS)
BRST_MarkupAnnot_SetSubject(BRST_Annotation annot, const char* name)
{
    BRST_PTRACE(" BRST_MarkupAnnot_SetSubject\n");

    return BRST_Dict_Add(annot, "Subj", BRST_String_New(annot->mmgr, name, NULL));
}

BRST_EXPORT(BRST_STATUS)
BRST_MarkupAnnot_SetCreationDate(BRST_Annotation annot, BRST_Date value)
{
    BRST_PTRACE(" BRST_MarkupAnnot_SetCreationDate\n");

    return BRST_Info_SetInfoDateAttr(annot, BRST_INFO_CREATION_DATE, value);
}

BRST_EXPORT(BRST_STATUS)
BRST_MarkupAnnot_SetTransparency(BRST_Annotation annot, BRST_REAL value)
{
    BRST_PTRACE(" BRST_MarkupAnnot_SetTransparency\n");

    return BRST_Dict_AddReal(annot, "CA", value);
}

BRST_EXPORT(BRST_STATUS)
BRST_MarkupAnnot_SetIntent(BRST_Annotation annot,
    BRST_AnnotIntent intent)
{
    BRST_PTRACE(" BRST_MarkupAnnot_SetIntent\n");

    if (BRST_Dict_AddName(annot, "IT",
            BRST_ANNOT_INTENT_NAMES[(BRST_INT)intent])
        != BRST_OK)
        return BRST_Error_Check(annot->error);

    return BRST_OK;
}

BRST_EXPORT(BRST_STATUS)
BRST_MarkupAnnot_SetPopup(BRST_Annotation annot,
    BRST_Annotation popup)
{
    BRST_PTRACE(" BRST_MarkupAnnot_SetPopup\n");

    return BRST_Dict_Add(annot, "Popup", popup);
}

BRST_EXPORT(BRST_STATUS)
BRST_MarkupAnnot_SetInteriorRGBColor(BRST_Annotation annot, BRST_RGBColor color) /* IC with RGB entry */
{
    BRST_Array cArray;
    BRST_STATUS ret = BRST_OK;

    BRST_PTRACE(" BRST_MarkupAnnot_SetInteriorRGBColor\n");

    cArray = BRST_Array_New(annot->mmgr);
    if (!cArray)
        return BRST_Error_Code(annot->error);

    ret += BRST_Dict_Add(annot, "IC", cArray);
    ret += BRST_Array_AddReal(cArray, color.r);
    ret += BRST_Array_AddReal(cArray, color.g);
    ret += BRST_Array_AddReal(cArray, color.b);

    if (ret != BRST_OK)
        return BRST_Error_Code(annot->error);

    return BRST_OK;
}

BRST_EXPORT(BRST_STATUS)
BRST_MarkupAnnot_SetInteriorCMYKColor(BRST_Annotation annot, BRST_CMYKColor color) /* IC with CMYK entry */
{
    BRST_Array cArray;
    BRST_STATUS ret = BRST_OK;

    BRST_PTRACE(" BRST_MarkupAnnot_SetInteriorCMYKColor\n");

    cArray = BRST_Array_New(annot->mmgr);
    if (!cArray)
        return BRST_Error_Code(annot->error);

    ret += BRST_Dict_Add(annot, "IC", cArray);
    ret += BRST_Array_AddReal(cArray, color.c);
    ret += BRST_Array_AddReal(cArray, color.m);
    ret += BRST_Array_AddReal(cArray, color.y);
    ret += BRST_Array_AddReal(cArray, color.k);

    if (ret != BRST_OK)
        return BRST_Error_Code(annot->error);

    return BRST_OK;
}

BRST_EXPORT(BRST_STATUS)
BRST_MarkupAnnot_SetInteriorGrayColor(BRST_Annotation annot, BRST_REAL color) /* IC with Gray entry */
{
    BRST_Array cArray;
    BRST_STATUS ret = BRST_OK;

    BRST_PTRACE(" BRST_MarkupAnnot_SetInteriorGrayColor\n");

    cArray = BRST_Array_New(annot->mmgr);
    if (!cArray)
        return BRST_Error_Code(annot->error);

    ret += BRST_Dict_Add(annot, "IC", cArray);
    ret += BRST_Array_AddReal(cArray, color);

    if (ret != BRST_OK)
        return BRST_Error_Code(annot->error);

    return BRST_OK;
}

BRST_EXPORT(BRST_STATUS)
BRST_MarkupAnnot_SetInteriorTransparent(BRST_Annotation annot) /* IC with No Color entry */
{
    BRST_Array cArray;
    BRST_STATUS ret = BRST_OK;

    BRST_PTRACE(" BRST_MarkupAnnot_SetInteriorTransparent\n");

    cArray = BRST_Array_New(annot->mmgr);
    if (!cArray)
        return BRST_Error_Code(annot->error);

    ret = BRST_Dict_Add(annot, "IC", cArray);

    return ret;
}

BRST_EXPORT(BRST_STATUS)
BRST_Annot_Set3DView(BRST_MMgr mmgr,
    BRST_Annotation annot,
    BRST_Annotation annot3d,
    BRST_Dict view3d)
{
    BRST_Proxy proxyView3d;
    BRST_Dict exData = BRST_Dict_New(mmgr);
    BRST_STATUS retS = BRST_OK;

    retS += BRST_Dict_AddName(exData, "Type", "ExData");
    retS += BRST_Dict_AddName(exData, "Subtype", "Markup3D");
    retS += BRST_Dict_Add(exData, "3DA", annot3d);

    proxyView3d = BRST_Proxy_New(mmgr, view3d);

    retS += BRST_Dict_Add(exData, "3DV", proxyView3d);
    retS += BRST_Dict_Add(annot, "ExData", exData);
    return retS;
}

BRST_EXPORT(BRST_STATUS)
BRST_TextMarkupAnnot_SetQuadPoints(BRST_Annotation annot, BRST_Point lb, BRST_Point rb, BRST_Point lt, BRST_Point rt) /* l-left, r-right, b-bottom, t-top positions */
{
    BRST_Array quadPoints;
    BRST_STATUS ret = BRST_OK;

    BRST_PTRACE(" BRST_TextMarkupAnnot_SetQuadPoints\n");

    quadPoints = BRST_Array_New(annot->mmgr);
    if (!quadPoints)
        return BRST_Error_Code(annot->error);

    if ((ret = BRST_Dict_Add(annot, "QuadPoints", quadPoints)) != BRST_OK)
        return ret;

    ret += BRST_Array_AddReal(quadPoints, lb.x);
    ret += BRST_Array_AddReal(quadPoints, lb.y);
    ret += BRST_Array_AddReal(quadPoints, rb.x);
    ret += BRST_Array_AddReal(quadPoints, rb.y);
    ret += BRST_Array_AddReal(quadPoints, lt.x);
    ret += BRST_Array_AddReal(quadPoints, lt.y);
    ret += BRST_Array_AddReal(quadPoints, rt.x);
    ret += BRST_Array_AddReal(quadPoints, rt.y);

    if (ret != BRST_OK)
        return BRST_Error_Code(quadPoints->error);

    return BRST_OK;
}

BRST_EXPORT(BRST_STATUS)
BRST_FreeTextAnnot_SetLineEndingStyle(BRST_Annotation annot, BRST_LineAnnotEndingStyle startStyle, BRST_LineAnnotEndingStyle endStyle)
{
    BRST_Array lineEndStyles;
    BRST_STATUS ret = BRST_OK;

    BRST_PTRACE(" BRST_FreeTextAnnot_SetLineEndingStyle\n");

    lineEndStyles = BRST_Array_New(annot->mmgr);
    if (!lineEndStyles)
        return BRST_Error_Code(annot->error);

    if ((ret = BRST_Dict_Add(annot, "LE", lineEndStyles)) != BRST_OK)
        return ret;

    ret += BRST_Array_AddName(lineEndStyles, BRST_LINE_ANNOT_ENDING_STYLE_NAMES[(BRST_INT)startStyle]);
    ret += BRST_Array_AddName(lineEndStyles, BRST_LINE_ANNOT_ENDING_STYLE_NAMES[(BRST_INT)endStyle]);

    if (ret != BRST_OK)
        return BRST_Error_Code(lineEndStyles->error);

    return BRST_OK;
}

BRST_EXPORT(BRST_STATUS)
BRST_MarkupAnnot_SetRectDiff(BRST_Annotation annot, BRST_Rect rect) /* RD entry : this is the difference between Rect and the text annotation rectangle */
{
    BRST_Array array;
    BRST_STATUS ret = BRST_OK;
    BRST_REAL tmp;

    BRST_PTRACE(" BRST_MarkupAnnot_SetRectDiff\n");

    array = BRST_Array_New(annot->mmgr);
    if (!array)
        return BRST_Error_Code(annot->error);

    if ((ret = BRST_Dict_Add(annot, "RD", array)) != BRST_OK)
        return ret;

    if (rect.top < rect.bottom) {
        tmp         = rect.top;
        rect.top    = rect.bottom;
        rect.bottom = tmp;
    }

    ret += BRST_Array_AddReal(array, rect.left);
    ret += BRST_Array_AddReal(array, rect.bottom);
    ret += BRST_Array_AddReal(array, rect.right);
    ret += BRST_Array_AddReal(array, rect.top);

    if (ret != BRST_OK)
        return BRST_Error_Code(array->error);

    return BRST_OK;
}

BRST_EXPORT(BRST_STATUS)
BRST_FreeTextAnnot_SetDefaultStyle(BRST_Annotation annot,
    const char* style)
{
    BRST_String s;
    BRST_STATUS ret = BRST_OK;

    BRST_PTRACE(" BRST_FreeTextAnnot_SetDefaultStyle\n");

    s = BRST_String_New(annot->mmgr, style, NULL);
    if (!s)
        return BRST_Error_Code(annot->error);

    ret = BRST_Dict_Add(annot, "DS", s);

    return ret;
}

BRST_EXPORT(BRST_STATUS)
BRST_FreeTextAnnot_Set3PointCalloutLine(BRST_Annotation annot, BRST_Point startPoint, BRST_Point kneePoint, BRST_Point endPoint) /* Callout line will be in default user space */
{
    BRST_Array clPoints;
    BRST_STATUS ret = BRST_OK;

    BRST_PTRACE(" BRST_FreeTextAnnot_Set3PointCalloutLine\n");

    clPoints = BRST_Array_New(annot->mmgr);
    if (!clPoints)
        return BRST_Error_Code(annot->error);

    if ((ret = BRST_Dict_Add(annot, "CL", clPoints)) != BRST_OK)
        return ret;

    ret += BRST_Array_AddReal(clPoints, startPoint.x);
    ret += BRST_Array_AddReal(clPoints, startPoint.y);
    ret += BRST_Array_AddReal(clPoints, kneePoint.x);
    ret += BRST_Array_AddReal(clPoints, kneePoint.y);
    ret += BRST_Array_AddReal(clPoints, endPoint.x);
    ret += BRST_Array_AddReal(clPoints, endPoint.y);

    if (ret != BRST_OK)
        return BRST_Error_Code(clPoints->error);

    return BRST_OK;
}

BRST_EXPORT(BRST_STATUS)
BRST_FreeTextAnnot_Set2PointCalloutLine(BRST_Annotation annot, BRST_Point startPoint, BRST_Point endPoint) /* Callout line will be in default user space */
{
    BRST_Array clPoints;
    BRST_STATUS ret = BRST_OK;

    BRST_PTRACE(" BRST_FreeTextAnnot_Set3PointCalloutLine\n");

    clPoints = BRST_Array_New(annot->mmgr);
    if (!clPoints)
        return BRST_Error_Code(annot->error);

    if ((ret = BRST_Dict_Add(annot, "CL", clPoints)) != BRST_OK)
        return ret;

    ret += BRST_Array_AddReal(clPoints, startPoint.x);
    ret += BRST_Array_AddReal(clPoints, startPoint.y);
    ret += BRST_Array_AddReal(clPoints, endPoint.x);
    ret += BRST_Array_AddReal(clPoints, endPoint.y);

    if (ret != BRST_OK)
        return BRST_Error_Code(clPoints->error);

    return BRST_OK;
}

BRST_EXPORT(BRST_STATUS)
BRST_MarkupAnnot_SetCloudEffect(BRST_Annotation annot, BRST_INT cloudIntensity) /* BE entry */
{
    BRST_Dict borderEffect;
    BRST_STATUS ret = BRST_OK;

    BRST_PTRACE(" BRST_MarkupAnnot_SetCloudEffect\n");

    borderEffect = BRST_Dict_New(annot->mmgr);
    if (!borderEffect)
        return BRST_Error_Code(annot->error);

    ret += BRST_Dict_Add(annot, "BE", borderEffect);
    ret += BRST_Dict_AddName(borderEffect, "S", "C");
    ret += BRST_Dict_AddNumber(borderEffect, "I", cloudIntensity);

    if (ret != BRST_OK)
        return BRST_Error_Code(annot->error);

    return BRST_OK;
}

BRST_EXPORT(BRST_STATUS)
BRST_LineAnnot_SetPosition(BRST_Annotation annot,
    BRST_Point startPoint, BRST_LineAnnotEndingStyle startStyle,
    BRST_Point endPoint, BRST_LineAnnotEndingStyle endStyle)
{
    BRST_Array lineEndPoints;
    BRST_Array lineEndStyles;
    BRST_STATUS ret = BRST_OK;

    BRST_PTRACE(" BRST_LineAnnot_SetPosition\n");

    lineEndPoints = BRST_Array_New(annot->mmgr);
    if (!lineEndPoints)
        return BRST_Error_Code(annot->error);

    if ((ret = BRST_Dict_Add(annot, "L", lineEndPoints)) != BRST_OK)
        return ret;

    ret += BRST_Array_AddReal(lineEndPoints, startPoint.x);
    ret += BRST_Array_AddReal(lineEndPoints, startPoint.y);
    ret += BRST_Array_AddReal(lineEndPoints, endPoint.x);
    ret += BRST_Array_AddReal(lineEndPoints, endPoint.y);

    if (ret != BRST_OK)
        return BRST_Error_Code(lineEndPoints->error);

    lineEndStyles = BRST_Array_New(annot->mmgr);
    if (!lineEndStyles)
        return BRST_Error_Code(annot->error);

    if ((ret = BRST_Dict_Add(annot, "LE", lineEndStyles)) != BRST_OK)
        return ret;

    ret += BRST_Array_AddName(lineEndStyles, BRST_LINE_ANNOT_ENDING_STYLE_NAMES[(BRST_INT)startStyle]);
    ret += BRST_Array_AddName(lineEndStyles, BRST_LINE_ANNOT_ENDING_STYLE_NAMES[(BRST_INT)endStyle]);

    if (ret != BRST_OK)
        return BRST_Error_Code(lineEndStyles->error);

    return BRST_OK;
}

BRST_EXPORT(BRST_STATUS)
BRST_LineAnnot_SetLeader(BRST_Annotation annot, BRST_INT leaderLen, BRST_INT leaderExtLen, BRST_INT leaderOffsetLen)
{
    BRST_STATUS ret = BRST_OK;

    BRST_PTRACE(" BRST_LineAnnot_SetLeader\n");

    ret += BRST_Dict_AddNumber(annot, "LL", leaderLen);
    ret += BRST_Dict_AddNumber(annot, "LLE", leaderExtLen);
    ret += BRST_Dict_AddNumber(annot, "LLO", leaderOffsetLen);

    if (ret != BRST_OK)
        return BRST_Error_Code(annot->error);

    return BRST_OK;
}

BRST_EXPORT(BRST_STATUS)
BRST_LineAnnot_SetCaption(BRST_Annotation annot, BRST_BOOL showCaption, BRST_LineAnnotCapPosition position, BRST_INT horzOffset, BRST_INT vertOffset)
{
    BRST_STATUS ret = BRST_OK;
    BRST_Array capOffset;
    BRST_PTRACE(" BRST_LineAnnot_SetCaption\n");

    ret += BRST_Dict_AddBoolean(annot, "Cap", showCaption);
    ret += BRST_Dict_AddName(annot, "CP", BRST_LINE_ANNOT_CAP_POSITION_NAMES[(BRST_INT)position]);

    if (ret != BRST_OK)
        return BRST_Error_Code(annot->error);

    capOffset = BRST_Array_New(annot->mmgr);
    if (!capOffset)
        return BRST_Error_Code(annot->error);

    if ((ret = BRST_Dict_Add(annot, "CO", capOffset)) != BRST_OK)
        return ret;

    ret += BRST_Array_AddNumber(capOffset, horzOffset);
    ret += BRST_Array_AddNumber(capOffset, vertOffset);

    if (ret != BRST_OK)
        return BRST_Error_Code(capOffset->error);

    return BRST_OK;
}

BRST_EXPORT(BRST_STATUS)
BRST_ProjectionAnnot_SetExData(BRST_Annotation annot, BRST_ExData exdata)
{
    BRST_STATUS ret = BRST_Dict_Add(annot, "ExData", exdata);

    return ret;
}

#ifdef LIBBRST_U3D_SUPPORT

BRST_EXPORT(BRST_Annotation)
BRST_Page_Create3DAnnot(BRST_Page page,
    BRST_Rect rect,
    BRST_BOOL tb,
    BRST_BOOL np,
    BRST_U3D u3d,
    BRST_Image ap)
{
    BRST_PageAttr attr;
    BRST_Annotation annot;

    BRST_PTRACE(" BRST_Page_Create3DAnnot\n");

    if (!BRST_Page_Validate(page))
        return NULL;

    attr = (BRST_PageAttr)page->attr;

    annot = BRST_3DAnnot_New(page->mmgr, attr->xref, rect, tb, np, u3d, ap);
    if (annot) {
        if (AddAnnotation(page, annot) != BRST_OK) {
            BRST_Error_Check(page->error);
            annot = NULL;
        }
    } else
        BRST_Error_Check(page->error);

    return annot;
}

#endif /* LIBBRST_U3D_SUPPORT */

BRST_EXPORT(BRST_Annotation)
BRST_Page_CreateTextAnnot(BRST_Page page,
    BRST_Rect rect,
    const char* text,
    BRST_Encoder encoder)
{
    BRST_PageAttr attr;
    BRST_Annotation annot;

    BRST_PTRACE(" BRST_Page_CreateTextAnnot\n");

    if (!BRST_Page_Validate(page))
        return NULL;

    attr = (BRST_PageAttr)page->attr;

    if (encoder && !BRST_Encoder_Validate(encoder)) {
        BRST_Error_Raise(page->error, BRST_INVALID_ENCODER, 0);
        return NULL;
    }

    annot = BRST_MarkupAnnot_New(page->mmgr, attr->xref, rect, text, encoder, BRST_ANNOT_TEXT_NOTES);
    if (annot) {
        if (AddAnnotation(page, annot) != BRST_OK) {
            BRST_Error_Check(page->error);
            annot = NULL;
        }
    } else
        BRST_Error_Check(page->error);

    return annot;
}

BRST_EXPORT(BRST_Annotation)
BRST_Page_CreateFreeTextAnnot(BRST_Page page,
    BRST_Rect rect,
    const char* text,
    BRST_Encoder encoder)
{
    BRST_PageAttr attr;
    BRST_Annotation annot;

    BRST_PTRACE(" BRST_Page_CreateFreeTextAnnot\n");

    if (!BRST_Page_Validate(page))
        return NULL;

    attr = (BRST_PageAttr)page->attr;

    if (encoder && !BRST_Encoder_Validate(encoder)) {
        BRST_Error_Raise(page->error, BRST_INVALID_ENCODER, 0);
        return NULL;
    }

    annot = BRST_MarkupAnnot_New(page->mmgr, attr->xref, rect, text, encoder, BRST_ANNOT_FREE_TEXT);
    if (annot) {
        if (AddAnnotation(page, annot) != BRST_OK) {
            BRST_Error_Check(page->error);
            annot = NULL;
        }
    } else
        BRST_Error_Check(page->error);

    return annot;
}

BRST_EXPORT(BRST_Annotation)
BRST_Page_CreateLineAnnot(BRST_Page page,
    const char* text,
    BRST_Encoder encoder)
{
    BRST_PageAttr attr;
    BRST_Annotation annot;
    BRST_Rect rect = { 0, 0, 0, 0 };

    BRST_PTRACE(" BRST_Page_CreateLineAnnot\n");

    if (!BRST_Page_Validate(page))
        return NULL;

    attr = (BRST_PageAttr)page->attr;

    if (encoder && !BRST_Encoder_Validate(encoder)) {
        BRST_Error_Raise(page->error, BRST_INVALID_ENCODER, 0);
        return NULL;
    }

    annot = BRST_MarkupAnnot_New(page->mmgr, attr->xref, rect, text, encoder, BRST_ANNOT_LINE);
    if (annot) {
        if (AddAnnotation(page, annot) != BRST_OK) {
            BRST_Error_Check(page->error);
            annot = NULL;
        }
    } else
        BRST_Error_Check(page->error);

    return annot;
}

BRST_EXPORT(BRST_Annotation)
BRST_Page_CreateWidgetAnnot(BRST_Page page,
    BRST_Rect rect)
{
    BRST_PageAttr attr;
    BRST_Annotation annot;

    BRST_PTRACE(" BRST_Page_CreateWidgetAnnot\n");

    if (!BRST_Page_Validate(page))
        return NULL;

    attr = (BRST_PageAttr)page->attr;

    annot = BRST_WidgetAnnot_New(page->mmgr, attr->xref, rect);

    if (annot) {
        if (AddAnnotation(page, annot) != BRST_OK) {
            BRST_Error_Check(page->error);
            annot = NULL;
        }
    } else
        BRST_Error_Check(page->error);

    return annot;
}

BRST_EXPORT(BRST_Annotation)
BRST_Page_CreateLinkAnnot(BRST_Page page,
    BRST_Rect rect,
    BRST_Destination dst)
{
    BRST_PageAttr attr;
    BRST_Annotation annot;

    BRST_PTRACE(" BRST_Page_CreateLinkAnnot\n");

    if (!BRST_Page_Validate(page))
        return NULL;

    attr = (BRST_PageAttr)page->attr;

    if (dst) {
        if (!BRST_Destination_Validate(dst)) {
            BRST_Error_Raise(page->error, BRST_INVALID_DESTINATION, 0);
            return NULL;
        }
    }

    annot = BRST_LinkAnnot_New(page->mmgr, attr->xref, rect, dst);
    if (annot) {
        if (AddAnnotation(page, annot) != BRST_OK) {
            BRST_Error_Check(page->error);
            annot = NULL;
        }
    } else
        BRST_Error_Check(page->error);

    return annot;
}

BRST_EXPORT(BRST_Annotation)
BRST_Page_CreateURILinkAnnot(BRST_Page page,
    BRST_Rect rect,
    const char* uri)
{
    BRST_PageAttr attr;
    BRST_Annotation annot;

    BRST_PTRACE(" BRST_Page_CreateURILinkAnnot\n");

    if (!BRST_Page_Validate(page))
        return NULL;

    attr = (BRST_PageAttr)page->attr;

    if (BRST_StrLen(uri, BRST_LIMIT_MAX_STRING_LEN) <= 0) {
        BRST_Error_Raise(page->error, BRST_INVALID_URI, 0);
        return NULL;
    }

    annot = BRST_URILinkAnnot_New(page->mmgr, attr->xref, rect, uri);
    if (annot) {
        if (AddAnnotation(page, annot) != BRST_OK) {
            BRST_Error_Check(page->error);
            annot = NULL;
        }
    } else
        BRST_Error_Check(page->error);

    return annot;
}

BRST_EXPORT(BRST_Annotation)
BRST_Page_CreateCircleAnnot(BRST_Page page,
    BRST_Rect rect,
    const char* text,
    BRST_Encoder encoder)
{
    BRST_PageAttr attr;
    BRST_Annotation annot;

    BRST_PTRACE(" BRST_Page_CreateCircleAnnot\n");

    if (!BRST_Page_Validate(page))
        return NULL;

    attr = (BRST_PageAttr)page->attr;

    if (encoder && !BRST_Encoder_Validate(encoder)) {
        BRST_Error_Raise(page->error, BRST_INVALID_ENCODER, 0);
        return NULL;
    }

    annot = BRST_MarkupAnnot_New(page->mmgr, attr->xref, rect, text, encoder, BRST_ANNOT_CIRCLE);
    if (annot) {
        if (AddAnnotation(page, annot) != BRST_OK) {
            BRST_Error_Check(page->error);
            annot = NULL;
        }
    } else
        BRST_Error_Check(page->error);

    return annot;
}

BRST_EXPORT(BRST_Annotation)
BRST_Page_CreateSquareAnnot(BRST_Page page,
    BRST_Rect rect,
    const char* text,
    BRST_Encoder encoder)
{
    BRST_PageAttr attr;
    BRST_Annotation annot;

    BRST_PTRACE(" BRST_Page_CreateCircleAnnot\n");

    if (!BRST_Page_Validate(page))
        return NULL;

    attr = (BRST_PageAttr)page->attr;

    if (encoder && !BRST_Encoder_Validate(encoder)) {
        BRST_Error_Raise(page->error, BRST_INVALID_ENCODER, 0);
        return NULL;
    }

    annot = BRST_MarkupAnnot_New(page->mmgr, attr->xref, rect, text, encoder, BRST_ANNOT_SQUARE);
    if (annot) {
        if (AddAnnotation(page, annot) != BRST_OK) {
            BRST_Error_Check(page->error);
            annot = NULL;
        }
    } else
        BRST_Error_Check(page->error);

    return annot;
}

BRST_EXPORT(BRST_Annotation)
BRST_Page_CreateTextMarkupAnnot(BRST_Page page,
    BRST_Rect rect,
    const char* text,
    BRST_Encoder encoder,
    BRST_AnnotType subType)
{
    BRST_PageAttr attr;
    BRST_Annotation annot;

    BRST_PTRACE(" BRST_Page_CreateTextMarkupAnnot\n");

    if (!BRST_Page_Validate(page))
        return NULL;

    attr = (BRST_PageAttr)page->attr;

    if (encoder && !BRST_Encoder_Validate(encoder)) {
        BRST_Error_Raise(page->error, BRST_INVALID_ENCODER, 0);
        return NULL;
    }

    annot = BRST_MarkupAnnot_New(page->mmgr, attr->xref, rect, text, encoder, subType);
    if (annot) {
        if (AddAnnotation(page, annot) != BRST_OK) {
            BRST_Error_Check(page->error);
            annot = NULL;
        }
    } else
        BRST_Error_Check(page->error);

    return annot;
}

BRST_EXPORT(BRST_Annotation)
BRST_Page_CreateHighlightAnnot(BRST_Page page,
    BRST_Rect rect,
    const char* text,
    BRST_Encoder encoder)
{
    BRST_PTRACE(" BRST_Page_CreateHighlightAnnot\n");

    return BRST_Page_CreateTextMarkupAnnot(page, rect, text, encoder, BRST_ANNOT_HIGHLIGHT);
}

BRST_EXPORT(BRST_Annotation)
BRST_Page_CreateSquigglyAnnot(BRST_Page page,
    BRST_Rect rect,
    const char* text,
    BRST_Encoder encoder)
{
    BRST_PTRACE(" BRST_Page_CreateSquigglyAnnot\n");

    return BRST_Page_CreateTextMarkupAnnot(page, rect, text, encoder, BRST_ANNOT_SQUIGGLY);
}

BRST_EXPORT(BRST_Annotation)
BRST_Page_CreateUnderlineAnnot(BRST_Page page,
    BRST_Rect rect,
    const char* text,
    BRST_Encoder encoder)
{
    BRST_PTRACE(" BRST_Page_CreateUnderlineAnnot\n");

    return BRST_Page_CreateTextMarkupAnnot(page, rect, text, encoder, BRST_ANNOT_UNDERLINE);
}

BRST_EXPORT(BRST_Annotation)
BRST_Page_CreateStrikeOutAnnot(BRST_Page page,
    BRST_Rect rect,
    const char* text,
    BRST_Encoder encoder)
{
    BRST_PTRACE(" BRST_Page_CreateStrikeOutAnnot\n");

    return BRST_Page_CreateTextMarkupAnnot(page, rect, text, encoder, BRST_ANNOT_STRIKE_OUT);
}

BRST_EXPORT(BRST_Annotation)
BRST_Page_CreatePopupAnnot(BRST_Page page,
    BRST_Rect rect,
    BRST_Annotation parent)
{
    BRST_PageAttr attr;
    BRST_Annotation annot;

    BRST_PTRACE(" BRST_Page_CreatePopupAnnot\n");

    if (!BRST_Page_Validate(page))
        return NULL;

    attr = (BRST_PageAttr)page->attr;

    annot = BRST_PopupAnnot_New(page->mmgr, attr->xref, rect, parent);
    if (annot) {
        if (AddAnnotation(page, annot) != BRST_OK) {
            BRST_Error_Check(page->error);
            annot = NULL;
        }
    } else
        BRST_Error_Check(page->error);

    return annot;
}

BRST_EXPORT(BRST_Annotation)
BRST_Page_CreateStampAnnot(BRST_Page page,
    BRST_Rect rect,
    BRST_StampAnnotName name,
    const char* text,
    BRST_Encoder encoder)
{
    BRST_PageAttr attr;
    BRST_Annotation annot;

    BRST_PTRACE(" BRST_Page_CreateStampAnnot\n");

    if (!BRST_Page_Validate(page))
        return NULL;

    attr = (BRST_PageAttr)page->attr;

    annot = BRST_StampAnnot_New(page->mmgr, attr->xref, rect, name, text, encoder);
    if (annot) {
        if (AddAnnotation(page, annot) != BRST_OK) {
            BRST_Error_Check(page->error);
            annot = NULL;
        }
    } else
        BRST_Error_Check(page->error);

    return annot;
}

BRST_EXPORT(BRST_Annotation)
BRST_Page_CreateProjectionAnnot(BRST_Page page,
    BRST_Rect rect,
    const char* text,
    BRST_Encoder encoder)
{
    BRST_PageAttr attr;
    BRST_Annotation annot;

    BRST_PTRACE(" BRST_Page_CreateProjectionAnnot\n");

    if (!BRST_Page_Validate(page))
        return NULL;

    attr = (BRST_PageAttr)page->attr;

    annot = BRST_ProjectionAnnot_New(page->mmgr, attr->xref, rect, text, encoder);
    if (annot) {
        if (AddAnnotation(page, annot) != BRST_OK) {
            BRST_Error_Check(page->error);
            annot = NULL;
        }
    } else
        BRST_Error_Check(page->error);

    return annot;
}
