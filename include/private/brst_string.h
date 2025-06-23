#ifndef PRIVATE_BRST_STRING_H
#define PRIVATE_BRST_STRING_H

#include "brst_encoder.h"

struct _BRST_String_Rec;
typedef struct _BRST_String_Rec* BRST_String;

BRST_String
BRST_String_New(
    BRST_MMgr    mmgr,
    const char*  value,
    BRST_Encoder encoder
);

BRST_STATUS
BRST_String_SetValue(
    BRST_String obj,
    const char* value
);

void
BRST_String_Free(
    BRST_String obj
);

BRST_INT32
BRST_String_Cmp(
    BRST_String s1,
    BRST_String s2
);

BRST_STATUS
BRST_String_Write(
    BRST_String  obj,
    BRST_Stream  stream,
    BRST_Encrypt e
);

const char*
BRST_String_Value(
    BRST_String string
);


#endif /* PRIVATE_BRST_STRING_H */