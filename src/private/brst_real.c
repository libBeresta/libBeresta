#include "brst_encrypt.h"
#include "brst_mmgr.h"
#include "brst_stream.h"
#include "private/brst_object.h"
#include "private/brst_real.h"
#include "private/brst_stream.h"
#include "brst_types.h"
#include "private/brst_utils.h"
#include "private/brst_defines.h"
#include "brst_consts.h"
#include "brst_error.h"

typedef struct _BRST_Real_Rec {
    BRST_Obj_Header header;
    BRST_Error error;
    BRST_REAL value;
} BRST_Real_Rec;

BRST_Real
BRST_Real_New(BRST_MMgr mmgr,
    BRST_REAL value)
{
    BRST_Real obj = BRST_GetMem(mmgr, sizeof(BRST_Real_Rec));

    if (obj) {
        BRST_MemSet(&obj->header, 0, sizeof(BRST_Obj_Header));
        obj->header.obj_class = BRST_OCLASS_REAL;
        obj->error            = BRST_MMgr_Error(mmgr);
        BRST_Real_SetValue(obj, value);
    }

    return obj;
}

BRST_STATUS
BRST_Real_Write(BRST_Real obj,
    BRST_Stream stream)
{
    return BRST_Stream_WriteReal(stream, obj->value);
}

BRST_STATUS
BRST_Real_SetValue(BRST_Real obj,
    BRST_REAL value)
{
    BRST_STATUS ret = BRST_OK;

    if (value > BRST_LIMIT_MAX_REAL)
        return BRST_Error_Set(obj->error, BRST_REAL_OUT_OF_RANGE, 0);

    if (value < BRST_LIMIT_MIN_REAL)
        return BRST_Error_Set(obj->error, BRST_REAL_OUT_OF_RANGE, 0);

    obj->value = value;

    return ret;
}

BRST_REAL
BRST_Real_Value(BRST_Real obj)
{
    return obj->value;
}