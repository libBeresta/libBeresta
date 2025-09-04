#include "brst_mmgr.h"
#include "brst_encrypt.h"
#include "brst_encoder.h"
#include "brst_stream.h"
#include "brst_dict.h"
#include "brst_matrix.h"
#include "brst_array.h"
#include "private/brst_array.h"
#include "brst_xref.h"
#include "private/brst_xref.h"
#include "private/brst_name_tree.h"
#include "brst_error.h"
#include "brst_consts.h"
#include "private/brst_utils.h"

/*------- NameTree -------*/
BRST_NameTree
BRST_NameTree_New(BRST_MMgr mmgr,
    BRST_Xref xref)
{
    BRST_STATUS ret = BRST_OK;
    BRST_NameTree ntree;
    BRST_Array items;

    BRST_PTRACE(" BRST_NameTree_New\n");

    ntree = BRST_Dict_New(mmgr);
    if (!ntree)
        return NULL;

    if (BRST_Xref_Add(xref, ntree) != BRST_OK)
        return NULL;

    ntree->header.obj_class |= BRST_OSUBCLASS_NAMETREE;

    items = BRST_Array_New(mmgr);
    if (!ntree)
        return NULL;

    ret += BRST_Dict_Add(ntree, "Names", items);
    if (ret != BRST_OK)
        return NULL;

    return ntree;
}

BRST_STATUS
BRST_NameTree_Add(BRST_NameTree tree,
    BRST_String name,
    void* obj)
{
    BRST_Array items;
    BRST_INT32 i, icount;

    if (!tree || !name)
        return BRST_INVALID_PARAMETER;

    items = BRST_Dict_Item(tree, "Names", BRST_OCLASS_ARRAY);
    if (!items)
        return BRST_INVALID_OBJECT;

    /* "The keys shall be sorted in lexical order" -- 7.9.6, Name Trees.
     * Since we store keys sorted, it's best to do a linear insertion sort
     * Find the first element larger than 'key', and insert 'key' and then
     * 'obj' into the items. */

    icount = BRST_Array_Count(items);

    for (i = 0; i < icount; i += 2) {
        BRST_String elem = BRST_Array_Item(items, i, BRST_OCLASS_STRING);
        if (BRST_String_Cmp(name, elem) < 0) {
            BRST_Array_Insert(items, elem, name);
            BRST_Array_Insert(items, elem, obj);
            return BRST_OK;
        }
    }

    /* Items list is empty */
    BRST_Array_Add(items, name);
    BRST_Array_Add(items, obj);
    return BRST_OK;
}

BRST_STATUS
BRST_NameTree_Add_String(BRST_NameTree tree,
    const char* name,
    const char* value)
{
    BRST_String strname;
    BRST_String strvalue;

    strname = BRST_String_New(tree->mmgr, name, NULL);
    if (!strname)
        return BRST_FAILED_TO_ALLOC_MEM;
    strvalue = BRST_String_New(tree->mmgr, value, NULL);
    if (!strvalue) {
        BRST_String_Free(strname);
        return BRST_FAILED_TO_ALLOC_MEM;
    }
    return BRST_NameTree_Add(tree, strname, strvalue);
}

BRST_BOOL
BRST_NameTree_Validate(BRST_NameTree nametree)
{
    if (!nametree)
        return BRST_FALSE;

    if (nametree->header.obj_class != (BRST_OSUBCLASS_NAMETREE | BRST_OCLASS_DICT)) {
        BRST_Error_Set(nametree->error, BRST_INVALID_OBJECT, 0);
        return BRST_FALSE;
    }

    return BRST_TRUE;
}
