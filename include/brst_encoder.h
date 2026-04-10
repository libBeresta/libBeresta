#ifndef BRST_ENCODER_H
#define BRST_ENCODER_H

#include "brst_external.h"
#include "brst_types.h"
#include "brst_text_defines.h"

#define BRST_ENCODER_SIG_BYTES 0x454E4344L // ENCD

#define  BRST_ENCODING_FONT_SPECIFIC  "FontSpecific"
#define  BRST_ENCODING_STANDARD       "StandardEncoding"
#define  BRST_ENCODING_MAC_ROMAN      "MacRomanEncoding"
#define  BRST_ENCODING_WIN_ANSI       "WinAnsiEncoding"
#define  BRST_ENCODING_ISO8859_2      "ISO8859-2"
#define  BRST_ENCODING_ISO8859_3      "ISO8859-3"
#define  BRST_ENCODING_ISO8859_4      "ISO8859-4"
#define  BRST_ENCODING_ISO8859_5      "ISO8859-5"
#define  BRST_ENCODING_ISO8859_6      "ISO8859-6"
#define  BRST_ENCODING_ISO8859_7      "ISO8859-7"
#define  BRST_ENCODING_ISO8859_8      "ISO8859-8"
#define  BRST_ENCODING_ISO8859_9      "ISO8859-9"
#define  BRST_ENCODING_ISO8859_10     "ISO8859-10"
#define  BRST_ENCODING_ISO8859_11     "ISO8859-11"
#define  BRST_ENCODING_ISO8859_13     "ISO8859-13"
#define  BRST_ENCODING_ISO8859_14     "ISO8859-14"
#define  BRST_ENCODING_ISO8859_15     "ISO8859-15"
#define  BRST_ENCODING_ISO8859_16     "ISO8859-16"
#define  BRST_ENCODING_CP1250         "CP1250"
#define  BRST_ENCODING_CP1251         "CP1251"
#define  BRST_ENCODING_CP1252         "CP1252"
#define  BRST_ENCODING_CP1253         "CP1253"
#define  BRST_ENCODING_CP1254         "CP1254"
#define  BRST_ENCODING_CP1255         "CP1255"
#define  BRST_ENCODING_CP1256         "CP1256"
#define  BRST_ENCODING_CP1257         "CP1257"
#define  BRST_ENCODING_CP1258         "CP1258"
#define  BRST_ENCODING_KOI8_R         "KOI8-R"

#define char_NOTDEF        ".notdef"

struct _BRST_Encoder_Rec;
typedef struct _BRST_Encoder_Rec* BRST_Encoder;

typedef BRST_STATUS
(*BRST_Encoder_Init_Func)  (BRST_Encoder  encoder);

typedef enum _BRST_EncodingType {
    BRST_STANDARD_ENCODING = 0,
    BRST_MAC_ROMAN_ENCODING,
    BRST_WIN_ANSI_ENCODING,
    BRST_FONT_SPECIFIC,
    BRST_ENCODING_EOF
} BRST_EncodingType;

typedef enum _BRST_BaseEncodings {
    BRST_BASE_ENCODING_STANDARD,
    BRST_BASE_ENCODING_WIN_ANSI,
    BRST_BASE_ENCODING_MAC_ROMAN,
    BRST_BASE_ENCODING_FONT_SPECIFIC,
    BRST_BASE_ENCODING_EOF
} BRST_BaseEncodings;

typedef enum _BRST_EncoderType {
    /// Single-byte character encoder
    BRST_ENCODER_TYPE_SINGLE_BYTE,
    /// Multi-byte character encoder
    BRST_ENCODER_TYPE_DOUBLE_BYTE,
    /// Encoder is not yet initialized
    BRST_ENCODER_TYPE_UNINITIALIZED,
    /// Encoder was not properly constructed
    BRST_ENCODER_UNKNOWN
} BRST_EncoderType;

typedef enum _BRST_ByteType {
    /// Single byte character.
    BRST_BYTE_TYPE_SINGLE = 0,
    /// Lead byte of a double-byte character.
    BRST_BYTE_TYPE_LEAD,
    /// Trailing byte of a double-byte character.
    BRST_BYTE_TYPE_TRAIL,
    /// Invalid encoder or cannot judge the byte type.
    BRST_BYTE_TYPE_UNKNOWN
} BRST_ByteType;

/**

  \ingroup encode
  \brief Get encoder object type.

  \copydoc dox_param_encoder

  \return Encoder object type value.

  \see \ref _BRST_EncoderType

*/
BRST_EXPORT(BRST_EncoderType)
BRST_Encoder_Type(
    BRST_Encoder encoder
);

/**

  \ingroup encode
  \brief Get byte type of a \c text char at \c index position.

  \copydoc dox_param_encoder
  \param text Text to analyze.
  \param index Character index.

  \return Character byte type value.

  \see \ref _BRST_ByteType

*/
BRST_EXPORT(BRST_ByteType)
BRST_Encoder_ByteType(
    BRST_Encoder encoder,
    BRST_CSTR    text,
    BRST_UINT    index
);

/**

  \ingroup encode
  \brief Convert a specified character code to Unicode value.

  \copydoc dox_param_encoder
  \param code Character code to convert.

  \return Character Unicode value.

*/
BRST_EXPORT(BRST_UNICODE)
BRST_Encoder_Unicode(
    BRST_Encoder encoder,
    BRST_UINT16  code
);

/**

  \ingroup encode
  \brief Get writing mode for the encoding object.

  \copydoc dox_param_encoder

  \return Encoder writing mode value.

  \see \ref _BRST_WritingMode
*/
BRST_EXPORT(BRST_WritingMode)
BRST_Encoder_WritingMode(
    BRST_Encoder encoder
);

#endif /* BRST_ENCODER_H */
