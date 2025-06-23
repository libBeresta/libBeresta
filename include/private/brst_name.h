#ifndef PRIVATE_BRST_NAME_H
#define PRIVATE_BRST_NAME_H

#include "brst_mmgr.h"
#include "brst_stream.h"

struct _BRST_Name_Rec;
typedef struct _BRST_Name_Rec *BRST_Name;

BRST_Name
BRST_Name_New(
    BRST_MMgr   mmgr,
    const char* value
);

BRST_STATUS
BRST_Name_SetValue(
    BRST_Name   obj,
    const char* value
);

BRST_STATUS
BRST_Name_Write(
    BRST_Name   obj,
    BRST_Stream stream
);

const char*
BRST_Name_Value(
    BRST_Name obj
);

#endif /* PRIVATE_BRST_NAME_H */