#include "brst_types.h"
#include "brst_encrypt.h"
#include "brst_encoder.h"
#include "brst_stream.h"
#include "brst_mmgr.h"
#include "brst_dict.h"
#include "brst_xref.h"
#include "private/brst_dict.h"
#include "brst_encoder.h"
#include "brst_page.h"
#include "brst_destination.h"
#include "brst_outline.h"
#include "private/brst_encrypt_dict.h"
#include "private/brst_catalog.h"
#include "brst_pdfa.h"
#include "brst_doc.h"
#include "private/brst_doc.h"
#include "private/brst_string.h"
#include "brst_page.h"
#include "brst_consts.h"
#include "brst_error.h"
#include "private/brst_utils.h"

BRST_Dict
BRST_PageLabel_New(BRST_Doc pdf,
    BRST_PageNumStyle style,
    BRST_INT first_page,
    const char* prefix)
{
    BRST_Dict obj = BRST_Dict_New(pdf->mmgr);

    BRST_PTRACE(" BRST_PageLabel_New\n");

    if (!obj)
        return NULL;

    switch (style) {
    case BRST_PAGE_NUM_DECIMAL:
        if (BRST_Dict_AddName(obj, "S", "D") != BRST_OK)
            goto Fail;
        break;
    case BRST_PAGE_NUM_UPPER_ROMAN:
        if (BRST_Dict_AddName(obj, "S", "R") != BRST_OK)
            goto Fail;
        break;
    case BRST_PAGE_NUM_LOWER_ROMAN:
        if (BRST_Dict_AddName(obj, "S", "r") != BRST_OK)
            goto Fail;
        break;
    case BRST_PAGE_NUM_UPPER_LETTERS:
        if (BRST_Dict_AddName(obj, "S", "A") != BRST_OK)
            goto Fail;
        break;
    case BRST_PAGE_NUM_LOWER_LETTERS:
        if (BRST_Dict_AddName(obj, "S", "a") != BRST_OK)
            goto Fail;
        break;
    default:
        BRST_Error_Set(pdf->error, BRST_PAGE_NUM_OUT_OF_RANGE,
            (BRST_STATUS)style);
        goto Fail;
    }

    if (prefix && prefix[0] != 0)
        if (BRST_Dict_Add(obj, "P", BRST_String_New(pdf->mmgr, prefix, pdf->def_encoder)) != BRST_OK)
            goto Fail;

    if (first_page != 0)
        if (BRST_Dict_AddNumber(obj, "St", first_page) != BRST_OK)
            goto Fail;

    return obj;

Fail:
    BRST_Dict_Free(obj);
    return NULL;
}
