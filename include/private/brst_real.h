#ifndef PRIVATE_BRST_REAL_H
#define PRIVATE_BRST_REAL_H

#include "private/brst_object.h"

typedef struct _BRST_Real_Rec* BRST_Real;

BRST_Real
BRST_Real_New(
    BRST_MMgr mmgr,
    BRST_REAL value
);

BRST_STATUS
BRST_Real_Write(
    BRST_Real   obj,
    BRST_Stream stream
);

BRST_STATUS
BRST_Real_SetValue(
    BRST_Real obj,
    BRST_REAL value
);

BRST_REAL
BRST_Real_Value(
    BRST_Real obj
);

#endif /* PRIVATE_BRST_REAL_H */