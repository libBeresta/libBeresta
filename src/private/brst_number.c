#include "brst_encrypt.h"
#include "brst_mmgr.h"
#include "brst_stream.h"
#include "private/brst_object.h"
#include "private/brst_number.h"
#include "private/brst_stream.h"
#include "brst_types.h"
#include "private/brst_utils.h"

typedef struct _BRST_Number_Rec {
    BRST_Obj_Header header;
    BRST_INT32 value;
} BRST_Number_Rec;

BRST_Number
BRST_Number_New(BRST_MMgr mmgr,
    BRST_INT32 value)
{
    BRST_Number obj = BRST_GetMem(mmgr, sizeof(BRST_Number_Rec));

    if (obj) {
        BRST_MemSet(&obj->header, 0, sizeof(BRST_Obj_Header));
        obj->header.obj_class = BRST_OCLASS_NUMBER;
        obj->value            = value;
    }

    return obj;
}

BRST_STATUS
BRST_Number_Write(BRST_Number obj,
    BRST_Stream stream)
{
    return BRST_Stream_WriteInt(stream, obj->value);
}

void BRST_Number_SetValue(BRST_Number obj,
    BRST_INT32 value)
{
    obj->value = value;
}

BRST_INT32
BRST_Number_Value(BRST_Number num)
{
    // TODO Переделать с ошибкой
    if (num)
        return num->value;
    return -1;
}
