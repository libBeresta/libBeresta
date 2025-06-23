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
#include "private/brst_encoding_jp.h"
#include "brst_base.h"

BRST_EXPORT(BRST_STATUS)
BRST_Doc_UseJPEncodings(BRST_Doc pdf)
{
    BRST_Encoder encoder;
    BRST_STATUS ret;

    if (!BRST_Doc_Initialized(pdf))
        return BRST_INVALID_DOCUMENT;

    /* Microsoft Code Page 932, JIS X 0208 character */
    encoder = BRST_CMapEncoder_New(pdf->mmgr, "90ms-RKSJ-H",
        MS_RKSJ_H_Init);

    if ((ret = BRST_Doc_RegisterEncoder(pdf, encoder)) != BRST_OK)
        return ret;

    /* Microsoft Code Page 932, JIS X 0208 character (vertical writing) */
    encoder = BRST_CMapEncoder_New(pdf->mmgr, "90ms-RKSJ-V",
        MS_RKSJ_V_Init);

    if ((ret = BRST_Doc_RegisterEncoder(pdf, encoder)) != BRST_OK)
        return ret;

    /* Microsoft Code Page 932, JIS X 0208 character (proportional) */
    encoder = BRST_CMapEncoder_New(pdf->mmgr, "90msp-RKSJ-H",
        MSP_RKSJ_H_Init);

    if ((ret = BRST_Doc_RegisterEncoder(pdf, encoder)) != BRST_OK)
        return ret;

    /* JIS X 0208 character set, EUC-JP encoding */
    encoder = BRST_CMapEncoder_New(pdf->mmgr, "EUC-H",
        EUC_H_Init);

    if ((ret = BRST_Doc_RegisterEncoder(pdf, encoder)) != BRST_OK)
        return ret;

    /* JIS X 0208 character set, EUC-JP encoding (vertical writing) */
    encoder = BRST_CMapEncoder_New(pdf->mmgr, "EUC-V",
        EUC_V_Init);

    if ((ret = BRST_Doc_RegisterEncoder(pdf, encoder)) != BRST_OK)
        return ret;

    return BRST_OK;
}
