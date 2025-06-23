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
#include "private/brst_pdfa.h"
#include "brst_pdfa.h"
#include "brst_doc_pdfa.h"
#include "brst_doc.h"
#include "private/brst_doc.h"

BRST_EXPORT(BRST_STATUS)
BRST_Doc_PDFA_SetConformance(BRST_Doc pdf,
    BRST_PDFAType pdfa_type)
{
    if (pdf == NULL)
        return BRST_DOC_INVALID_OBJECT;

    pdf->pdfa_type = pdfa_type;
    return BRST_OK;
}

BRST_EXPORT(BRST_STATUS)
BRST_Doc_PDFA_AddXmpExtension(BRST_Doc pdf,
    const char* xmp_extension)
{
    if (pdf == NULL)
        return BRST_DOC_INVALID_OBJECT;

    return BRST_PDFA_AddXmpExtension(pdf, xmp_extension);
}

BRST_EXPORT(BRST_STATUS)
BRST_Doc_PDFA_AppendOutputIntents(BRST_Doc pdf, BRST_CSTR iccname, BRST_Dict iccdict)
{
    return BRST_PDFA_AppendOutputIntents(pdf, iccname, iccdict);
}
