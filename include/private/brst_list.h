#ifndef PRIVATE_BRST_LIST_H
#define PRIVATE_BRST_LIST_H

#include "brst_error.h"
#include "brst_mmgr.h"
#include "brst_types.h"

struct _BRST_List_Rec;
typedef struct _BRST_List_Rec *BRST_List;

BRST_List
BRST_List_New(
    BRST_MMgr mmgr,
    BRST_UINT items_per_block
);

void
BRST_List_Free(
    BRST_List list
);

BRST_STATUS
BRST_List_Add(
    BRST_List list,
    void*     item
);

BRST_STATUS
BRST_List_Insert(
    BRST_List list,
    void*     target,
    void*     item
);

BRST_STATUS
BRST_List_Remove(
    BRST_List list,
    void*     item
);

void*
BRST_List_RemoveByIndex(
    BRST_List list,
    BRST_UINT index
);

void*
BRST_List_ItemAt(
    BRST_List list,
    BRST_UINT index
);

BRST_INT32
BRST_List_Find(
    BRST_List list,
    void*     item
);

void
BRST_List_Clear(
    BRST_List list
);

BRST_INT32
BRST_List_Count(
    BRST_List list
);

#endif /* PRIVATE_BRST_LIST_H */