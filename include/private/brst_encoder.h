#ifndef PRIVATE_BRST_ENCODER_H
#define PRIVATE_BRST_ENCODER_H

#include "brst_types.h"
#include "brst_stream.h"
#include "brst_encoder.h"
#include "private/brst_defines.h"

typedef struct _BRST_ParseText_Rec {
    const BRST_BYTE* text;
    BRST_UINT        index;
    BRST_UINT        len;
    BRST_ByteType    byte_type;
} BRST_ParseText_Rec;

typedef struct _BRST_BuiltinEncodingData {
    const char* encoding_name;
    BRST_BaseEncodings base_encoding;
    const BRST_UNICODE* ovewrride_map;
} BRST_BuiltinEncodingData;

typedef struct _BRST_UnicodeGlyphPair {
    BRST_UNICODE unicode;
    const char* glyph_name;
} BRST_UnicodeGlyphPair;

struct _BRST_CidRange_Rec;

typedef struct _BRST_BasicEncoderAttr_Rec* BRST_BasicEncoderAttr;
typedef struct _BRST_CidRange_Rec   BRST_CidRange_Rec;

typedef BRST_ByteType
(*BRST_Encoder_ByteType_Func)  (BRST_Encoder        encoder,
                                BRST_ParseText_Rec* state);

typedef BRST_UNICODE
(*BRST_Encoder_ToUnicode_Func)  (BRST_Encoder   encoder,
                                 BRST_UINT16    code);

typedef char *
(*BRST_Encoder_EncodeText_Func)  (BRST_Encoder  encoder,
				  const char   *text,
				  BRST_UINT     len,
				  BRST_UINT    *encoded_length);

typedef BRST_STATUS
(*BRST_Encoder_Write_Func)  (BRST_Encoder  encoder,
                             BRST_Stream   out);

typedef void
(*BRST_Encoder_Free_Func)  (BRST_Encoder  encoder);

typedef struct _BRST_Encoder_Rec {
    BRST_UINT32                     sig_bytes;
    char                            name[BRST_LIMIT_MAX_NAME_LEN + 1];
    BRST_MMgr                       mmgr;
    BRST_Error                      error;
    BRST_EncoderType                type;

    BRST_Encoder_ByteType_Func      byte_type_fn;
    BRST_Encoder_ToUnicode_Func     to_unicode_fn;
    BRST_Encoder_EncodeText_Func    encode_text_fn;
    BRST_Encoder_Write_Func         write_fn;
    BRST_Encoder_Free_Func          free_fn;
    BRST_Encoder_Init_Func          init_fn;
    /*
    char                         lang_code[3];
    char                         country_code[3];
    */
    void                            *attr;
} BRST_Encoder_Rec;

typedef BRST_BOOL
(*BRST_CMapEncoder_ByteType_Func)  (BRST_Encoder  encoder,
                                    BRST_BYTE     b);

BRST_STATUS
BRST_Encoder_Validate(
    BRST_Encoder encoder
);

void
BRST_Encoder_SetParseText(
    BRST_Encoder        encoder,
    BRST_ParseText_Rec *state,
    const BRST_BYTE    *text,
    BRST_UINT           len
);

BRST_ByteType
BRST_Encoder_ByteType_Internal(
    BRST_Encoder        encoder,
    BRST_ParseText_Rec* state
);

BRST_UNICODE
BRST_Encoder_ToUnicode(
    BRST_Encoder encoder,
    BRST_UINT16  code
);

void
BRST_Encoder_Free(
    BRST_Encoder encoder
);

#endif /* PRIVATE_BRST_ENCODER_H */
