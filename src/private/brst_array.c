
#include "brst_error.h"
#include "brst_mmgr.h"
#include "private/brst_list.h"
#include "brst_encrypt.h"
#include "private/brst_encrypt.h"
#include "brst_stream.h"
#include "brst_matrix.h"
#include "brst_array.h"
#include "private/brst_array.h"
#include "private/brst_object_write.h"
#include "brst_consts.h"
#include "private/brst_object.h"
#include "private/brst_defines.h"
#include "private/brst_proxy.h"
#include "private/brst_null.h"
#include "private/brst_name.h"
#include "private/brst_real.h"
#include "private/brst_number.h"
#include "private/brst_utils.h"

BRST_Array
BRST_Array_New(BRST_MMgr mmgr)
{
    BRST_Array obj;

    BRST_PTRACE(" BRST_Array_New\n");

    obj = BRST_GetMem(mmgr, sizeof(BRST_Array_Rec));
    if (obj) {
        BRST_MemSet(obj, 0, sizeof(BRST_Array_Rec));
        obj->header.obj_class = BRST_OCLASS_ARRAY;
        obj->mmgr             = mmgr;
        obj->error            = BRST_MMgr_Error(mmgr);
        obj->list             = BRST_List_New(mmgr, BRST_DEF_ITEMS_PER_BLOCK);
        if (!obj->list) {
            BRST_FreeMem(mmgr, obj);
            obj = NULL;
        }
    }

    return obj;
}

BRST_Array
BRST_Box_Array_New(BRST_MMgr mmgr,
    BRST_Box box)
{
    BRST_Array obj;
    BRST_STATUS ret = BRST_OK;

    BRST_PTRACE(" BRST_Box_Array_New\n");

    obj = BRST_Array_New(mmgr);
    if (!obj)
        return NULL;

    ret += BRST_Array_Add(obj, BRST_Real_New(mmgr, box.left));
    ret += BRST_Array_Add(obj, BRST_Real_New(mmgr, box.bottom));
    ret += BRST_Array_Add(obj, BRST_Real_New(mmgr, box.right));
    ret += BRST_Array_Add(obj, BRST_Real_New(mmgr, box.top));

    if (ret != BRST_OK) {
        BRST_Array_Free(obj);
        return NULL;
    }

    return obj;
}

BRST_Array
BRST_Matrix_Array_New(BRST_MMgr mmgr,
    BRST_Matrix matrix)
{
    BRST_Array obj;
    BRST_STATUS ret = BRST_OK;

    BRST_PTRACE(" BRST_Matrix_Array_New\n");

    obj = BRST_Array_New(mmgr);
    if (!obj)
        return NULL;

    ret += BRST_Array_Add(obj, BRST_Real_New(mmgr, matrix->a));
    ret += BRST_Array_Add(obj, BRST_Real_New(mmgr, matrix->b));
    ret += BRST_Array_Add(obj, BRST_Real_New(mmgr, matrix->c));
    ret += BRST_Array_Add(obj, BRST_Real_New(mmgr, matrix->d));
    ret += BRST_Array_Add(obj, BRST_Real_New(mmgr, matrix->x));
    ret += BRST_Array_Add(obj, BRST_Real_New(mmgr, matrix->y));

    if (ret != BRST_OK) {
        BRST_Array_Free(obj);
        return NULL;
    }

    return obj;
}


void BRST_Array_Free(BRST_Array array)
{
    if (!array)
        return;

    BRST_PTRACE(" BRST_Array_Free\n");

    BRST_Array_Clear(array);

    BRST_List_Free(array->list);

    array->header.obj_class = 0;

    BRST_FreeMem(array->mmgr, array);
}

BRST_STATUS
BRST_Array_Write(BRST_Array array,
    BRST_Stream stream,
    BRST_Encrypt e)
{
    BRST_UINT i;
    BRST_STATUS ret;

    BRST_PTRACE(" BRST_Array_Write\n");

    ret = BRST_Stream_WriteStr(stream, "[ ");
    if (ret != BRST_OK)
        return ret;

    for (i = 0; i < BRST_List_Count(array->list); i++) {
        void* element = BRST_List_ItemAt(array->list, i);

        ret = BRST_Obj_Write(element, stream, e);
        if (ret != BRST_OK)
            return ret;

        ret = BRST_Stream_WriteChar(stream, ' ');
        if (ret != BRST_OK)
            return ret;
    }

    ret = BRST_Stream_WriteChar(stream, ']');

    return ret;
}

BRST_STATUS
BRST_Array_AddNumber(BRST_Array array,
    BRST_INT32 value)
{
    BRST_Number n = BRST_Number_New(array->mmgr, value);

    BRST_PTRACE(" BRST_Array_AddNumber\n");

    if (!n)
        return BRST_Error_Code(array->error);
    else
        return BRST_Array_Add(array, n);
}

BRST_STATUS
BRST_Array_AddReal(BRST_Array array,
    BRST_REAL value)
{
    BRST_Real r = BRST_Real_New(array->mmgr, value);

    BRST_PTRACE(" BRST_Array_AddReal\n");

    if (!r)
        return BRST_Error_Code(array->error);
    else
        return BRST_Array_Add(array, r);
}

BRST_STATUS
BRST_Array_AddNull(BRST_Array array)
{
    BRST_Null n = BRST_Null_New(array->mmgr);

    BRST_PTRACE(" BRST_Array_AddNull\n");

    if (!n)
        return BRST_Error_Code(array->error);
    else
        return BRST_Array_Add(array, n);
}

BRST_STATUS
BRST_Array_AddName(BRST_Array array,
    const char* value)
{
    BRST_Name n = BRST_Name_New(array->mmgr, value);

    BRST_PTRACE(" BRST_Array_AddName\n");

    if (!n)
        return BRST_Error_Code(array->error);
    else
        return BRST_Array_Add(array, n);
}

BRST_STATUS
BRST_Array_Add(BRST_Array array,
    void* obj)
{
    BRST_Obj_Header* header;
    BRST_STATUS ret;

    BRST_PTRACE(" BRST_Array_Add\n");

    if (!obj) {
        if (BRST_Error_Code(array->error) == BRST_OK)
            return BRST_Error_Set(array->error, BRST_INVALID_OBJECT, 0);
        else
            return BRST_INVALID_OBJECT;
    }

    header = (BRST_Obj_Header*)obj;

    if (header->obj_id & BRST_OTYPE_DIRECT)
        return BRST_Error_Set(array->error, BRST_INVALID_OBJECT, 0);

    if (BRST_List_Count(array->list) >= BRST_LIMIT_MAX_ARRAY) {
        BRST_PTRACE(" BRST_Array_Add exceed limitatin of array count(%d)\n",
            BRST_LIMIT_MAX_ARRAY);

        BRST_Obj_Free(array->mmgr, obj);
        return BRST_Error_Set(array->error, BRST_ARRAY_COUNT_ERR, 0);
    }

    if (header->obj_id & BRST_OTYPE_INDIRECT) {
        BRST_Proxy proxy = BRST_Proxy_New(array->mmgr, obj);

        if (!proxy) {
            BRST_Obj_Free(array->mmgr, obj);
            return BRST_Error_Code(array->error);
        }

        proxy->header.obj_id |= BRST_OTYPE_DIRECT;
        obj = proxy;
    } else
        header->obj_id |= BRST_OTYPE_DIRECT;

    ret = BRST_List_Add(array->list, obj);
    if (ret != BRST_OK)
        BRST_Obj_Free(array->mmgr, obj);

    return ret;
}

BRST_UINT
BRST_Array_Count(BRST_Array array)
{
    return BRST_List_Count(array->list);
}

BRST_STATUS
BRST_Array_Insert(BRST_Array array,
    void* target,
    void* obj)
{
    BRST_Obj_Header* header;
    BRST_STATUS ret;
    BRST_UINT i;

    BRST_PTRACE(" BRST_Array_Insert\n");

    if (!obj) {
        if (BRST_Error_Code(array->error) == BRST_OK)
            return BRST_Error_Set(array->error, BRST_INVALID_OBJECT, 0);
        else
            return BRST_INVALID_OBJECT;
    }

    header = (BRST_Obj_Header*)obj;

    if (header->obj_id & BRST_OTYPE_DIRECT) {
        BRST_PTRACE(" BRST_Array_Add this object cannot be owned by array "
                     "obj=0x%p\n", (void*)array);

        return BRST_Error_Set(array->error, BRST_INVALID_OBJECT, 0);
    }

    if (BRST_List_Count(array->list) >= BRST_LIMIT_MAX_ARRAY) {
        BRST_PTRACE(" BRST_Array_Add exceed limitatin of array count(%d)\n",
            BRST_LIMIT_MAX_ARRAY);

        BRST_Obj_Free(array->mmgr, obj);

        return BRST_Error_Set(array->error, BRST_ARRAY_COUNT_ERR, 0);
    }

    if (header->obj_id & BRST_OTYPE_INDIRECT) {
        BRST_Proxy proxy = BRST_Proxy_New(array->mmgr, obj);

        if (!proxy) {
            BRST_Obj_Free(array->mmgr, obj);
            return BRST_Error_Code(array->error);
        }

        proxy->header.obj_id |= BRST_OTYPE_DIRECT;
        obj = proxy;
    } else
        header->obj_id |= BRST_OTYPE_DIRECT;

    /* get the target-object from object-list
     * consider that the pointer contained in list may be proxy-object.
     */
    for (i = 0; i < BRST_List_Count(array->list); i++) {
        void* ptr = BRST_List_ItemAt(array->list, i);
        void* obj_ptr;

        header = (BRST_Obj_Header*)ptr;
        if (header->obj_class == BRST_OCLASS_PROXY)
            obj_ptr = ((BRST_Proxy)ptr)->obj;
        else
            obj_ptr = ptr;

        if (obj_ptr == target) {
            ret = BRST_List_Insert(array->list, ptr, obj);
            if (ret != BRST_OK)
                BRST_Obj_Free(array->mmgr, obj);

            return ret;
        }
    }

    BRST_Obj_Free(array->mmgr, obj);

    return BRST_ITEM_NOT_FOUND;
}

void* BRST_Array_Item(BRST_Array array,
    BRST_UINT index,
    BRST_UINT16 obj_class)
{
    void* obj;
    BRST_Obj_Header* header;

    BRST_PTRACE(" BRST_Array_Item\n");

    obj = BRST_List_ItemAt(array->list, index);

    if (!obj) {
        BRST_Error_Set(array->error, BRST_ARRAY_ITEM_NOT_FOUND, 0);
        return NULL;
    }

    header = (BRST_Obj_Header*)obj;

    if (header->obj_class == BRST_OCLASS_PROXY) {
        obj    = ((BRST_Proxy)obj)->obj;
        header = (BRST_Obj_Header*)obj;
    }

    if ((header->obj_class & BRST_OCLASS_ANY) != obj_class) {
        BRST_Error_Set(array->error, BRST_ARRAY_ITEM_UNEXPECTED_TYPE, 0);

        return NULL;
    }

    return obj;
}

void BRST_Array_Clear(BRST_Array array)
{
    BRST_UINT i;

    BRST_PTRACE(" BRST_Array_Clear\n");

    if (!array)
        return;

    for (i = 0; i < BRST_List_Count(array->list); i++) {
        void* obj = BRST_List_ItemAt(array->list, i);

        if (obj) {
            BRST_Obj_Free(array->mmgr, obj);
        }
    }

    BRST_List_Clear(array->list);
}
