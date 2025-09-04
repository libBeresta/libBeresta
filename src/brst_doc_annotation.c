#include "brst_external.h"
#include "brst_types.h"
#include "brst_mmgr.h"
#include "brst_encrypt.h"
#include "brst_stream.h"
#include "brst_dict.h"
#include "brst_xref.h"
#include "brst_transmatrix.h"
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
#include "private/brst_encrypt_dict.h"
#include "brst_outline.h"
#include "private/brst_catalog.h"
#include "private/brst_pdfa.h"
#include "brst_pdfa.h"
#include "brst_doc.h"
#include "private/brst_doc.h"
#include "brst_fontdef.h"
#include "private/brst_doc_fontdef.h"
#include "private/brst_doc_encoder.h"
#include "brst_version.h"
#include "brst_geometry_defines.h"
#include "private/brst_destination.h"
#include "brst_exdata.h"
#include "brst_javascript.h"
#include "brst_doc_page_xobject.h"
#include "brst_doc_annotation.h"
#include "brst_page_annotation.h"

BRST_EXPORT(BRST_Annotation)
BRST_Doc_Page_CreateWidgetAnnot_WhiteOnlyWhilePrint(BRST_Doc pdf,
    BRST_Page page,
    BRST_Rect rect)
{
    BRST_XObject fxobj;
    BRST_Annotation annot;
    BRST_Dict appearance;
    BRST_Dict mk;
    BRST_STATUS ret = BRST_OK;
    BRST_Array array_bg;

    BRST_PTRACE(" BRST_Doc_Page_CreateWidgetAnnot_WhiteOnlyWhilePrint\n");

    annot = BRST_Page_CreateWidgetAnnot(page, rect);

    fxobj = BRST_Doc_Page_XObject_CreateAsWhiteRect(pdf, page, rect);
    if (!fxobj)
        return NULL;

    appearance = BRST_Dict_New(annot->mmgr);
    if (!appearance)
        return NULL;

    ret = BRST_Dict_Add(annot, "AP", appearance);
    if (ret != BRST_OK)
        return NULL;

    ret = BRST_Dict_Add(appearance, "N", fxobj);
    if (ret != BRST_OK)
        return NULL;

    mk = BRST_Dict_New(annot->mmgr);
    if (!mk)
        return NULL;

    ret = BRST_Dict_Add(annot, "MK", mk);
    if (ret != BRST_OK)
        return NULL;

    array_bg = BRST_Array_New(annot->mmgr);
    if (!array_bg)
        return NULL;

    if (BRST_Dict_Add(mk, "BG", array_bg) != BRST_OK)
        return NULL;

    ret = BRST_Array_AddReal(array_bg, 1.0);
    ret += BRST_Array_AddReal(array_bg, 1.0);
    ret += BRST_Array_AddReal(array_bg, 1.0);

    ret += BRST_Dict_AddName(annot, "FT", "Btn");
    if (ret != BRST_OK)
        return NULL;

    ret = BRST_Dict_AddNumber(annot, "F", 36);
    if (ret != BRST_OK)
        return NULL;

    ret = BRST_Dict_Add(annot, "T", BRST_String_New(annot->mmgr, "Blind", NULL));
    if (ret != BRST_OK)
        return NULL;

    return annot;
}
