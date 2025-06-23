#ifndef PRIVATE_BRST_NULL_H
#define PRIVATE_BRST_NULL_H

#include "private/brst_object.h"
#include "brst_mmgr.h"

struct _BRST_Null_Rec;
typedef struct _BRST_Null_Rec* BRST_Null;

BRST_Null
BRST_Null_New(
    BRST_MMgr mmgr
);

#endif /* PRIVATE_BRST_NULL_H */