#ifndef PRIVATE_BRST_ENCODER_CMAP_H
#define PRIVATE_BRST_ENCODER_CMAP_H

typedef struct _BRST_UnicodeMap_Rec {
    BRST_UINT16 code;
    BRST_UINT16 unicode;
} BRST_UnicodeMap_Rec;

typedef struct _BRST_CMapEncoderAttr_Rec {
    BRST_UNICODE                   unicode_map[256][256];
    BRST_UINT16                    cid_map[256][256];
    BRST_UINT16                    jww_line_head[BRST_MAX_JWW_NUM];
    BRST_List                      cmap_range;
    BRST_List                      notdef_range;
    BRST_List                      code_space_range;
    BRST_WritingMode               writing_mode;
    char                           registry[BRST_LIMIT_MAX_NAME_LEN + 1];
    char                           ordering[BRST_LIMIT_MAX_NAME_LEN + 1];
    BRST_INT                       suppliment;
    BRST_CMapEncoder_ByteType_Func is_lead_byte_fn;
    BRST_CMapEncoder_ByteType_Func is_trial_byte_fn;
    BRST_INT                       uid_offset;
    BRST_UINT                      xuid[3];
} BRST_CMapEncoderAttr_Rec;
typedef struct _BRST_CMapEncoderAttr_Rec* BRST_CMapEncoderAttr;

typedef struct _BRST_CidRange_Rec {
    BRST_UINT16 from;
    BRST_UINT16 to;
    BRST_UINT16 cid;
} BRST_CidRange_Rec;

BRST_Encoder
BRST_CMapEncoder_New(
    BRST_MMgr mmgr,
    char* name,
    BRST_Encoder_Init_Func init_fn);

BRST_STATUS
BRST_CMapEncoder_InitAttr(
    BRST_Encoder encoder);

void BRST_CMapEncoder_Free(
    BRST_Encoder encoder);

BRST_STATUS
BRST_CMapEncoder_Write(
    BRST_Encoder encoder,
    BRST_Stream out);

BRST_UNICODE
BRST_CMapEncoder_ToUnicode(
    BRST_Encoder encoder,
    BRST_UINT16 code);

BRST_UINT16
BRST_CMapEncoder_ToCID(
    BRST_Encoder encoder,
    BRST_UINT16 code);

BRST_STATUS
BRST_CMapEncoder_SetParseText(
    BRST_Encoder encoder,
    BRST_ParseText_Rec* state,
    const BRST_BYTE* text,
    BRST_UINT len);

BRST_ByteType
BRST_CMapEncoder_ByteType(
    BRST_Encoder encoder,
    BRST_ParseText_Rec* state);

BRST_STATUS
BRST_CMapEncoder_AddCMap(
    BRST_Encoder encoder,
    const BRST_CidRange_Rec* range);

BRST_STATUS
BRST_CMapEncoder_AddNotDefRange(
    BRST_Encoder encoder,
    BRST_CidRange_Rec range);

BRST_STATUS
BRST_CMapEncoder_AddCodeSpaceRange(
    BRST_Encoder encoder,
    BRST_CidRange_Rec range);

void BRST_CMapEncoder_SetUnicodeArray(
    BRST_Encoder encoder,
    const BRST_UnicodeMap_Rec* array1);

BRST_STATUS
BRST_CMapEncoder_AddJWWLineHead(
    BRST_Encoder encoder,
    const BRST_UINT16* code);

// TODO Переименовать в BRST_CMapEncoder_CheckJWWLineHead?
BRST_BOOL
BRST_Encoder_CheckJWWLineHead(
    BRST_Encoder encoder,
    const BRST_UINT16 code);

#endif /* PRIVATE_BRST_ENCODER_CMAP_H */