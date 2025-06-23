#ifndef PRIVATE_BRST_BOOLEAN_H
#define PRIVATE_BRST_BOOLEAN_H

#include "brst_stream.h"

struct _BRST_Boolean_Rec;
typedef struct _BRST_Boolean_Rec* BRST_Boolean;

BRST_Boolean
BRST_Boolean_New(
    BRST_MMgr mmgr,
    BRST_BOOL value
);

BRST_STATUS
BRST_Boolean_Write(
    BRST_Boolean obj,
    BRST_Stream  stream
);

void
BRST_Boolean_SetValue(
    BRST_Boolean obj,
    BRST_BOOL value
);

BRST_BOOL
BRST_Boolean_Value(
    BRST_Boolean obj
);

#endif /* PRIVATE_BRST_BOOLEAN_H */