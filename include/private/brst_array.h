#ifndef PRIVATE_BRST_ARRAY_H
#define PRIVATE_BRST_ARRAY_H

#include "brst_array.h"
#include "brst_types.h"
#include "brst_encrypt.h"
#include "private/brst_encrypt.h"
#include "brst_stream.h"
#include "brst_error.h"
#include "brst_list.h"
#include "brst_matrix.h"
#include "private/brst_matrix.h"

#include "brst_geometry_defines.h"

#include "private/brst_object.h"

typedef struct _BRST_Array_Rec {
    BRST_Obj_Header header;
    BRST_MMgr       mmgr;
    BRST_Error      error;
    BRST_List       list;
} BRST_Array_Rec;

BRST_Array
BRST_Array_New(
    BRST_MMgr mmgr
);

BRST_Array
BRST_Box_Array_New(
    BRST_MMgr mmgr,
    BRST_Box  box
);

BRST_Array
BRST_Matrix_Array_New(
    BRST_MMgr   mmgr,
    BRST_Matrix matrix
);

void
BRST_Array_Free(
    BRST_Array array
);

BRST_STATUS
BRST_Array_Write(
    BRST_Array   array,
    BRST_Stream  stream,
    BRST_Encrypt e
);

BRST_STATUS
BRST_Array_Add(
    BRST_Array array,
    void*      obj
);

BRST_STATUS
BRST_Array_Insert(
    BRST_Array array,
    void*      target,
    void*      obj
);

void*
BRST_Array_Item(
    BRST_Array  array,
    BRST_UINT   index,
    BRST_UINT16 obj_class
);

BRST_STATUS
BRST_Array_AddNumber(
    BRST_Array array,
    BRST_INT32 value
);

BRST_STATUS
BRST_Array_AddReal(
    BRST_Array array,
    BRST_REAL  value
);

BRST_STATUS
BRST_Array_AddNull(
    BRST_Array array
);

BRST_STATUS
BRST_Array_AddName(
    BRST_Array  array,
    const char* value
);

void
BRST_Array_Clear(
    BRST_Array array
);

BRST_UINT
BRST_Array_Count(
    BRST_Array array
);

#endif /* PRIVATE_BRST_ARRAY_H */