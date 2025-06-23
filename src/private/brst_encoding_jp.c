#include "brst_external.h"
#include "brst_types.h"
#include "brst_mmgr.h"
#include "brst_encrypt.h"
#include "brst_stream.h"
#include "brst_dict.h"
#include "brst_xref.h"
#include "brst_encoder.h"
#include "brst_error.h"
#include "brst_consts.h"
#include "private/brst_utils.h"
#include "brst_page.h"
#include "private/brst_encrypt_dict.h"
#include "brst_outline.h"
#include "private/brst_catalog.h"
#include "private/brst_pdfa.h"
#include "brst_pdfa.h"
#include "brst_doc.h"
#include "private/brst_doc.h"
#include "private/brst_encoder_cmap.h"
#include "private/brst_doc_encoder.h"
#include "brst_base.h"
#include "private/brst_encoding_jp.h"

#include "../src/private/data/encoder_jp.data"

static const BRST_CidRange_Rec MS_RKSJ_NOTDEF_RANGE  = { 0x00, 0x1F, 231 };
static const BRST_CidRange_Rec MSP_RKSJ_NOTDEF_RANGE = { 0x00, 0x1F, 1 };
static const BRST_CidRange_Rec EUC_NOTDEF_RANGE      = { 0x00, 0x1F, 231 };

static BRST_BOOL
RKSJ_IsLeadByte(BRST_Encoder encoder,
    BRST_BYTE b);

static BRST_BOOL
RKSJ_IsTrialByte(BRST_Encoder encoder,
    BRST_BYTE b);

static BRST_STATUS
RKSJ_AddCodeSpaceRange(BRST_Encoder encoder);

static BRST_BOOL
EUC_IsLeadByte(BRST_Encoder encoder,
    BRST_BYTE b);

static BRST_BOOL
EUC_IsTrialByte(BRST_Encoder encoder,
    BRST_BYTE b);

static BRST_STATUS
EUC_AddCodeSpaceRange(BRST_Encoder encoder);

/*--------------------------------------------------------------------------*/

static BRST_BOOL
RKSJ_IsLeadByte(BRST_Encoder encoder,
    BRST_BYTE b)
{
    BRST_UNUSED(encoder);
    return ((b >= 0x81 && b <= 0x9f) || (b >= 0xe0 && b <= 0xfc));
}

static BRST_BOOL
RKSJ_IsTrialByte(BRST_Encoder encoder,
    BRST_BYTE b)
{
    BRST_UNUSED(encoder);
    return (b >= 0x40 && b <= 0xfc && b != 0x7f);
}

static BRST_STATUS
RKSJ_AddCodeSpaceRange(BRST_Encoder encoder)
{
    BRST_CidRange_Rec code_space_range1 = { 0x00, 0x80, 0 };
    BRST_CidRange_Rec code_space_range2 = { 0x8140, 0x9FFC, 0 };
    BRST_CidRange_Rec code_space_range3 = { 0xA0, 0xDF, 0 };
    BRST_CidRange_Rec code_space_range4 = { 0xE040, 0xFCFC, 0 };

    if (BRST_CMapEncoder_AddCodeSpaceRange(encoder, code_space_range1)
        != BRST_OK)
        return BRST_Error_Code(encoder->error);

    if (BRST_CMapEncoder_AddCodeSpaceRange(encoder, code_space_range2)
        != BRST_OK)
        return BRST_Error_Code(encoder->error);

    if (BRST_CMapEncoder_AddCodeSpaceRange(encoder, code_space_range3)
        != BRST_OK)
        return BRST_Error_Code(encoder->error);

    if (BRST_CMapEncoder_AddCodeSpaceRange(encoder, code_space_range4)
        != BRST_OK)
        return BRST_Error_Code(encoder->error);

    return BRST_OK;
}

BRST_STATUS
MS_RKSJ_H_Init(BRST_Encoder encoder)
{
    BRST_CMapEncoderAttr attr;
    BRST_STATUS ret;

    if ((ret = BRST_CMapEncoder_InitAttr(encoder)) != BRST_OK)
        return ret;

    attr = (BRST_CMapEncoderAttr)encoder->attr;

    if (BRST_CMapEncoder_AddCMap(encoder, CMAP_ARRAY_90ms_RKSJ_H) != BRST_OK)
        return BRST_Error_Code(encoder->error);

    if ((ret = RKSJ_AddCodeSpaceRange(encoder)) != BRST_OK)
        return ret;

    if (BRST_CMapEncoder_AddNotDefRange(encoder, MS_RKSJ_NOTDEF_RANGE)
        != BRST_OK)
        return BRST_Error_Code(encoder->error);

    BRST_CMapEncoder_SetUnicodeArray(encoder, CP932_UNICODE_ARRAY);

    attr->is_lead_byte_fn  = RKSJ_IsLeadByte;
    attr->is_trial_byte_fn = RKSJ_IsTrialByte;
    BRST_StrCpy(attr->registry, "Adobe", attr->registry + BRST_LIMIT_MAX_NAME_LEN);
    BRST_StrCpy(attr->ordering, "Japan1", attr->ordering + BRST_LIMIT_MAX_NAME_LEN);
    attr->suppliment = 2;
    attr->uid_offset = 950;
    attr->xuid[0]    = 1;
    attr->xuid[1]    = 10;
    attr->xuid[2]    = 25343;

    encoder->type = BRST_ENCODER_TYPE_DOUBLE_BYTE;

    BRST_CMapEncoder_AddJWWLineHead(encoder, JWW_LINE_HEAD_SJIS);

    return BRST_OK;
}

BRST_STATUS
MSP_RKSJ_H_Init(BRST_Encoder encoder)
{
    BRST_CMapEncoderAttr attr;
    BRST_STATUS ret;

    if ((ret = BRST_CMapEncoder_InitAttr(encoder)) != BRST_OK)
        return ret;

    attr = (BRST_CMapEncoderAttr)encoder->attr;

    if ((ret = BRST_CMapEncoder_AddCMap(encoder, CMAP_ARRAY_90msp_RKSJ_H)) != BRST_OK)
        return ret;

    if ((ret = RKSJ_AddCodeSpaceRange(encoder)) != BRST_OK)
        return ret;

    if (BRST_CMapEncoder_AddNotDefRange(encoder, MSP_RKSJ_NOTDEF_RANGE)
        != BRST_OK)
        return BRST_Error_Code(encoder->error);

    BRST_CMapEncoder_SetUnicodeArray(encoder, CP932_UNICODE_ARRAY);

    attr->is_lead_byte_fn  = RKSJ_IsLeadByte;
    attr->is_trial_byte_fn = RKSJ_IsTrialByte;
    BRST_StrCpy(attr->registry, "Adobe", attr->registry + BRST_LIMIT_MAX_NAME_LEN);
    BRST_StrCpy(attr->ordering, "Japan1", attr->ordering + BRST_LIMIT_MAX_NAME_LEN);
    attr->suppliment = 2;
    attr->uid_offset = 950;
    attr->xuid[0]    = 1;
    attr->xuid[1]    = 10;
    attr->xuid[2]    = 25445;

    encoder->type = BRST_ENCODER_TYPE_DOUBLE_BYTE;

    BRST_CMapEncoder_AddJWWLineHead(encoder, JWW_LINE_HEAD_SJIS);

    return BRST_OK;
}

BRST_STATUS
MS_RKSJ_V_Init(BRST_Encoder encoder)
{
    BRST_CMapEncoderAttr attr;
    BRST_STATUS ret;

    if ((ret = BRST_CMapEncoder_InitAttr(encoder)) != BRST_OK)
        return ret;

    attr = (BRST_CMapEncoderAttr)encoder->attr;

    if ((ret = BRST_CMapEncoder_AddCMap(encoder, CMAP_ARRAY_90ms_RKSJ_H)) != BRST_OK)
        return ret;

    if ((ret = BRST_CMapEncoder_AddCMap(encoder, CMAP_ARRAY_90ms_RKSJ_V)) != BRST_OK)
        return ret;

    if ((ret = RKSJ_AddCodeSpaceRange(encoder)) != BRST_OK)
        return ret;

    if (BRST_CMapEncoder_AddNotDefRange(encoder, MS_RKSJ_NOTDEF_RANGE)
        != BRST_OK)
        return BRST_Error_Code(encoder->error);

    BRST_CMapEncoder_SetUnicodeArray(encoder, CP932_UNICODE_ARRAY);

    attr->is_lead_byte_fn  = RKSJ_IsLeadByte;
    attr->is_trial_byte_fn = RKSJ_IsTrialByte;
    BRST_StrCpy(attr->registry, "Adobe", attr->registry + BRST_LIMIT_MAX_NAME_LEN);
    BRST_StrCpy(attr->ordering, "Japan1", attr->ordering + BRST_LIMIT_MAX_NAME_LEN);
    attr->suppliment = 2;
    attr->uid_offset = 1020;
    attr->xuid[0]    = 1;
    attr->xuid[1]    = 10;
    attr->xuid[2]    = 25344;

    attr->writing_mode = BRST_WMODE_VERTICAL;

    encoder->type = BRST_ENCODER_TYPE_DOUBLE_BYTE;

    BRST_CMapEncoder_AddJWWLineHead(encoder, JWW_LINE_HEAD_SJIS);

    return BRST_OK;
}

static BRST_BOOL
EUC_IsLeadByte(BRST_Encoder encoder,
    BRST_BYTE b)
{
    BRST_UNUSED(encoder);
    return ((b >= 0xa1 && b <= 0xfe) || b == 0x8e);
}

static BRST_BOOL
EUC_IsTrialByte(BRST_Encoder encoder,
    BRST_BYTE b)
{
    BRST_UNUSED(encoder);
    return (b >= 0xa0 && b <= 0xfe);
}

static BRST_STATUS
EUC_AddCodeSpaceRange(BRST_Encoder encoder)
{
    BRST_CidRange_Rec code_space_range1 = { 0x00, 0x80, 0 };
    BRST_CidRange_Rec code_space_range2 = { 0x8EA0, 0x8EDF, 0 };
    BRST_CidRange_Rec code_space_range3 = { 0xA1A1, 0xFEFE, 0 };

    if (BRST_CMapEncoder_AddCodeSpaceRange(encoder, code_space_range1)
        != BRST_OK)
        return BRST_Error_Code(encoder->error);

    if (BRST_CMapEncoder_AddCodeSpaceRange(encoder, code_space_range2)
        != BRST_OK)
        return BRST_Error_Code(encoder->error);

    if (BRST_CMapEncoder_AddCodeSpaceRange(encoder, code_space_range3)
        != BRST_OK)
        return BRST_Error_Code(encoder->error);

    return BRST_OK;
}

BRST_STATUS
EUC_H_Init(BRST_Encoder encoder)
{
    BRST_CMapEncoderAttr attr;
    BRST_STATUS ret;

    if ((ret = BRST_CMapEncoder_InitAttr(encoder)) != BRST_OK)
        return ret;

    attr = (BRST_CMapEncoderAttr)encoder->attr;

    if (BRST_CMapEncoder_AddCMap(encoder, CMAP_ARRAY_EUC_H) != BRST_OK)
        return BRST_Error_Code(encoder->error);

    if ((ret = EUC_AddCodeSpaceRange(encoder)) != BRST_OK)
        return ret;

    if (BRST_CMapEncoder_AddNotDefRange(encoder, EUC_NOTDEF_RANGE) != BRST_OK)
        return BRST_Error_Code(encoder->error);

    BRST_CMapEncoder_SetUnicodeArray(encoder, EUC_UNICODE_ARRAY);

    attr->is_lead_byte_fn  = EUC_IsLeadByte;
    attr->is_trial_byte_fn = EUC_IsTrialByte;
    BRST_StrCpy(attr->registry, "Adobe", attr->registry + BRST_LIMIT_MAX_NAME_LEN);
    BRST_StrCpy(attr->ordering, "Japan1", attr->ordering + BRST_LIMIT_MAX_NAME_LEN);
    attr->suppliment = 1;
    attr->uid_offset = 680;
    attr->xuid[0]    = 1;
    attr->xuid[1]    = 10;
    attr->xuid[2]    = 25329;

    encoder->type = BRST_ENCODER_TYPE_DOUBLE_BYTE;

    BRST_CMapEncoder_AddJWWLineHead(encoder, JWW_LINE_HEAD_EUC);

    return BRST_OK;
}

BRST_STATUS
EUC_V_Init(BRST_Encoder encoder)
{
    BRST_CMapEncoderAttr attr;
    BRST_STATUS ret;

    if ((ret = BRST_CMapEncoder_InitAttr(encoder)) != BRST_OK)
        return ret;

    attr = (BRST_CMapEncoderAttr)encoder->attr;

    if (BRST_CMapEncoder_AddCMap(encoder, CMAP_ARRAY_EUC_H) != BRST_OK)
        return BRST_Error_Code(encoder->error);

    if (BRST_CMapEncoder_AddCMap(encoder, CMAP_ARRAY_EUC_V) != BRST_OK)
        return BRST_Error_Code(encoder->error);

    if ((ret = EUC_AddCodeSpaceRange(encoder)) != BRST_OK)
        return ret;

    if (BRST_CMapEncoder_AddNotDefRange(encoder, EUC_NOTDEF_RANGE) != BRST_OK)
        return BRST_Error_Code(encoder->error);

    BRST_CMapEncoder_SetUnicodeArray(encoder, EUC_UNICODE_ARRAY);

    attr->is_lead_byte_fn  = EUC_IsLeadByte;
    attr->is_trial_byte_fn = EUC_IsTrialByte;
    BRST_StrCpy(attr->registry, "Adobe", attr->registry + BRST_LIMIT_MAX_NAME_LEN);
    BRST_StrCpy(attr->ordering, "Japan1", attr->ordering + BRST_LIMIT_MAX_NAME_LEN);
    attr->suppliment   = 1;
    attr->writing_mode = BRST_WMODE_VERTICAL;
    attr->uid_offset   = 800;
    attr->xuid[0]      = 1;
    attr->xuid[1]      = 10;
    attr->xuid[2]      = 25330;

    encoder->type = BRST_ENCODER_TYPE_DOUBLE_BYTE;

    BRST_CMapEncoder_AddJWWLineHead(encoder, JWW_LINE_HEAD_EUC);

    return BRST_OK;
}
