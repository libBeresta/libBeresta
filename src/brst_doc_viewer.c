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
#include "private/brst_catalog.h"
#include "brst_pdfa.h"
#include "private/brst_doc.h"
#include "brst_doc.h"
#include "private/brst_destination.h"
#include "brst_base.h"
#include "brst_doc_viewer.h"

BRST_EXPORT(BRST_STATUS)
BRST_Doc_SetOpenAction(BRST_Doc pdf,
    BRST_Destination open_action)
{
    BRST_STATUS ret;

    BRST_PTRACE((" BRST_Doc_SetOpenAction\n"));

    if (!BRST_Doc_Initialized(pdf))
        return BRST_INVALID_DOCUMENT;

    if (open_action && !BRST_Destination_Validate(open_action))
        return BRST_Error_Raise(pdf->error, BRST_INVALID_DESTINATION, 0);

    ret = BRST_Catalog_SetOpenAction(pdf->catalog, open_action);
    if (ret != BRST_OK)
        return BRST_Error_Check(pdf->error);

    return BRST_OK;
}

BRST_EXPORT(BRST_UINT)
BRST_Doc_ViewerPreference(BRST_Doc pdf)
{
    BRST_PTRACE((" BRST_Doc_ViewerPreference\n"));

    if (!BRST_Doc_Initialized(pdf))
        return 0;

    return BRST_Catalog_ViewerPreference(pdf->catalog);
}

BRST_EXPORT(BRST_STATUS)
BRST_Doc_SetViewerPreference(BRST_Doc pdf,
    BRST_UINT value)
{
    BRST_STATUS ret;

    BRST_PTRACE((" BRST_Doc_SetViewerPreference\n"));

    if (!BRST_Doc_Initialized(pdf))
        return BRST_INVALID_DOCUMENT;

    ret = BRST_Catalog_SetViewerPreference(pdf->catalog, value);
    if (ret != BRST_OK)
        return BRST_Error_Check(pdf->error);

    pdf->pdf_version = (pdf->pdf_version > BRST_VER_16 ? pdf->pdf_version : BRST_VER_16);

    return BRST_OK;
}
