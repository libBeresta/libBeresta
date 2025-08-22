#include "brst_types.h"
#include "brst_mmgr.h"
#include "brst_encrypt.h"
#include "brst_stream.h"
#include "brst_dict.h"
#include "brst_xref.h"
#include "brst_encoder.h"
#include "brst_page.h"
#include "brst_destination.h"
#include "brst_outline.h"
#include "private/brst_encrypt_dict.h"
#include "private/brst_catalog.h"
#include "brst_pdfa.h"
#include "brst_doc.h"
#include "private/brst_doc.h"
#include "brst_base.h"
#include "brst_error.h"
#include "brst_fontdef.h"
#include "private/brst_fontdef.h"
#include "brst_consts.h"
#include "private/brst_utils.h"

BRST_Pages
BRST_Doc_Pages_Current(BRST_Doc pdf)
{
    BRST_PTRACE(" BRST_Doc_Pages_Current\n");

    if (!BRST_Doc_Initialized(pdf))
        return NULL;

    return pdf->cur_pages;
}

BRST_STATUS
BRST_Doc_Pages_SetCurrent(BRST_Doc pdf,
    BRST_Pages pages)
{
    BRST_PTRACE(" BRST_Doc_SetCurrentPages\n");

    if (!BRST_Doc_Initialized(pdf))
        return BRST_INVALID_DOCUMENT;

    if (!BRST_Pages_Validate(pages))
        return BRST_Error_Set(pdf->error, BRST_INVALID_PAGES, 0);

    /* check whether the pages belong to the pdf */
    if (pdf->mmgr != pages->mmgr)
        return BRST_Error_Set(pdf->error, BRST_INVALID_PAGES, 0);

    pdf->cur_pages = pages;

    return BRST_OK;
}

BRST_Pages
BRST_Doc_Pages_AddTo(BRST_Doc pdf,
    BRST_Pages parent)
{
    BRST_Pages pages;

    BRST_PTRACE(" BRST_Doc_Pages_AddTo\n");

    if (!BRST_Doc_Initialized(pdf))
        return NULL;

    if (!BRST_Pages_Validate(parent)) {
        BRST_Error_Raise(pdf->error, BRST_INVALID_PAGES, 0);
        return NULL;
    }

    /* check whether the page belong to the pdf */
    if (pdf->mmgr != parent->mmgr) {
        BRST_Error_Raise(pdf->error, BRST_INVALID_PAGES, 0);
        return NULL;
    }

    pages = BRST_Pages_New(pdf->mmgr, parent, pdf->xref);
    if (pages)
        pdf->cur_pages = pages;
    else
        BRST_Error_Check(pdf->error);

    return pages;
}
