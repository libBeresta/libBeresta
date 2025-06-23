#ifndef PRIVATE_BRST_DIRECT_H
#define PRIVATE_BRST_DIRECT_H

typedef struct _BRST_Direct_Rec {
    BRST_Obj_Header  header;
    BRST_MMgr        mmgr;
    BRST_Error       error;
    BRST_BYTE        *value;
    BRST_UINT        len;
} BRST_Direct_Rec;
typedef struct _BRST_Direct_Rec  *BRST_Direct;

BRST_Direct
BRST_Direct_New(
    BRST_MMgr  mmgr,
    BRST_BYTE* value,
    BRST_UINT  len
);

BRST_STATUS
BRST_Direct_SetValue(
    BRST_Direct obj,
    BRST_BYTE*  value,
    BRST_UINT   len
);

void
BRST_Direct_Free(
    BRST_Direct obj
);


BRST_STATUS
BRST_Direct_Write(
    BRST_Direct obj,
    BRST_Stream stream
);

#endif /* PRIVATE_BRST_DIRECT_H */