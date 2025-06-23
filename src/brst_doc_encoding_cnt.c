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
#include "brst_doc.h"
#include "private/brst_doc.h"
#include "private/brst_encoder_cmap.h"
#include "private/brst_doc_encoder.h"
#include "private/brst_encoding_cnt.h"
#include "brst_base.h"

BRST_EXPORT(BRST_STATUS)
BRST_Doc_UseCNTEncodings(BRST_Doc pdf)
{
    BRST_Encoder encoder;
    BRST_STATUS ret;

    if (!BRST_Doc_Initialized(pdf))
        return BRST_INVALID_DOCUMENT;

    /* Microsoft Code Page 950 (lfCharSet 0x88) Big Five character set with
     * ETen extensions
     */
    encoder = BRST_CMapEncoder_New(pdf->mmgr, "ETen-B5-H",
        ETen_B5_H_Init);

    if ((ret = BRST_Doc_RegisterEncoder(pdf, encoder)) != BRST_OK)
        return ret;

    /* Microsoft Code Page 950 (lfCharSet 0x88) Big Five character set with
     * ETen extensions (vertical writing) */
    encoder = BRST_CMapEncoder_New(pdf->mmgr, "ETen-B5-V",
        ETen_B5_V_Init);

    if ((ret = BRST_Doc_RegisterEncoder(pdf, encoder)) != BRST_OK)
        return ret;

    return BRST_OK;
}
