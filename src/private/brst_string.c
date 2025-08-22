#include "brst_mmgr.h"
#include "brst_stream.h"
#include "brst_encrypt.h"
#include "brst_encoder.h"
#include "private/brst_object.h"
#include "private/brst_string.h"
#include "private/brst_stream.h"
#include "brst_types.h"
#include "private/brst_utils.h"
#include "private/brst_defines.h"
#include "brst_consts.h"
#include "brst_error.h"

#include <string.h>

static const BRST_BYTE UNICODE_HEADER[] = {
    0xFE, 0xFF
};

typedef struct _BRST_String_Rec {
    BRST_Obj_Header header;
    BRST_MMgr mmgr;
    BRST_Error error;
    BRST_Encoder encoder;
    BRST_BYTE* value;
    BRST_UINT len;
} BRST_String_Rec;

const char*
BRST_String_Value(BRST_String string)
{
    if (!string)
        return NULL;
    return (const char*)(string->value);
}

BRST_String
BRST_String_New(BRST_MMgr mmgr,
    const char* value,
    BRST_Encoder encoder)
{
    BRST_String obj;

    BRST_PTRACE(" BRST_String_New\n");

    obj = (BRST_String)BRST_GetMem(mmgr, sizeof(BRST_String_Rec));
    if (obj) {
        BRST_MemSet(&obj->header, 0, sizeof(BRST_Obj_Header));
        obj->header.obj_class = BRST_OCLASS_STRING;

        obj->mmgr    = mmgr;
        obj->error   = BRST_MMgr_Error(mmgr);
        obj->encoder = encoder;
        obj->value   = NULL;
        obj->len     = 0;

        if (BRST_String_SetValue(obj, value) != BRST_OK) {
            BRST_FreeMem(obj->mmgr, obj);
            return NULL;
        }
    }

    return obj;
}

BRST_STATUS
BRST_String_SetValue(BRST_String obj,
    const char* value)
{
    BRST_UINT len;
    BRST_STATUS ret = BRST_OK;

    BRST_PTRACE(" BRST_String_SetValue\n");

    if (obj->value) {
        BRST_FreeMem(obj->mmgr, obj->value);
        obj->len = 0;
    }

    len = BRST_StrLen(value, BRST_LIMIT_MAX_STRING_LEN + 1);

    if (len > BRST_LIMIT_MAX_STRING_LEN)
        return BRST_Error_Set(obj->error, BRST_STRING_OUT_OF_RANGE, 0);

    obj->value = BRST_GetMem(obj->mmgr, len + 1);
    if (!obj->value)
        return BRST_Error_Code(obj->error);

    BRST_StrCpy((char*)obj->value, value, (char*)obj->value + len);
    obj->len = len;

    return ret;
}

void BRST_String_Free(BRST_String obj)
{
    if (!obj)
        return;

    BRST_PTRACE(" BRST_String_Free\n");

    BRST_FreeMem(obj->mmgr, obj->value);
    BRST_FreeMem(obj->mmgr, obj);
}

BRST_INT32
BRST_String_Cmp(BRST_String s1,
    BRST_String s2)
{
    BRST_INT32 res;
    BRST_UINT minLen;

    minLen = s1->len;
    if (s1->len > s2->len) {
        minLen = s2->len;
    }

    res = memcmp(s1->value, s2->value, minLen);
    if (res == 0) {
        if (s1->len < s2->len)
            res = -1;
        if (s1->len > s2->len)
            res = +1;
    }

    return res;
}

BRST_STATUS
BRST_String_Write(BRST_String obj,
    BRST_Stream stream,
    BRST_Encrypt e)
{
    BRST_STATUS ret;

    /*
     *  When encoder is not NULL, text is changed to unicode using encoder,
     *  and it outputs by BRST_write_binary method.
     */

    BRST_PTRACE(" BRST_String_Write\n");

    if (e)
        BRST_Encrypt_Reset(e);

    if (obj->encoder == NULL) {
        if (e) {
            if ((ret = BRST_Stream_WriteChar(stream, '<')) != BRST_OK)
                return ret;

            if ((ret = BRST_Stream_WriteBinary(stream, obj->value,
                     BRST_StrLen((char*)obj->value, -1), e))
                != BRST_OK)
                return ret;

            return BRST_Stream_WriteChar(stream, '>');
        } else {
            return BRST_Stream_WriteEscapeText(stream, (char*)obj->value);
        }
    } else {
        BRST_BYTE* src = obj->value;
        BRST_BYTE buf[BRST_TEXT_DEFAULT_LEN * 2];
        BRST_UINT tmp_len = 0;
        BRST_BYTE* pbuf   = buf;
        BRST_INT32 len    = obj->len;
        BRST_ParseText_Rec parse_state;
        BRST_UINT i;

        if ((ret = BRST_Stream_WriteChar(stream, '<')) != BRST_OK)
            return ret;

        if ((ret = BRST_Stream_WriteBinary(stream, UNICODE_HEADER, 2, e))
            != BRST_OK)
            return ret;

        BRST_Encoder_SetParseText(obj->encoder, &parse_state, src, len);

        for (i = 0; (BRST_INT32)i < len; i++) {
            BRST_BYTE b = src[i];
            BRST_UNICODE tmp_unicode;
            BRST_ByteType btype = BRST_Encoder_ByteType_Internal(obj->encoder,
                &parse_state);

            if (tmp_len >= BRST_TEXT_DEFAULT_LEN - 1) {
                if ((ret = BRST_Stream_WriteBinary(stream, buf,
                         tmp_len * 2, e))
                    != BRST_OK)
                    return ret;

                tmp_len = 0;
                pbuf    = buf;
            }

            if (btype != BRST_BYTE_TYPE_TRAIL) {
                if (btype == BRST_BYTE_TYPE_LEAD) {
                    BRST_BYTE b2          = src[i + 1];
                    BRST_UINT16 char_code = (BRST_UINT16)((BRST_UINT)b * 256 + b2);

                    tmp_unicode = BRST_Encoder_ToUnicode(obj->encoder,
                        char_code);
                } else {
                    tmp_unicode = BRST_Encoder_ToUnicode(obj->encoder, b);
                }

                BRST_UInt16Swap(&tmp_unicode);
                BRST_MemCpy(pbuf, (BRST_BYTE*)&tmp_unicode, 2);
                pbuf += 2;
                tmp_len++;
            }
        }

        if (tmp_len > 0) {
            if ((ret = BRST_Stream_WriteBinary(stream, buf, tmp_len * 2, e))
                != BRST_OK)
                return ret;
        }

        if ((ret = BRST_Stream_WriteChar(stream, '>')) != BRST_OK)
            return ret;
    }

    return BRST_OK;
}
