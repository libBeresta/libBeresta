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
#include "private/brst_encoding_utf.h"
#include "brst_base.h"

typedef struct _UTF8_EncoderAttr_Rec* UTF8_EncoderAttr;
typedef struct _UTF8_EncoderAttr_Rec {
    BRST_BYTE current_byte;
    BRST_BYTE end_byte;
    BRST_BYTE utf8_bytes[8];
} UTF8_EncoderAttr_Rec;

static const BRST_CidRange_Rec UTF8_NOTDEF_RANGE = { 0x0000, 0x001F, 1 };
static const BRST_CidRange_Rec UTF8_SPACE_RANGE  = { 0x0000, 0xFFFF, 0 };
static const BRST_CidRange_Rec UTF8_CID_RANGE[]  = {
     { 0x0000, 0xFFFF, 0x0 },
     { 0xFFFF, 0xFFFF, 0x0 }
};

static BRST_ByteType
UTF8_Encoder_ByteType_Func(BRST_Encoder encoder,
    BRST_ParseText_Rec* state);

static BRST_UNICODE
UTF8_Encoder_ToUnicode_Func(BRST_Encoder encoder,
    BRST_UINT16 code);

static char*
UTF8_Encoder_EncodeText_Func(BRST_Encoder encoder,
    const char* text,
    BRST_UINT len,
    BRST_UINT* length);

/*--------------------------------------------------------------------------*/

/*
 * This function is taken from brst_encoder_utf8.c, originally submitted
 * to libharu by 'Mirco'
 */
static BRST_ByteType
UTF8_Encoder_ByteType_Func(BRST_Encoder encoder,
    BRST_ParseText_Rec* state)
{
    // This function is supposed to increment state->index
    // Not logical ! (look at function BRST_String_Write in brst_string.c)

    // When BRST_BYTE_TYPE_SINGLE is returned, the current byte is the
    //   CODE argument in call ToUnicodeFunc
    // When BRST_BYTE_TYPE_LEAD is returned, the current byte (msb) and the
    //   next byte (lsb) is the CODE argument in call ToUnicodeFunc
    // When BRST_BYTE_TYPE_TRAIL is returned, the current byte is ignored

    BRST_CMapEncoderAttr encoder_attr;
    BRST_BYTE byte;
    UTF8_EncoderAttr utf8_attr;

    encoder_attr = (BRST_CMapEncoderAttr)encoder->attr;
    utf8_attr    = (UTF8_EncoderAttr)((void*)encoder_attr->cid_map[0]);

    if (state->index == 0) {
        // First byte, initialize.
        BRST_PTRACE(" UTF8_Encoder_ByteType_Func - Initialize: (%u) %s\n",
            state->len, state->text);

        utf8_attr->current_byte = 0;
    }

    byte = state->text[state->index];
    state->index++;

    BRST_PTRACE(" UTF8_Encoder_ByteType_Func - Byte: %hx\n", byte);

    if (utf8_attr->current_byte == 0) {
        utf8_attr->utf8_bytes[0] = byte;
        utf8_attr->current_byte  = 1;

        if (!(byte & 0x80)) {
            utf8_attr->current_byte = 0;
            utf8_attr->end_byte     = 0;
            return BRST_BYTE_TYPE_SINGLE;
        }

        if ((byte & 0xf8) == 0xf0)
            utf8_attr->end_byte = 3;
        else if ((byte & 0xf0) == 0xe0)
            utf8_attr->end_byte = 2;
        else if ((byte & 0xe0) == 0xc0)
            utf8_attr->end_byte = 1;
        else
            utf8_attr->current_byte = 0; // ERROR, skip this byte
    } else {
        utf8_attr->utf8_bytes[utf8_attr->current_byte] = byte;
        if (utf8_attr->current_byte == utf8_attr->end_byte) {
            utf8_attr->current_byte = 0;
            return BRST_BYTE_TYPE_SINGLE;
        }

        utf8_attr->current_byte++;
    }

    return BRST_BYTE_TYPE_TRAIL;
}

/*
 * This function is taken from brst_encoder_utf8.c, originally submitted
 * to libharu by 'Mirco'
 */
static BRST_UNICODE
UTF8_Encoder_ToUnicode_Func(BRST_Encoder encoder,
    BRST_UINT16 code)
{
    // Supposed to convert CODE to unicode.
    // This function is always called after ByteType_Func.
    // ByteType_Func recognizes the utf-8 bytes belonging to one character.

    BRST_CMapEncoderAttr encoder_attr;
    UTF8_EncoderAttr utf8_attr;
    unsigned int val;

    encoder_attr = (BRST_CMapEncoderAttr)encoder->attr;
    utf8_attr    = (UTF8_EncoderAttr)((void*)encoder_attr->cid_map[0]);

    switch (utf8_attr->end_byte) {
    case 3:
        val = (unsigned int)((utf8_attr->utf8_bytes[0] & 0x7) << 18) + (unsigned int)((utf8_attr->utf8_bytes[1]) << 12) + (unsigned int)((utf8_attr->utf8_bytes[2] & 0x3f) << 6) + (unsigned int)((utf8_attr->utf8_bytes[3] & 0x3f));
        break;
    case 2:
        val = (unsigned int)((utf8_attr->utf8_bytes[0] & 0xf) << 12) + (unsigned int)((utf8_attr->utf8_bytes[1] & 0x3f) << 6) + (unsigned int)((utf8_attr->utf8_bytes[2] & 0x3f));
        break;
    case 1:
        val = (unsigned int)((utf8_attr->utf8_bytes[0] & 0x1f) << 6) + (unsigned int)((utf8_attr->utf8_bytes[1] & 0x3f));
        break;
    case 0:
        val = (unsigned int)utf8_attr->utf8_bytes[0];
        break;
    default:
        val = 32; // Unknown character
    }

    if (val > 65535) // Convert everything outside UCS-2 to space
        val = 32;

    return val;
}

static char*
UTF8_Encoder_EncodeText_Func(BRST_Encoder encoder,
    const char* text,
    BRST_UINT len,
    BRST_UINT* length)
{
    char* result = malloc(len * 2);
    char* c      = result;
    BRST_ParseText_Rec parse_state;
    BRST_UINT i;

    BRST_Encoder_SetParseText(encoder, &parse_state,
        (const BRST_BYTE*)text, len);

    for (i = 0; i < len; i++) {
        BRST_UNICODE tmp_unicode;
        BRST_ByteType btype = BRST_Encoder_ByteType_Internal(encoder, &parse_state);

        if (btype != BRST_BYTE_TYPE_TRAIL) {
            tmp_unicode = BRST_Encoder_ToUnicode(encoder, 0);

            BRST_UInt16Swap(&tmp_unicode);
            BRST_MemCopy((BRST_BYTE*)c, (const BRST_BYTE*)&tmp_unicode, 2);
            c += 2;
        }
    }

    *length = (BRST_UINT)(c - result);

    return result;
}

BRST_STATUS
UTF8_Init(BRST_Encoder encoder)
{
    BRST_CMapEncoderAttr attr;
    BRST_STATUS ret;

    if ((ret = BRST_CMapEncoder_InitAttr(encoder)) != BRST_OK)
        return ret;

    /*
     * We override these two
     */
    encoder->byte_type_fn   = UTF8_Encoder_ByteType_Func;
    encoder->to_unicode_fn  = UTF8_Encoder_ToUnicode_Func;
    encoder->encode_text_fn = UTF8_Encoder_EncodeText_Func;

    attr = (BRST_CMapEncoderAttr)encoder->attr;

    if (BRST_CMapEncoder_AddCMap(encoder, UTF8_CID_RANGE) != BRST_OK)
        return BRST_Error_Code(encoder->error);

    if (BRST_CMapEncoder_AddCodeSpaceRange(encoder, UTF8_SPACE_RANGE)
        != BRST_OK)
        return BRST_Error_Code(encoder->error);

    if (BRST_CMapEncoder_AddNotDefRange(encoder, UTF8_NOTDEF_RANGE)
        != BRST_OK)
        return BRST_Error_Code(encoder->error);

    attr->is_lead_byte_fn  = NULL;
    attr->is_trial_byte_fn = NULL;

    BRST_StrCopy(attr->registry, "Adobe", attr->registry + BRST_LIMIT_MAX_NAME_LEN);
    BRST_StrCopy(attr->ordering, "Identity-H", attr->ordering + BRST_LIMIT_MAX_NAME_LEN);
    attr->supplement   = 0;
    attr->writing_mode = BRST_WMODE_HORIZONTAL;

    /* Not sure about this
    attr->uid_offset = 0;
    attr->xuid[0] = 0;
    attr->xuid[1] = 0;
    attr->xuid[2] = 0;
    */

    encoder->type = BRST_ENCODER_TYPE_DOUBLE_BYTE;

    return BRST_OK;
}
