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
#include "private/brst_encoder_basic.h"
#include "private/brst_encoder_cmap.h"
#include "brst_doc_encoder.h"
#include "private/brst_doc_encoder.h"
#include "brst_base.h"

BRST_EXPORT(BRST_Encoder)
BRST_Doc_Encoder_Current(BRST_Doc pdf)
{
    if (!BRST_Doc_Initialized(pdf))
        return NULL;

    return pdf->cur_encoder;
}

BRST_EXPORT(BRST_STATUS)
BRST_Doc_Encoder_SetCurrent(BRST_Doc pdf,
    const char* encoding_name)
{
    BRST_PTRACE((" BRST_Doc_Encoder_SetCurrent\n"));

    BRST_Encoder encoder;

    if (!BRST_Doc_Initialized(pdf))
        return BRST_Doc_Error_Code(pdf);

    encoder = BRST_Doc_Encoder_Prepare(pdf, encoding_name);

    if (!encoder)
        return BRST_Doc_Error_Code(pdf);

    pdf->cur_encoder = encoder;

    return BRST_OK;
}

BRST_EXPORT(BRST_Encoder)
BRST_Doc_Encoder_Prepare(BRST_Doc pdf,
    const char* encoding_name)
{
    BRST_Encoder encoder;
    BRST_STATUS ret;

    BRST_PTRACE((" BRST_Doc_Encoder_Prepare\n"));

    if (!BRST_Doc_Initialized(pdf))
        return NULL;

    encoder = BRST_Doc_FindEncoder(pdf, encoding_name);

    if (!encoder) {
        encoder = BRST_BasicEncoder_New(pdf->mmgr, encoding_name);

        if (!encoder) {
            BRST_Error_Check(pdf->error);
            return NULL;
        }

        if ((ret = BRST_List_Add(pdf->encoder_list, encoder)) != BRST_OK) {
            BRST_Encoder_Free(encoder);
            BRST_Error_Raise(pdf->error, ret, 0);
            return NULL;
        }
    }

    return encoder;
}
