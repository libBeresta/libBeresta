#include "brst_external.h"
#include "brst_types.h"
#include "brst_mmgr.h"
#include "brst_encrypt.h"
#include "brst_stream.h"
#include "private/brst_stream.h"
#include "brst_xref.h"
#include "brst_dict.h"
#include "private/brst_dict.h"
#include "brst_encoder.h"
#include "private/brst_encoder.h"
#include "brst_error.h"
#include "brst_consts.h"
#include "brst_ext_gstate.h"
#include "brst_font.h"
#include "brst_shading.h"
#include "brst_doc.h"
#include "brst_pdfa.h"
#include "brst_page.h"
#include "brst_page_routines.h"
#include "private/brst_catalog.h"
#include "brst_pattern.h"
#include "private/brst_page.h"
#include "brst_base.h"
#include "brst_matrix.h"
#include "private/brst_gstate.h"
#include "private/brst_page_attr.h"
#include "private/brst_array.h"
#include "brst_geometry.h"

const char* const BRST_PATTERN_COLORSPACE_NAMES[] = {
    "patrgbcs",
    "patcmykcs",
};

BRST_STATUS
BRST_Doc_Page_Pattern_EnsureColorSpace(
    BRST_Dict       dict,
    BRST_ColorSpace cs
) {
    BRST_Dict resources = BRST_Page_InheritableItem(dict, "Resources",
        BRST_OCLASS_DICT);
    if (!resources) {
        return BRST_INVALID_DOCUMENT;
    }

    BRST_Dict colorSpace = (BRST_Dict)BRST_Dict_Item(resources, "ColorSpace", BRST_OCLASS_DICT);

    if (!colorSpace) {
        colorSpace = BRST_Dict_New(BRST_Dict_MMgr(dict));
        BRST_Dict_Add(resources, "ColorSpace", colorSpace);
    }

    BRST_CSTR cs_name;
    if (cs == BRST_COLORSPACE_DEVICERGB) {
        cs_name = BRST_PATTERN_COLORSPACE_NAMES[0];
    } else if (cs == BRST_COLORSPACE_DEVICECMYK) {
        cs_name = BRST_PATTERN_COLORSPACE_NAMES[1];
    } else {
        cs_name = NULL;
        BRST_Error_Raise(dict->error, BRST_INVALID_COLOR_SPACE, 0);
        return BRST_INVALID_COLOR_SPACE;
    }
    BRST_Array cs_data = (BRST_Array)BRST_Dict_Item(colorSpace, cs_name, BRST_OCLASS_ARRAY);

    if (!cs_data) {
        cs_data = BRST_Array_New(BRST_Dict_MMgr(dict));
        BRST_Array_AddName(cs_data, "Pattern");
        BRST_CSTR dev;
        // TODO Вынести куда-то в общее место
        if (cs == BRST_COLORSPACE_DEVICERGB) {
            dev = "DeviceRGB";
        } else if (cs == BRST_COLORSPACE_DEVICECMYK) {
            dev = "DeviceCMYK";
        } else {
            cs_name = NULL;
            return BRST_INVALID_COLOR_SPACE;
        }
        BRST_Array_AddName(cs_data, dev);
        BRST_Dict_Add(colorSpace, cs_name, cs_data);
    }

    return BRST_OK;
}

/* scn */
BRST_EXPORT(BRST_STATUS)
BRST_Doc_Dict_RGBPatternFill_Select(
    BRST_Doc  pdf,
    BRST_Dict dict,
    BRST_REAL r,
    BRST_REAL g,
    BRST_REAL b,
    BRST_Pattern pattern)
{

    BRST_PTRACE(" BRST_Doc_Dict_RGBPatternFill_Select\n");

    BRST_STATUS ret = BRST_OK;

    BRST_BOOL isPage = BRST_Dict_IsPage(dict);

    if (isPage) {
        ret += BRST_Page_CheckState(dict, BRST_GMODE_PAGE_DESCRIPTION);
    }

    if (ret != BRST_OK)
        return ret;

    if (!pattern || pattern->header.obj_class != (BRST_OSUBCLASS_PATTERN | BRST_OCLASS_DICT))
        return BRST_Error_Raise(dict->error, BRST_INVALID_OBJECT, 0);

    if (dict->mmgr != pattern->mmgr)
        return BRST_Error_Raise(dict->error, BRST_PAGE_INVALID_PATTERN, 0);

    BRST_PageAttr attr = (BRST_PageAttr)dict->attr;

    BRST_Stream stream = attr ? attr->stream : dict->stream;

    if (!isPage || (isPage && attr && attr->gstate->pattern == NULL)) {
        BRST_Doc_Page_Pattern_EnsureColorSpace(dict, BRST_COLORSPACE_DEVICERGB);

        BRST_CSTR cs_name = BRST_PATTERN_COLORSPACE_NAMES[0];

        if (BRST_Stream_WriteEscapeName(stream, cs_name) != BRST_OK) {
            return BRST_Error_Check(dict->error);
        }
        if (BRST_Stream_WriteStr(stream, " cs ") != BRST_OK) {
            return BRST_Error_Check(dict->error);
        }
    }

    if (BRST_Dict_SetRGBPatternFill(dict, r, g, b, pattern) != BRST_OK) {
        return BRST_Error_Check(dict->error);
    }

    return ret;
}

BRST_EXPORT(BRST_STATUS)
BRST_Doc_Page_RGBPatternFill_Select(
    BRST_Doc  pdf,
    BRST_Page page,
    BRST_REAL r,
    BRST_REAL g,
    BRST_REAL b,
    BRST_Pattern pattern)
{

    BRST_PTRACE(" BRST_Doc_Page_RGBPatternFill_Select\n");
    return BRST_Doc_Dict_RGBPatternFill_Select(pdf, page, r, g, b, pattern);
}

BRST_EXPORT(BRST_STATUS)
BRST_Doc_Dict_RGBPatternFillUint_Select(
    BRST_Doc     pdf,
    BRST_Dict    dict,
    BRST_UINT8   r,
    BRST_UINT8   g,
    BRST_UINT8   b,
    BRST_Pattern pattern) {

    BRST_REAL rr = ((BRST_REAL)r) / 255.0f;
    BRST_REAL gg = ((BRST_REAL)g) / 255.0f;
    BRST_REAL bb = ((BRST_REAL)b) / 255.0f;

    return BRST_Doc_Dict_RGBPatternFill_Select(pdf, dict, rr, gg, bb, pattern);
}

BRST_EXPORT(BRST_STATUS)
BRST_Doc_Page_RGBPatternFillUint_Select(
    BRST_Doc     pdf,
    BRST_Page    page,
    BRST_UINT8   r,
    BRST_UINT8   g,
    BRST_UINT8   b,
    BRST_Pattern pattern) {

    BRST_PTRACE(" BRST_Doc_Page_RGBPatternFillUint_Select\n");
    return BRST_Doc_Dict_RGBPatternFillUint_Select(pdf, page, r, g, b, pattern);
}

BRST_EXPORT(BRST_STATUS)
BRST_Doc_Dict_RGBPatternFillHex_Select(
    BRST_Doc     pdf,
    BRST_Dict    dict,
    BRST_UINT32  rgb,
    BRST_Pattern pattern) {

    return BRST_Doc_Dict_RGBPatternFill_Select(pdf, dict, 
        (BRST_REAL)((rgb >> 16) & 0xFF), 
        (BRST_REAL)((rgb >>  8) & 0xFF), 
        (BRST_REAL)(rgb & 0xFF), pattern);
}

BRST_EXPORT(BRST_STATUS)
BRST_Doc_Page_RGBPatternFillHex_Select(
    BRST_Doc     pdf,
    BRST_Dict    dict,
    BRST_UINT32  rgb,
    BRST_Pattern pattern) {

    BRST_PTRACE(" BRST_Doc_Page_RGBPatternFillHex_Select\n");

    return BRST_Doc_Dict_RGBPatternFillHex_Select(pdf, dict, rgb, pattern);

}