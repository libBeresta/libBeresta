#include "brst_external.h"
#include "brst_types.h"
#include "brst_mmgr.h"
#include "brst_encrypt.h"
#include "brst_stream.h"
#include "brst_dict.h"
#include "brst_xref.h"
#include "brst_encoder.h"
#include "brst_error.h"
#include "private/brst_error.h"
#include "brst_consts.h"
#include "private/brst_utils.h"
#include "brst_page.h"
#include "private/brst_encrypt_dict.h"
#include "brst_outline.h"
#include "brst_pdfa.h"
#include "private/brst_catalog.h"
#include "brst_doc.h"
#include "private/brst_doc.h"

BRST_EXPORT(BRST_STATUS)
BRST_Error_Check(BRST_Error error)
{
    BRST_PTRACE(" BRST_Error_Check: error_no=0x%04X detail_no=0x%04X\n",
        (BRST_UINT)BRST_Error_Code(error), (BRST_UINT)BRST_Error_DetailCode(error));

    if (BRST_Error_Code(error) != BRST_OK && BRST_Error_ErrorFn(error))
        BRST_Error_ErrorFn(error)(BRST_Error_Code(error), BRST_Error_DetailCode(error), BRST_Error_UserData(error));

    return BRST_Error_Code(error);
}

BRST_EXPORT(BRST_STATUS)
BRST_Doc_Error_Code(BRST_Doc pdf)
{
    if (!BRST_Doc_Validate(pdf))
        return BRST_INVALID_DOCUMENT;

    return BRST_Error_Code(pdf->error);
}

BRST_EXPORT(BRST_STATUS)
BRST_Doc_Error_DetailCode(BRST_Doc pdf)
{
    if (!BRST_Doc_Validate(pdf))
        return BRST_INVALID_DOCUMENT;

    return BRST_Error_DetailCode(pdf->error);
}

BRST_EXPORT(void)
BRST_Doc_Error_Reset(BRST_Doc pdf)
{
    if (!BRST_Doc_Validate(pdf))
        return;

    BRST_Error_Reset(pdf->error);
}

BRST_EXPORT(BRST_STATUS)
BRST_Doc_Error_SetHandler(BRST_Doc pdf,
    BRST_Error_Handler user_error_fn)
{
    if (!BRST_Doc_Validate(pdf))
        return BRST_INVALID_DOCUMENT;

    BRST_Error_SetHandler(pdf->error, user_error_fn);

    return BRST_OK;
}
