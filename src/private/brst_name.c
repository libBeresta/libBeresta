#include "brst_mmgr.h"
#include "brst_stream.h"
#include "brst_encrypt.h"
#include "private/brst_name.h"
#include "private/brst_utils.h"
#include "private/brst_object.h"
#include "brst_error.h"
#include "brst_consts.h"
#include "private/brst_defines.h"

typedef struct _BRST_Name_Rec {
    BRST_Obj_Header header;
    BRST_Error error;
    char value[BRST_LIMIT_MAX_NAME_LEN + 1];
} BRST_Name_Rec;

BRST_Name
BRST_Name_New(BRST_MMgr mmgr,
    const char* value)
{
    BRST_Name obj;

    obj = BRST_GetMem(mmgr, sizeof(BRST_Name_Rec));

    if (obj) {
        BRST_MemSet(&obj->header, 0, sizeof(BRST_Obj_Header));
        obj->header.obj_class = BRST_OCLASS_NAME;
        obj->error            = BRST_MMgr_Error(mmgr);
        if (BRST_Name_SetValue(obj, value) == BRST_NAME_INVALID_VALUE) {
            BRST_FreeMem(mmgr, obj);
            return NULL;
        }
    }

    return obj;
}

BRST_STATUS
BRST_Name_Write(BRST_Name obj,
    BRST_Stream stream)
{
    return BRST_Stream_WriteEscapeName(stream, obj->value);
}

BRST_STATUS
BRST_Name_SetValue(BRST_Name obj,
    const char* value)
{
    if (!value || value[0] == 0)
        return BRST_Error_Set(obj->error, BRST_NAME_INVALID_VALUE, 0);

    if (BRST_StrLen(value, BRST_LIMIT_MAX_NAME_LEN + 1) > BRST_LIMIT_MAX_NAME_LEN)
        return BRST_Error_Set(obj->error, BRST_NAME_OUT_OF_RANGE, 0);

    BRST_StrCopy(obj->value, value, obj->value + BRST_LIMIT_MAX_NAME_LEN);

    return BRST_OK;
}

const char*
BRST_Name_Value(BRST_Name obj)
{
    return (const char*)obj->value;
}
