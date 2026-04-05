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

#include "../src/private/data/encoder_cns.data"

static const BRST_CidRange_Rec GBK_EUC_NOTDEF_RANGE = { 0x00, 0x1F, 7716 };
static const BRST_CidRange_Rec GB_EUC_NOTDEF_RANGE  = { 0x00, 0x1F, 7716 };

static BRST_BOOL
GBK_EUC_IsLeadByte(BRST_Encoder encoder,
    BRST_BYTE b);

static BRST_BOOL
GBK_EUC_IsTrialByte(BRST_Encoder encoder,
    BRST_BYTE b);

static BRST_STATUS
GBK_EUC_AddCodeSpaceRange(BRST_Encoder encoder);

static BRST_BOOL
GB_EUC_IsLeadByte(BRST_Encoder encoder,
    BRST_BYTE b);

static BRST_BOOL
GB_EUC_IsTrialByte(BRST_Encoder encoder,
    BRST_BYTE b);

static BRST_STATUS
GB_EUC_AddCodeSpaceRange(BRST_Encoder encoder);

/*--------------------------------------------------------------------------*/

static BRST_BOOL
GBK_EUC_IsLeadByte(BRST_Encoder encoder,
    BRST_BYTE b)
{
    BRST_UNUSED(encoder);
    return ((b >= 0x81 && b <= 0xfe));
}

static BRST_BOOL
GBK_EUC_IsTrialByte(BRST_Encoder encoder,
    BRST_BYTE b)
{
    BRST_UNUSED(encoder);
    return (b >= 0x40 && b <= 0xfe);
}

static BRST_STATUS
GBK_EUC_AddCodeSpaceRange(BRST_Encoder encoder)
{
    BRST_CidRange_Rec code_space_range1 = { 0x00, 0x80, 0 };
    BRST_CidRange_Rec code_space_range2 = { 0x8140, 0xFEFE, 0 };

    if (BRST_CMapEncoder_AddCodeSpaceRange(encoder, code_space_range1)
        != BRST_OK)
        return BRST_Error_Code(encoder->error);

    if (BRST_CMapEncoder_AddCodeSpaceRange(encoder, code_space_range2)
        != BRST_OK)
        return BRST_Error_Code(encoder->error);

    return BRST_OK;
}

BRST_STATUS
GBK_EUC_H_Init(BRST_Encoder encoder)
{
    BRST_CMapEncoderAttr attr;
    BRST_STATUS ret;

    if ((ret = BRST_CMapEncoder_InitAttr(encoder)) != BRST_OK)
        return ret;

    attr = (BRST_CMapEncoderAttr)encoder->attr;

    if (BRST_CMapEncoder_AddCMap(encoder, CMAP_ARRAY_GBK_EUC_H) != BRST_OK)
        return BRST_Error_Code(encoder->error);

    if ((ret = GBK_EUC_AddCodeSpaceRange(encoder)) != BRST_OK)
        return ret;

    if (BRST_CMapEncoder_AddNotDefRange(encoder, GBK_EUC_NOTDEF_RANGE)
        != BRST_OK)
        return BRST_Error_Code(encoder->error);

    BRST_CMapEncoder_SetUnicodeArray(encoder, CP936_UNICODE_ARRAY);

    attr->is_lead_byte_fn  = GBK_EUC_IsLeadByte;
    attr->is_trial_byte_fn = GBK_EUC_IsTrialByte;
    BRST_StrCopy(attr->registry, "Adobe", attr->registry + BRST_LIMIT_MAX_NAME_LEN);
    BRST_StrCopy(attr->ordering, "GB1", attr->ordering + BRST_LIMIT_MAX_NAME_LEN);
    attr->supplement = 2;
    attr->uid_offset = -1;
    attr->xuid[0]    = 1;
    attr->xuid[1]    = 10;
    attr->xuid[2]    = 25377;

    encoder->type = BRST_ENCODER_TYPE_DOUBLE_BYTE;

    return BRST_OK;
}

BRST_STATUS
GBK_EUC_V_Init(BRST_Encoder encoder)
{
    BRST_CMapEncoderAttr attr;
    BRST_STATUS ret;

    if ((ret = BRST_CMapEncoder_InitAttr(encoder)) != BRST_OK)
        return ret;

    attr = (BRST_CMapEncoderAttr)encoder->attr;

    if ((ret = BRST_CMapEncoder_AddCMap(encoder, CMAP_ARRAY_GBK_EUC_H)) != BRST_OK)
        return ret;

    if ((ret = BRST_CMapEncoder_AddCMap(encoder, CMAP_ARRAY_GBK_EUC_V)) != BRST_OK)
        return ret;

    if ((ret = GBK_EUC_AddCodeSpaceRange(encoder)) != BRST_OK)
        return ret;

    if (BRST_CMapEncoder_AddNotDefRange(encoder, GBK_EUC_NOTDEF_RANGE)
        != BRST_OK)
        return BRST_Error_Code(encoder->error);

    BRST_CMapEncoder_SetUnicodeArray(encoder, CP936_UNICODE_ARRAY);

    attr->is_lead_byte_fn  = GBK_EUC_IsLeadByte;
    attr->is_trial_byte_fn = GBK_EUC_IsTrialByte;
    BRST_StrCopy(attr->registry, "Adobe", attr->registry + BRST_LIMIT_MAX_NAME_LEN);
    BRST_StrCopy(attr->ordering, "GB1", attr->ordering + BRST_LIMIT_MAX_NAME_LEN);
    attr->supplement = 2;
    attr->uid_offset = -1;
    attr->xuid[0]    = 1;
    attr->xuid[1]    = 10;
    attr->xuid[2]    = 25378;

    attr->writing_mode = BRST_WMODE_VERTICAL;

    encoder->type = BRST_ENCODER_TYPE_DOUBLE_BYTE;

    return BRST_OK;
}

static BRST_BOOL
GB_EUC_IsLeadByte(BRST_Encoder encoder,
    BRST_BYTE b)
{
    BRST_UNUSED(encoder);
    return (b >= 0xa1 && b <= 0xfe);
}

static BRST_BOOL
GB_EUC_IsTrialByte(BRST_Encoder encoder,
    BRST_BYTE b)
{
    BRST_UNUSED(encoder);
    return (b >= 0xa1 && b <= 0xfe);
}

static BRST_STATUS
GB_EUC_AddCodeSpaceRange(BRST_Encoder encoder)
{
    BRST_CidRange_Rec code_space_range1 = { 0x00, 0x80, 0 };
    BRST_CidRange_Rec code_space_range2 = { 0xA1A1, 0xFEFE, 0 };

    if (BRST_CMapEncoder_AddCodeSpaceRange(encoder, code_space_range1)
        != BRST_OK)
        return BRST_Error_Code(encoder->error);

    if (BRST_CMapEncoder_AddCodeSpaceRange(encoder, code_space_range2)
        != BRST_OK)
        return BRST_Error_Code(encoder->error);

    return BRST_OK;
}

BRST_STATUS
GB_EUC_H_Init(BRST_Encoder encoder)
{
    BRST_CMapEncoderAttr attr;
    BRST_STATUS ret;

    if ((ret = BRST_CMapEncoder_InitAttr(encoder)) != BRST_OK)
        return ret;

    attr = (BRST_CMapEncoderAttr)encoder->attr;

    if (BRST_CMapEncoder_AddCMap(encoder, CMAP_ARRAY_GB_EUC_H) != BRST_OK)
        return BRST_Error_Code(encoder->error);

    if ((ret = GB_EUC_AddCodeSpaceRange(encoder)) != BRST_OK)
        return ret;

    if (BRST_CMapEncoder_AddNotDefRange(encoder, GB_EUC_NOTDEF_RANGE) != BRST_OK)
        return BRST_Error_Code(encoder->error);

    BRST_CMapEncoder_SetUnicodeArray(encoder, EUC_CN_UNICODE_ARRAY);

    attr->is_lead_byte_fn  = GB_EUC_IsLeadByte;
    attr->is_trial_byte_fn = GB_EUC_IsTrialByte;
    BRST_StrCopy(attr->registry, "Adobe", attr->registry + BRST_LIMIT_MAX_NAME_LEN);
    BRST_StrCopy(attr->ordering, "GB1", attr->ordering + BRST_LIMIT_MAX_NAME_LEN);
    attr->supplement = 0;
    attr->uid_offset = 100;
    attr->xuid[0]    = 1;
    attr->xuid[1]    = 10;
    attr->xuid[2]    = 25360;

    encoder->type = BRST_ENCODER_TYPE_DOUBLE_BYTE;

    return BRST_OK;
}

BRST_STATUS
GB_EUC_V_Init(BRST_Encoder encoder)
{
    BRST_CMapEncoderAttr attr;
    BRST_STATUS ret;

    if ((ret = BRST_CMapEncoder_InitAttr(encoder)) != BRST_OK)
        return ret;

    attr = (BRST_CMapEncoderAttr)encoder->attr;

    if (BRST_CMapEncoder_AddCMap(encoder, CMAP_ARRAY_GB_EUC_H) != BRST_OK)
        return BRST_Error_Code(encoder->error);

    if (BRST_CMapEncoder_AddCMap(encoder, CMAP_ARRAY_GB_EUC_V) != BRST_OK)
        return BRST_Error_Code(encoder->error);

    if ((ret = GB_EUC_AddCodeSpaceRange(encoder)) != BRST_OK)
        return ret;

    if (BRST_CMapEncoder_AddNotDefRange(encoder, GB_EUC_NOTDEF_RANGE) != BRST_OK)
        return BRST_Error_Code(encoder->error);

    BRST_CMapEncoder_SetUnicodeArray(encoder, EUC_CN_UNICODE_ARRAY);

    attr->is_lead_byte_fn  = GB_EUC_IsLeadByte;
    attr->is_trial_byte_fn = GB_EUC_IsTrialByte;
    BRST_StrCopy(attr->registry, "Adobe", attr->registry + BRST_LIMIT_MAX_NAME_LEN);
    BRST_StrCopy(attr->ordering, "GB1", attr->ordering + BRST_LIMIT_MAX_NAME_LEN);
    attr->supplement   = 0;
    attr->writing_mode = BRST_WMODE_VERTICAL;
    attr->uid_offset   = 310;
    attr->xuid[0]      = 1;
    attr->xuid[1]      = 10;
    attr->xuid[2]      = 25361;

    encoder->type = BRST_ENCODER_TYPE_DOUBLE_BYTE;

    return BRST_OK;
}
