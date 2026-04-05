#include "brst_types.h"
#include "brst_mmgr.h"
#include "brst_encoder.h"
#include "brst_encrypt.h"
#include "brst_stream.h"
#include "private/brst_stream.h"
#include "brst_mmgr.h"
#include "brst_dict.h"
#include "brst_error.h"
#include "private/brst_error.h"
#include "private/brst_list.h"
#include "private/brst_defines.h"
#include "brst_fontdef.h"
#include "private/brst_fontdef.h"
#include "private/brst_fontdef_type1.h"
#include "brst_unicode_glyph.h"
#include "private/brst_utils.h"
#include "brst_consts.h"

static void
FreeWidth(BRST_FontDef fontdef);

static void
FreeFunc(BRST_FontDef fontdef);

static const char*
GetKeyword(const char* src,
    char* keyword,
    BRST_UINT len);

static BRST_STATUS
LoadAfm(BRST_FontDef fontdef,
    BRST_Stream stream);

static BRST_STATUS
LoadFontData(BRST_FontDef fontdef,
    BRST_Stream stream);

/*---------------------------------------------------------------------------*/

static void
FreeWidth(BRST_FontDef fontdef)
{
    BRST_Type1FontDefAttr attr = (BRST_Type1FontDefAttr)fontdef->attr;

    BRST_PTRACE(" FreeWidth\n");

    BRST_FreeMem(fontdef->mmgr, attr->widths);
    attr->widths = NULL;

    fontdef->valid = BRST_FALSE;
}

BRST_FontDef
BRST_Type1FontDef_New(BRST_MMgr mmgr)
{
    BRST_FontDef fontdef;
    BRST_Type1FontDefAttr fontdef_attr;

    BRST_PTRACE(" BRST_Type1FontDef_New\n");

    if (!mmgr)
        return NULL;

    fontdef = BRST_GetMem(mmgr, sizeof(BRST_FontDef_Rec));
    if (!fontdef)
        return NULL;

    BRST_MemSet(fontdef, 0, sizeof(BRST_FontDef_Rec));
    fontdef->sig_bytes = BRST_FONTDEF_SIG_BYTES;
    fontdef->mmgr      = mmgr;
    fontdef->error     = BRST_MMgr_Error(mmgr);
    fontdef->type      = BRST_FONTDEF_TYPE_TYPE1;
    fontdef->free_fn   = FreeFunc;

    fontdef_attr = BRST_GetMem(mmgr, sizeof(BRST_Type1FontDefAttr_Rec));
    if (!fontdef_attr) {
        BRST_FreeMem(fontdef->mmgr, fontdef);
        return NULL;
    }

    fontdef->attr = fontdef_attr;
    BRST_MemSet((BRST_BYTE*)fontdef_attr, 0, sizeof(BRST_Type1FontDefAttr_Rec));
    fontdef->flags = BRST_FONT_STD_CHARSET;

    return fontdef;
}

static const char*
GetKeyword(const char* src,
    char* keyword,
    BRST_UINT len)
{
    BRST_UINT src_len = BRST_StrLen(src, -1);

    BRST_PTRACE(" GetKeyword\n");

    if (!keyword || src_len == 0 || len == 0)
        return NULL;

    *keyword = 0;

    while (len > 1) {
        if (BRST_IS_WHITE_SPACE(*src)) {
            *keyword = 0;

            while (BRST_IS_WHITE_SPACE(*src))
                src++;
            return src;
        }

        *keyword++ = *src++;
        len--;
    }

    *keyword = 0;
    return NULL;
}

static BRST_STATUS
LoadAfm(BRST_FontDef fontdef,
    BRST_Stream stream)
{
    BRST_Type1FontDefAttr attr = (BRST_Type1FontDefAttr)fontdef->attr;
    char buf[BRST_TMP_BUF_SIZE];
    BRST_CharData* cdata;
    BRST_STATUS ret;
    BRST_UINT len;
    char keyword[BRST_LIMIT_MAX_NAME_LEN + 1];
    BRST_UINT i;

    BRST_PTRACE(" LoadAfm\n");

    len = BRST_TMP_BUF_SIZE;

    /* check AFM header */
    if ((ret = BRST_Stream_ReadLn(stream, buf, &len)) != BRST_OK)
        return ret;

    GetKeyword(buf, keyword, BRST_LIMIT_MAX_NAME_LEN + 1);

    if (BRST_StrCmp(keyword, "StartFontMetrics") != 0)
        return BRST_INVALID_AFM_HEADER;

    /* Global Font Information */

    for (;;) {
        const char* s;

        len = BRST_TMP_BUF_SIZE;
        if ((ret = BRST_Stream_ReadLn(stream, buf, &len)) != BRST_OK)
            return ret;

        s = GetKeyword(buf, keyword, BRST_LIMIT_MAX_NAME_LEN + 1);

        if (BRST_StrCmp(keyword, "FontName") == 0) {
            BRST_StrCopy(fontdef->base_font, s,
                fontdef->base_font + BRST_LIMIT_MAX_NAME_LEN);
        } else

            if (BRST_StrCmp(keyword, "Weight") == 0) {
            if (BRST_StrCmp(s, "Bold") == 0)
                fontdef->flags |= BRST_FONT_FOURCE_BOLD;
        } else

            if (BRST_StrCmp(keyword, "IsFixedPitch") == 0) {
            if (BRST_StrCmp(s, "true") == 0)
                fontdef->flags |= BRST_FONT_FIXED_WIDTH;
        } else

            if (BRST_StrCmp(keyword, "ItalicAngle") == 0) {
            fontdef->italic_angle = (BRST_INT16)BRST_AToI(s);
            if (fontdef->italic_angle != 0)
                fontdef->flags |= BRST_FONT_ITALIC;
        } else

            if (BRST_StrCmp(keyword, "CharacterSet") == 0) {
            BRST_UINT len1 = BRST_StrLen(s, BRST_LIMIT_MAX_STRING_LEN);

            if (len1 > 0) {
                attr->char_set = BRST_GetMem(fontdef->mmgr, len1 + 1);
                if (!attr->char_set)
                    return BRST_Error_Code(fontdef->error);

                BRST_StrCopy(attr->char_set, s, attr->char_set + len1);
            }
        } else if (BRST_StrCmp(keyword, "FontBBox") == 0) {
            char buf1[BRST_INT_LEN + 1];

            s                       = GetKeyword(s, buf1, BRST_INT_LEN + 1);
            fontdef->font_bbox.left = (BRST_REAL)BRST_AToI(buf1);

            s                         = GetKeyword(s, buf1, BRST_INT_LEN + 1);
            fontdef->font_bbox.bottom = (BRST_REAL)BRST_AToI(buf1);

            s                        = GetKeyword(s, buf1, BRST_INT_LEN + 1);
            fontdef->font_bbox.right = (BRST_REAL)BRST_AToI(buf1);

            GetKeyword(s, buf1, BRST_INT_LEN + 1);
            fontdef->font_bbox.top = (BRST_REAL)BRST_AToI(buf1);
        } else if (BRST_StrCmp(keyword, "EncodingScheme") == 0) {
            BRST_StrCopy(attr->encoding_scheme, s,
                attr->encoding_scheme + BRST_LIMIT_MAX_NAME_LEN);
        } else if (BRST_StrCmp(keyword, "CapHeight") == 0) {
            fontdef->cap_height = (BRST_UINT16)BRST_AToI(s);
        } else if (BRST_StrCmp(keyword, "Ascender") == 0) {
            fontdef->ascent = (BRST_INT16)BRST_AToI(s);
        } else if (BRST_StrCmp(keyword, "Descender") == 0) {
            fontdef->descent = (BRST_INT16)BRST_AToI(s);
        } else if (BRST_StrCmp(keyword, "STDHW") == 0) {
            fontdef->stemh = (BRST_UINT16)BRST_AToI(s);
        } else if (BRST_StrCmp(keyword, "STDHV") == 0) {
            fontdef->stemv = (BRST_UINT16)BRST_AToI(s);
        } else if (BRST_StrCmp(keyword, "StartCharMetrics") == 0) {
            attr->widths_count = BRST_AToI(s);
            break;
        }
    }

    cdata = (BRST_CharData*)BRST_GetMem(fontdef->mmgr,
        sizeof(BRST_CharData) * attr->widths_count);
    if (cdata == NULL)
        return BRST_Error_Code(fontdef->error);

    BRST_MemSet(cdata, 0, sizeof(BRST_CharData) * attr->widths_count);
    attr->widths = cdata;

    /* load CharMetrics */
    for (i = 0; i < attr->widths_count; i++, cdata++) {
        const char* s;
        char buf2[BRST_LIMIT_MAX_NAME_LEN + 1] = { 0 };

        len = BRST_TMP_BUF_SIZE;
        if ((ret = BRST_Stream_ReadLn(stream, buf, &len)) != BRST_OK)
            return ret;

        /* C default character code. */
        s = GetKeyword(buf, buf2, BRST_LIMIT_MAX_NAME_LEN + 1);
        if (BRST_StrCmp(buf2, "CX") == 0) {
            /* not supported yet. */
            return BRST_Error_Set(fontdef->error,
                BRST_INVALID_CHAR_MATRIX_DATA, 0);
        } else if (BRST_StrCmp(buf2, "C") == 0) {
            s += 2;

            s              = GetKeyword(s, buf2, BRST_LIMIT_MAX_NAME_LEN + 1);
            cdata->char_cd = (BRST_INT16)BRST_AToI(buf2);

        } else
            return BRST_Error_Set(fontdef->error,
                BRST_INVALID_CHAR_MATRIX_DATA, 0);

        /* WX Character width */
        s = BRST_StrStr(s, "WX ", 0);
        if (!s)
            return BRST_Error_Set(fontdef->error, BRST_INVALID_WX_DATA, 0);

        s += 3;

        s = GetKeyword(s, buf2, BRST_LIMIT_MAX_NAME_LEN + 1);
        if (buf2[0] == 0)
            return BRST_Error_Set(fontdef->error, BRST_INVALID_WX_DATA, 0);

        cdata->width = (BRST_INT16)BRST_AToI(buf2);

        /* N PostScript language character name */
        s = BRST_StrStr(s, "N ", 0);
        if (!s)
            return BRST_Error_Set(fontdef->error, BRST_INVALID_N_DATA, 0);

        s += 2;

        GetKeyword(s, buf2, BRST_LIMIT_MAX_NAME_LEN + 1);

        cdata->unicode = BRST_GlyphNameToUnicode(buf2);
    }

    return BRST_OK;
}

static BRST_STATUS
LoadFontData(BRST_FontDef fontdef,
    BRST_Stream stream)
{
    BRST_Type1FontDefAttr attr = (BRST_Type1FontDefAttr)fontdef->attr;
    char buf[BRST_STREAM_BUF_SIZE];
    char* pbuf    = buf;
    BRST_UINT len = 0;
    BRST_STATUS ret;
    BRST_BOOL end_flg = BRST_FALSE;

    BRST_PTRACE(" LoadFontData\n");

    attr->font_data = BRST_MemStream_New(fontdef->mmgr, BRST_STREAM_BUF_SIZE);

    if (!attr->font_data)
        return BRST_Error_Code(fontdef->error);

    len = 11;
    ret = BRST_Stream_Read(stream, (BRST_BYTE*)pbuf, &len);
    if (ret != BRST_OK)
        return ret;
    pbuf += 11;

    for (;;) {
        len = BRST_STREAM_BUF_SIZE - 11;
        ret = BRST_Stream_Read(stream, (BRST_BYTE*)pbuf, &len);
        if (ret == BRST_STREAM_EOF) {
            end_flg = BRST_TRUE;
        } else if (ret != BRST_OK)
            return ret;

        if (len > 0) {
            if (attr->length1 == 0) {
                const char* s1 = BRST_StrStr(buf, "eexec", len + 11);

                /* length1 indicate the size of ascii-data of font-file. */
                if (s1)
                    attr->length1 = (BRST_UINT)(attr->font_data->size + (s1 - buf) + 6);
            }

            if (attr->length1 > 0 && attr->length2 == 0) {
                const char* s2 = BRST_StrStr(buf, "cleartomark",
                    len + 11);

                if (s2)
                    attr->length2 = (BRST_UINT)(attr->font_data->size - 520 - attr->length1 + (s2 - buf));
                /*  length1 indicate the size of binary-data.
                 *  in most fonts, it is all right at 520 bytes . but it need
                 *  to modify because it does not fully satisfy the
                 *  specification of type-1 font.
                 */
            }
        }

        if (end_flg) {
            if ((ret = BRST_Stream_Write(attr->font_data, (BRST_BYTE*)buf, len + 11)) != BRST_OK)
                return ret;

            break;
        } else {
            if ((ret = BRST_Stream_Write(attr->font_data, (BRST_BYTE*)buf, len)) != BRST_OK)
                return ret;
            BRST_MemCopy((BRST_BYTE*)buf, (BRST_BYTE*)buf + len, 11);
            pbuf = buf + 11;
        }
    }

    if (attr->length1 == 0 || attr->length2 == 0)
        return BRST_Error_Set(fontdef->error, BRST_UNSUPPORTED_TYPE1_FONT, 0);

    attr->length3 = attr->font_data->size - attr->length1 - attr->length2;

    return BRST_OK;
}

BRST_FontDef
BRST_Type1FontDef_Load(BRST_MMgr mmgr,
    BRST_Stream afm,
    BRST_Stream font_data)
{
    BRST_FontDef fontdef;
    BRST_STATUS ret;

    BRST_PTRACE(" BRST_Type1FontDef_Load\n");

    if (!afm)
        return NULL;

    fontdef = BRST_Type1FontDef_New(mmgr);

    if (!fontdef)
        return NULL;

    ret = LoadAfm(fontdef, afm);
    if (ret != BRST_OK) {
        BRST_FontDef_Free(fontdef);
        return NULL;
    }

    /* if font-data is specified, the font data is embedded */
    if (font_data) {
        ret = LoadFontData(fontdef, font_data);
        if (ret != BRST_OK) {
            BRST_FontDef_Free(fontdef);
            return NULL;
        }
    }

    return fontdef;
}

BRST_FontDef
BRST_Type1FontDef_Duplicate(BRST_MMgr mmgr,
    BRST_FontDef src)
{
    BRST_FontDef fontdef = BRST_Type1FontDef_New(mmgr);

    BRST_PTRACE(" BRST_Type1FontDef_Duplicate\n");

    fontdef->type  = src->type;
    fontdef->valid = src->valid;

    /* copy data of attr,widths
     attention to charset */
    return NULL;
}

BRST_STATUS
BRST_Type1FontDef_SetWidths(BRST_FontDef fontdef,
    const BRST_CharData* widths)
{
    const BRST_CharData* src   = widths;
    BRST_Type1FontDefAttr attr = (BRST_Type1FontDefAttr)fontdef->attr;
    BRST_CharData* dst;
    BRST_UINT i = 0;

    BRST_PTRACE(" BRST_Type1FontDef_SetWidths\n");

    FreeWidth(fontdef);

    while (src->unicode != 0xFFFF) {
        src++;
        i++;
    }

    attr->widths_count = i;

    dst = (BRST_CharData*)BRST_GetMem(fontdef->mmgr, sizeof(BRST_CharData) * attr->widths_count);
    if (dst == NULL)
        return BRST_Error_Code(fontdef->error);

    BRST_MemSet(dst, 0, sizeof(BRST_CharData) * attr->widths_count);
    attr->widths = dst;

    src = widths;
    for (i = 0; i < attr->widths_count; i++) {
        dst->char_cd = src->char_cd;
        dst->unicode = src->unicode;
        dst->width   = src->width;
        if (dst->unicode == 0x0020) {
            fontdef->missing_width = src->width;
        }

        src++;
        dst++;
    }

    return BRST_OK;
}

BRST_INT16
BRST_Type1FontDef_WidthByName(BRST_FontDef fontdef,
    const char* glyph_name)
{
    BRST_UNICODE unicode = BRST_GlyphNameToUnicode(glyph_name);

    BRST_PTRACE(" BRST_Type1FontDef_WidthByName\n");

    return BRST_Type1FontDef_Width(fontdef, unicode);
}

BRST_INT16
BRST_Type1FontDef_Width(BRST_FontDef fontdef,
    BRST_UNICODE unicode)
{
    BRST_Type1FontDefAttr attr = (BRST_Type1FontDefAttr)fontdef->attr;
    BRST_CharData* cdata       = attr->widths;
    BRST_UINT i;

    BRST_PTRACE(" BRST_Type1FontDef_Width\n");

    for (i = 0; i < attr->widths_count; i++) {
        if (cdata->unicode == unicode)
            return cdata->width;
        cdata++;
    }

    return fontdef->missing_width;
}

static void
FreeFunc(BRST_FontDef fontdef)
{
    BRST_Type1FontDefAttr attr = (BRST_Type1FontDefAttr)fontdef->attr;

    BRST_PTRACE(" FreeFunc\n");

    if (attr->char_set)
        BRST_FreeMem(fontdef->mmgr, attr->char_set);

    if (attr->font_data)
        BRST_Stream_Free(attr->font_data);

    BRST_FreeMem(fontdef->mmgr, attr->widths);
    BRST_FreeMem(fontdef->mmgr, attr);
}
