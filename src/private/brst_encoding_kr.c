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
#include "private/brst_encoding_kr.h"

#include "../src/private/data/encoder_kr.data"

static const BRST_CidRange_Rec KSCms_UHC_NOTDEF_RANGE    = { 0x00, 0x1F, 1 };
static const BRST_CidRange_Rec KSCms_UHC_HW_NOTDEF_RANGE = { 0x00, 0x1F, 8094 };
static const BRST_CidRange_Rec KSC_EUC_NOTDEF_RANGE      = { 0x00, 0x1F, 8094 };

static BRST_BOOL
KSCms_UHC_IsLeadByte(BRST_Encoder encoder,
    BRST_BYTE b);

static BRST_BOOL
KSCms_UHC_IsTrialByte(BRST_Encoder encoder,
    BRST_BYTE b);

static BRST_STATUS
KSCms_UHC_AddCodeSpaceRange(BRST_Encoder encoder);

static BRST_BOOL
KSC_EUC_IsLeadByte(BRST_Encoder encoder,
    BRST_BYTE b);

static BRST_BOOL
KSC_EUC_IsTrialByte(BRST_Encoder encoder,
    BRST_BYTE b);

static BRST_STATUS
KSC_EUC_AddCodeSpaceRange(BRST_Encoder encoder);

/*--------------------------------------------------------------------------*/

BRST_BOOL
KSCms_UHC_IsLeadByte(BRST_Encoder encoder,
    BRST_BYTE b)
{
    BRST_UNUSED(encoder);
    return (b >= 0x81 && b <= 0xFE);
}

static BRST_BOOL
KSCms_UHC_IsTrialByte(BRST_Encoder encoder,
    BRST_BYTE b)
{
    BRST_UNUSED(encoder);
    return (b >= 0x41 && b <= 0xfe);
}

static BRST_STATUS
KSCms_UHC_AddCodeSpaceRange(BRST_Encoder encoder)
{
    BRST_CidRange_Rec code_space_range1 = { 0x00, 0x80, 0 };
    BRST_CidRange_Rec code_space_range2 = { 0x8141, 0xFEFE, 0 };

    if (BRST_CMapEncoder_AddCodeSpaceRange(encoder, code_space_range1)
        != BRST_OK)
        return BRST_Error_Code(encoder->error);

    if (BRST_CMapEncoder_AddCodeSpaceRange(encoder, code_space_range2)
        != BRST_OK)
        return BRST_Error_Code(encoder->error);

    return BRST_OK;
}

BRST_STATUS
KSCms_UHC_H_Init(BRST_Encoder encoder)
{
    BRST_CMapEncoderAttr attr;
    BRST_STATUS ret;

    if ((ret = BRST_CMapEncoder_InitAttr(encoder)) != BRST_OK)
        return ret;

    attr = (BRST_CMapEncoderAttr)encoder->attr;

    if (BRST_CMapEncoder_AddCMap(encoder, CMAP_ARRAY_KSCms_UHC_H) != BRST_OK)
        return BRST_Error_Code(encoder->error);

    if ((ret = KSCms_UHC_AddCodeSpaceRange(encoder)) != BRST_OK)
        return ret;

    if (BRST_CMapEncoder_AddNotDefRange(encoder, KSCms_UHC_NOTDEF_RANGE)
        != BRST_OK)
        return BRST_Error_Code(encoder->error);

    BRST_CMapEncoder_SetUnicodeArray(encoder, CP949_UNICODE_ARRAY);

    attr->is_lead_byte_fn  = KSCms_UHC_IsLeadByte;
    attr->is_trial_byte_fn = KSCms_UHC_IsTrialByte;
    BRST_StrCpy(attr->registry, "Adobe", attr->registry + BRST_LIMIT_MAX_NAME_LEN);
    BRST_StrCpy(attr->ordering, "Korea1", attr->ordering + BRST_LIMIT_MAX_NAME_LEN);
    attr->suppliment = 1;
    attr->uid_offset = 430;
    attr->xuid[0]    = 1;
    attr->xuid[1]    = 10;
    attr->xuid[2]    = 25409;

    encoder->type = BRST_ENCODER_TYPE_DOUBLE_BYTE;

    return BRST_OK;
}

BRST_STATUS
KSCms_UHC_HW_H_Init(BRST_Encoder encoder)
{
    BRST_CMapEncoderAttr attr;
    BRST_STATUS ret;

    if ((ret = BRST_CMapEncoder_InitAttr(encoder)) != BRST_OK)
        return ret;

    attr = (BRST_CMapEncoderAttr)encoder->attr;

    if (BRST_CMapEncoder_AddCMap(encoder, CMAP_ARRAY_KSCms_UHC_HW_H) != BRST_OK)
        return BRST_Error_Code(encoder->error);

    if ((ret = KSCms_UHC_AddCodeSpaceRange(encoder)) != BRST_OK)
        return ret;

    if (BRST_CMapEncoder_AddNotDefRange(encoder, KSCms_UHC_HW_NOTDEF_RANGE)
        != BRST_OK)
        return BRST_Error_Code(encoder->error);

    BRST_CMapEncoder_SetUnicodeArray(encoder, CP949_UNICODE_ARRAY);

    attr->is_lead_byte_fn  = KSCms_UHC_IsLeadByte;
    attr->is_trial_byte_fn = KSCms_UHC_IsTrialByte;
    BRST_StrCpy(attr->registry, "Adobe", attr->registry + BRST_LIMIT_MAX_NAME_LEN);
    BRST_StrCpy(attr->ordering, "Korea1", attr->ordering + BRST_LIMIT_MAX_NAME_LEN);
    attr->suppliment = 1;
    attr->uid_offset = -1;
    attr->xuid[0]    = 1;
    attr->xuid[1]    = 10;
    attr->xuid[2]    = 25416;

    encoder->type = BRST_ENCODER_TYPE_DOUBLE_BYTE;

    return BRST_OK;
}

BRST_STATUS
KSCms_UHC_HW_V_Init(BRST_Encoder encoder)
{
    BRST_CMapEncoderAttr attr;
    BRST_STATUS ret;

    if ((ret = BRST_CMapEncoder_InitAttr(encoder)) != BRST_OK)
        return ret;

    attr = (BRST_CMapEncoderAttr)encoder->attr;

    if ((ret = BRST_CMapEncoder_AddCMap(encoder, CMAP_ARRAY_KSCms_UHC_HW_H)) != BRST_OK)
        return ret;

    if ((ret = BRST_CMapEncoder_AddCMap(encoder, CMAP_ARRAY_KSCms_UHC_HW_V)) != BRST_OK)
        return ret;

    if ((ret = KSCms_UHC_AddCodeSpaceRange(encoder)) != BRST_OK)
        return ret;

    if (BRST_CMapEncoder_AddNotDefRange(encoder, KSCms_UHC_HW_NOTDEF_RANGE)
        != BRST_OK)
        return BRST_Error_Code(encoder->error);

    BRST_CMapEncoder_SetUnicodeArray(encoder, CP949_UNICODE_ARRAY);

    attr->is_lead_byte_fn  = KSCms_UHC_IsLeadByte;
    attr->is_trial_byte_fn = KSCms_UHC_IsTrialByte;
    BRST_StrCpy(attr->registry, "Adobe", attr->registry + BRST_LIMIT_MAX_NAME_LEN);
    BRST_StrCpy(attr->ordering, "Korea1", attr->ordering + BRST_LIMIT_MAX_NAME_LEN);
    attr->suppliment = 1;
    attr->uid_offset = -1;
    attr->xuid[0]    = 1;
    attr->xuid[1]    = 10;
    attr->xuid[2]    = 25417;

    attr->writing_mode = BRST_WMODE_VERTICAL;

    encoder->type = BRST_ENCODER_TYPE_DOUBLE_BYTE;

    return BRST_OK;
}

static BRST_BOOL
KSC_EUC_IsLeadByte(BRST_Encoder encoder,
    BRST_BYTE b)
{
    BRST_UNUSED(encoder);
    return (b >= 0xa1 && b <= 0xfe);
}

static BRST_BOOL
KSC_EUC_IsTrialByte(BRST_Encoder encoder,
    BRST_BYTE b)
{
    BRST_UNUSED(encoder);
    return (b >= 0xa0 && b <= 0xfe);
}

static BRST_STATUS
KSC_EUC_AddCodeSpaceRange(BRST_Encoder encoder)
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
KSC_EUC_H_Init(BRST_Encoder encoder)
{
    BRST_CMapEncoderAttr attr;
    BRST_STATUS ret;

    if ((ret = BRST_CMapEncoder_InitAttr(encoder)) != BRST_OK)
        return ret;

    attr = (BRST_CMapEncoderAttr)encoder->attr;

    if (BRST_CMapEncoder_AddCMap(encoder, CMAP_ARRAY_KSC_EUC_H) != BRST_OK)
        return BRST_Error_Code(encoder->error);

    if ((ret = KSC_EUC_AddCodeSpaceRange(encoder)) != BRST_OK)
        return ret;

    if (BRST_CMapEncoder_AddNotDefRange(encoder, KSC_EUC_NOTDEF_RANGE)
        != BRST_OK)
        return BRST_Error_Code(encoder->error);

    BRST_CMapEncoder_SetUnicodeArray(encoder, KSC_EUC_UNICODE_ARRAY);

    attr->is_lead_byte_fn  = KSC_EUC_IsLeadByte;
    attr->is_trial_byte_fn = KSC_EUC_IsTrialByte;
    BRST_StrCpy(attr->registry, "Adobe", attr->registry + BRST_LIMIT_MAX_NAME_LEN);
    BRST_StrCpy(attr->ordering, "Korea1", attr->ordering + BRST_LIMIT_MAX_NAME_LEN);
    attr->suppliment = 0;
    attr->uid_offset = 100;
    attr->xuid[0]    = 1;
    attr->xuid[1]    = 10;
    attr->xuid[2]    = 25400;

    encoder->type = BRST_ENCODER_TYPE_DOUBLE_BYTE;

    return BRST_OK;
}

BRST_STATUS
KSC_EUC_V_Init(BRST_Encoder encoder)
{
    BRST_CMapEncoderAttr attr;
    BRST_STATUS ret;

    if ((ret = BRST_CMapEncoder_InitAttr(encoder)) != BRST_OK)
        return ret;

    attr = (BRST_CMapEncoderAttr)encoder->attr;

    if (BRST_CMapEncoder_AddCMap(encoder, CMAP_ARRAY_KSC_EUC_H) != BRST_OK)
        return BRST_Error_Code(encoder->error);

    if (BRST_CMapEncoder_AddCMap(encoder, CMAP_ARRAY_KSC_EUC_V) != BRST_OK)
        return BRST_Error_Code(encoder->error);

    if ((ret = KSC_EUC_AddCodeSpaceRange(encoder)) != BRST_OK)
        return ret;

    if (BRST_CMapEncoder_AddNotDefRange(encoder, KSC_EUC_NOTDEF_RANGE)
        != BRST_OK)
        return BRST_Error_Code(encoder->error);

    BRST_CMapEncoder_SetUnicodeArray(encoder, KSC_EUC_UNICODE_ARRAY);

    attr->is_lead_byte_fn  = KSC_EUC_IsLeadByte;
    attr->is_trial_byte_fn = KSC_EUC_IsTrialByte;
    BRST_StrCpy(attr->registry, "Adobe", attr->registry + BRST_LIMIT_MAX_NAME_LEN);
    BRST_StrCpy(attr->ordering, "Korea1", attr->ordering + BRST_LIMIT_MAX_NAME_LEN);
    attr->suppliment   = 0;
    attr->writing_mode = BRST_WMODE_VERTICAL;
    attr->uid_offset   = 310;
    attr->xuid[0]      = 1;
    attr->xuid[1]      = 10;
    attr->xuid[2]      = 25401;

    encoder->type = BRST_ENCODER_TYPE_DOUBLE_BYTE;

    return BRST_OK;
}
