#ifndef PRIVATE_BRST_ENCODER_BASIC_H
#define PRIVATE_BRST_ENCODER_BASIC_H

#include "brst_mmgr.h"
#include "brst_encoder.h"
#include "brst_stream.h"
#include "brst_types.h"
#include "private/brst_encoder.h"

typedef struct _BRST_BasicEncoderAttr_Rec {
      char         base_encoding[BRST_LIMIT_MAX_NAME_LEN + 1];
      BRST_BYTE    first_char;
      BRST_BYTE    last_char;
      BRST_UNICODE unicode_map[256];
      BRST_BOOL    has_differences;
      BRST_BYTE    differences[256];
} BRST_BasicEncoderAttr_Rec;

BRST_Encoder
BRST_BasicEncoder_New(
    BRST_MMgr   mmgr,
    const char *encoding_name
);

void
BRST_BasicEncoder_Free(
    BRST_Encoder encoder
);

BRST_STATUS
BRST_BasicEncoder_Write(
    BRST_Encoder encoder,
    BRST_Stream  out
);


BRST_UNICODE
BRST_BasicEncoder_ToUnicode(
    BRST_Encoder encoder,
    BRST_UINT16  code
);

#endif /* PRIVATE_BRST_ENCODER_BASIC_H */