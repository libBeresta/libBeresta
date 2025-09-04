#include "brst_mmgr.h"
#include "brst_encrypt.h"
#include "brst_encoder.h"
#include "brst_stream.h"
#include "brst_dict.h"
#include "brst_page.h"
#include "brst_xref.h"
#include "private/brst_xref.h"
#include "brst_transmatrix.h"
#include "brst_array.h"
#include "private/brst_array.h"
#include "brst_destination.h"
#include "private/brst_destination.h"
#include "brst_consts.h"
#include "brst_error.h"
#include "private/brst_utils.h"
#include "brst_shading.h"
#include "brst_font.h"
#include "brst_ext_gstate.h"
#include "private/brst_page.h"

const char* const BRST_DESTINATION_TYPE_NAMES[] = {
    "XYZ",
    "Fit",
    "FitH",
    "FitV",
    "FitR",
    "FitB",
    "FitBH",
    "FitBV",
    NULL
};

BRST_Destination
BRST_Destination_New(BRST_MMgr mmgr,
    BRST_Page target,
    BRST_Xref xref)
{
    BRST_Destination dst;

    BRST_PTRACE(" BRST_Destination_New\n");

    if (!BRST_Page_Validate(target)) {
        BRST_Error_Set(BRST_MMgr_Error(mmgr), BRST_INVALID_PAGE, 0);
        return NULL;
    }

    dst = BRST_Array_New(mmgr);
    if (!dst)
        return NULL;

    dst->header.obj_class |= BRST_OSUBCLASS_DESTINATION;

    if (BRST_Xref_Add(xref, dst) != BRST_OK)
        return NULL;

    /* first item of array must be target page */
    if (BRST_Array_Add(dst, target) != BRST_OK)
        return NULL;

    /* default type is BRST_FIT */
    if (BRST_Array_AddName(dst,
            BRST_DESTINATION_TYPE_NAMES[(BRST_INT)BRST_FIT])
        != BRST_OK)
        return NULL;

    return dst;
}

BRST_BOOL
BRST_Destination_Validate(BRST_Destination dst)
{
    BRST_Obj_Header* header = (BRST_Obj_Header*)dst;
    BRST_Page target;

    if (!dst || header->obj_class != (BRST_OCLASS_ARRAY | BRST_OSUBCLASS_DESTINATION))
        return BRST_FALSE;

    /* destination-types not defined. */
    if (BRST_List_Count(dst->list) < 2)
        return BRST_FALSE;

    target = (BRST_Page)BRST_Array_Item(dst, 0, BRST_OCLASS_DICT);
    if (!BRST_Page_Validate(target)) {
        BRST_Error_Set(dst->error, BRST_INVALID_PAGE, 0);
        return BRST_FALSE;
    }

    return BRST_TRUE;
}
