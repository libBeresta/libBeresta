#ifndef PRIVATE_BRST_DICT_H
#define PRIVATE_BRST_DICT_H

#include "brst_dict.h"
#include "brst_list.h"
#include "brst_mmgr.h"
#include "brst_encrypt.h"
#include "private/brst_object.h"

struct _BRST_Dict_Rec;

typedef void
(*BRST_Dict_FreeFunc) (
    BRST_Dict obj
);

typedef BRST_STATUS
(*BRST_Dict_BeforeWriteFunc) (
    BRST_Dict obj
);

typedef BRST_STATUS
(*BRST_Dict_AfterWriteFunc) (
    BRST_Dict obj
);

typedef BRST_STATUS
(*BRST_Dict_OnWriteFunc) (
    BRST_Dict   obj,
    BRST_Stream stream
);

typedef struct _BRST_Dict_Rec {
    BRST_Obj_Header           header;
    BRST_MMgr                 mmgr;
    BRST_Error                error;
    BRST_List                 list;
    BRST_Dict_BeforeWriteFunc before_write_fn;
    BRST_Dict_OnWriteFunc     write_fn;
    BRST_Dict_AfterWriteFunc  after_write_fn;
    BRST_Dict_FreeFunc        free_fn;
    BRST_Stream               stream;
    BRST_UINT                 filter;
    BRST_Dict                 filterParams;
    void*                     attr;
} BRST_Dict_Rec;

typedef struct _BRST_DictElement_Rec* BRST_DictElement;

BRST_Dict
BRST_Dict_New(
    BRST_MMgr mmgr
);

void
BRST_Dict_Free(
    BRST_Dict dict
);

BRST_STATUS
BRST_Dict_Write(
    BRST_Dict    dict,
    BRST_Stream  stream,
    BRST_Encrypt e
);

const char*
BRST_Dict_KeyByObj(
    BRST_Dict dict,
    void*     obj
);

BRST_STATUS
BRST_Dict_Add(
    BRST_Dict   dict,
    const char* key,
    void*       obj
);

void*
BRST_Dict_Item(
    BRST_Dict   dict,
    const char* key,
    BRST_UINT16 obj_class
);

BRST_STATUS
BRST_Dict_AddName(
    BRST_Dict   dict,
    const char* key,
    const char* value
);

BRST_STATUS
BRST_Dict_AddNumber(
    BRST_Dict   dict,
    const char* key,
    BRST_INT32  value
);

BRST_STATUS
BRST_Dict_AddReal(
    BRST_Dict   dict,
    const char* key,
    BRST_REAL   value
);

BRST_STATUS
BRST_Dict_AddBoolean(
    BRST_Dict   dict,
    const char* key,
    BRST_BOOL   value
);

BRST_STATUS
BRST_Dict_RemoveElement(
    BRST_Dict   dict,
    const char* key
);

BRST_Stream
BRST_Dict_Stream(
    BRST_Dict dict
);

void
BRST_Dict_SetStream(
    BRST_Dict dict,
    BRST_Stream stream
);

#endif /* PRIVATE_BRST_DICT_H */
