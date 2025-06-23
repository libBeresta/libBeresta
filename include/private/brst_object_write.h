#ifndef PRIVATE_BRST_OBJECT_WRITE_H
#define PRIVATE_BRST_OBJECT_WRITE_H

#include "brst_types.h"
#include "brst_stream.h"
#include "brst_encrypt.h"

BRST_STATUS
BRST_Obj_WriteValue(
    void*        obj,
    BRST_Stream  stream,
    BRST_Encrypt e
);

BRST_STATUS
BRST_Obj_Write(
    void*        obj,
    BRST_Stream  stream,
    BRST_Encrypt e
);

#endif /* PRIVATE_BRST_OBJECT_WRITE_H */