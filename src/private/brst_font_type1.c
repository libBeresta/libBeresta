#include "brst_types.h"
#include "brst_encrypt.h"
#include "brst_mmgr.h"
#include "brst_stream.h"
#include "brst_encoder.h"
#include "private/brst_encoder.h"
#include "private/brst_encoder_basic.h"
#include "brst_xref.h"
#include "brst_dict.h"
#include "private/brst_dict.h"
#include "brst_matrix.h"
#include "brst_array.h"
#include "private/brst_array.h"
#include "private/brst_defines.h"
#include "brst_fontdef.h"
#include "private/brst_fontdef.h"
#include "private/brst_fontdef_type1.h"
#include "private/brst_xref.h"
#include "brst_font.h"
#include "private/brst_font.h"
#include "private/brst_utils.h"
#include "brst_error.h"
#include "brst_consts.h"

static BRST_STATUS
Type1Font_OnWrite(BRST_Dict obj,
    BRST_Stream stream);

static void
Type1Font_OnFree(BRST_Dict obj);

static BRST_TextWidth
Type1Font_TextWidth(BRST_Font font,
    const BRST_BYTE* text,
    BRST_UINT len);

static BRST_UINT
Type1Font_MeasureText(BRST_Font font,
    const BRST_BYTE* text,
    BRST_UINT len,
    BRST_REAL width,
    BRST_REAL font_size,
    BRST_REAL char_space,
    BRST_REAL word_space,
    BRST_BOOL wordwrap,
    BRST_REAL* real_width);

static BRST_STATUS
Type1Font_CreateDescriptor(BRST_MMgr mmgr,
    BRST_Font font,
    BRST_Xref xref);

BRST_Font
BRST_Type1Font_New(BRST_MMgr mmgr,
    BRST_FontDef fontdef,
    BRST_Encoder encoder,
    BRST_Xref xref)
{
    BRST_Dict font;
    BRST_FontAttr attr;
    BRST_Type1FontDefAttr fontdef_attr;
    BRST_BasicEncoderAttr encoder_attr;
    BRST_STATUS ret = 0;
    BRST_UINT i;

    BRST_PTRACE(" BRST_Type1Font_New\n");

    /* check whether the fontdef object and the encoder object is valid. */
    if (encoder->type != BRST_ENCODER_TYPE_SINGLE_BYTE) {
        BRST_Error_Set(BRST_MMgr_Error(mmgr), BRST_INVALID_ENCODER_TYPE, 0);
        return NULL;
    }

    if (fontdef->type != BRST_FONTDEF_TYPE_TYPE1) {
        BRST_Error_Set(BRST_MMgr_Error(mmgr), BRST_INVALID_FONTDEF_TYPE, 0);
        return NULL;
    }

    font = BRST_Dict_New(mmgr);
    if (!font)
        return NULL;

    font->header.obj_class |= BRST_OSUBCLASS_FONT;

    attr = BRST_GetMem(mmgr, sizeof(BRST_FontAttr_Rec));
    if (!attr) {
        BRST_Dict_Free(font);
        return NULL;
    }

    font->header.obj_class |= BRST_OSUBCLASS_FONT;
    font->write_fn = Type1Font_OnWrite;
    font->free_fn  = Type1Font_OnFree;

    BRST_MemSet(attr, 0, sizeof(BRST_FontAttr_Rec));

    font->attr            = attr;
    attr->type            = BRST_FONT_TYPE1;
    attr->writing_mode    = BRST_WMODE_HORIZONTAL;
    attr->text_width_fn   = Type1Font_TextWidth;
    attr->measure_text_fn = Type1Font_MeasureText;
    attr->fontdef         = fontdef;
    attr->encoder         = encoder;
    attr->xref            = xref;

    /* singlebyte-font has a widths-array which is an array of 256 signed
     * short integer.
     */
    attr->widths = BRST_GetMem(mmgr, sizeof(BRST_INT16) * 256);
    if (!attr->widths) {
        BRST_Dict_Free(font);
        return NULL;
    }

    encoder_attr = (BRST_BasicEncoderAttr)encoder->attr;

    BRST_MemSet(attr->widths, 0, sizeof(BRST_INT16) * 256);
    for (i = encoder_attr->first_char; i <= encoder_attr->last_char; i++) {
        BRST_UNICODE u = encoder_attr->unicode_map[i];

        BRST_UINT16 w   = BRST_Type1FontDef_Width(fontdef, u);
        attr->widths[i] = w;
    }

    fontdef_attr = (BRST_Type1FontDefAttr)fontdef->attr;

    ret += BRST_Dict_AddName(font, "Type", "Font");
    ret += BRST_Dict_AddName(font, "BaseFont", fontdef->base_font);
    ret += BRST_Dict_AddName(font, "Subtype", "Type1");

    if (!fontdef_attr->is_base14font) {
        if (fontdef->missing_width != 0)
            ret += BRST_Dict_AddNumber(font, "MissingWidth",
                fontdef->missing_width);

        ret += Type1Font_CreateDescriptor(mmgr, font, xref);
    }

    if (ret != BRST_OK) {
        BRST_Dict_Free(font);
        return NULL;
    }

    if (BRST_Xref_Add(xref, font) != BRST_OK)
        return NULL;

    return font;
}

static BRST_STATUS
Type1Font_CreateDescriptor(BRST_MMgr mmgr,
    BRST_Font font,
    BRST_Xref xref)
{
    BRST_FontAttr font_attr        = (BRST_FontAttr)font->attr;
    BRST_FontDef def               = font_attr->fontdef;
    BRST_Type1FontDefAttr def_attr = (BRST_Type1FontDefAttr)def->attr;

    BRST_PTRACE(" BRST_Type1Font_CreateDescriptor\n");

    if (!font_attr->fontdef->descriptor) {
        BRST_Dict descriptor = BRST_Dict_New(mmgr);
        BRST_STATUS ret      = 0;
        BRST_Array array;

        if (!descriptor)
            return BRST_Error_Code(font->error);

        ret += BRST_Xref_Add(xref, descriptor);
        ret += BRST_Dict_AddName(descriptor, "Type", "FontDescriptor");
        ret += BRST_Dict_AddNumber(descriptor, "Ascent", def->ascent);
        ret += BRST_Dict_AddNumber(descriptor, "Descent", def->descent);
        ret += BRST_Dict_AddNumber(descriptor, "Flags", def->flags);

        array = BRST_Box_Array_New(mmgr, def->font_bbox);
        ret += BRST_Dict_Add(descriptor, "FontBBox", array);

        ret += BRST_Dict_AddName(descriptor, "FontName",
            font_attr->fontdef->base_font);
        ret += BRST_Dict_AddNumber(descriptor, "ItalicAngle",
            def->italic_angle);
        ret += BRST_Dict_AddNumber(descriptor, "StemV", def->stemv);
        ret += BRST_Dict_AddNumber(descriptor, "XHeight", def->x_height);

        if (def_attr->char_set)
            ret += BRST_Dict_AddName(descriptor, "CharSet",
                def_attr->char_set);

        if (ret != BRST_OK)
            return BRST_Error_Code(font->error);

        if (def_attr->font_data) {
            BRST_Dict font_data = BRST_Dict_New_Stream_Init(mmgr, xref);

            if (!font_data)
                return BRST_Error_Code(font->error);

            if (BRST_Stream_WriteToStream(def_attr->font_data,
                    font_data->stream, BRST_STREAM_FILTER_NONE, NULL)
                != BRST_OK)
                return BRST_Error_Code(font->error);

            ret += BRST_Dict_Add(descriptor, "FontFile", font_data);
            ret += BRST_Dict_AddNumber(font_data, "Length1",
                def_attr->length1);
            ret += BRST_Dict_AddNumber(font_data, "Length2",
                def_attr->length2);
            ret += BRST_Dict_AddNumber(font_data, "Length3",
                def_attr->length3);

            font_data->filter = font->filter;
        }

        if (ret != BRST_OK)
            return BRST_Error_Code(font->error);

        font_attr->fontdef->descriptor = descriptor;
    }

    return BRST_Dict_Add(font, "FontDescriptor",
        font_attr->fontdef->descriptor);
}

static BRST_TextWidth
Type1Font_TextWidth(BRST_Font font,
    const BRST_BYTE* text,
    BRST_UINT len)
{
    BRST_FontAttr attr = (BRST_FontAttr)font->attr;
    BRST_TextWidth ret = { 0, 0, 0, 0 };
    BRST_UINT i;
    BRST_BYTE b = 0;

    BRST_PTRACE(" BRST_Type1Font_TextWidth\n");

    if (attr->widths) {
        for (i = 0; i < len; i++) {
            b = text[i];
            ret.numchars++;
            ret.width += attr->widths[b];

            if (BRST_IS_WHITE_SPACE(b)) {
                ret.numspace++;
                ret.numwords++;
            }
        }
    } else
        BRST_Error_Set(font->error, BRST_FONT_INVALID_WIDTH_TABLE, 0);

    /* 2006.08.19 add. */
    if (BRST_IS_WHITE_SPACE(b))
        ; /* do nothing. */
    else
        ret.numwords++;

    return ret;
}

static BRST_UINT
Type1Font_MeasureText(BRST_Font font,
    const BRST_BYTE* text,
    BRST_UINT len,
    BRST_REAL width,
    BRST_REAL font_size,
    BRST_REAL char_space,
    BRST_REAL word_space,
    BRST_BOOL wordwrap,
    BRST_REAL* real_width)
{
    BRST_REAL w       = 0;
    BRST_UINT tmp_len = 0;
    BRST_UINT i;
    BRST_FontAttr attr = (BRST_FontAttr)font->attr;

    BRST_PTRACE(" BRST_Type1Font_MeasureText\n");

    for (i = 0; i < len; i++) {
        BRST_BYTE b = text[i];

        if (BRST_IS_WHITE_SPACE(b)) {
            tmp_len = i + 1;

            if (real_width)
                *real_width = w;

            w += word_space;
        } else if (!wordwrap) {
            tmp_len = i;

            if (real_width)
                *real_width = w;
        }

        w += attr->widths[b] * font_size / 1000;

        /* 2006.08.04 break when it encountered  line feed */
        if (w > width || b == 0x0A)
            return tmp_len;

        if (i > 0)
            w += char_space;
    }

    /* all of text can be put in the specified width */
    if (real_width)
        *real_width = w;

    return len;
}

static BRST_STATUS
Type1Font_OnWrite(BRST_Dict obj,
    BRST_Stream stream)
{
    BRST_FontAttr attr                 = (BRST_FontAttr)obj->attr;
    BRST_Type1FontDefAttr fontdef_attr = (BRST_Type1FontDefAttr)attr->fontdef->attr;
    BRST_BasicEncoderAttr encoder_attr = (BRST_BasicEncoderAttr)attr->encoder->attr;
    BRST_UINT i;
    BRST_STATUS ret;
    char buf[BRST_TMP_BUF_SIZE];
    char* eptr = buf + BRST_TMP_BUF_SIZE - 1;

    BRST_PTRACE(" BRST_Font_Type1Font_OnWrite\n");

    /* if font is base14-font these entries is not required */
    if (!fontdef_attr->is_base14font || encoder_attr->has_differences) {
        char* pbuf;

        pbuf = (char*)BRST_StrCpy(buf, "/FirstChar ", eptr);
        pbuf = BRST_IToA(pbuf, encoder_attr->first_char, eptr);
        BRST_StrCpy(pbuf, "\012", eptr);
        if ((ret = BRST_Stream_WriteStr(stream, buf)) != BRST_OK)
            return ret;

        pbuf = (char*)BRST_StrCpy(buf, "/LastChar ", eptr);
        pbuf = BRST_IToA(pbuf, encoder_attr->last_char, eptr);
        BRST_StrCpy(pbuf, "\012", eptr);
        if ((ret = BRST_Stream_WriteStr(stream, buf)) != BRST_OK)
            return ret;

        /* Widths entry */
        if ((ret = BRST_Stream_WriteEscapeName(stream, "Widths")) != BRST_OK)
            return ret;

        if ((ret = BRST_Stream_WriteStr(stream, " [\012")) != BRST_OK)
            return ret;

        pbuf = buf;
        for (i = encoder_attr->first_char; i <= encoder_attr->last_char; i++) {

            pbuf    = BRST_IToA(pbuf, attr->widths[i], eptr);
            *pbuf++ = ' ';

            if ((i + 1) % 16 == 0) {
                BRST_StrCpy(pbuf, "\012", eptr);
                if ((ret = BRST_Stream_WriteStr(stream, buf)) != BRST_OK)
                    return ret;
                pbuf = buf;
            }
        }

        BRST_StrCpy(pbuf, "]\012", eptr);

        if ((ret = BRST_Stream_WriteStr(stream, buf)) != BRST_OK)
            return ret;
    }

    return attr->encoder->write_fn(attr->encoder, stream);
}

static void
Type1Font_OnFree(BRST_Dict obj)
{
    BRST_FontAttr attr = (BRST_FontAttr)obj->attr;

    BRST_PTRACE(" BRST_Type1Font_OnFree\n");

    if (attr) {
        if (attr->widths) {
            BRST_FreeMem(obj->mmgr, attr->widths);
        }
        BRST_FreeMem(obj->mmgr, attr);
    }
}
