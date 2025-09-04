#include "brst_mmgr.h"
#include "brst_stream.h"
#include "brst_encrypt.h"
#include "brst_encoder.h"
#include "brst_matrix.h"
#include "brst_array.h"
#include "brst_xref.h"
#include "brst_dict.h"
#include "private/brst_array.h"
#include "private/brst_object.h"
#include "private/brst_utils.h"
#include "private/brst_string.h"
#include "private/brst_binary.h"
#include "private/brst_direct.h"
#include "private/brst_dict.h"
#include "private/brst_object_write.h"

void BRST_Obj_Free(BRST_MMgr mmgr,
    void* obj)
{
    BRST_Obj_Header* header;

    BRST_PTRACE(" BRST_Obj_Free\n");

    if (!obj)
        return;

    header = (BRST_Obj_Header*)obj;

    if (!(header->obj_id & BRST_OTYPE_INDIRECT))
        BRST_Obj_ForceFree(mmgr, obj);
}

void BRST_Obj_ForceFree(BRST_MMgr mmgr,
    void* obj)
{
    BRST_Obj_Header* header;

    BRST_PTRACE(" BRST_Obj_ForceFree\n");

    if (!obj)
        return;

    header = (BRST_Obj_Header*)obj;

    BRST_PTRACE(" BRST_Obj_ForceFree obj=0x%p obj_id=0x%08X "
                 "obj_class=0x%08X\n",
        (void*)obj, (BRST_UINT)(header->obj_id),
        (BRST_UINT)(header->obj_class));

    switch (header->obj_class & BRST_OCLASS_ANY) {
    case BRST_OCLASS_STRING:
        BRST_String_Free(obj);
        break;
    case BRST_OCLASS_BINARY:
        BRST_Binary_Free(obj);
        break;
    case BRST_OCLASS_ARRAY:
        BRST_Array_Free(obj);
        break;
    case BRST_OCLASS_DICT:
        BRST_Dict_Free(obj);
        break;
    case BRST_OCLASS_DIRECT:
        BRST_Direct_Free(obj);
        break;
    default:
        BRST_FreeMem(mmgr, obj);
    }
}

BRST_UINT32
BRST_Obj_ID(void* obj)
{
    BRST_Obj_Header* header;

    BRST_PTRACE(" BRST_Obj_ID\n");

    if (!obj)
        return BRST_OTYPE_NONE;

    header = (BRST_Obj_Header*)obj;

    return header->obj_id;
}

void BRST_Obj_SetID(void* obj, BRST_UINT32 id)
{
    BRST_Obj_Header* header;

    BRST_PTRACE(" BRST_Obj_SetID\n");

    header = (BRST_Obj_Header*)obj;

    if (header)
        header->obj_id = id;
}

BRST_UINT16
BRST_Obj_Class(void* obj)
{
    BRST_Obj_Header* header;

    BRST_PTRACE(" BRST_Obj_Class\n");

    if (!obj)
        return BRST_OCLASS_UNKNOWN;

    header = (BRST_Obj_Header*)obj;

    return header->obj_class;
}

void BRST_Obj_SetClass(void* obj, BRST_UINT16 cls)
{
    BRST_Obj_Header* header;

    BRST_PTRACE(" BRST_Obj_SetClass\n");

    header = (BRST_Obj_Header*)obj;

    if (header)
        header->obj_class = cls;
}
