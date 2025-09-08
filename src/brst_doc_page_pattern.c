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
#include "brst_destination.h"
#include "private/brst_catalog.h"
#include "brst_outline.h"
#include "private/brst_encrypt_dict.h"
#include "private/brst_doc.h"
#include "brst_pattern.h"
#include "private/brst_page.h"
#include "brst_base.h"
#include "brst_image.h"
#include "brst_matrix.h"
#include "private/brst_gstate.h"
#include "private/brst_page_attr.h"
#include "private/brst_array.h"
#include "private/brst_name.h"
#include "brst_doc_page_xobject.h"
#include "private/brst_pattern.h"
#include "brst_geometry.h"

const char* const BRST_PATTERN_COLORSPACE_NAMES[] = {
    "patrgbcs",
    "patcmykcs",
};

BRST_EXPORT(BRST_Pattern)
BRST_Doc_Page_Pattern_Tiling_Create(
    BRST_Doc pdf,
    BRST_Page page,
    BRST_REAL left,
    BRST_REAL bottom,
    BRST_REAL right,
    BRST_REAL top,
    BRST_REAL xstep,
    BRST_REAL ystep,
    BRST_Matrix matrix
) {
    return BRST_Pattern_Tiling_New(page->mmgr, pdf->xref, left, bottom, right, top, xstep, ystep, matrix);
}

BRST_EXPORT(BRST_Stream)
BRST_Doc_Page_Pattern_Stream(BRST_Pattern pat) {
    return BRST_Pattern_Stream(pat);
}

BRST_STATUS
BRST_Doc_Page_Pattern_EnsureColorSpace(
    BRST_Doc        pdf, 
    BRST_Page       page, 
    BRST_ColorSpace cs
) {
    BRST_Dict resources = BRST_Page_InheritableItem(page, "Resources",
        BRST_OCLASS_DICT);
    if (!resources) {
        printf("HIA: 1\n");
        return BRST_INVALID_DOCUMENT;
    }

    BRST_Dict colorSpace = (BRST_Dict)BRST_Dict_Item(resources, "ColorSpace", BRST_OCLASS_DICT);

    if (!colorSpace) {
        printf("HIA: 2\n");
        colorSpace = BRST_Dict_New(BRST_Page_MMgr(page));
        BRST_Xref_Add(pdf->xref, colorSpace);
        BRST_Dict_Add(resources, "ColorSpace", colorSpace);
    }
        
    BRST_CSTR cs_name;
    printf("HIA: c s = %d \n", cs);
    if (cs == BRST_CS_DEVICE_RGB) {
        cs_name = BRST_PATTERN_COLORSPACE_NAMES[0];
    } else if (cs == BRST_CS_DEVICE_CMYK) {
        cs_name = BRST_PATTERN_COLORSPACE_NAMES[1];
    } else {
        cs_name = NULL;
        BRST_Error_Raise(page->error, BRST_INVALID_COLOR_SPACE, 0);
        return BRST_INVALID_COLOR_SPACE;
    }
    BRST_Array cs_data = (BRST_Array)BRST_Dict_Item(colorSpace, cs_name, BRST_OCLASS_ARRAY);

    if (!cs_data) {
        cs_data = BRST_Array_New(BRST_Page_MMgr(page));
        BRST_Array_AddName(cs_data, "Pattern");
        BRST_CSTR dev;
        // TODO Вынести куда-то в общее место
        if (cs == BRST_CS_DEVICE_RGB) {
            dev = "DeviceRGB";
        } else if (cs == BRST_CS_DEVICE_CMYK) {
            dev = "DeviceCMYK";
        } else {
            cs_name = NULL;
            return BRST_INVALID_COLOR_SPACE;
        }        
        BRST_Array_AddName(cs_data, dev);
        BRST_Dict_Add(colorSpace, cs_name, cs_data);
    }

    printf("HIA: OK\n");

    return BRST_OK;    
}

/* scn */
BRST_EXPORT(BRST_STATUS)
BRST_Doc_Page_RGBPatternFill_Select(
    BRST_Doc  pdf,
    BRST_Page page,
    BRST_REAL r,
    BRST_REAL g,
    BRST_REAL b,
    BRST_Pattern pattern)
{
    BRST_STATUS ret = BRST_Page_CheckState(page, BRST_GMODE_PAGE_DESCRIPTION);

    BRST_PTRACE(" BRST_Doc_Page_RGBPatternFill_Select\n");

    if (ret != BRST_OK)
        return ret;

    if (!pattern || pattern->header.obj_class != (BRST_OSUBCLASS_PATTERN | BRST_OCLASS_DICT))
        return BRST_Error_Raise(page->error, BRST_INVALID_OBJECT, 0);

    if (page->mmgr != pattern->mmgr)
        return BRST_Error_Raise(page->error, BRST_PAGE_INVALID_PATTERN, 0);

    BRST_PageAttr attr = (BRST_PageAttr)page->attr;

    if (attr->gstate->pattern == NULL) {
        BRST_Doc_Page_Pattern_EnsureColorSpace(pdf, page, BRST_CS_DEVICE_RGB);
        
        BRST_CSTR cs_name = BRST_PATTERN_COLORSPACE_NAMES[0];

        if (BRST_Stream_WriteEscapeName(attr->stream, cs_name) != BRST_OK) {
            return BRST_Error_Check(page->error);            
        }
        if (BRST_Stream_WriteStr(attr->stream, " cs ") != BRST_OK) {
            return BRST_Error_Check(page->error);            
        }
    }

    if (BRST_Page_SetRGBPatternFill(page, r, g, b, pattern) != BRST_OK) {
        return BRST_Error_Check(page->error);
    }

    return ret;
}

BRST_EXPORT(BRST_STATUS)
BRST_Doc_Page_RGBPatternFillUint_Select(
    BRST_Doc     pdf,
    BRST_Page    page,
    BRST_UINT8   r,
    BRST_UINT8   g,
    BRST_UINT8   b,
    BRST_Pattern pattern) {

    BRST_REAL rr = (BRST_REAL)r / 255.0;
    BRST_REAL gg = (BRST_REAL)g / 255.0;
    BRST_REAL bb = (BRST_REAL)b / 255.0;

    return BRST_Doc_Page_RGBPatternFill_Select(pdf, page, rr, gg, bb, pattern);
}

BRST_EXPORT(BRST_STATUS)
BRST_Doc_Page_RGBPatternFillHex_Select(
    BRST_Doc     pdf,
    BRST_Page    page,
    BRST_UINT32  rgb,
    BRST_Pattern pattern) {

    return BRST_Doc_Page_RGBPatternFill_Select(pdf, page, (rgb >> 16) & 0xFF, (rgb >> 8) & 0xFF, rgb & 0xFF, pattern);
}
