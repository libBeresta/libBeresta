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
#include "private/brst_encoding_kr.h"
#include "brst_base.h"

BRST_EXPORT(BRST_STATUS)
BRST_Doc_UseKREncodings(BRST_Doc pdf)
{
    BRST_Encoder encoder;
    BRST_STATUS ret;

    if (!BRST_Doc_Initialized(pdf))
        return BRST_INVALID_DOCUMENT;

    /* Microsoft Code Page 949 (lfCharSet 0x81), KS X 1001:1992 character
     * set plus 8822 additional hangul, Unified Hangul Code (UHC) encoding
     * (proportional)
     */
    encoder = BRST_CMapEncoder_New(pdf->mmgr, "KSCms-UHC-H",
        KSCms_UHC_H_Init);

    if ((ret = BRST_Doc_RegisterEncoder(pdf, encoder)) != BRST_OK)
        return ret;

    /* Microsoft Code Page 949 (lfCharSet 0x81), KS X 1001:1992 character
     * set plus 8822 additional hangul, Unified Hangul Code (UHC) encoding
     * (fixed width)
     */
    encoder = BRST_CMapEncoder_New(pdf->mmgr, "KSCms-UHC-HW-H",
        KSCms_UHC_HW_H_Init);

    if ((ret = BRST_Doc_RegisterEncoder(pdf, encoder)) != BRST_OK)
        return ret;

    /* vertical writing virsion of KSCms-UHC-HW-H */
    encoder = BRST_CMapEncoder_New(pdf->mmgr, "KSCms-UHC-HW-V",
        KSCms_UHC_HW_V_Init);

    if ((ret = BRST_Doc_RegisterEncoder(pdf, encoder)) != BRST_OK)
        return ret;

    /*  KS X 1001:1992 character set, EUC-KR encoding */
    encoder = BRST_CMapEncoder_New(pdf->mmgr, "KSC-EUC-H",
        KSC_EUC_H_Init);

    if ((ret = BRST_Doc_RegisterEncoder(pdf, encoder)) != BRST_OK)
        return ret;

    /* KS X 1001:1992 character set, EUC-KR encoding (vertical writing)*/
    encoder = BRST_CMapEncoder_New(pdf->mmgr, "KSC-EUC-V",
        KSC_EUC_V_Init);

    if ((ret = BRST_Doc_RegisterEncoder(pdf, encoder)) != BRST_OK)
        return ret;

    return BRST_OK;
}
