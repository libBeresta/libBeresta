#include "brst_mmgr.h"
#include "private/brst_object.h"
#include "private/brst_null.h"
#include "private/brst_utils.h"

typedef struct _BRST_Null_Rec {
    BRST_Obj_Header header;
} BRST_Null_Rec;

// typedef struct BRST_Obj_Header BRST_Obj_Header;

BRST_Null
BRST_Null_New(BRST_MMgr mmgr)
{
    BRST_Null obj = BRST_GetMem(mmgr, sizeof(BRST_Null_Rec));

    if (obj) {
        BRST_MemSet(&obj->header, 0, sizeof(BRST_Obj_Header));
        obj->header.obj_class = BRST_OCLASS_NULL;
    }

    return obj;
}
