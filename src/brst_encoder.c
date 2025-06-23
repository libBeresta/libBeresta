#include "brst_external.h"
#include "brst_types.h"
#include "brst_mmgr.h"
#include "brst_encrypt.h"
#include "brst_stream.h"
#include "brst_encoder.h"
#include "brst_error.h"
#include "brst_consts.h"
#include "private/brst_utils.h"
#include "private/brst_encoder_basic.h"
#include "private/brst_encoder_cmap.h"
#include "brst_base.h"

BRST_EXPORT(BRST_UNICODE)
BRST_Encoder_Unicode(BRST_Encoder encoder,
    BRST_UINT16 code)
{
    BRST_PTRACE((" BRST_Encoder_Unicode\n"));

    if (!BRST_Encoder_Validate(encoder))
        return 0;

    return BRST_Encoder_ToUnicode(encoder, code);
}

BRST_EXPORT(BRST_ByteType)
BRST_Encoder_ByteType(BRST_Encoder encoder,
    const char* text,
    BRST_UINT index)
{
    BRST_ParseText_Rec parse_state;
    BRST_ByteType btype;

    BRST_PTRACE((" BRST_Encoder_ByteType\n"));

    if (!BRST_Encoder_Validate(encoder))
        return BRST_BYTE_TYPE_UNKNOWN;

    if (encoder->type != BRST_ENCODER_TYPE_DOUBLE_BYTE)
        return BRST_BYTE_TYPE_SINGLE;

    BRST_Encoder_SetParseText(encoder, &parse_state, (BRST_BYTE*)text, index + 1);

    for (;;) {
        btype = BRST_CMapEncoder_ByteType(encoder, &parse_state);

        if (index == 0)
            break;

        text++;
        if (!(*text))
            return BRST_BYTE_TYPE_UNKNOWN;
        index--;
    }

    return btype;
}

BRST_EXPORT(BRST_EncoderType)
BRST_Encoder_Type(BRST_Encoder encoder)
{
    BRST_PTRACE((" BRST_Encoder_Type\n"));

    if (!BRST_Encoder_Validate(encoder))
        return BRST_ENCODER_UNKNOWN;

    return encoder->type;
}

BRST_EXPORT(BRST_WritingMode)
BRST_Encoder_WritingMode(BRST_Encoder encoder)
{
    BRST_PTRACE((" BRST_Encoder_WritingMode\n"));

    if (!BRST_Encoder_Validate(encoder))
        return BRST_WMODE_HORIZONTAL;

    if (encoder->type == BRST_ENCODER_TYPE_DOUBLE_BYTE) {
        BRST_CMapEncoderAttr attr = (BRST_CMapEncoderAttr)encoder->attr;
        return attr->writing_mode;
    }

    return BRST_WMODE_HORIZONTAL;
}
