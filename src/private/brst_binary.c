#include "brst_mmgr.h"
#include "brst_stream.h"
#include "brst_encrypt.h"
#include "brst_consts.h"
#include "private/brst_object.h"
#include "private/brst_binary.h"
#include "private/brst_stream.h"
#include "brst_types.h"
#include "private/brst_utils.h"
#include "private/brst_defines.h"
#include "brst_error.h"

typedef struct _BRST_Binary_Rec {
    BRST_Obj_Header header;
    BRST_MMgr mmgr;
    BRST_Error error;
    BRST_BYTE* value;
    BRST_UINT len;
} BRST_Binary_Rec;

BRST_Binary
BRST_Binary_New(BRST_MMgr mmgr,
    BRST_BYTE* value,
    BRST_UINT len)
{
    BRST_Binary obj;

    obj = BRST_GetMem(mmgr, sizeof(BRST_Binary_Rec));

    if (obj) {
        BRST_MemSet(&obj->header, 0, sizeof(BRST_Obj_Header));
        obj->header.obj_class = BRST_OCLASS_BINARY;

        obj->mmgr  = mmgr;
        obj->error = BRST_MMgr_Error(mmgr);
        obj->value = NULL;
        obj->len   = 0;
        if (BRST_Binary_SetValue(obj, value, len) != BRST_OK) {
            BRST_FreeMem(mmgr, obj);
            return NULL;
        }
    }

    return obj;
}

BRST_STATUS
BRST_Binary_Write(BRST_Binary obj,
    BRST_Stream stream,
    BRST_Encrypt e)
{
    BRST_STATUS ret;

    if (obj->len == 0)
        return BRST_Stream_WriteStr(stream, "<>");

    if ((ret = BRST_Stream_WriteChar(stream, '<')) != BRST_OK)
        return ret;

    if (e)
        BRST_Encrypt_Reset(e);

    if ((ret = BRST_Stream_WriteBinary(stream, obj->value, obj->len, e)) != BRST_OK)
        return ret;

    return BRST_Stream_WriteChar(stream, '>');
}

BRST_STATUS
BRST_Binary_SetValue(BRST_Binary obj,
    BRST_BYTE* value,
    BRST_UINT len)
{
    if (len > BRST_LIMIT_MAX_STRING_LEN)
        return BRST_Error_Set(obj->error, BRST_BINARY_LENGTH_ERR, 0);

    if (obj->value) {
        BRST_FreeMem(obj->mmgr, obj->value);
        obj->len = 0;
    }

    obj->value = BRST_GetMem(obj->mmgr, len);
    if (!obj->value)
        return BRST_Error_Code(obj->error);

    BRST_MemCopy(obj->value, value, len);
    obj->len = len;

    return BRST_OK;
}

void BRST_Binary_Free(BRST_Binary obj)
{
    if (!obj)
        return;

    if (obj->value)
        BRST_FreeMem(obj->mmgr, obj->value);

    BRST_FreeMem(obj->mmgr, obj);
}

BRST_UINT
BRST_Binary_Len(BRST_Binary obj)
{
    return obj->len;
}

BRST_BYTE*
BRST_Binary_Value(BRST_Binary obj)
{
    return obj->value;
}
