#include "brst_types.h"
#include "brst_mmgr.h"
#include "brst_stream.h"
#include "brst_encrypt.h"
#include "brst_encoder.h"
#include "brst_consts.h"
#include "brst_error.h"
#include "private/brst_utils.h"
#include "private/brst_encoder.h"

BRST_UNICODE
BRST_Encoder_ToUnicode(BRST_Encoder encoder,
    BRST_UINT16 code)
{
    return encoder->to_unicode_fn(encoder, code);
}

void BRST_Encoder_Free(BRST_Encoder encoder)
{
    BRST_PTRACE((" BRST_Encoder_Free\n"));

    if (!encoder)
        return;

    if (encoder->free_fn)
        encoder->free_fn(encoder);
    BRST_FreeMem(encoder->mmgr, encoder);
}

BRST_STATUS
BRST_Encoder_Validate(BRST_Encoder encoder)
{
    BRST_PTRACE((" BRST_Encoder_Validate\n"));

    if (!encoder || encoder->sig_bytes != BRST_ENCODER_SIG_BYTES)
        return BRST_FALSE;
    else
        return BRST_TRUE;
}

void BRST_Encoder_SetParseText(BRST_Encoder encoder,
    BRST_ParseText_Rec* state,
    const BRST_BYTE* text,
    BRST_UINT len)
{
    BRST_PTRACE((" BRST_CMapEncoder_SetParseText\n"));
    BRST_UNUSED(encoder);

    state->text      = text;
    state->index     = 0;
    state->len       = len;
    state->byte_type = BRST_BYTE_TYPE_SINGLE;
}

BRST_ByteType
BRST_Encoder_ByteType_Internal(BRST_Encoder encoder,
    BRST_ParseText_Rec* state)
{
    BRST_PTRACE((" BRST_Encoder_ByteType\n"));

    if (encoder->byte_type_fn)
        return encoder->byte_type_fn(encoder, state);
    else
        return BRST_BYTE_TYPE_SINGLE;
}
