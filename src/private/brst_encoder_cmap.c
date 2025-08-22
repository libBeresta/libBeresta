#include "brst_types.h"
#include "brst_mmgr.h"
#include "private/brst_list.h"
#include "brst_stream.h"
#include "brst_encrypt.h"
#include "brst_encoder.h"
#include "private/brst_encoder.h"
#include "private/brst_defines.h"
#include "private/brst_utils.h"
#include "brst_consts.h"
#include "private/brst_encoder_cmap.h"
#include "brst_error.h"

/* At first, CMAP encoder is create as 'virtual' object.
 * When init_fn is called, cmap-data is loaded and it becomes to be available
 */

static BRST_STATUS
AddCidRange(BRST_MMgr mmgr,
    BRST_CidRange_Rec range,
    BRST_List target);

BRST_Encoder
BRST_CMapEncoder_New(BRST_MMgr mmgr,
    char* name,
    BRST_Encoder_Init_Func init_fn)
{
    BRST_Encoder encoder;

    BRST_PTRACE(" BRST_CMapEncoder_New\n");

    if (mmgr == NULL)
        return NULL;

    encoder = BRST_GetMem(mmgr, sizeof(BRST_Encoder_Rec));
    if (!encoder)
        return NULL;

    BRST_MemSet(encoder, 0, sizeof(BRST_Encoder_Rec));

    BRST_StrCpy(encoder->name, name, encoder->name + BRST_LIMIT_MAX_NAME_LEN);
    encoder->mmgr          = mmgr;
    encoder->error         = BRST_MMgr_Error(mmgr);
    encoder->type          = BRST_ENCODER_TYPE_UNINITIALIZED;
    encoder->byte_type_fn  = BRST_CMapEncoder_ByteType;
    encoder->to_unicode_fn = BRST_CMapEncoder_ToUnicode;
    encoder->write_fn      = BRST_CMapEncoder_Write;
    encoder->free_fn       = BRST_CMapEncoder_Free;
    encoder->init_fn       = init_fn;
    encoder->sig_bytes     = BRST_ENCODER_SIG_BYTES;

    return encoder;
}

BRST_STATUS
BRST_CMapEncoder_InitAttr(BRST_Encoder encoder)
{
    BRST_CMapEncoderAttr encoder_attr;
    BRST_UINT i;
    BRST_UINT j;

    BRST_PTRACE(" BRST_CMapEncoder_InitAttr\n");

    if (encoder->attr)
        return BRST_INVALID_ENCODER;

    encoder_attr = BRST_GetMem(encoder->mmgr,
        sizeof(BRST_CMapEncoderAttr_Rec));

    if (!encoder_attr) {
        BRST_Error error = encoder->error;
        if (error)
            return BRST_Error_Code(error);
        return -1;
    }

    BRST_MemSet(encoder_attr, 0, sizeof(BRST_CMapEncoderAttr_Rec));
    encoder->attr = encoder_attr;

    encoder_attr->writing_mode = BRST_WMODE_HORIZONTAL;

    for (i = 0; i <= 255; i++) {
        for (j = 0; j <= 255; j++) {
            /* undefined characters are replaced to square */
            encoder_attr->unicode_map[i][j] = 0x25A1;
        }
    }

    /* create cmap range */
    encoder_attr->cmap_range = BRST_List_New(encoder->mmgr,
        BRST_DEF_RANGE_TBL_NUM);
    if (!encoder_attr->cmap_range) {
        BRST_Error error = encoder->error;
        if (error)
            return BRST_Error_Code(error);
        return -1;
    }

    encoder_attr->notdef_range = BRST_List_New(encoder->mmgr,
        BRST_DEF_ITEMS_PER_BLOCK);
    if (!encoder_attr->notdef_range) {
        BRST_Error error = encoder->error;
        if (error)
            return BRST_Error_Code(error);
        return -1;
    }

    encoder_attr->code_space_range = BRST_List_New(encoder->mmgr,
        BRST_DEF_ITEMS_PER_BLOCK);
    if (!encoder_attr->code_space_range) {
        BRST_Error error = encoder->error;
        if (error)
            return BRST_Error_Code(error);
        return -1;
    }

    return BRST_OK;
}

BRST_UNICODE
BRST_CMapEncoder_ToUnicode(BRST_Encoder encoder,
    BRST_UINT16 code)
{
    BRST_BYTE l               = (BRST_BYTE)code;
    BRST_BYTE h               = (BRST_BYTE)(code >> 8);
    BRST_CMapEncoderAttr attr = (BRST_CMapEncoderAttr)encoder->attr;

    return attr->unicode_map[l][h];
}

BRST_UINT16
BRST_CMapEncoder_ToCID(BRST_Encoder encoder,
    BRST_UINT16 code)
{
    BRST_BYTE l = (BRST_BYTE)code;
    BRST_BYTE h = (BRST_BYTE)(code >> 8);

    BRST_CMapEncoderAttr attr = (BRST_CMapEncoderAttr)encoder->attr;

    return attr->cid_map[l][h];
}

void BRST_CMapEncoder_Free(BRST_Encoder encoder)
{
    BRST_CMapEncoderAttr attr;
    BRST_UINT i;
    BRST_CidRange_Rec* data;

    BRST_PTRACE(" BRST_CMapEncoder_Free\n");

    attr = (BRST_CMapEncoderAttr)encoder->attr;

    if (attr && attr->cmap_range) {
        for (i = 0; i < BRST_List_Count(attr->cmap_range); i++) {
            data = BRST_List_ItemAt(attr->cmap_range, i);

            BRST_FreeMem(encoder->mmgr, data);
        }

        BRST_List_Free(attr->cmap_range);
    }

    if (attr && attr->notdef_range) {
        for (i = 0; i < BRST_List_Count(attr->notdef_range); i++) {
            data = BRST_List_ItemAt(attr->notdef_range, i);

            BRST_FreeMem(encoder->mmgr, data);
        }

        BRST_List_Free(attr->notdef_range);
    }

    if (attr && attr->code_space_range) {
        for (i = 0; i < BRST_List_Count(attr->code_space_range); i++) {
            data = BRST_List_ItemAt(attr->code_space_range, i);

            BRST_FreeMem(encoder->mmgr, data);
        }

        BRST_List_Free(attr->code_space_range);
    }

    BRST_FreeMem(encoder->mmgr, encoder->attr);
    encoder->attr = NULL;
}

BRST_STATUS
BRST_CMapEncoder_Write(BRST_Encoder encoder,
    BRST_Stream out)
{
    BRST_STATUS ret = BRST_OK;
    BRST_UNUSED(out);
    BRST_UNUSED(encoder);

    return ret;
}

BRST_STATUS
BRST_CMapEncoder_AddCMap(BRST_Encoder encoder,
    const BRST_CidRange_Rec* range)
{
    BRST_CMapEncoderAttr attr = (BRST_CMapEncoderAttr)encoder->attr;

    BRST_PTRACE(" BRST_CMapEncoder_AddCMap\n");

    /* Copy specified pdf_cid_range array to fRangeArray. */
    while (range->from != 0xffff || range->to != 0xffff) {
        BRST_CidRange_Rec* prange;
        BRST_STATUS ret;

        /*
         * Only if we have the default to_unicode_fn
         */
        if (encoder->to_unicode_fn == BRST_CMapEncoder_ToUnicode) {
            BRST_UINT16 code = range->from;
            BRST_UINT16 cid  = range->cid;

            while (code <= range->to) {
                BRST_BYTE l = (BRST_BYTE)code;
                BRST_BYTE h = code >> 8;

                attr->cid_map[l][h] = cid;
                code++;
                cid++;
            }
        }

        prange = BRST_GetMem(encoder->mmgr, sizeof(BRST_CidRange_Rec));
        if (!prange) {
            BRST_Error error = encoder->error;
            if (error)
                return BRST_Error_Code(error);
            return -1;
        }

        prange->from = range->from;
        prange->to   = range->to;
        prange->cid  = range->cid;

        if ((ret = BRST_List_Add(attr->cmap_range, prange)) != BRST_OK) {
            BRST_FreeMem(encoder->mmgr, prange);
            return ret;
        }

        range++;
    }

    return BRST_OK;
}

BRST_STATUS
BRST_CMapEncoder_AddNotDefRange(BRST_Encoder encoder,
    BRST_CidRange_Rec range)
{
    BRST_CMapEncoderAttr attr = (BRST_CMapEncoderAttr)encoder->attr;

    BRST_PTRACE(" BRST_CMapEncoder_AddNotDefRange\n");

    return AddCidRange(encoder->mmgr, range, attr->notdef_range);
}

BRST_STATUS
BRST_CMapEncoder_AddCodeSpaceRange(BRST_Encoder encoder,
    BRST_CidRange_Rec range)
{
    BRST_CMapEncoderAttr attr = (BRST_CMapEncoderAttr)encoder->attr;

    BRST_PTRACE(" BRST_CMapEncoder_AddNotDefRange\n");

    return AddCidRange(encoder->mmgr, range, attr->code_space_range);
}

void BRST_CMapEncoder_SetUnicodeArray(BRST_Encoder encoder,
    const BRST_UnicodeMap_Rec* array)
{
    BRST_CMapEncoderAttr attr = (BRST_CMapEncoderAttr)encoder->attr;

    BRST_PTRACE(" BRST_CMapEncoder_SetUnicodeArray\n");

    if (array != NULL)
        while (array->unicode != 0xffff) {
            BRST_BYTE l             = (BRST_BYTE)array->code;
            BRST_BYTE h             = (BRST_BYTE)(array->code >> 8);
            attr->unicode_map[l][h] = array->unicode;
            array++;
        }
}

BRST_STATUS
BRST_CMapEncoder_AddJWWLineHead(BRST_Encoder encoder,
    const BRST_UINT16* code)
{
    BRST_CMapEncoderAttr attr = (BRST_CMapEncoderAttr)encoder->attr;
    BRST_UINT i, j;

    BRST_PTRACE(" BRST_CMapEncoder_AddJWWLineHead\n");

    for (i = 0; i < BRST_MAX_JWW_NUM; i++) {
        if (*code == 0)
            break;

        for (j = 0; j < BRST_MAX_JWW_NUM; j++) {
            if (attr->jww_line_head[j] == *code)
                break;

            if (attr->jww_line_head[j] == 0) {
                attr->jww_line_head[j] = *code;
                break;
            }

            if (j == BRST_MAX_JWW_NUM - 1)
                return BRST_Error_Set(encoder->error,
                    BRST_EXCEED_JWW_CODE_NUM_LIMIT, i);
        }

        code++;
    }

    return BRST_OK;
}

BRST_ByteType
BRST_CMapEncoder_ByteType(BRST_Encoder encoder,
    BRST_ParseText_Rec* state)
{
    BRST_CMapEncoderAttr attr = (BRST_CMapEncoderAttr)encoder->attr;

    BRST_PTRACE(" BRST_CMapEncoder_ByteType\n");

    if (state->index >= state->len)
        return BRST_BYTE_TYPE_UNKNOWN;

    if (state->byte_type == BRST_BYTE_TYPE_LEAD) {
        if (attr->is_trial_byte_fn(encoder, state->text[state->index]))
            state->byte_type = BRST_BYTE_TYPE_TRAIL;
        else
            state->byte_type = BRST_BYTE_TYPE_UNKNOWN;
    } else {
        if (attr->is_lead_byte_fn(encoder, state->text[state->index]))
            state->byte_type = BRST_BYTE_TYPE_LEAD;
        else
            state->byte_type = BRST_BYTE_TYPE_SINGLE;
    }

    state->index++;

    return state->byte_type;
}

static BRST_STATUS
AddCidRange(BRST_MMgr mmgr,
    BRST_CidRange_Rec range,
    BRST_List target)
{
    BRST_CidRange_Rec* prange;
    BRST_STATUS ret;

    prange = BRST_GetMem(mmgr, sizeof(BRST_CidRange_Rec));
    if (!prange) {
        BRST_Error error = BRST_MMgr_Error(mmgr);
        if (error)
            return BRST_Error_Code(error);
        return -1;
    }

    prange->from = range.from;
    prange->to   = range.to;
    prange->cid  = range.cid;

    if ((ret = BRST_List_Add(target, prange))
        != BRST_OK) {
        BRST_FreeMem(mmgr, prange);
        return ret;
    }

    return BRST_OK;
}

BRST_BOOL
BRST_Encoder_CheckJWWLineHead(BRST_Encoder encoder,
    const BRST_UINT16 code)
{
    BRST_CMapEncoderAttr attr;
    BRST_UINT j;

    BRST_PTRACE(" BRST_Encoder_CheckJWWLineHead\n");

    if (!BRST_Encoder_Validate(encoder))
        return BRST_FALSE;

    if (encoder->type != BRST_ENCODER_TYPE_DOUBLE_BYTE)
        return BRST_FALSE;

    attr = (BRST_CMapEncoderAttr)encoder->attr;

    for (j = 0; j < BRST_MAX_JWW_NUM; j++) {
        if (code == attr->jww_line_head[j])
            return BRST_TRUE;

        if (attr->jww_line_head[j] == 0)
            return BRST_FALSE;
    }

    return BRST_FALSE;
}
