#include "brst_types.h"
#include "brst_mmgr.h"
#include "brst_encrypt.h"
#include "brst_stream.h"
#include "brst_xref.h"
#include "brst_dict.h"
#include "private/brst_dict.h"
#include "private/brst_xref.h"
#include "brst_encoder.h"
#include "brst_page.h"
#include "brst_destination.h"
#include "brst_outline.h"
#include "private/brst_encrypt_dict.h"
#include "private/brst_catalog.h"
#include "brst_pdfa.h"
#include "brst_doc.h"
#include "private/brst_doc.h"
#include "private/brst_utils.h"
#include "brst_consts.h"
#include "brst_error.h"

BRST_Encoder
BRST_Doc_FindEncoder(BRST_Doc pdf,
    const char* encoding_name)
{
    BRST_List list = pdf->encoder_list;
    BRST_UINT i;

    BRST_PTRACE((" BRST_Doc_FindEncoder\n"));

    for (i = 0; i < BRST_List_Count(list); i++) {
        BRST_Encoder encoder = (BRST_Encoder)BRST_List_ItemAt(list, i);

        if (BRST_StrCmp(encoding_name, encoder->name) == 0) {

            /* if encoder is uninitialize, call init_fn() */
            if (encoder->type == BRST_ENCODER_TYPE_UNINITIALIZED) {
                if (!encoder->init_fn || encoder->init_fn(encoder) != BRST_OK)
                    return NULL;
            }

            return encoder;
        }
    }

    return NULL;
}

BRST_STATUS
BRST_Doc_RegisterEncoder(BRST_Doc pdf,
    BRST_Encoder encoder)
{
    BRST_STATUS ret;

    if (!encoder)
        return BRST_Error_Set(pdf->error, BRST_INVALID_OBJECT, 0);

    if (BRST_Doc_FindEncoder(pdf, encoder->name) != NULL) {
        BRST_Encoder_Free(encoder);
        return BRST_Error_Set(pdf->error, BRST_DUPLICATE_REGISTRATION, 0);
    }

    if ((ret = BRST_List_Add(pdf->encoder_list, encoder)) != BRST_OK) {
        BRST_Encoder_Free(encoder);
        return BRST_Error_Set(pdf->error, ret, 0);
    }

    return BRST_OK;
}

void FreeEncoderList(BRST_Doc pdf)
{
    BRST_List list = pdf->encoder_list;
    BRST_UINT i;

    BRST_PTRACE((" FreeEncoderList\n"));

    for (i = 0; i < BRST_List_Count(list); i++) {
        BRST_Encoder encoder = (BRST_Encoder)BRST_List_ItemAt(list, i);

        BRST_Encoder_Free(encoder);
    }

    BRST_List_Free(list);

    pdf->encoder_list = NULL;
}
