#include "brst_types.h"
#include "brst_mmgr.h"
#include "brst_error.h"
#include "brst_consts.h"
#include "private/brst_defines.h"
#include "private/brst_error.h"
#include "private/brst_list.h"
#include "private/brst_mmgr.h"
#include "private/brst_utils.h"

typedef struct _BRST_List_Rec {
    BRST_MMgr mmgr;
    BRST_Error error;
    BRST_UINT block_size;
    BRST_UINT items_per_block;
    BRST_UINT count;
    void** obj;
} BRST_List_Rec;

static BRST_STATUS
Resize(BRST_List list,
    BRST_UINT count);

/*
 *  BRST_List_new
 *
 *  mmgr :  handle to a BRST_MMgr object.
 *  items_per_block :  number of increases of pointers.
 *
 *  return:  If BRST_List_New success, it returns a handle to new BRST_List
 *           object, otherwise it returns NULL.
 *
 */

BRST_List
BRST_List_New(BRST_MMgr mmgr,
    BRST_UINT items_per_block)
{
    BRST_List list;

    BRST_PTRACE(" BRST_List_New\n");

    if (mmgr == NULL)
        return NULL;

    list = (BRST_List)BRST_GetMem(mmgr, sizeof(BRST_List_Rec));
    if (list) {
        list->mmgr            = mmgr;
        list->error           = BRST_MMgr_Error(mmgr);
        list->block_size      = 0;
        list->items_per_block = (items_per_block <= 0 ? BRST_DEF_ITEMS_PER_BLOCK : items_per_block);
        list->count           = 0;
        list->obj             = NULL;
    }

    return list;
}

/*
 *  BRST_List_add
 *
 *  list :  Pointer to a BRST_List object.
 *  item :  Pointer to a object to be added.
 *
 *  return:  If BRST_List_Add success, it returns BRST_OK.
 *           BRST_FAILED_TO_ALLOC_MEM is returned when the expansion of the
 *           object list is failed.
 *
 */

BRST_STATUS
BRST_List_Add(BRST_List list,
    void* item)
{
    BRST_PTRACE(" BRST_List_Add\n");

    if (list->count >= list->block_size) {
        BRST_STATUS ret = Resize(list,
            list->block_size + list->items_per_block);

        if (ret != BRST_OK) {
            return ret;
        }
    }

    list->obj[list->count++] = item;
    return BRST_OK;
}

/*
 *  BRST_List_Insert
 *
 *  list   :  Pointer to a BRST_List object.
 *  target :  Pointer to the target object.
 *  item   :  Pointer to a object to be inserted.
 *
 *  insert the item before the target.
 *
 *  return:  If BRST_List_Add success, it returns BRST_OK.
 *           BRST_FAILED_TO_ALLOC_MEM is returned when the expansion of the
 *           object list is failed.
 *           BRST_ITEM_NOT_FOUND is returned where the target object is not
 *           found.
 *
 */

BRST_STATUS
BRST_List_Insert(BRST_List list,
    void* target,
    void* item)
{
    BRST_INT target_idx = BRST_List_Find(list, target);
    void* last_item     = list->obj[list->count - 1];
    BRST_INT i;

    BRST_PTRACE(" BRST_List_Insert\n");

    if (target_idx < 0)
        return BRST_ITEM_NOT_FOUND;

    /* move the item of the list to behind one by one. */
    for (i = list->count - 2; i >= target_idx; i--)
        list->obj[i + 1] = list->obj[i];

    list->obj[target_idx] = item;

    return BRST_List_Add(list, last_item);
}

/*
 *  BRST_List_Remove
 *
 *  Remove the object specified by item parameter from the list object. The
 *  memory area that the object uses is not released.
 *
 *  list :  Pointer to a BRST_List object.
 *  item :  Pointer to a object to be remove.
 *
 *  return:  If BRST_List_Remove success, it returns BRST_OK.
 *           BRST_ITEM_NOT_FOUND is returned when the object specified by item
 *           parameter is not found.
 *
 */

BRST_STATUS
BRST_List_Remove(BRST_List list,
    void* item)
{
    BRST_UINT i;
    void** obj = list->obj;

    BRST_PTRACE(" BRST_List_Remove\n");

    for (i = 0; i < list->count; i++) {
        if (*obj == item) {
            BRST_List_RemoveByIndex(list, i);
            return BRST_OK;
        } else
            obj++;
    }

    return BRST_ITEM_NOT_FOUND;
}

/*
 *  BRST_List_RemoveByIndex
 *
 *  Remove the object by index number.
 *
 *  list :  Pointer to a BRST_List object.
 *  index :  Index of a object to be remove.
 *
 *  return:  If BRST_List_RemoveByIndex success, it returns BRST_OK.
 *           BRST_ITEM_NOT_FOUND is returned when the value which is specified
 *           by index parameter is invalid.
 *
 */

void* BRST_List_RemoveByIndex(BRST_List list,
    BRST_UINT index)
{
    void* tmp;

    BRST_PTRACE(" BRST_List_RemoveByIndex\n");

    if (list->count <= index)
        return NULL;

    tmp = list->obj[index];

    while (index < list->count - 1) {
        list->obj[index] = list->obj[index + 1];
        index++;
    }

    list->count--;

    return tmp;
}

/*
 *  BRST_List_ItemAt
 *
 *  list :  Pointer to a BRST_List object.
 *  index :  Index of a object.
 *
 *  return:  If BRST_List_at success, it returns a pointer to the object.
 *           otherwise it returns NULL.
 *
 */

void* BRST_List_ItemAt(BRST_List list,
    BRST_UINT index)
{
    BRST_PTRACE(" BRST_List_ItemAt\n");

    return (list->count <= index) ? NULL : list->obj[index];
}

/*
 *  BRST_List_free
 *
 *  list :  Pointer to a BRST_List object.
 *
 */

void BRST_List_Free(BRST_List list)
{
    BRST_PTRACE(" BRST_List_Free\n");

    if (!list)
        return;

    BRST_List_Clear(list);
    BRST_FreeMem(list->mmgr, list);
}

/*
 *  BRST_List_Clear
 *
 *  list :  Pointer to a BRST_List object.
 *
 */

void BRST_List_Clear(BRST_List list)
{
    BRST_PTRACE(" BRST_List_Clear\n");

    if (list->obj)
        BRST_FreeMem(list->mmgr, list->obj);

    list->block_size = 0;
    list->count      = 0;
    list->obj        = NULL;
}

/*
 *  Resize
 *
 *  list :  Pointer to a BRST_List object.
 *  count : The size of array of pointers.
 *
 *  return:  If Resize success, it returns BRST_OK.
 *           otherwise it returns error-code which is set by BRST_MMgr object.
 *
 */

static BRST_STATUS
Resize(BRST_List list,
    BRST_UINT count)
{
    void** new_obj;

    BRST_PTRACE(" BRST_List_Resize\n");

    if (list->count >= count) {
        if (list->count == count)
            return BRST_OK;
        else
            return BRST_INVALID_PARAMETER;
    }

    new_obj = (void**)BRST_GetMem(list->mmgr, count * sizeof(void*));

    if (!new_obj)
        return BRST_Error_Code(list->error);

    if (list->obj)
        BRST_MemCopy((BRST_BYTE*)new_obj, (BRST_BYTE*)list->obj,
            list->block_size * sizeof(void*));

    list->block_size = count;
    if (list->obj)
        BRST_FreeMem(list->mmgr, list->obj);
    list->obj = new_obj;

    return BRST_OK;
}

/*
 *  BRST_List_Find
 *
 *  list :  Pointer to a BRST_List object.
 *  count : the size of array of pointers.
 *
 *  return:  If BRST_List_Find success, it returns index of the object.
 *           otherwise it returns negative value.
 *
 */

BRST_INT32
BRST_List_Find(BRST_List list,
    void* item)
{
    BRST_UINT i;

    BRST_PTRACE(" BRST_List_Find\n");

    for (i = 0; i < list->count; i++) {
        if (list->obj[i] == item)
            return i;
    }

    return -1;
}

BRST_INT32
BRST_List_Count(BRST_List list)
{

    BRST_PTRACE(" BRST_List_Count\n");

    if (!list)
        return -1;

    return list->count;
}
