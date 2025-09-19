#include "brst_external.h"
#include "brst_types.h"
#include "brst_mmgr.h"
#include "brst_encrypt.h"
#include "brst_stream.h"
#include "brst_dict.h"
#include "brst_xref.h"
#include "brst_encoder.h"
#include "private/brst_list.h"
#include "private/brst_defines.h"
#include "private/brst_encoder.h"
#include "private/brst_encoder_cmap.h"
#include "brst_error.h"
#include "brst_consts.h"
#include "brst_font.h"
#include "private/brst_font.h"
#include "brst_consts.h"
#include "brst_font.h"
#include "private/brst_encrypt_dict.h"
#include "brst_base.h"
#include "private/brst_fontdef.h"
#include "private/brst_fontdef_type1.h"
#include "private/brst_fontdef_ttf.h"
#include "private/brst_fontdef_cid.h"
#include "private/brst_utils.h"

BRST_EXPORT(BRST_TextWidth)
BRST_Font_TextWidth(BRST_Font font,
    const BRST_BYTE* text,
    BRST_UINT len)
{
    BRST_TextWidth tw = { 0, 0, 0, 0 };
    BRST_FontAttr attr;

    BRST_PTRACE(" BRST_Font_TextWidth\n");

    if (!BRST_Font_Validate(font))
        return tw;

    if (len > BRST_LIMIT_MAX_STRING_LEN) {
        BRST_Error_Raise(font->error, BRST_STRING_OUT_OF_RANGE, 0);
        return tw;
    }

    attr = (BRST_FontAttr)font->attr;

    if (!attr->text_width_fn) {
        BRST_Error_Set(font->error, BRST_INVALID_OBJECT, 0);
        return tw;
    }

    tw = attr->text_width_fn(font, text, len);

    return tw;
}


// То же, что и BRST_Font_TextWidth(), но без косвенного возврата.
// Если со шрифтом проблемы, возвращает отрицательное значение.
BRST_EXPORT(BRST_REAL)
BRST_Font_TextWidth2(BRST_Font font,
    BRST_REAL font_size,
    BRST_REAL word_space,
    BRST_REAL char_space,
    BRST_CSTR text
) {

    if (!BRST_Font_Validate(font) || font_size <= 0 || text == NULL) {
        return -1;
    }

    BRST_REAL ret = 0;

    BRST_UINT len = BRST_StrLen(text, BRST_LIMIT_MAX_STRING_LEN + 1);
    BRST_TextWidth tw = BRST_Font_TextWidth(font, (BRST_BYTE*)text, len);

    ret += word_space * tw.numspace;
    ret += tw.width   * font_size / 1000;
    ret += char_space * tw.numchars;

    return ret;
}


BRST_EXPORT(BRST_UINT)
BRST_Font_MeasureText(BRST_Font font,
    const BRST_BYTE* text,
    BRST_UINT len,
    BRST_REAL width,
    BRST_REAL font_size,
    BRST_REAL char_space,
    BRST_REAL word_space,
    BRST_BOOL wordwrap,
    BRST_REAL* real_width)
{
    BRST_FontAttr attr;

    BRST_PTRACE(" BRST_Font_MeasureText\n");

    if (!BRST_Font_Validate(font))
        return 0;

    if (len > BRST_LIMIT_MAX_STRING_LEN) {
        BRST_Error_Raise(font->error, BRST_STRING_OUT_OF_RANGE, 0);
        return 0;
    }

    attr = (BRST_FontAttr)font->attr;

    if (!attr->measure_text_fn) {
        BRST_Error_Raise(font->error, BRST_INVALID_OBJECT, 0);
        return 0;
    }

    return attr->measure_text_fn(font, text, len, width, font_size,
        char_space, word_space, wordwrap, real_width);
}

BRST_EXPORT(const char*)
BRST_Font_FontName(BRST_Font font)
{
    BRST_FontAttr attr;

    BRST_PTRACE(" BRST_Font_FontName\n");

    if (!BRST_Font_Validate(font))
        return NULL;

    attr = (BRST_FontAttr)font->attr;

    return attr->fontdef->base_font;
}

BRST_EXPORT(const char*)
BRST_Font_EncodingName(BRST_Font font)
{
    BRST_FontAttr attr;

    BRST_PTRACE(" BRST_Font_EncodingName\n");

    if (!BRST_Font_Validate(font))
        return NULL;

    attr = (BRST_FontAttr)font->attr;

    return attr->encoder->name;
}

BRST_EXPORT(BRST_INT)
BRST_Font_UnicodeWidth(BRST_Font font,
    BRST_UNICODE code)
{
    BRST_FontAttr attr;
    BRST_FontDef fontdef;

    BRST_PTRACE(" BRST_Font_UnicodeWidth\n");

    if (!BRST_Font_Validate(font))
        return 0;

    attr    = (BRST_FontAttr)font->attr;
    fontdef = attr->fontdef;

    if (fontdef->type == BRST_FONTDEF_TYPE_TYPE1) {
        return BRST_Type1FontDef_Width(fontdef, code);
    } else if (fontdef->type == BRST_FONTDEF_TYPE_TRUETYPE) {
        return BRST_TTFontDef_CharWidth(fontdef, code);
    } else if (fontdef->type == BRST_FONTDEF_TYPE_CID) {
        BRST_CMapEncoderAttr encoder_attr = (BRST_CMapEncoderAttr)attr->encoder->attr;
        BRST_UINT l, h;

        for (l = 0; l <= 255; l++) {
            for (h = 0; h < 255; h++) {
                if (code == encoder_attr->unicode_map[l][h]) {
                    BRST_UINT16 cid = encoder_attr->cid_map[l][h];

                    return BRST_CIDFontDef_CIDWidth(fontdef, cid);
                }
            }
        }
    }

    BRST_PTRACE(" BRST_Font_GetUnicodeWidth not found (0x%04X)\n", code);

    return 0;
}

BRST_EXPORT(BRST_Box)
BRST_Font_BBox(BRST_Font font)
{
    BRST_Box bbox = { 0, 0, 0, 0 };

    BRST_PTRACE(" BRST_Font_BBox\n");
    if (BRST_Font_Validate(font))
        return ((BRST_FontAttr)font->attr)->fontdef->font_bbox;

    return bbox;
}

BRST_EXPORT(BRST_INT)
BRST_Font_Ascent(BRST_Font font)
{
    BRST_PTRACE(" BRST_Font_Ascent\n");

    if (BRST_Font_Validate(font))
        return ((BRST_FontAttr)font->attr)->fontdef->ascent;

    return 0;
}

BRST_EXPORT(BRST_INT)
BRST_Font_Descent(BRST_Font font)
{
    BRST_PTRACE(" BRST_Font_Descent\n");

    if (BRST_Font_Validate(font))
        return ((BRST_FontAttr)font->attr)->fontdef->descent;

    return 0;
}

BRST_EXPORT(BRST_UINT)
BRST_Font_XHeight(BRST_Font font)
{
    BRST_PTRACE(" BRST_Font_XHeight\n");

    if (BRST_Font_Validate(font))
        return ((BRST_FontAttr)font->attr)->fontdef->x_height;

    return 0;
}

BRST_EXPORT(BRST_UINT)
BRST_Font_CapHeight(BRST_Font font)
{
    BRST_PTRACE(" BRST_Font_CapHeight\n");

    if (BRST_Font_Validate(font))
        return ((BRST_FontAttr)font->attr)->fontdef->cap_height;

    return 0;
}
