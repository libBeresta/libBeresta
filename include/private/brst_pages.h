#ifndef PRIVATE_BRST_PAGES_H
#define PRIVATE_BRST_PAGES_H

#include "brst_dict.h"

typedef BRST_Dict BRST_Pages;

BRST_Pages
BRST_Pages_New(
    BRST_MMgr  mmgr,
    BRST_Pages parent,
    BRST_Xref  xref
);

BRST_BOOL
BRST_Pages_Validate(
    BRST_Pages pages
);

BRST_STATUS
BRST_Pages_AddKids(
    BRST_Pages parent,
    BRST_Dict  kid
);

struct _BRST_PageAttr_Rec;
typedef struct _BRST_PageAttr_Rec* BRST_PageAttr;

#endif /* PRIVATE_BRST_PAGES_H */
