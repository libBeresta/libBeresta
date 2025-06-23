#ifndef PRIVATE_BRST_STREAM_H
#define PRIVATE_BRST_STREAM_H

#include "brst_types.h"
#include "brst_stream.h"
#include "brst_encrypt.h"
#include "private/brst_encrypt.h"
#include "private/brst_list.h"
#include "private/brst_mmgr.h"

#define BRST_STREAM_SIG_BYTES  0x5354524DL

#define BRST_STREAM_FILTER_NONE          0x0000
#define BRST_STREAM_FILTER_ASCIIHEX      0x0100
#define BRST_STREAM_FILTER_ASCII85       0x0200
#define BRST_STREAM_FILTER_FLATE_DECODE  0x0400
#define BRST_STREAM_FILTER_DCT_DECODE    0x0800
#define BRST_STREAM_FILTER_CCITT_DECODE  0x1000

typedef enum _BRST_WhenceMode {
    BRST_SEEK_SET = 0,
    BRST_SEEK_CUR,
    BRST_SEEK_END
} BRST_WhenceMode;

typedef BRST_STATUS
(*BRST_Stream_Write_Func) (
    BRST_Stream      stream,
    const BRST_BYTE* ptr,
    BRST_UINT        size
);

typedef BRST_STATUS
(*BRST_Stream_Read_Func) (
    BRST_Stream stream,
    BRST_BYTE*  ptr,
    BRST_UINT*  size
);

typedef BRST_STATUS
(*BRST_Stream_Seek_Func) (
    BRST_Stream     stream,
    BRST_INT        pos,
    BRST_WhenceMode mode
);

typedef BRST_INT32
(*BRST_Stream_Tell_Func) (
    BRST_Stream stream
);

typedef void
(*BRST_Stream_Free_Func) (
    BRST_Stream stream
);

typedef BRST_UINT32
(*BRST_Stream_Size_Func) (
    BRST_Stream stream
);

typedef enum _BRST_StreamType {
    BRST_STREAM_UNKNOWN = 0,
    BRST_STREAM_CALLBACK,
    BRST_STREAM_FILE,
    BRST_STREAM_MEMORY
} BRST_StreamType;

typedef struct _BRST_Stream_Rec {
    BRST_UINT32               sig_bytes;
    BRST_StreamType           type;
    BRST_MMgr                 mmgr;
    BRST_Error                error;
    BRST_UINT                 size;
    BRST_Stream_Write_Func    write_fn;
    BRST_Stream_Read_Func     read_fn;
    BRST_Stream_Seek_Func     seek_fn;
    BRST_Stream_Free_Func     free_fn;
    BRST_Stream_Tell_Func     tell_fn;
    BRST_Stream_Size_Func     size_fn;
    void*                     attr;
} BRST_Stream_Rec;

typedef struct _BRST_MemStreamAttr_Rec {
    BRST_List  buf;
    BRST_UINT  buf_size;
    BRST_UINT  w_pos;
    BRST_BYTE  *w_ptr;
    BRST_UINT  r_ptr_idx;
    BRST_UINT  r_pos;
    BRST_BYTE  *r_ptr;
} BRST_MemStreamAttr_Rec;
typedef struct _BRST_MemStreamAttr_Rec *BRST_MemStreamAttr;

typedef BRST_Stream_Write_Func BRST_Stream_Write_Func;
typedef BRST_Stream_Seek_Func  BRST_Stream_Seek_Func;
typedef BRST_Stream_Tell_Func  BRST_Stream_Tell_Func;
typedef BRST_Stream_Size_Func  BRST_Stream_Size_Func;
typedef BRST_Stream_Read_Func  BRST_Stream_Read_Func;

BRST_Stream
BRST_MemStream_New(
    BRST_MMgr mmgr,
    BRST_UINT buf_size
);

BRST_BYTE*
BRST_MemStream_GetBufPtr(
    BRST_Stream stream,
    BRST_UINT   index,
    BRST_UINT*  length
);

BRST_UINT
BRST_MemStream_GetBufSize(
    BRST_Stream stream
);

BRST_UINT
BRST_MemStream_GetBufCount(
    BRST_Stream stream
);

BRST_STATUS
BRST_MemStream_Rewrite(
    BRST_Stream stream,
    BRST_BYTE*  buf,
    BRST_UINT   size
);

void
BRST_MemStream_FreeData(
    BRST_Stream stream
);

BRST_Stream
BRST_FileReader_New(
    BRST_MMgr   mmgr,
    const char* fname
);

BRST_Stream
BRST_FileWriter_New(
    BRST_MMgr   mmgr,
    const char* fname
);

BRST_Stream
BRST_CallbackReader_New(
    BRST_MMgr             mmgr,
    BRST_Stream_Read_Func read_fn,
    BRST_Stream_Seek_Func seek_fn,
    BRST_Stream_Tell_Func tell_fn,
    BRST_Stream_Size_Func size_fn,
    void*                 data
);

BRST_Stream
BRST_CallbackWriter_New(
    BRST_MMgr              mmgr,
    BRST_Stream_Write_Func write_fn,
    void*                  data
);

void
BRST_Stream_Free(
    BRST_Stream stream
);

BRST_STATUS
BRST_Stream_WriteChar(
    BRST_Stream stream,
    char        value
);

BRST_STATUS
BRST_Stream_WriteStr(
    BRST_Stream stream,
    const char* value);

BRST_STATUS
BRST_Stream_WriteUChar(
    BRST_Stream stream,
    BRST_BYTE   value
);

BRST_STATUS
BRST_Stream_WriteInt(
    BRST_Stream stream,
    BRST_INT    value
);

BRST_STATUS
BRST_Stream_WriteUInt(
    BRST_Stream stream,
    BRST_UINT   value
);

BRST_STATUS
BRST_Stream_WriteReal(
    BRST_Stream stream,
    BRST_REAL   value
);

BRST_STATUS
BRST_Stream_Write(
    BRST_Stream      stream,
    const BRST_BYTE* ptr,
    BRST_UINT        size
);

BRST_STATUS
BRST_Stream_Read(
    BRST_Stream stream,
    BRST_BYTE*  ptr,
    BRST_UINT*  size
);

BRST_STATUS
BRST_Stream_ReadLn(
    BRST_Stream stream,
    char*       s,
    BRST_UINT*  size
);

BRST_INT32
BRST_Stream_Tell(
    BRST_Stream stream
);

BRST_STATUS
BRST_Stream_Seek(
    BRST_Stream     stream,
    BRST_INT        pos,
    BRST_WhenceMode mode
);

BRST_BOOL
BRST_Stream_EOF(
    BRST_Stream stream
);

BRST_UINT32
BRST_Stream_Size(
    BRST_Stream stream
);

BRST_STATUS
BRST_Stream_Flush(
    BRST_Stream stream
);

BRST_STATUS
BRST_Stream_WriteEscapeName(
    BRST_Stream stream,
    const char* value
);

BRST_STATUS
BRST_Stream_WriteEscapeText2(
    BRST_Stream stream,
    const char* text,
    BRST_UINT   len
);

BRST_STATUS
BRST_Stream_WriteEscapeText(
    BRST_Stream stream,
    const char* text
);

BRST_STATUS
BRST_Stream_Validate(
    BRST_Stream stream
);

BRST_STATUS
BRST_Stream_WriteBinary(
    BRST_Stream      stream,
    const BRST_BYTE* data,
    BRST_UINT        len,
    BRST_Encrypt     e
);

BRST_STATUS
BRST_Stream_WriteToStream(
    BRST_Stream  src,
    BRST_Stream  dst,
    BRST_UINT    filter,
    BRST_Encrypt e
);

#endif /* PRIVATE_BRST_STREAM_H */
