#include "brst_mmgr.h"
#include "brst_types.h"
#include "brst_stream.h"
#include "brst_encrypt.h"
#include "private/brst_stream.h"
#include "private/brst_object.h"
#include "private/brst_boolean.h"
#include "private/brst_utils.h"
#include "brst_consts.h"

typedef struct _BRST_Boolean_Rec {
    BRST_Obj_Header header;
    BRST_BOOL value;
} BRST_Boolean_Rec;

BRST_Boolean
BRST_Boolean_New(BRST_MMgr mmgr,
    BRST_BOOL value)
{
    BRST_Boolean obj = BRST_GetMem(mmgr, sizeof(BRST_Boolean_Rec));

    if (obj) {
        BRST_MemSet(&obj->header, 0, sizeof(BRST_Obj_Header));
        obj->header.obj_class = BRST_OCLASS_BOOLEAN;
        obj->value            = value;
    }

    return obj;
}

BRST_STATUS
BRST_Boolean_Write(BRST_Boolean obj,
    BRST_Stream stream)
{
    BRST_STATUS ret;

    if (obj->value)
        ret = BRST_Stream_WriteStr(stream, "true");
    else
        ret = BRST_Stream_WriteStr(stream, "false");

    return ret;
}

void BRST_Boolean_SetValue(BRST_Boolean obj,
    BRST_BOOL value)
{
    if (obj)
        obj->value = value;
}

// TODO переделать с ошибкой
BRST_BOOL
BRST_Boolean_Value(BRST_Boolean obj)
{
    if (obj)
        return obj->value;
    return BRST_FALSE;
}