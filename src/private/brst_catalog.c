#include "brst_types.h"
#include "brst_encrypt.h"
#include "brst_encoder.h"
#include "brst_stream.h"
#include "brst_mmgr.h"
#include "brst_dict.h"
#include "brst_array.h"
#include "private/brst_array.h"
#include "brst_xref.h"
#include "private/brst_boolean.h"
#include "private/brst_name.h"
#include "brst_page.h"
#include "private/brst_defines.h"
#include "brst_destination.h"
#include "private/brst_catalog.h"
#include "brst_error.h"
#include "brst_consts.h"
#include "private/brst_utils.h"

static const char* const BRST_PAGE_LAYOUT_NAMES[] = {
    "SinglePage",
    "OneColumn",
    "TwoColumnLeft",
    "TwoColumnRight",
    "TwoPageLeft",
    "TwoPageRight",
    NULL
};

static const char* const BRST_PAGE_MODE_NAMES[] = {
    "UseNone",
    "UseOutlines",
    "UseThumbs",
    "FullScreen",
    "UseOC",
    "UseAttachments",
    NULL
};

BRST_Catalog
BRST_Catalog_New(BRST_MMgr mmgr,
    BRST_Xref xref)
{
    BRST_Catalog catalog;
    BRST_STATUS ret = 0;

    catalog = BRST_Dict_New(mmgr);
    if (!catalog)
        return NULL;

    catalog->header.obj_class |= BRST_OSUBCLASS_CATALOG;

    if (BRST_Xref_Add(xref, catalog) != BRST_OK)
        return NULL;

    /* add required elements */
    ret += BRST_Dict_AddName(catalog, "Type", "Catalog");
    ret += BRST_Dict_Add(catalog, "Pages", BRST_Pages_New(mmgr, NULL, xref));

    if (ret != BRST_OK)
        return NULL;

    return catalog;
}

BRST_Pages
BRST_Catalog_Root(BRST_Catalog catalog)
{
    BRST_Dict pages;

    if (!catalog)
        return NULL;

    pages = BRST_Dict_Item(catalog, "Pages", BRST_OCLASS_DICT);
    if (!pages || pages->header.obj_class != (BRST_OSUBCLASS_PAGES | BRST_OCLASS_DICT))
        BRST_Error_Set(catalog->error, BRST_PAGE_CANNOT_GET_ROOT_PAGES, 0);

    return pages;
}

BRST_NameDict
BRST_Catalog_Names(BRST_Catalog catalog)
{
    if (!catalog)
        return NULL;
    return BRST_Dict_Item(catalog, "Names", BRST_OCLASS_DICT);
}

BRST_STATUS
BRST_Catalog_SetNames(BRST_Catalog catalog,
    BRST_NameDict dict)
{
    return BRST_Dict_Add(catalog, "Names", dict);
}

BRST_PageLayout
BRST_Catalog_PageLayout(BRST_Catalog catalog)
{
    BRST_Name layout;
    BRST_UINT i = 0;

    layout = (BRST_Name)BRST_Dict_Item(catalog, "PageLayout",
        BRST_OCLASS_NAME);
    if (!layout)
        return BRST_PAGE_LAYOUT_EOF;

    while (BRST_PAGE_LAYOUT_NAMES[i]) {
        if (BRST_StrCmp(BRST_Name_Value(layout), BRST_PAGE_LAYOUT_NAMES[i]) == 0)
            return (BRST_PageLayout)i;
        i++;
    }

    return BRST_PAGE_LAYOUT_EOF;
}

BRST_STATUS
BRST_Catalog_SetPageLayout(BRST_Catalog catalog,
    BRST_PageLayout layout)
{
    return BRST_Dict_AddName(catalog, "PageLayout",
        BRST_PAGE_LAYOUT_NAMES[(BRST_INT)layout]);
}

BRST_PageMode
BRST_Catalog_PageMode(BRST_Catalog catalog)
{
    BRST_Name mode;
    BRST_UINT i = 0;

    mode = (BRST_Name)BRST_Dict_Item(catalog, "PageMode", BRST_OCLASS_NAME);
    if (!mode)
        return BRST_PAGE_MODE_USE_NONE;

    while (BRST_PAGE_MODE_NAMES[i]) {
        if (BRST_StrCmp(BRST_Name_Value(mode), BRST_PAGE_MODE_NAMES[i]) == 0)
            return (BRST_PageMode)i;
        i++;
    }

    return BRST_PAGE_MODE_USE_NONE;
}

BRST_STATUS
BRST_Catalog_SetPageMode(BRST_Catalog catalog,
    BRST_PageMode mode)
{
    return BRST_Dict_AddName(catalog, "PageMode",
        BRST_PAGE_MODE_NAMES[(BRST_INT)mode]);
}

BRST_STATUS
BRST_Catalog_SetOpenAction(BRST_Catalog catalog,
    BRST_Destination open_action)
{
    if (!open_action) {
        BRST_Dict_RemoveElement(catalog, "OpenAction");
        return BRST_OK;
    }

    return BRST_Dict_Add(catalog, "OpenAction", open_action);
}

BRST_BOOL
BRST_Catalog_Validate(BRST_Catalog catalog)
{
    if (!catalog)
        return BRST_FALSE;

    if (catalog->header.obj_class != (BRST_OSUBCLASS_CATALOG | BRST_OCLASS_DICT)) {
        BRST_Error_Set(catalog->error, BRST_INVALID_OBJECT, 0);
        return BRST_FALSE;
    }

    return BRST_TRUE;
}

BRST_STATUS
BRST_Catalog_AddPageLabel(BRST_Catalog catalog,
    BRST_UINT page_num,
    BRST_Dict page_label)
{
    BRST_STATUS ret;
    BRST_Array nums;
    BRST_Dict labels = BRST_Dict_Item(catalog, "PageLabels",
        BRST_OCLASS_DICT);

    BRST_PTRACE((" BRST_Catalog_AddPageLabel\n"));

    if (!labels) {
        labels = BRST_Dict_New(catalog->mmgr);

        if (!labels)
            return BRST_Error_Code(catalog->error);

        if ((ret = BRST_Dict_Add(catalog, "PageLabels", labels)) != BRST_OK)
            return ret;
    }

    nums = BRST_Dict_Item(labels, "Nums", BRST_OCLASS_ARRAY);

    if (!nums) {
        nums = BRST_Array_New(catalog->mmgr);

        if (!nums)
            return BRST_Error_Code(catalog->error);

        if ((ret = BRST_Dict_Add(labels, "Nums", nums)) != BRST_OK)
            return ret;
    }

    if ((ret = BRST_Array_AddNumber(nums, page_num)) != BRST_OK)
        return ret;

    return BRST_Array_Add(nums, page_label);
}

BRST_STATUS
BRST_Catalog_SetViewerPreference(BRST_Catalog catalog,
    BRST_UINT value)
{
    BRST_STATUS ret;
    BRST_Dict preferences;

    BRST_PTRACE((" BRST_Catalog_SetViewerPreference\n"));

    if (!value) {
        ret = BRST_Dict_RemoveElement(catalog, "ViewerPreferences");

        if (ret == BRST_DICT_ITEM_NOT_FOUND)
            ret = BRST_OK;

        return ret;
    }

    preferences = BRST_Dict_New(catalog->mmgr);
    if (!preferences)
        return BRST_Error_Code(catalog->error);

    if ((ret = BRST_Dict_Add(catalog, "ViewerPreferences", preferences))
        != BRST_OK)
        return ret;

    /*  */

    if (value & BRST_HIDE_TOOLBAR) {
        if ((ret = BRST_Dict_AddBoolean(preferences, "HideToolbar",
                 BRST_TRUE))
            != BRST_OK)
            return ret;
    } else {
        if ((ret = BRST_Dict_RemoveElement(preferences, "HideToolbar")) != BRST_OK)
            if (ret != BRST_DICT_ITEM_NOT_FOUND)
                return ret;
    }

    if (value & BRST_HIDE_MENUBAR) {
        if ((ret = BRST_Dict_AddBoolean(preferences, "HideMenubar",
                 BRST_TRUE))
            != BRST_OK)
            return ret;
    } else {
        if ((ret = BRST_Dict_RemoveElement(preferences, "HideMenubar")) != BRST_OK)
            if (ret != BRST_DICT_ITEM_NOT_FOUND)
                return ret;
    }

    if (value & BRST_HIDE_WINDOW_UI) {
        if ((ret = BRST_Dict_AddBoolean(preferences, "HideWindowUI",
                 BRST_TRUE))
            != BRST_OK)
            return ret;
    } else {
        if ((ret = BRST_Dict_RemoveElement(preferences, "HideWindowUI")) != BRST_OK)
            if (ret != BRST_DICT_ITEM_NOT_FOUND)
                return ret;
    }

    if (value & BRST_FIT_WINDOW) {
        if ((ret = BRST_Dict_AddBoolean(preferences, "FitWindow",
                 BRST_TRUE))
            != BRST_OK)
            return ret;
    } else {
        if ((ret = BRST_Dict_RemoveElement(preferences, "FitWindow")) != BRST_OK)
            if (ret != BRST_DICT_ITEM_NOT_FOUND)
                return ret;
    }

    if (value & BRST_CENTER_WINDOW) {
        if ((ret = BRST_Dict_AddBoolean(preferences, "CenterWindow",
                 BRST_TRUE))
            != BRST_OK)
            return ret;
    } else {
        if ((ret = BRST_Dict_RemoveElement(preferences, "CenterWindow")) != BRST_OK)
            if (ret != BRST_DICT_ITEM_NOT_FOUND)
                return ret;
    }

    if (value & BRST_PRINT_SCALING_NONE) {
        if ((ret = BRST_Dict_AddName(preferences, "PrintScaling",
                 "None"))
            != BRST_OK)
            return ret;
    } else {
        if ((ret = BRST_Dict_RemoveElement(preferences, "PrintScaling")) != BRST_OK)
            if (ret != BRST_DICT_ITEM_NOT_FOUND)
                return ret;
    }

    return BRST_OK;
}

BRST_UINT
BRST_Catalog_ViewerPreference(BRST_Catalog catalog)
{
    BRST_Dict preferences;
    BRST_UINT value = 0;
    BRST_Boolean obj;

    BRST_PTRACE((" BRST_Catalog_ViewerPreference\n"));

    preferences = (BRST_Dict)BRST_Dict_Item(catalog, "ViewerPreferences",
        BRST_OCLASS_DICT);

    if (!preferences)
        return 0;

    obj = (BRST_Boolean)BRST_Dict_Item(preferences, "HideToolbar",
        BRST_OCLASS_BOOLEAN);
    if (obj) {
        if (BRST_Boolean_Value(obj))
            value += BRST_HIDE_TOOLBAR;
    }

    obj = (BRST_Boolean)BRST_Dict_Item(preferences, "HideMenubar",
        BRST_OCLASS_BOOLEAN);
    if (obj) {
        if (BRST_Boolean_Value(obj))
            value += BRST_HIDE_MENUBAR;
    }

    obj = (BRST_Boolean)BRST_Dict_Item(preferences, "HideWindowUI",
        BRST_OCLASS_BOOLEAN);
    if (obj) {
        if (BRST_Boolean_Value(obj))
            value += BRST_HIDE_WINDOW_UI;
    }

    obj = (BRST_Boolean)BRST_Dict_Item(preferences, "FitWindow",
        BRST_OCLASS_BOOLEAN);
    if (obj) {
        if (BRST_Boolean_Value(obj))
            value += BRST_FIT_WINDOW;
    }

    obj = (BRST_Boolean)BRST_Dict_Item(preferences, "CenterWindow",
        BRST_OCLASS_BOOLEAN);
    if (obj) {
        if (BRST_Boolean_Value(obj))
            value += BRST_CENTER_WINDOW;
    }

    return value;
}
