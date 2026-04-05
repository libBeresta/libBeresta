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
#include "private/brst_fontdef_ttf.h"
#include "private/brst_xref.h"
#include "brst_font.h"
#include "private/brst_font.h"
#include "private/brst_utils.h"
#include "brst_error.h"
#include "brst_consts.h"

static BRST_STATUS
OnWrite(BRST_Dict obj,
    BRST_Stream stream);

static BRST_STATUS
BeforeWrite(BRST_Dict obj);

static void
OnFree(BRST_Dict obj);

static BRST_INT
CharWidth(BRST_Font font,
    BRST_BYTE code);

static BRST_TextWidth
TextWidth(BRST_Font font,
    const BRST_BYTE* text,
    BRST_UINT len);

static BRST_STATUS
CreateDescriptor(BRST_Font font);

static BRST_UINT
MeasureText(BRST_Font font,
    const BRST_BYTE* text,
    BRST_UINT len,
    BRST_REAL width,
    BRST_REAL font_size,
    BRST_REAL char_space,
    BRST_REAL word_space,
    BRST_BOOL wordwrap,
    BRST_REAL* real_width);

BRST_Font
BRST_TTFont_New(BRST_MMgr mmgr,
    BRST_FontDef fontdef,
    BRST_Encoder encoder,
    BRST_Xref xref)
{
    BRST_Dict font;
    BRST_FontAttr attr;
    BRST_TTFontDefAttr fontdef_attr;
    BRST_BasicEncoderAttr encoder_attr;
    BRST_STATUS ret = 0;

    BRST_PTRACE(" BRST_TTFont_New\n");

    font = BRST_Dict_New(mmgr);
    if (!font)
        return NULL;

    font->header.obj_class |= BRST_OSUBCLASS_FONT;

    /* check whether the fontdef object and the encoder object is valid. */
    if (encoder->type != BRST_ENCODER_TYPE_SINGLE_BYTE) {
        BRST_Error_Set(font->error, BRST_INVALID_ENCODER_TYPE, 0);
        return NULL;
    }

    if (fontdef->type != BRST_FONTDEF_TYPE_TRUETYPE) {
        BRST_Error_Set(font->error, BRST_INVALID_FONTDEF_TYPE, 0);
        return NULL;
    }

    attr = BRST_GetMem(mmgr, sizeof(BRST_FontAttr_Rec));
    if (!attr) {
        BRST_Dict_Free(font);
        return NULL;
    }

    BRST_MemSet(attr, 0, sizeof(BRST_FontAttr_Rec));

    font->header.obj_class |= BRST_OSUBCLASS_FONT;
    font->write_fn        = OnWrite;
    font->before_write_fn = BeforeWrite;
    font->free_fn         = OnFree;
    font->attr            = attr;

    attr->type            = BRST_FONT_TRUETYPE;
    attr->writing_mode    = BRST_WMODE_HORIZONTAL;
    attr->text_width_fn   = TextWidth;
    attr->measure_text_fn = MeasureText;
    attr->fontdef         = fontdef;
    attr->encoder         = encoder;
    attr->xref            = xref;

    /* singlebyte-font has a widths-array which is an array of 256 signed
     * short integer.
     * in the case of type1-font, widths-array for all letters is made in
     * constructor. but in the case of true-type-font, the array is
     * initialized at 0, and set when the corresponding character was used
     * for the first time.
     */
    attr->widths = BRST_GetMem(mmgr, sizeof(BRST_INT16) * 256);
    if (!attr->widths) {
        BRST_Dict_Free(font);
        return NULL;
    }

    BRST_MemSet(attr->widths, 0, sizeof(BRST_INT16) * 256);

    attr->used = BRST_GetMem(mmgr, sizeof(BRST_BYTE) * 256);
    if (!attr->used) {
        BRST_Dict_Free(font);
        return NULL;
    }

    BRST_MemSet(attr->used, 0, sizeof(BRST_BYTE) * 256);

    fontdef_attr = (BRST_TTFontDefAttr)fontdef->attr;

    ret += BRST_Dict_AddName(font, "Type", "Font");
    ret += BRST_Dict_AddName(font, "BaseFont", fontdef_attr->base_font);
    ret += BRST_Dict_AddName(font, "Subtype", "TrueType");

    encoder_attr = (BRST_BasicEncoderAttr)encoder->attr;

    ret += BRST_Dict_AddNumber(font, "FirstChar", encoder_attr->first_char);
    ret += BRST_Dict_AddNumber(font, "LastChar", encoder_attr->last_char);
    if (fontdef->missing_width != 0)
        ret += BRST_Dict_AddNumber(font, "MissingWidth",
            fontdef->missing_width);

    if (ret != BRST_OK) {
        BRST_Dict_Free(font);
        return NULL;
    }

    if (BRST_Xref_Add(xref, font) != BRST_OK)
        return NULL;

    return font;
}

static BRST_STATUS
CreateDescriptor(BRST_Font font)
{
    BRST_FontAttr font_attr     = (BRST_FontAttr)font->attr;
    BRST_FontDef def            = font_attr->fontdef;
    BRST_TTFontDefAttr def_attr = (BRST_TTFontDefAttr)def->attr;

    BRST_PTRACE(" BRST_TTFont_CreateDescriptor\n");

    if (!font_attr->fontdef->descriptor) {
        BRST_Dict descriptor = BRST_Dict_New(font->mmgr);
        BRST_STATUS ret      = 0;
        BRST_Array array;

        if (!descriptor)
            return BRST_Error_Code(font->error);

        ret += BRST_Xref_Add(font_attr->xref, descriptor);
        ret += BRST_Dict_AddName(descriptor, "Type", "FontDescriptor");
        ret += BRST_Dict_AddNumber(descriptor, "Ascent", def->ascent);
        ret += BRST_Dict_AddNumber(descriptor, "Descent", def->descent);
        ret += BRST_Dict_AddNumber(descriptor, "CapHeight", def->cap_height);
        ret += BRST_Dict_AddNumber(descriptor, "Flags", def->flags);

        array = BRST_Box_Array_New(font->mmgr, def->font_bbox);
        ret += BRST_Dict_Add(descriptor, "FontBBox", array);

        ret += BRST_Dict_AddName(descriptor, "FontName", def_attr->base_font);
        ret += BRST_Dict_AddNumber(descriptor, "ItalicAngle",
            def->italic_angle);
        ret += BRST_Dict_AddNumber(descriptor, "StemV", def->stemv);
        ret += BRST_Dict_AddNumber(descriptor, "XHeight", def->x_height);

        if (def_attr->char_set)
            ret += BRST_Dict_AddName(descriptor, "CharSet",
                def_attr->char_set);

        if (ret != BRST_OK)
            return BRST_Error_Code(font->error);

        if (def_attr->embedding) {
            BRST_Dict font_data = BRST_Dict_New_Stream_Init(font->mmgr,
                font_attr->xref);

            if (!font_data)
                return BRST_Error_Code(font->error);

            if (BRST_TTFontDef_SaveFontData(font_attr->fontdef,
                    font_data->stream)
                != BRST_OK)
                return BRST_Error_Code(font->error);

            ret += BRST_Dict_Add(descriptor, "FontFile2", font_data);
            ret += BRST_Dict_AddNumber(font_data, "Length1",
                def_attr->length1);
            ret += BRST_Dict_AddNumber(font_data, "Length2", 0);
            ret += BRST_Dict_AddNumber(font_data, "Length3", 0);

            font_data->filter = font->filter;
        }

        if (ret != BRST_OK)
            return BRST_Error_Code(font->error);

        font_attr->fontdef->descriptor = descriptor;
    }

    return BRST_Dict_Add(font, "FontDescriptor",
        font_attr->fontdef->descriptor);
}

static BRST_INT
CharWidth(BRST_Font font,
    BRST_BYTE code)
{
    BRST_FontAttr attr = (BRST_FontAttr)font->attr;

    if (attr->used[code] == 0) {
        BRST_UNICODE unicode = BRST_Encoder_ToUnicode(attr->encoder, code);

        attr->used[code]   = 1;
        attr->widths[code] = BRST_TTFontDef_CharWidth(attr->fontdef,
            unicode);
    }

    return attr->widths[code];
}

static BRST_TextWidth
TextWidth(BRST_Font font,
    const BRST_BYTE* text,
    BRST_UINT len)
{
    BRST_FontAttr attr = (BRST_FontAttr)font->attr;
    BRST_TextWidth ret = { 0, 0, 0, 0 };
    BRST_UINT i;
    BRST_BYTE b = 0;

    BRST_PTRACE(" BRST_TTFont_TextWidth\n");

    if (attr->widths) {
        for (i = 0; i < len; i++) {
            b = text[i];
            ret.numchars++;
            ret.width += CharWidth(font, b);

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
MeasureText(BRST_Font font,
    const BRST_BYTE* text,
    BRST_UINT len,
    BRST_REAL width,
    BRST_REAL font_size,
    BRST_REAL char_space,
    BRST_REAL word_space,
    BRST_BOOL wordwrap,
    BRST_REAL* real_width)
{
    BRST_DOUBLE w     = 0;
    BRST_UINT tmp_len = 0;
    BRST_UINT i;

    BRST_PTRACE(" BRST_TTFont_MeasureText\n");

    for (i = 0; i < len; i++) {
        BRST_BYTE b = text[i];

        if (BRST_IS_WHITE_SPACE(b)) {
            tmp_len = i + 1;

            if (real_width)
                *real_width = (BRST_REAL)w;

            w += word_space;
        } else if (!wordwrap) {
            tmp_len = i;

            if (real_width)
                *real_width = (BRST_REAL)w;
        }

        w += (BRST_DOUBLE)CharWidth(font, b) * font_size / 1000;

        /* 2006.08.04 break when it encountered  line feed */
        if (w > width || b == 0x0A)
            return tmp_len;

        if (i > 0)
            w += char_space;
    }

    /* all of text can be put in the specified width */
    if (real_width)
        *real_width = (BRST_REAL)w;
    return len;
}

static BRST_STATUS
OnWrite(BRST_Dict obj,
    BRST_Stream stream)
{
    BRST_FontAttr attr                 = (BRST_FontAttr)obj->attr;
    BRST_BasicEncoderAttr encoder_attr = (BRST_BasicEncoderAttr)attr->encoder->attr;
    BRST_UINT i;
    BRST_STATUS ret;
    char buf[128];
    char* pbuf = buf;
    char* eptr = buf + 127;

    BRST_PTRACE(" BRST_Font_OnWrite\n");

    /* Widths entry */
    if ((ret = BRST_Stream_WriteEscapeName(stream, "Widths")) != BRST_OK)
        return ret;

    if ((ret = BRST_Stream_WriteStr(stream, " [\012")) != BRST_OK)
        return ret;

    for (i = encoder_attr->first_char; i <= encoder_attr->last_char; i++) {

        pbuf    = BRST_IToA(pbuf, attr->widths[i], eptr);
        *pbuf++ = ' ';

        if ((i + 1) % 16 == 0) {
            BRST_StrCopy(pbuf, "\012", eptr);
            if ((ret = BRST_Stream_WriteStr(stream, buf)) != BRST_OK)
                return ret;
            pbuf = buf;
        }
    }

    BRST_StrCopy(pbuf, "]\012", eptr);

    if ((ret = BRST_Stream_WriteStr(stream, buf)) != BRST_OK)
        return ret;

    return attr->encoder->write_fn(attr->encoder, stream);
}

static BRST_STATUS
BeforeWrite(BRST_Dict obj)
{
    BRST_PTRACE(" BRST_TTFont_BeforeWrite\n");

    return CreateDescriptor(obj);
}

static void
OnFree(BRST_Dict obj)
{
    BRST_FontAttr attr = (BRST_FontAttr)obj->attr;

    BRST_PTRACE(" BRST_TTFont_OnFree\n");

    if (attr) {
        if (attr->widths) {
            BRST_FreeMem(obj->mmgr, attr->widths);
        }

        if (attr->used) {
            BRST_FreeMem(obj->mmgr, attr->used);
        }

        BRST_FreeMem(obj->mmgr, attr);
    }
}
