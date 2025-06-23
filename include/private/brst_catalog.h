#ifndef PRIVATE_BRST_CATALOG_H
#define PRIVATE_BRST_CATALOG_H

#include "private/brst_dict.h"
#include "private/brst_xref.h"
#include "private/brst_name_dict.h"
#include "private/brst_pages.h"

typedef BRST_Dict BRST_Catalog;

BRST_Catalog
BRST_Catalog_New(
    BRST_MMgr mmgr,
    BRST_Xref xref
);

BRST_NameDict
BRST_Catalog_Names(
    BRST_Catalog catalog
);

BRST_STATUS
BRST_Catalog_SetNames(
    BRST_Catalog  catalog,
    BRST_NameDict dict
);

BRST_Pages
BRST_Catalog_Root(
    BRST_Catalog catalog
);

BRST_PageLayout
BRST_Catalog_PageLayout(
    BRST_Catalog catalog
);

BRST_STATUS
BRST_Catalog_SetPageLayout(
    BRST_Catalog    catalog,
    BRST_PageLayout layout
);

BRST_PageMode
BRST_Catalog_PageMode(
    BRST_Catalog catalog
);

BRST_STATUS
BRST_Catalog_SetPageMode(
    BRST_Catalog  catalog,
    BRST_PageMode mode
);

BRST_STATUS
BRST_Catalog_SetOpenAction(
    BRST_Catalog     catalog,
    BRST_Destination open_action
);

BRST_STATUS
BRST_Catalog_AddPageLabel(
    BRST_Catalog catalog,
    BRST_UINT    page_num,
    BRST_Dict    page_label
);

BRST_UINT
BRST_Catalog_ViewerPreference(
    BRST_Catalog catalog
);

BRST_STATUS
BRST_Catalog_SetViewerPreference(
    BRST_Catalog catalog,
    BRST_UINT    value
);

BRST_BOOL
BRST_Catalog_Validate(
    BRST_Catalog catalog
);

#endif /* PRIVATE_BRST_CATALOG_H */
