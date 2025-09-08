#include "brst_types.h"
#include "brst_types.h"
#include "brst_encrypt.h"
#include "brst_encoder.h"
#include "brst_stream.h"
#include "brst_mmgr.h"
#include "brst_dict.h"
#include "brst_matrix.h"
#include "brst_array.h"
#include "private/brst_array.h"
#include "private/brst_number.h"
#include "brst_xref.h"
#include "private/brst_xref.h"
#include "private/brst_pages.h"
#include "brst_consts.h"
#include "private/brst_utils.h"
#include "brst_geometry_defines.h"
#include "brst_font.h"
#include "private/brst_gstate.h"
#include "brst_error.h"
#include "private/brst_page_attr.h"

static BRST_STATUS
BRST_Pages_BeforeWrite(BRST_Pages obj);

BRST_Pages
BRST_Pages_New(BRST_MMgr mmgr,
    BRST_Pages parent,
    BRST_Xref xref)
{
    BRST_STATUS ret = BRST_OK;
    BRST_Pages pages;

    BRST_PTRACE(" BRST_Pages_New\n");

    pages = BRST_Dict_New(mmgr);
    if (!pages)
        return NULL;

    pages->header.obj_class |= BRST_OSUBCLASS_PAGES;
    pages->before_write_fn = BRST_Pages_BeforeWrite;

    if (BRST_Xref_Add(xref, pages) != BRST_OK)
        return NULL;

    /* add required elements */
    ret += BRST_Dict_AddName(pages, "Type", "Pages");
    ret += BRST_Dict_Add(pages, "Kids", BRST_Array_New(pages->mmgr));
    ret += BRST_Dict_Add(pages, "Count", BRST_Number_New(pages->mmgr, 0));

    if (ret == BRST_OK && parent)
        ret += BRST_Pages_AddKids(parent, pages);

    if (ret != BRST_OK)
        return NULL;

    return pages;
}

BRST_STATUS
BRST_Pages_AddKids(BRST_Pages parent,
    BRST_Dict kid)
{
    BRST_Array kids;
    BRST_STATUS ret;

    BRST_PTRACE(" BRST_Pages_AddKids\n");

    if (BRST_Dict_Item(kid, "Parent", BRST_OCLASS_DICT))
        return BRST_Error_Set(parent->error, BRST_PAGE_CANNOT_SET_PARENT, 0);

    if ((ret = BRST_Dict_Add(kid, "Parent", parent)) != BRST_OK)
        return ret;

    kids = (BRST_Array)BRST_Dict_Item(parent, "Kids", BRST_OCLASS_ARRAY);
    if (!kids)
        return BRST_Error_Set(parent->error, BRST_PAGES_MISSING_KIDS_ENTRY, 0);

    if (kid->header.obj_class == (BRST_OCLASS_DICT | BRST_OSUBCLASS_PAGE)) {
        BRST_PageAttr attr = (BRST_PageAttr)kid->attr;

        attr->parent = parent;
    }

    return BRST_Array_Add(kids, kid);
}

static BRST_UINT
BRST_Pages_PageCount(BRST_Pages pages)
{
    BRST_UINT i;
    BRST_UINT count = 0;
    BRST_Array kids = (BRST_Array)BRST_Dict_Item(pages, "Kids",
        BRST_OCLASS_ARRAY);

    BRST_PTRACE(" BRST_Pages_PageCount\n");

    if (!kids)
        return 0;

    for (i = 0; i < BRST_List_Count(kids->list); i++) {
        void* obj               = BRST_Array_Item(kids, i, BRST_OCLASS_DICT);
        BRST_Obj_Header* header = (BRST_Obj_Header*)obj;

        if (header->obj_class == (BRST_OCLASS_DICT | BRST_OSUBCLASS_PAGES))
            count += BRST_Pages_PageCount((BRST_Dict)obj);
        else if (header->obj_class == (BRST_OCLASS_DICT | BRST_OSUBCLASS_PAGE))
            count += 1;
    }

    return count;
}

BRST_STATUS
BRST_Pages_BeforeWrite(BRST_Pages obj)
{
    BRST_Array kids   = (BRST_Array)BRST_Dict_Item(obj, "Kids",
          BRST_OCLASS_ARRAY);
    BRST_Number count = (BRST_Number)BRST_Dict_Item(obj, "Count",
        BRST_OCLASS_NUMBER);
    BRST_STATUS ret;

    BRST_PTRACE(" BRST_Pages_BeforeWrite\n");

    if (!kids)
        return BRST_Error_Set(obj->error, BRST_PAGES_MISSING_KIDS_ENTRY, 0);

    // TODO Скорректировать вызов BRST_GetPageCount

    if (count)
        BRST_Number_SetValue(count, BRST_Pages_PageCount(obj));
    else {
        count = BRST_Number_New(obj->mmgr, BRST_Pages_PageCount(obj));
        if (!count)
            return BRST_Error_Code(obj->error);

        if ((ret = BRST_Dict_Add(obj, "Count", count)) != BRST_OK)
            return ret;
    }

    return BRST_OK;
}

BRST_BOOL
BRST_Pages_Validate(BRST_Pages pages)
{
    BRST_Obj_Header* header = (BRST_Obj_Header*)pages;

    BRST_PTRACE(" BRST_Pages_Validate\n");

    if (!pages || header->obj_class != (BRST_OCLASS_DICT | BRST_OSUBCLASS_PAGES))
        return BRST_FALSE;

    return BRST_TRUE;
}
