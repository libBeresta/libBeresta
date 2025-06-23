#ifndef PRIVATE_BRST_NAME_TREE_H
#define PRIVATE_BRST_NAME_TREE_H

#include "brst_mmgr.h"
#include "private/brst_dict.h"
#include "private/brst_string.h"

typedef BRST_Dict BRST_NameTree; 

BRST_NameTree
BRST_NameTree_New(
    BRST_MMgr mmgr,
    BRST_Xref xref
);

BRST_STATUS
BRST_NameTree_Add(
    BRST_NameTree tree,
    BRST_String   name,
    void*         obj
);

BRST_STATUS
BRST_NameTree_Add_String(
    BRST_NameTree tree,
    const char*   name,
    const char*   value
);

BRST_BOOL
BRST_NameTree_Validate(
    BRST_NameTree tree
);

#endif /* PRIVATE_BRST_NAME_TREE_H */