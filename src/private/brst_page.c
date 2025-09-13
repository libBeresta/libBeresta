#include "brst_types.h"
#include "brst_encrypt.h"
#include "brst_encoder.h"
#include "brst_stream.h"
#include "brst_mmgr.h"
#include "brst_dict.h"
#include "brst_matrix.h"
#include "brst_array.h"
#include "private/brst_utils.h"
#include "brst_ext_gstate.h"
#include "brst_xref.h"
#include "private/brst_xref.h"
#include "private/brst_array.h"
#include "private/brst_pages.h"
#include "private/brst_name.h"
#include "private/brst_real.h"
#include "private/brst_defines.h"
#include "brst_page.h"
#include "brst_font.h"
#include "brst_pattern.h"
#include "brst_geometry.h"
#include "private/brst_gstate.h"
#include "brst_page_routines.h"
#include "brst_pattern.h"
#include "private/brst_page.h"
#include "brst_consts.h"
#include "brst_error.h"
#include "private/brst_utils.h"
#include "private/brst_page_attr.h"
#include "brst_pattern.h"

static BRST_STATUS
Page_BeforeWrite(BRST_Dict obj);

static void
Page_OnFree(BRST_Dict obj);

static BRST_STATUS
BRST_Page_AddResource(BRST_Page page);

static const char* const BRST_INHERITABLE_ENTRIES[5] = {
    "Resources",
    "MediaBox",
    "CropBox",
    "Rotate",
    NULL
};

BRST_STATUS
BRST_Page_InsertBefore(BRST_Page page,
    BRST_Page target)
{
    BRST_Page parent;
    BRST_Array kids;
    BRST_STATUS ret;
    BRST_PageAttr attr;

    BRST_PTRACE(" BRST_Page_InsertBefore\n");

    if (!target)
        return BRST_INVALID_PARAMETER;

    attr   = (BRST_PageAttr)target->attr;
    parent = attr->parent;

    if (!parent)
        return BRST_PAGE_CANNOT_SET_PARENT;

    if (BRST_Dict_Item(page, "Parent", BRST_OCLASS_DICT))
        return BRST_Error_Set(parent->error, BRST_PAGE_CANNOT_SET_PARENT, 0);

    if ((ret = BRST_Dict_Add(page, "Parent", parent)) != BRST_OK)
        return ret;

    kids = (BRST_Array)BRST_Dict_Item(parent, "Kids", BRST_OCLASS_ARRAY);
    if (!kids)
        return BRST_Error_Set(parent->error, BRST_PAGES_MISSING_KIDS_ENTRY, 0);

    attr         = (BRST_PageAttr)page->attr;
    attr->parent = parent;

    return BRST_Array_Insert(kids, target, page);
}

static BRST_STATUS
Page_BeforeWrite(BRST_Dict obj)
{
    BRST_STATUS ret;
    BRST_Page page     = (BRST_Page)obj;
    BRST_PageAttr attr = (BRST_PageAttr)obj->attr;

    BRST_PTRACE(" BRST_Page_BeforeWrite\n");

    if (attr->gmode == BRST_GMODE_PATH_OBJECT) {
        BRST_PTRACE(" BRST_Page_BeforeWrite warning path object is not"
                     " end\n");

        if ((ret = BRST_Page_EndPath(page)) != BRST_OK)
            return ret;
    }

    /* TODO Этот закомментированный код относится к тексту.
       TODO Его необходимо обернуть условной компиляцией для текстов.
       TODO Убирать его в другое место не планируется.
       TODO Временно отключен для сборки
    if (attr->gmode == BRST_GMODE_TEXT_OBJECT) {
        BRST_PTRACE(" BRST_Page_BeforeWrite warning text block is not end\n");

        if ((ret = BRST_Page_EndText (page)) != BRST_OK)
            return ret;
    }
    */

    if (attr->gstate)
        while (attr->gstate->prev) {
            if ((ret = BRST_Page_GRestore(page)) != BRST_OK)
                return ret;
        }

    return BRST_OK;
}

BRST_BOOL
BRST_Dict_IsPage(BRST_Dict dict) {
    if (dict) {
        return (dict->header.obj_class & BRST_OSUBCLASS_PAGE) != BRST_OSUBCLASS_PAGE;
    }

    return BRST_FALSE;
}

BRST_Page
BRST_Page_New(BRST_MMgr mmgr,
    BRST_Xref xref)
{
    BRST_STATUS ret;
    BRST_PageAttr attr;
    BRST_Page page;

    BRST_PTRACE(" BRST_Page_New\n");

    page = BRST_Dict_New(mmgr);
    if (!page)
        return NULL;

    page->header.obj_class |= BRST_OSUBCLASS_PAGE;
    page->free_fn         = Page_OnFree;
    page->before_write_fn = Page_BeforeWrite;

    attr = BRST_GetMem(page->mmgr, sizeof(BRST_PageAttr_Rec));
    if (!attr) {
        BRST_Dict_Free(page);
        return NULL;
    }

    page->attr = attr;
    BRST_MemSet(attr, 0, sizeof(BRST_PageAttr_Rec));
    attr->gmode    = BRST_GMODE_PAGE_DESCRIPTION;
    attr->cur_pos  = BRST_ToPoint(0, 0);
    attr->text_pos = BRST_ToPoint(0, 0);

    ret = BRST_Xref_Add(xref, page);
    if (ret != BRST_OK)
        return NULL;

    attr->gstate   = BRST_GState_New(page->mmgr, NULL);
    attr->contents = BRST_Dict_New_Stream_Init(page->mmgr, xref);

    if (!attr->gstate || !attr->contents)
        return NULL;

    attr->stream = attr->contents->stream;
    attr->xref   = xref;

    /* add required elements */
    ret += BRST_Dict_AddName(page, "Type", "Page");
    ret += BRST_Dict_Add(page, "MediaBox", BRST_Box_Array_New(page->mmgr, BRST_ToBox(0, 0, (BRST_INT16)(BRST_DEF_PAGE_WIDTH), (BRST_INT16)(BRST_DEF_PAGE_HEIGHT))));
    ret += BRST_Dict_Add(page, "Contents", attr->contents);

    ret += BRST_Page_AddResource(page);

    if (ret != BRST_OK)
        return NULL;

    return page;
}

static void
Page_OnFree(BRST_Dict obj)
{
    BRST_PageAttr attr = (BRST_PageAttr)obj->attr;

    BRST_PTRACE(" BRST_Page_OnFree\n");

    if (attr) {
        if (attr->gstate)
            BRST_GState_Free(obj->mmgr, attr->gstate);

        BRST_FreeMem(obj->mmgr, attr);
    }
}

BRST_STATUS
BRST_Page_CheckState(BRST_Page page,
    BRST_UINT mode)
{
    if (!page)
        return BRST_INVALID_OBJECT;

    if (page->header.obj_class != (BRST_OSUBCLASS_PAGE | BRST_OCLASS_DICT))
        return BRST_INVALID_PAGE;

    if (!(((BRST_PageAttr)page->attr)->gmode & mode))
        return BRST_Error_Raise(page->error, BRST_PAGE_INVALID_GMODE, 0);

    return BRST_OK;
}

void* BRST_Page_InheritableItem(BRST_Page page,
    const char* key,
    BRST_UINT16 obj_class)
{
    BRST_BOOL chk = BRST_FALSE;
    BRST_INT i    = 0;
    void* obj;

    BRST_PTRACE(" BRST_Page_InheritableItem\n");

    /* check whether the specified key is valid */
    while (BRST_INHERITABLE_ENTRIES[i]) {
        if (BRST_StrCmp(key, BRST_INHERITABLE_ENTRIES[i]) == 0) {
            chk = BRST_TRUE;
            break;
        }
        i++;
    }

    /* the key is not inheritable */
    if (chk != BRST_TRUE) {
        BRST_Error_Set(page->error, BRST_INVALID_PARAMETER, 0);
        return NULL;
    }

    obj = BRST_Dict_Item(page, key, obj_class);

    /* if resources of the object is NULL, search resources of parent
     * pages recursively
     */
    if (!obj) {
        BRST_Pages pages = BRST_Dict_Item(page, "Parent", BRST_OCLASS_DICT);
        while (pages) {
            obj = BRST_Dict_Item(page, key, obj_class);

            if (obj)
                break;

            pages = BRST_Dict_Item(pages, "Parent", BRST_OCLASS_DICT);
        }
    }

    return obj;
}

BRST_STATUS
BRST_Page_AddResource(BRST_Page page)
{
    BRST_STATUS ret = BRST_OK;
    BRST_Dict resource;
    BRST_Array procset;

    BRST_PTRACE(" BRST_Page_AddResource\n");

    resource = BRST_Dict_New(page->mmgr);
    if (!resource)
        return BRST_Error_Code(page->error);

    /* althoth ProcSet-entry is obsolete, add it to resource for
     * compatibility
     */

    ret += BRST_Dict_Add(page, "Resources", resource);

    procset = BRST_Array_New(page->mmgr);
    if (!procset)
        return BRST_Error_Code(page->error);

    if (BRST_Dict_Add(resource, "ProcSet", procset) != BRST_OK)
        return BRST_Error_Code(resource->error);

    ret += BRST_Array_Add(procset, BRST_Name_New(page->mmgr, "PDF"));
    ret += BRST_Array_Add(procset, BRST_Name_New(page->mmgr, "Text"));
    ret += BRST_Array_Add(procset, BRST_Name_New(page->mmgr, "ImageB"));
    ret += BRST_Array_Add(procset, BRST_Name_New(page->mmgr, "ImageC"));
    ret += BRST_Array_Add(procset, BRST_Name_New(page->mmgr, "ImageI"));

    if (ret != BRST_OK)
        return BRST_Error_Code(procset->error);

    return BRST_OK;
}

BRST_Box
BRST_Page_MediaBox(BRST_Page page)
{
    BRST_Box media_box = { 0, 0, 0, 0 };

    BRST_PTRACE(" BRST_Page_MediaBox\n");

    if (BRST_Page_Validate(page)) {
        BRST_Array array = BRST_Page_InheritableItem(page, "MediaBox",
            BRST_OCLASS_ARRAY);

        if (array) {
            BRST_Real r;

            r = BRST_Array_Item(array, 0, BRST_OCLASS_REAL);
            if (r)
                media_box.left = BRST_Real_Value(r);

            r = BRST_Array_Item(array, 1, BRST_OCLASS_REAL);
            if (r)
                media_box.bottom = BRST_Real_Value(r);

            r = BRST_Array_Item(array, 2, BRST_OCLASS_REAL);
            if (r)
                media_box.right = BRST_Real_Value(r);

            r = BRST_Array_Item(array, 3, BRST_OCLASS_REAL);
            if (r)
                media_box.top = BRST_Real_Value(r);

            BRST_Error_Check(page->error);
        } else
            BRST_Error_Raise(page->error, BRST_PAGE_CANNOT_FIND_OBJECT, 0);
    }

    return media_box;
}

BRST_CSTR
BRST_Page_XObjectName(BRST_Page page,
    BRST_XObject xobj)
{
    BRST_PageAttr attr = (BRST_PageAttr)page->attr;
    const char* key;

    BRST_PTRACE(" BRST_Page_XObjectName\n");

    if (!attr->xobjects) {
        BRST_Dict resources;
        BRST_Dict xobjects;

        resources = BRST_Page_InheritableItem(page, "Resources",
            BRST_OCLASS_DICT);
        if (!resources)
            return NULL;

        xobjects = BRST_Dict_New(page->mmgr);
        if (!xobjects)
            return NULL;

        if (BRST_Dict_Add(resources, "XObject", xobjects) != BRST_OK)
            return NULL;

        attr->xobjects = xobjects;
    }

    /* search xobject-object from xobject-resource */
    key = BRST_Dict_KeyByObj(attr->xobjects, xobj);
    if (!key) {
        /* if the xobject is not registered in xobject-resource, register
         * xobject to xobject-resource.
         */
        char xobj_name[BRST_LIMIT_MAX_NAME_LEN + 1];
        char* ptr;
        char* end_ptr = xobj_name + BRST_LIMIT_MAX_NAME_LEN;

        ptr = (char*)BRST_StrCpy(xobj_name, "X", end_ptr);
        BRST_IToA(ptr, BRST_List_Count(attr->xobjects->list) + 1, end_ptr);

        if (BRST_Dict_Add(attr->xobjects, xobj_name, xobj) != BRST_OK)
            return NULL;

        key = BRST_Dict_KeyByObj(attr->xobjects, xobj);
    }

    return key;
}

BRST_CSTR
BRST_Page_PatternName(BRST_Page page,
    BRST_Pattern pat)
{
    const char* key;
    
    BRST_PTRACE(" BRST_Page_PatternName\n");

    BRST_Dict resources;
    BRST_Dict patterns;

    resources = BRST_Page_InheritableItem(page, "Resources",
        BRST_OCLASS_DICT);

    if (!resources)
        return NULL;

    patterns = (BRST_Dict)BRST_Dict_Item(resources, "Pattern", BRST_OCLASS_DICT);

    if (!patterns) {
        patterns = BRST_Dict_New(BRST_Page_MMgr(page));

        if (BRST_Dict_Add(resources, "Pattern", patterns) != BRST_OK)
            return NULL;
    }


    /* search pattern-object from pattern-resource */
    key = BRST_Dict_KeyByObj(patterns, pat);
    if (!key) {
        /* if the pattern is not registered in pattern-resource, register
         * pattern to pattern-resource.
         */
        char pattern_name[BRST_LIMIT_MAX_NAME_LEN + 1];
        char* ptr;
        char* end_ptr = pattern_name + BRST_LIMIT_MAX_NAME_LEN;

        ptr = (char*)BRST_StrCpy(pattern_name, "P", end_ptr);
        BRST_IToA(ptr, BRST_List_Count(patterns->list) + 1, end_ptr);

        if (BRST_Dict_Add(patterns, pattern_name, pat) != BRST_OK)
            return NULL;

        key = BRST_Dict_KeyByObj(patterns, pat);
    }

    return key;
}

BRST_CSTR
BRST_Page_ExtGStateName(BRST_Page page,
    BRST_ExtGState state)
{
    BRST_PageAttr attr = (BRST_PageAttr)page->attr;
    const char* key;

    BRST_PTRACE(" BRST_Page_ExtGStateName\n");

    if (!attr->ext_gstates) {
        BRST_Dict resources;
        BRST_Dict ext_gstates;

        resources = BRST_Page_InheritableItem(page, "Resources",
            BRST_OCLASS_DICT);
        if (!resources)
            return NULL;

        ext_gstates = BRST_Dict_New(page->mmgr);
        if (!ext_gstates)
            return NULL;

        if (BRST_Dict_Add(resources, "ExtGState", ext_gstates) != BRST_OK)
            return NULL;

        attr->ext_gstates = ext_gstates;
    }

    /* search ext_gstate-object from ext_gstate-resource */
    key = BRST_Dict_KeyByObj(attr->ext_gstates, state);
    if (!key) {
        /* if the ext-gstate is not registered in ext-gstate resource, register
         *  to ext-gstate resource.
         */
        char ext_gstate_name[BRST_LIMIT_MAX_NAME_LEN + 1];
        char* ptr;
        char* end_ptr = ext_gstate_name + BRST_LIMIT_MAX_NAME_LEN;

        ptr = (char*)BRST_StrCpy(ext_gstate_name, "E", end_ptr);
        BRST_IToA(ptr, BRST_List_Count(attr->ext_gstates->list) + 1, end_ptr);

        if (BRST_Dict_Add(attr->ext_gstates, ext_gstate_name, state) != BRST_OK)
            return NULL;

        key = BRST_Dict_KeyByObj(attr->ext_gstates, state);
    }

    return key;
}

const char*
BRST_Page_ShadingName(BRST_Page page,
    BRST_Shading shading)
{
    BRST_PageAttr attr = (BRST_PageAttr)page->attr;
    const char* key;

    BRST_PTRACE(" BRST_Page_ShadingName\n");

    if (!attr->shadings) {
        BRST_Dict resources;
        BRST_Dict shadings;

        resources = BRST_Page_InheritableItem(page, "Resources",
            BRST_OCLASS_DICT);
        if (!resources)
            return NULL;

        shadings = BRST_Dict_New(page->mmgr);
        if (!shadings)
            return NULL;

        if (BRST_Dict_Add(resources, "Shading", shadings) != BRST_OK)
            return NULL;

        attr->shadings = shadings;
    }

    /* search shading-object from shading-resource */
    key = BRST_Dict_KeyByObj(attr->shadings, shading);
    if (!key) {
        /* if the shading is not registered in shadings resource, register
         *  to shadings resource.
         */
        char shading_str[BRST_LIMIT_MAX_NAME_LEN + 1];
        char* ptr;
        char* end_ptr = shading_str + BRST_LIMIT_MAX_NAME_LEN;

        ptr = (char*)BRST_StrCpy(shading_str, "Sh", end_ptr);
        BRST_IToA(ptr, BRST_List_Count(attr->shadings->list), end_ptr);

        if (BRST_Dict_Add(attr->shadings, shading_str, shading) != BRST_OK)
            return NULL;

        key = BRST_Dict_KeyByObj(attr->shadings, shading);
    }

    return key;
}

BRST_STATUS
BRST_Page_SetBoxValue(BRST_Page page,
    const char* name,
    BRST_UINT index,
    BRST_REAL value)
{
    BRST_Real r;
    BRST_Array array;

    BRST_PTRACE(" BRST_Page_SetBoxValue\n");

    if (!BRST_Page_Validate(page))
        return BRST_INVALID_PAGE;

    array = BRST_Page_InheritableItem(page, name, BRST_OCLASS_ARRAY);
    if (!array)
        return BRST_Error_Set(page->error, BRST_PAGE_CANNOT_FIND_OBJECT, 0);

    r = BRST_Array_Item(array, index, BRST_OCLASS_REAL);
    if (!r)
        return BRST_Error_Set(page->error, BRST_PAGE_INVALID_INDEX, 0);

    BRST_Real_SetValue(r, value);

    return BRST_OK;
}

BRST_BOOL
BRST_Page_Validate(BRST_Page page)
{
    BRST_Obj_Header* header = (BRST_Obj_Header*)page;

    BRST_PTRACE(" BRST_Page_Validate\n");

    if (!page || !page->attr)
        return BRST_FALSE;

    if (header->obj_class != (BRST_OCLASS_DICT | BRST_OSUBCLASS_PAGE))
        return BRST_FALSE;

    return BRST_TRUE;
}

void BRST_Page_SetFilter(BRST_Page page,
    BRST_UINT filter)
{
    BRST_PageAttr attr;

    BRST_PTRACE(" BRST_Page_SetFilter\n");

    attr                   = (BRST_PageAttr)page->attr;
    attr->contents->filter = filter;
}
