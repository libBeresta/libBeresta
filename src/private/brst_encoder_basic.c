#include "brst_types.h"
#include "brst_mmgr.h"
#include "brst_stream.h"
#include "brst_encoder.h"
#include "brst_consts.h"
#include "brst_error.h"
#include "brst_encrypt.h"
#include "private/brst_encoder_basic.h"
#include "brst_unicode_glyph.h"
#include "private/brst_defines.h"
#include "private/brst_utils.h"

#define BRST_BASIC_ENCODER_FIRST_CHAR 32
#define BRST_BASIC_ENCODER_LAST_CHAR 255

#include "../src/private/data/encoding.data"

// TODO Нужны предварительные объявления?
const BRST_BuiltinEncodingData*
BRST_BasicEncoder_FindBuiltinData(const char* encoding_name);

void BRST_BasicEncoder_CopyMap(BRST_Encoder encoder,
    const BRST_UNICODE* map);

BRST_STATUS
BRST_BasicEncoder_OverrideMap(BRST_Encoder encoder,
    const BRST_UNICODE* map);

BRST_Encoder
BRST_BasicEncoder_New(BRST_MMgr mmgr,
    const char* encoding_name)
{
    BRST_Encoder encoder;
    BRST_BasicEncoderAttr encoder_attr;
    const BRST_BuiltinEncodingData* data;
    char* eptr;

    BRST_PTRACE(" BRST_BasicEncoder_New\n");

    if (mmgr == NULL)
        return NULL;

    data = BRST_BasicEncoder_FindBuiltinData(encoding_name);
    if (!data->encoding_name) {
        BRST_Error_Set(BRST_MMgr_Error(mmgr), BRST_INVALID_ENCODING_NAME, 0);
        return NULL;
    }

    encoder = BRST_GetMem(mmgr, sizeof(BRST_Encoder_Rec));
    if (!encoder)
        return NULL;

    BRST_MemSet(encoder, 0, sizeof(BRST_Encoder_Rec));

    eptr = encoder->name + BRST_LIMIT_MAX_NAME_LEN;
    BRST_StrCopy(encoder->name, data->encoding_name, eptr);

    encoder->mmgr           = mmgr;
    encoder->error          = BRST_MMgr_Error(mmgr);
    encoder->type           = BRST_ENCODER_TYPE_SINGLE_BYTE;
    encoder->to_unicode_fn  = BRST_BasicEncoder_ToUnicode;
    encoder->encode_text_fn = NULL;
    encoder->write_fn       = BRST_BasicEncoder_Write;
    encoder->free_fn        = BRST_BasicEncoder_Free;

    encoder_attr = BRST_GetMem(mmgr, sizeof(BRST_BasicEncoderAttr_Rec));
    if (!encoder_attr) {
        BRST_FreeMem(encoder->mmgr, encoder);
        return NULL;
    }

    encoder->sig_bytes = BRST_ENCODER_SIG_BYTES;
    encoder->attr      = encoder_attr;
    BRST_MemSet(encoder_attr, 0, sizeof(BRST_BasicEncoderAttr_Rec));

    encoder_attr->first_char      = BRST_BASIC_ENCODER_FIRST_CHAR;
    encoder_attr->last_char       = BRST_BASIC_ENCODER_LAST_CHAR;
    encoder_attr->has_differences = BRST_FALSE;

    eptr = encoder_attr->base_encoding + BRST_LIMIT_MAX_NAME_LEN;

    switch (data->base_encoding) {
    case BRST_BASE_ENCODING_STANDARD:
        BRST_StrCopy(encoder_attr->base_encoding,
            BRST_ENCODING_STANDARD, eptr);
        BRST_BasicEncoder_CopyMap(encoder, BRST_UNICODE_MAP_STANDARD);
        break;
    case BRST_BASE_ENCODING_WIN_ANSI:
        BRST_StrCopy(encoder_attr->base_encoding,
            BRST_ENCODING_WIN_ANSI, eptr);
        BRST_BasicEncoder_CopyMap(encoder, BRST_UNICODE_MAP_WIN_ANSI);
        break;
    case BRST_BASE_ENCODING_MAC_ROMAN:
        BRST_StrCopy(encoder_attr->base_encoding,
            BRST_ENCODING_MAC_ROMAN, eptr);
        BRST_BasicEncoder_CopyMap(encoder, BRST_UNICODE_MAP_MAC_ROMAN);
        break;
    default:
        BRST_StrCopy(encoder_attr->base_encoding,
            BRST_ENCODING_FONT_SPECIFIC, eptr);
        BRST_BasicEncoder_CopyMap(encoder,
            BRST_UNICODE_MAP_FONT_SPECIFIC);
    }

    if (data->ovewrride_map)
        BRST_BasicEncoder_OverrideMap(encoder, data->ovewrride_map);

    return encoder;
}

BRST_UNICODE
BRST_BasicEncoder_ToUnicode(BRST_Encoder encoder,
    BRST_UINT16 code)
{
    BRST_BasicEncoderAttr attr = (BRST_BasicEncoderAttr)encoder->attr;

    if (code > 255)
        return 0;

    return attr->unicode_map[code];
}

void BRST_BasicEncoder_Free(BRST_Encoder encoder)
{
    BRST_PTRACE(" BRST_BasicEncoder_Free\n");

    BRST_FreeMem(encoder->mmgr, encoder->attr);
    encoder->attr = NULL;
}

BRST_STATUS
BRST_BasicEncoder_Write(BRST_Encoder encoder,
    BRST_Stream out)
{
    BRST_STATUS ret;
    BRST_BasicEncoderAttr attr = (BRST_BasicEncoderAttr)encoder->attr;

    BRST_PTRACE(" BRST_BasicEncoder_Write\n");

    /*  if BRST_ENCODING_FONT_SPECIFIC is selected, no Encoding object will be "
     *  written.
     */
    if (BRST_StrCmp(attr->base_encoding, BRST_ENCODING_FONT_SPECIFIC) == 0)
        return BRST_OK;

    /* if encoder has differences-data, encoding object is written as
       dictionary-object, otherwise it is written as name-object. */
    if (attr->has_differences == BRST_TRUE) {
        ret = BRST_Stream_WriteStr(out,
            "/Encoding <<\012"
            "/Type /Encoding\012"
            "/BaseEncoding ");
        if (ret != BRST_OK)
            return ret;
    } else {
        ret = BRST_Stream_WriteStr(out, "/Encoding ");
        if (ret != BRST_OK)
            return ret;
    }

    ret = BRST_Stream_WriteEscapeName(out, attr->base_encoding);
    if (ret != BRST_OK)
        return ret;

    ret = BRST_Stream_WriteStr(out, "\012");
    if (ret != BRST_OK)
        return ret;

    /* write differences data */
    if (attr->has_differences == BRST_TRUE) {
        BRST_INT i;

        ret = BRST_Stream_WriteStr(out, "/Differences [");
        if (ret != BRST_OK)
            return ret;

        for (i = attr->first_char; i <= attr->last_char; i++) {
            if (attr->differences[i] == 1) {
                char tmp[BRST_TEXT_DEFAULT_LEN];
                char* ptmp            = tmp;
                const char* char_name = BRST_UnicodeToGlyphName(attr->unicode_map[i]);

                ptmp    = BRST_IToA(ptmp, i, tmp + BRST_TEXT_DEFAULT_LEN - 1);
                *ptmp++ = ' ';
                *ptmp++ = '/';
                ptmp    = (char*)BRST_StrCopy(ptmp, char_name, tmp + BRST_TEXT_DEFAULT_LEN - 1);
                *ptmp++ = ' ';
                *ptmp   = 0;

                ret = BRST_Stream_WriteStr(out, tmp);
                if (ret != BRST_OK)
                    return ret;
            }
        }

        ret = BRST_Stream_WriteStr(out, "]\012>>\012");
    }

    return ret;
}

const BRST_BuiltinEncodingData*
BRST_BasicEncoder_FindBuiltinData(const char* encoding_name)
{
    BRST_UINT i = 0;

    BRST_PTRACE(" BRST_BasicEncoder_FindBuiltinData\n");

    while (BRST_BUILTIN_ENCODINGS[i].encoding_name) {
        if (BRST_StrCmp(BRST_BUILTIN_ENCODINGS[i].encoding_name,
                encoding_name)
            == 0)
            break;

        i++;
    }

    return &BRST_BUILTIN_ENCODINGS[i];
}

void BRST_BasicEncoder_CopyMap(BRST_Encoder encoder,
    const BRST_UNICODE* map)
{
    BRST_UINT i;
    BRST_UNICODE* dst = ((BRST_BasicEncoderAttr)encoder->attr)->unicode_map + BRST_BASIC_ENCODER_FIRST_CHAR;

    BRST_PTRACE(" BRST_BasicEncoder_CopyMap\n");

    for (i = 0; i <= BRST_BASIC_ENCODER_LAST_CHAR - BRST_BASIC_ENCODER_FIRST_CHAR; i++)
        *dst++ = *map++;
}

BRST_STATUS
BRST_BasicEncoder_OverrideMap(BRST_Encoder encoder,
    const BRST_UNICODE* map)
{
    BRST_UINT i;
    BRST_BasicEncoderAttr data = (BRST_BasicEncoderAttr)encoder->attr;
    BRST_UNICODE* dst;
    BRST_BYTE* flgs;

    BRST_PTRACE(" BRST_BasicEncoder_OverrideMap\n");

    if (data->has_differences)
        return BRST_Error_Set(encoder->error, BRST_INVALID_OPERATION, 0);

    dst  = data->unicode_map + BRST_BASIC_ENCODER_FIRST_CHAR;
    flgs = data->differences + BRST_BASIC_ENCODER_FIRST_CHAR;

    for (i = 0; i <= BRST_BASIC_ENCODER_LAST_CHAR - BRST_BASIC_ENCODER_FIRST_CHAR; i++) {
        if (*map != *dst) {
            *dst  = *map;
            *flgs = 1;
        }
        map++;
        dst++;
        flgs++;
    }
    data->has_differences = BRST_TRUE;

    return BRST_OK;
}
