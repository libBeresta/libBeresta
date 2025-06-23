#include "brst_mmgr.h"
#include "brst_encrypt.h"
#include "brst_stream.h"
#include "private/brst_stream.h"
#include "private/brst_object.h"
#include "private/brst_direct.h"
#include "private/brst_utils.h"
#include "private/brst_defines.h"
#include "brst_consts.h"
#include "brst_error.h"

BRST_Direct
BRST_Direct_New(BRST_MMgr mmgr,
    BRST_BYTE* value,
    BRST_UINT len)
{
    BRST_Direct obj;

    obj = BRST_GetMem(mmgr, sizeof(BRST_Direct_Rec));

    if (obj) {
        BRST_MemSet(&obj->header, 0, sizeof(BRST_Obj_Header));
        obj->header.obj_class = BRST_OCLASS_DIRECT;

        obj->mmgr  = mmgr;
        obj->error = BRST_MMgr_Error(mmgr);
        obj->value = NULL;
        obj->len   = 0;
        if (BRST_Direct_SetValue(obj, value, len) != BRST_OK) {
            BRST_FreeMem(mmgr, obj);
            return NULL;
        }
    }

    return obj;
}

BRST_STATUS
BRST_Direct_Write(BRST_Direct obj,
    BRST_Stream stream)
{
    return BRST_Stream_Write(stream, obj->value, obj->len);
}

BRST_STATUS
BRST_Direct_SetValue(BRST_Direct obj,
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

    BRST_MemCpy(obj->value, value, len);
    obj->len = len;

    return BRST_OK;
}

void BRST_Direct_Free(BRST_Direct obj)
{
    if (!obj)
        return;

    if (obj->value)
        BRST_FreeMem(obj->mmgr, obj->value);

    BRST_FreeMem(obj->mmgr, obj);
}
