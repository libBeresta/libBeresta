#ifndef PRIVATE_BRST_NUMBER_H
#define PRIVATE_BRST_NUMBER_H

#include "private/brst_object.h"
#include "private/brst_number.h"

typedef struct _BRST_Number_Rec* BRST_Number;

BRST_Number
BRST_Number_New(
    BRST_MMgr  mmgr,
    BRST_INT32 value
);

void
BRST_Number_SetValue(
    BRST_Number obj,
    BRST_INT32  value
);

BRST_INT32
BRST_Number_Value(
    BRST_Number num
);

BRST_STATUS
BRST_Number_Write(
    BRST_Number obj,
    BRST_Stream stream
);

#endif /* PRIVATE_BRST_NUMBER_H */