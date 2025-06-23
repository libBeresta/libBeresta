#ifndef PRIVATE_BRST_BINARY_H
#define PRIVATE_BRST_BINARY_H

#include "brst_types.h"
#include "brst_mmgr.h"
#include "brst_encrypt.h"

struct _BRST_Binary_Rec;
typedef struct _BRST_Binary_Rec *BRST_Binary;

BRST_Binary
BRST_Binary_New(
    BRST_MMgr  mmgr,
    BRST_BYTE* value,
    BRST_UINT  len
);

BRST_STATUS
BRST_Binary_SetValue(
    BRST_Binary obj,
    BRST_BYTE*  value,
    BRST_UINT   len
);

BRST_BYTE*
BRST_Binary_Value(
    BRST_Binary obj
);

void
BRST_Binary_Free(
    BRST_Binary obj
);

BRST_STATUS
BRST_Binary_Write(
    BRST_Binary  obj,
    BRST_Stream  stream,
    BRST_Encrypt e
);

BRST_UINT
BRST_Binary_Len(
    BRST_Binary obj
);
#endif