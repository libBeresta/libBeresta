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
#include "brst_page.h"
#include "private/brst_encrypt_dict.h"
#include "brst_outline.h"
#include "private/brst_outline.h"
#include "brst_base.h"
#include "private/brst_number.h"
#include "brst_destination.h"
#include "private/brst_destination.h"

BRST_EXPORT(BRST_STATUS)
BRST_Outline_SetDestination(BRST_Outline outline,
    BRST_Destination dst)
{
    BRST_PTRACE((" BRST_Outline_SetDestination\n"));

    if (!BRST_Outline_Validate(outline))
        return BRST_INVALID_OUTLINE;

    if (!BRST_Destination_Validate(dst))
        return BRST_Error_Raise(outline->error, BRST_INVALID_DESTINATION, 0);

    if (dst == NULL)
        return BRST_Dict_RemoveElement(outline, "Dest");

    if (BRST_Dict_Add(outline, "Dest", dst) != BRST_OK)
        return BRST_Error_Check(outline->error);

    return BRST_OK;
}

BRST_EXPORT(BRST_STATUS)
BRST_Outline_SetOpened(BRST_Outline outline,
    BRST_BOOL opened)
{
    BRST_Number n;

    if (!BRST_Outline_Validate(outline))
        return BRST_INVALID_OUTLINE;

    n = (BRST_Number)BRST_Dict_Item(outline, "_OPENED",
        BRST_OCLASS_NUMBER);

    BRST_PTRACE((" BRST_Outline_SetOpened\n"));

    if (!n) {
        n = BRST_Number_New(outline->mmgr, (BRST_INT)opened);
        if (!n || BRST_Dict_Add(outline, "_OPENED", n) != BRST_OK)
            return BRST_Error_Check(outline->error);
    } else
        BRST_Number_SetValue(n, (BRST_INT)opened);

    return BRST_OK;
}
