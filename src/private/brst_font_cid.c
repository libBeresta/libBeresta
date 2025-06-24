#include "brst_types.h"
#include "brst_encrypt.h"
#include "brst_mmgr.h"
#include "brst_stream.h"
#include "brst_encoder.h"
#include "private/brst_encoder.h"
#include "private/brst_encoder_basic.h"
#include "private/brst_encoder_cmap.h"
#include "brst_dict.h"
#include "private/brst_dict.h"
#include "private/brst_string.h"
#include "brst_array.h"
#include "private/brst_array.h"
#include "private/brst_defines.h"
#include "brst_fontdef.h"
#include "private/brst_fontdef.h"
#include "private/brst_fontdef_cid.h"
#include "private/brst_fontdef_ttf.h"
#include "brst_xref.h"
#include "private/brst_xref.h"
#include "brst_font.h"
#include "private/brst_font.h"
#include "private/brst_utils.h"
#include "brst_error.h"
#include "brst_consts.h"

static BRST_Font
CIDFontType0_New(BRST_Font parent,
    BRST_Xref xref);

static BRST_Font
CIDFontType2_New(BRST_Font parent,
    BRST_Xref xref);

static BRST_TextWidth
TextWidth(BRST_Font font,
    const BRST_BYTE* text,
    BRST_UINT len);

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

static char*
UINT16ToHex(char* s,
    BRST_UINT16 val,
    char* eptr,
    BRST_BYTE width);

static char*
CidRangeToHex(char* s,
    BRST_UINT16 from,
    BRST_UINT16 to,
    char* eptr);

static BRST_Dict
CreateCMap(BRST_Encoder encoder,
    BRST_Xref xref);

static void
OnFree_Func(BRST_Dict obj);

static BRST_STATUS
CIDFontType2_BeforeWrite_Func(BRST_Dict obj);

/*--------------------------------------------------------------------------*/

BRST_Font
BRST_Type0Font_New(BRST_MMgr mmgr,
    BRST_FontDef fontdef,
    BRST_Encoder encoder,
    BRST_Xref xref)
{
    BRST_Dict font;
    BRST_FontAttr attr;
    BRST_CMapEncoderAttr encoder_attr;
    BRST_STATUS ret = 0;
    BRST_Array descendant_fonts;

    BRST_PTRACE((" BRST_Type0Font_New\n"));

    font = BRST_Dict_New(mmgr);
    if (!font)
        return NULL;

    font->header.obj_class |= BRST_OSUBCLASS_FONT;

    /* check whether the fontdef object and the encoder object is valid. */
    if (encoder->type != BRST_ENCODER_TYPE_DOUBLE_BYTE) {
        BRST_Error_Set(font->error, BRST_INVALID_ENCODER_TYPE, 0);
        return NULL;
    }

    if (fontdef->type != BRST_FONTDEF_TYPE_CID && fontdef->type != BRST_FONTDEF_TYPE_TRUETYPE) {
        BRST_Error_Set(font->error, BRST_INVALID_FONTDEF_TYPE, 0);
        return NULL;
    }

    attr = BRST_GetMem(mmgr, sizeof(BRST_FontAttr_Rec));
    if (!attr) {
        BRST_Dict_Free(font);
        return NULL;
    }

    font->header.obj_class |= BRST_OSUBCLASS_FONT;
    font->write_fn = NULL;
    font->free_fn  = OnFree_Func;
    font->attr     = attr;

    encoder_attr = (BRST_CMapEncoderAttr)encoder->attr;

    BRST_MemSet(attr, 0, sizeof(BRST_FontAttr_Rec));

    attr->writing_mode    = encoder_attr->writing_mode;
    attr->text_width_fn   = TextWidth;
    attr->measure_text_fn = MeasureText;
    attr->fontdef         = fontdef;
    attr->encoder         = encoder;
    attr->xref            = xref;

    if (BRST_Xref_Add(xref, font) != BRST_OK)
        return NULL;

    ret += BRST_Dict_AddName(font, "Type", "Font");
    ret += BRST_Dict_AddName(font, "BaseFont", fontdef->base_font);
    ret += BRST_Dict_AddName(font, "Subtype", "Type0");

    if (fontdef->type == BRST_FONTDEF_TYPE_CID) {
        ret += BRST_Dict_AddName(font, "Encoding", encoder->name);
    } else {
        /*
         * Handle the Unicode encoding, see brst_encoding_utf.c For some
         * reason, xpdf-based readers cannot deal with our cmap but work
         * fine when using the predefined "Identity-H"
         * encoding. However, text selection does not work, unless we
         * add a ToUnicode cmap. This CMap should also be "Identity",
         * but that does not work -- specifying our cmap as a stream however
         * does work. Who can understand that ?
         */
        if (BRST_StrCmp(encoder_attr->ordering, "Identity-H") == 0) {
            ret += BRST_Dict_AddName(font, "Encoding", "Identity-H");
            attr->cmap_stream = CreateCMap(encoder, xref);

            if (attr->cmap_stream) {
                ret += BRST_Dict_Add(font, "ToUnicode", attr->cmap_stream);
            } else
                return NULL;
        } else {
            attr->cmap_stream = CreateCMap(encoder, xref);

            if (attr->cmap_stream) {
                ret += BRST_Dict_Add(font, "Encoding", attr->cmap_stream);
            } else
                return NULL;
        }
    }

    if (ret != BRST_OK)
        return NULL;

    descendant_fonts = BRST_Array_New(mmgr);
    if (!descendant_fonts)
        return NULL;

    if (BRST_Dict_Add(font, "DescendantFonts", descendant_fonts) != BRST_OK)
        return NULL;

    if (fontdef->type == BRST_FONTDEF_TYPE_CID) {
        attr->descendant_font = CIDFontType0_New(font, xref);
        attr->type            = BRST_FONT_TYPE0_CID;
    } else {
        attr->descendant_font = CIDFontType2_New(font, xref);
        attr->type            = BRST_FONT_TYPE0_TT;
    }

    if (!attr->descendant_font)
        return NULL;
    else if (BRST_Array_Add(descendant_fonts, attr->descendant_font) != BRST_OK)
        return NULL;

    return font;
}

static void
OnFree_Func(BRST_Dict obj)
{
    BRST_FontAttr attr = (BRST_FontAttr)obj->attr;

    BRST_PTRACE((" BRST_Type0Font_OnFree\n"));

    if (attr)
        BRST_FreeMem(obj->mmgr, attr);
}

static BRST_Font
CIDFontType0_New(BRST_Font parent, BRST_Xref xref)
{
    BRST_STATUS ret                   = BRST_OK;
    BRST_FontAttr attr                = (BRST_FontAttr)parent->attr;
    BRST_FontDef fontdef              = attr->fontdef;
    BRST_CIDFontDefAttr fontdef_attr  = (BRST_CIDFontDefAttr)fontdef->attr;
    BRST_Encoder encoder              = attr->encoder;
    BRST_CMapEncoderAttr encoder_attr = (BRST_CMapEncoderAttr)encoder->attr;

    BRST_UINT16 save_cid = 0;
    BRST_Font font;
    BRST_Array array;
    BRST_Array sub_array = NULL;
    BRST_UINT i;

    BRST_Dict descriptor;
    BRST_Dict cid_system_info;

    BRST_PTRACE((" BRST_CIDFontType0_New\n"));

    font = BRST_Dict_New(parent->mmgr);
    if (!font)
        return NULL;

    if (BRST_Xref_Add(xref, font) != BRST_OK)
        return NULL;

    ret += BRST_Dict_AddName(font, "Type", "Font");
    ret += BRST_Dict_AddName(font, "Subtype", "CIDFontType0");
    ret += BRST_Dict_AddNumber(font, "DW", fontdef_attr->DW);
    ret += BRST_Dict_AddName(font, "BaseFont", fontdef->base_font);
    if (ret != BRST_OK)
        return NULL;

    /* add 'DW2' element */
    array = BRST_Array_New(parent->mmgr);
    if (!array)
        return NULL;

    if (BRST_Dict_Add(font, "DW2", array) != BRST_OK)
        return NULL;

    ret += BRST_Array_AddNumber(array, fontdef_attr->DW2[0]);
    ret += BRST_Array_AddNumber(array, fontdef_attr->DW2[1]);

    if (ret != BRST_OK)
        return NULL;

    /* add 'W' element */
    array = BRST_Array_New(parent->mmgr);
    if (!array)
        return NULL;

    if (BRST_Dict_Add(font, "W", array) != BRST_OK)
        return NULL;

    /* Create W array. */
    for (i = 0; i < BRST_List_Count(fontdef_attr->widths); i++) {
        BRST_CID_Width* w = (BRST_CID_Width*)BRST_List_ItemAt(fontdef_attr->widths, i);

        if (w->cid != save_cid + 1 || !sub_array) {
            sub_array = BRST_Array_New(parent->mmgr);
            if (!sub_array)
                return NULL;

            ret += BRST_Array_AddNumber(array, w->cid);
            ret += BRST_Array_Add(array, sub_array);
        }

        ret += BRST_Array_AddNumber(sub_array, w->width);
        save_cid = w->cid;

        if (ret != BRST_OK)
            return NULL;
    }

    /* create descriptor */
    descriptor = BRST_Dict_New(parent->mmgr);
    if (!descriptor)
        return NULL;

    if (BRST_Xref_Add(xref, descriptor) != BRST_OK)
        return NULL;

    if (BRST_Dict_Add(font, "FontDescriptor", descriptor) != BRST_OK)
        return NULL;

    ret += BRST_Dict_AddName(descriptor, "Type", "FontDescriptor");
    ret += BRST_Dict_AddName(descriptor, "FontName", fontdef->base_font);
    ret += BRST_Dict_AddNumber(descriptor, "Ascent", fontdef->ascent);
    ret += BRST_Dict_AddNumber(descriptor, "Descent", fontdef->descent);
    ret += BRST_Dict_AddNumber(descriptor, "CapHeight",
        fontdef->cap_height);
    ret += BRST_Dict_AddNumber(descriptor, "MissingWidth",
        fontdef->missing_width);
    ret += BRST_Dict_AddNumber(descriptor, "Flags", fontdef->flags);

    if (ret != BRST_OK)
        return NULL;

    array = BRST_Box_Array_New(parent->mmgr, fontdef->font_bbox);
    if (!array)
        return NULL;

    ret += BRST_Dict_Add(descriptor, "FontBBox", array);
    ret += BRST_Dict_AddNumber(descriptor, "ItalicAngle",
        fontdef->italic_angle);
    ret += BRST_Dict_AddNumber(descriptor, "StemV", fontdef->stemv);

    if (ret != BRST_OK)
        return NULL;

    /* create CIDSystemInfo dictionary */
    cid_system_info = BRST_Dict_New(parent->mmgr);
    if (!cid_system_info)
        return NULL;

    if (BRST_Dict_Add(font, "CIDSystemInfo", cid_system_info) != BRST_OK)
        return NULL;

    ret += BRST_Dict_Add(cid_system_info, "Registry",
        BRST_String_New(parent->mmgr, encoder_attr->registry, NULL));
    ret += BRST_Dict_Add(cid_system_info, "Ordering",
        BRST_String_New(parent->mmgr, encoder_attr->ordering, NULL));
    ret += BRST_Dict_AddNumber(cid_system_info, "Supplement",
        encoder_attr->supplement);

    if (ret != BRST_OK)
        return NULL;

    return font;
}

static BRST_Font
CIDFontType2_New(BRST_Font parent, BRST_Xref xref)
{
    BRST_STATUS ret                   = BRST_OK;
    BRST_FontAttr attr                = (BRST_FontAttr)parent->attr;
    BRST_FontDef fontdef              = attr->fontdef;
    BRST_TTFontDefAttr fontdef_attr   = (BRST_TTFontDefAttr)fontdef->attr;
    BRST_Encoder encoder              = attr->encoder;
    BRST_CMapEncoderAttr encoder_attr = (BRST_CMapEncoderAttr)encoder->attr;

    BRST_Font font;
    BRST_Array array;
    BRST_UINT i;
    BRST_UNICODE tmp_map[65536];
    BRST_Dict cid_system_info;

    BRST_UINT16 max = 0;

    BRST_PTRACE((" BRST_CIDFontType2_New\n"));

    font = BRST_Dict_New(parent->mmgr);
    if (!font)
        return NULL;

    if (BRST_Xref_Add(xref, font) != BRST_OK)
        return NULL;

    parent->before_write_fn = CIDFontType2_BeforeWrite_Func;

    ret += BRST_Dict_AddName(font, "Type", "Font");
    ret += BRST_Dict_AddName(font, "Subtype", "CIDFontType2");
    ret += BRST_Dict_AddNumber(font, "DW", fontdef->missing_width);
    if (ret != BRST_OK)
        return NULL;

    /* add 'DW2' element */
    array = BRST_Array_New(font->mmgr);
    if (!array)
        return NULL;

    if (BRST_Dict_Add(font, "DW2", array) != BRST_OK)
        return NULL;

    ret += BRST_Array_AddNumber(array, (BRST_INT32)(fontdef->font_bbox.bottom));
    ret += BRST_Array_AddNumber(array, (BRST_INT32)(fontdef->font_bbox.bottom - fontdef->font_bbox.top));

    BRST_MemSet(tmp_map, 0, sizeof(BRST_UNICODE) * 65536);

    if (ret != BRST_OK)
        return NULL;

    for (i = 0; i < 256; i++) {
        BRST_UINT j;

        for (j = 0; j < 256; j++) {
            if (encoder->to_unicode_fn == BRST_CMapEncoder_ToUnicode) {
                BRST_UINT16 cid = encoder_attr->cid_map[i][j];
                if (cid != 0) {
                    BRST_UNICODE unicode = encoder_attr->unicode_map[i][j];
                    BRST_UINT16 gid      = BRST_TTFontDef_Glyphid(fontdef,
                             unicode);
                    tmp_map[cid]         = gid;
                    if (max < cid)
                        max = cid;
                }
            } else {
                BRST_UNICODE unicode = (i << 8) | j;
                BRST_UINT16 gid      = BRST_TTFontDef_Glyphid(fontdef,
                         unicode);
                tmp_map[unicode]     = gid;
                if (max < unicode)
                    max = unicode;
            }
        }
    }

    if (max > 0) {
        BRST_INT16 dw          = fontdef->missing_width;
        BRST_UNICODE* ptmp_map = tmp_map;
        BRST_Array tmp_array   = NULL;

        /* add 'W' element */
        array = BRST_Array_New(font->mmgr);
        if (!array)
            return NULL;

        if (BRST_Dict_Add(font, "W", array) != BRST_OK)
            return NULL;

        for (i = 0; i < max; i++, ptmp_map++) {
            BRST_INT w = BRST_TTFontDef_GidWidth(fontdef, *ptmp_map);

            if (w != dw) {
                if (!tmp_array) {
                    if (BRST_Array_AddNumber(array, i) != BRST_OK)
                        return NULL;

                    tmp_array = BRST_Array_New(font->mmgr);
                    if (!tmp_array)
                        return NULL;

                    if (BRST_Array_Add(array, tmp_array) != BRST_OK)
                        return NULL;
                }

                if ((ret = BRST_Array_AddNumber(tmp_array, w)) != BRST_OK)
                    return NULL;
            } else
                tmp_array = NULL;
        }

        /* create "CIDToGIDMap" data */
        if (fontdef_attr->embedding) {
            attr->map_stream = BRST_DictStream_New(font->mmgr, xref);
            if (!attr->map_stream)
                return NULL;

            if (BRST_Dict_Add(font, "CIDToGIDMap", attr->map_stream) != BRST_OK)
                return NULL;

            for (i = 0; i < max; i++) {
                BRST_BYTE u[2];
                BRST_UINT16 gid = tmp_map[i];

                u[0] = (BRST_BYTE)(gid >> 8);
                u[1] = (BRST_BYTE)gid;

                BRST_MemCpy((BRST_BYTE*)(tmp_map + i), u, 2);
            }

            if ((ret = BRST_Stream_Write(attr->map_stream->stream,
                     (BRST_BYTE*)tmp_map, max * 2))
                != BRST_OK)
                return NULL;
        }
    } else {
        BRST_Error_Set(font->error, BRST_INVALID_FONTDEF_DATA, 0);
        return 0;
    }

    /* create CIDSystemInfo dictionary */
    cid_system_info = BRST_Dict_New(parent->mmgr);
    if (!cid_system_info)
        return NULL;

    if (BRST_Dict_Add(font, "CIDSystemInfo", cid_system_info) != BRST_OK)
        return NULL;

    ret += BRST_Dict_Add(cid_system_info, "Registry",
        BRST_String_New(parent->mmgr, encoder_attr->registry, NULL));
    ret += BRST_Dict_Add(cid_system_info, "Ordering",
        BRST_String_New(parent->mmgr, encoder_attr->ordering, NULL));
    ret += BRST_Dict_AddNumber(cid_system_info, "Supplement",
        encoder_attr->supplement);

    if (ret != BRST_OK)
        return NULL;

    return font;
}

static BRST_STATUS
CIDFontType2_BeforeWrite_Func(BRST_Dict obj)
{
    BRST_FontAttr font_attr     = (BRST_FontAttr)obj->attr;
    BRST_FontDef def            = font_attr->fontdef;
    BRST_TTFontDefAttr def_attr = (BRST_TTFontDefAttr)def->attr;
    BRST_STATUS ret             = 0;

    BRST_PTRACE((" CIDFontType2_BeforeWrite_Func\n"));

    if (font_attr->map_stream)
        font_attr->map_stream->filter = obj->filter;

    if (font_attr->cmap_stream)
        font_attr->cmap_stream->filter = obj->filter;

    if (!font_attr->fontdef->descriptor) {
        BRST_Dict descriptor = BRST_Dict_New(obj->mmgr);
        BRST_Array array;

        if (!descriptor)
            return BRST_Error_Code(obj->error);

        if (def_attr->embedding) {
            BRST_Dict font_data = BRST_DictStream_New(obj->mmgr,
                font_attr->xref);

            if (!font_data)
                return BRST_Error_Code(obj->error);

            if (BRST_TTFontDef_SaveFontData(font_attr->fontdef,
                    font_data->stream)
                != BRST_OK)
                return BRST_Error_Code(obj->error);

            ret += BRST_Dict_Add(descriptor, "FontFile2", font_data);
            ret += BRST_Dict_AddNumber(font_data, "Length1",
                def_attr->length1);
            ret += BRST_Dict_AddNumber(font_data, "Length2", 0);
            ret += BRST_Dict_AddNumber(font_data, "Length3", 0);

            font_data->filter = obj->filter;

            if (ret != BRST_OK)
                return BRST_Error_Code(obj->error);
        }

        ret += BRST_Xref_Add(font_attr->xref, descriptor);
        ret += BRST_Dict_AddName(descriptor, "Type", "FontDescriptor");
        ret += BRST_Dict_AddNumber(descriptor, "Ascent", def->ascent);
        ret += BRST_Dict_AddNumber(descriptor, "Descent", def->descent);
        ret += BRST_Dict_AddNumber(descriptor, "CapHeight", def->cap_height);
        ret += BRST_Dict_AddNumber(descriptor, "Flags", def->flags);

        array = BRST_Box_Array_New(obj->mmgr, def->font_bbox);
        ret += BRST_Dict_Add(descriptor, "FontBBox", array);

        ret += BRST_Dict_AddName(descriptor, "FontName", def_attr->base_font);
        ret += BRST_Dict_AddNumber(descriptor, "ItalicAngle",
            def->italic_angle);
        ret += BRST_Dict_AddNumber(descriptor, "StemV", def->stemv);
        ret += BRST_Dict_AddNumber(descriptor, "XHeight", def->x_height);

        if (ret != BRST_OK)
            return BRST_Error_Code(obj->error);

        font_attr->fontdef->descriptor = descriptor;
    }

    if ((ret = BRST_Dict_AddName(obj, "BaseFont",
             def_attr->base_font))
        != BRST_OK)
        return ret;

    if ((ret = BRST_Dict_AddName(font_attr->descendant_font, "BaseFont",
             def_attr->base_font))
        != BRST_OK)
        return ret;

    return BRST_Dict_Add(font_attr->descendant_font, "FontDescriptor",
        font_attr->fontdef->descriptor);
}

static BRST_TextWidth
TextWidth(BRST_Font font,
    const BRST_BYTE* text,
    BRST_UINT len)
{
    BRST_TextWidth tw  = { 0, 0, 0, 0 };
    BRST_FontAttr attr = (BRST_FontAttr)font->attr;
    BRST_ParseText_Rec parse_state;
    BRST_Encoder encoder = attr->encoder;
    BRST_UINT i          = 0;
    BRST_INT dw2;
    BRST_BYTE b = 0;

    BRST_PTRACE((" BRST_Type0Font_TextWidth\n"));

    if (attr->fontdef->type == BRST_FONTDEF_TYPE_CID) {
        BRST_CIDFontDefAttr cid_fontdef_attr = (BRST_CIDFontDefAttr)attr->fontdef->attr;
        dw2                                  = cid_fontdef_attr->DW2[1];
    } else {
        dw2 = (BRST_INT)(attr->fontdef->font_bbox.bottom - attr->fontdef->font_bbox.top);
    }

    BRST_Encoder_SetParseText(encoder, &parse_state, text, len);

    while (i < len) {
        BRST_ByteType btype = (encoder->byte_type_fn)(encoder, &parse_state);
        BRST_UINT16 cid;
        BRST_UNICODE unicode;
        BRST_UINT16 code;
        BRST_UINT w = 0;

        b    = *text++;
        code = b;

        if (btype == BRST_BYTE_TYPE_LEAD) {
            code <<= 8;
            code = (BRST_UINT16)(code + *text);
        }

        if (btype != BRST_BYTE_TYPE_TRAIL) {
            if (attr->writing_mode == BRST_WMODE_HORIZONTAL) {
                if (attr->fontdef->type == BRST_FONTDEF_TYPE_CID) {
                    /* cid-based font */
                    cid = BRST_CMapEncoder_ToCID(encoder, code);
                    w   = BRST_CIDFontDef_CIDWidth(attr->fontdef, cid);
                } else {
                    /* unicode-based font */
                    unicode = (encoder->to_unicode_fn)(encoder, code);
                    w       = BRST_TTFontDef_CharWidth(attr->fontdef, unicode);
                }
            } else {
                w = -dw2;
            }

            tw.numchars++;
        }

        if (BRST_IS_WHITE_SPACE(code)) {
            tw.numwords++;
            tw.numspace++;
        }

        tw.width += w;
        i++;
    }

    /* 2006.08.19 add. */
    if (BRST_IS_WHITE_SPACE(b))
        ; /* do nothing. */
    else
        tw.numwords++;

    return tw;
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
    BRST_REAL w       = 0;
    BRST_UINT tmp_len = 0;
    BRST_UINT i;
    BRST_FontAttr attr = (BRST_FontAttr)font->attr;
    // Comment to make compiler happy
    // BRST_ByteType last_btype = BRST_BYTE_TYPE_TRAIL;
    BRST_Encoder encoder = attr->encoder;
    BRST_ParseText_Rec parse_state;
    BRST_INT dw2;

    BRST_PTRACE((" BRST_Type0Font_MeasureText\n"));

    if (attr->fontdef->type == BRST_FONTDEF_TYPE_CID) {
        BRST_CIDFontDefAttr cid_fontdef_attr = (BRST_CIDFontDefAttr)attr->fontdef->attr;
        dw2                                  = cid_fontdef_attr->DW2[1];
    } else {
        dw2 = (BRST_INT)(attr->fontdef->font_bbox.bottom - attr->fontdef->font_bbox.top);
    }

    BRST_Encoder_SetParseText(encoder, &parse_state, text, len);

    for (i = 0; i < len; i++) {
        BRST_BYTE b         = *text++;
        BRST_BYTE b2        = *text; /* next byte */
        BRST_ByteType btype = BRST_Encoder_ByteType_Internal(encoder, &parse_state);
        BRST_UNICODE unicode;
        BRST_UINT16 code  = b;
        BRST_UINT16 tmp_w = 0;

        if (btype == BRST_BYTE_TYPE_LEAD) {
            code <<= 8;
            code = (BRST_UINT16)(code + b2);
        }

        if (!wordwrap) {
            if (BRST_IS_WHITE_SPACE(b)) {
                tmp_len = i + 1;
                if (real_width)
                    *real_width = w;
            } else if (btype == BRST_BYTE_TYPE_SINGLE || btype == BRST_BYTE_TYPE_LEAD) {
                tmp_len = i;
                if (real_width)
                    *real_width = w;
            }
        } else {
            if (BRST_IS_WHITE_SPACE(b)) {
                tmp_len = i + 1;
                if (real_width)
                    *real_width = w;
            }
            /* else
            // Commenting this out fixes problem with BRST_Text_Rect() splitting the words
            if (last_btype == BRST_BYTE_TYPE_TRAIL ||
                    (btype == BRST_BYTE_TYPE_LEAD &&
                    last_btype == BRST_BYTE_TYPE_SINGLE)) {
                if (!BRST_Encoder_CheckJWWLineHead(encoder, code)) {
                    tmp_len = i;
                    if (real_width)
                        *real_width = w;
                }
            }
            */
        }

        if (BRST_IS_WHITE_SPACE(b)) {
            w += word_space;
        }

        if (btype != BRST_BYTE_TYPE_TRAIL) {
            if (attr->writing_mode == BRST_WMODE_HORIZONTAL) {
                if (attr->fontdef->type == BRST_FONTDEF_TYPE_CID) {
                    /* cid-based font */
                    BRST_UINT16 cid = BRST_CMapEncoder_ToCID(encoder, code);
                    tmp_w           = BRST_CIDFontDef_CIDWidth(attr->fontdef, cid);
                } else {
                    /* unicode-based font */
                    unicode = (encoder->to_unicode_fn)(encoder, code);
                    tmp_w   = BRST_TTFontDef_CharWidth(attr->fontdef,
                          unicode);
                }
            } else {
                tmp_w = (BRST_UINT16)(-dw2);
            }

            if (i > 0)
                w += char_space;
        }

        w += (BRST_REAL)((BRST_DOUBLE)tmp_w * font_size / 1000);

        /* 2006.08.04 break when it encountered  line feed */
        if (w > width || b == 0x0A)
            return tmp_len;

        /*
        // Commented alongside of previous commented items
        if (BRST_IS_WHITE_SPACE(b))
            last_btype = BRST_BYTE_TYPE_TRAIL;
        else
            last_btype = btype;
        */
    }

    /* all of text can be put in the specified width */
    if (real_width)
        *real_width = w;

    return len;
}

static char*
UINT16ToHex(char* s,
    BRST_UINT16 val,
    char* eptr,
    BRST_BYTE width)
{
    BRST_BYTE b[2];
    BRST_UINT16 val2;
    char c;

    if (eptr - s < 7)
        return s;

    /* align byte-order */
    BRST_MemCpy(b, (BRST_BYTE*)&val, 2);
    val2 = (BRST_UINT16)((BRST_UINT16)b[0] << 8 | (BRST_UINT16)b[1]);

    BRST_MemCpy(b, (BRST_BYTE*)&val2, 2);

    *s++ = '<';

    /*
     * In principle a range of <00> - <1F> can now not be
     * distinguished from <0000> - <001F>..., this seems something
     * that is wrong with CID ranges. For the UCS-2 encoding we need
     * to add <0000> - <FFFF> and this cannot be <00> - <FFFF> (or at
     * least, that crashes Mac OSX Preview).
     */
    if (width == 2) {
        c = b[0] >> 4;
        if (c <= 9)
            c += 0x30;
        else
            c += 0x41 - 10;
        *s++ = c;

        c = (char)(b[0] & 0x0f);
        if (c <= 9)
            c += 0x30;
        else
            c += 0x41 - 10;
        *s++ = c;
    }

    c = (char)(b[1] >> 4);
    if (c <= 9)
        c += 0x30;
    else
        c += 0x41 - 10;
    *s++ = c;

    c = (char)(b[1] & 0x0f);
    if (c <= 9)
        c += 0x30;
    else
        c += 0x41 - 10;
    *s++ = c;

    *s++ = '>';
    *s   = 0;

    return s;
}

static char*
CidRangeToHex(char* s,
    BRST_UINT16 from,
    BRST_UINT16 to,
    char* eptr)
{
    BRST_BYTE width = (to > 255) ? 2 : 1;
    char* pbuf;

    pbuf    = UINT16ToHex(s, from, eptr, width);
    *pbuf++ = ' ';
    pbuf    = UINT16ToHex(pbuf, to, eptr, width);

    return pbuf;
}

static BRST_Dict
CreateCMap(BRST_Encoder encoder,
    BRST_Xref xref)
{
    BRST_STATUS ret           = BRST_OK;
    BRST_Dict cmap            = BRST_DictStream_New(encoder->mmgr, xref);
    BRST_CMapEncoderAttr attr = (BRST_CMapEncoderAttr)encoder->attr;
    char buf[BRST_TMP_BUF_SIZE];
    char* pbuf;
    char* eptr = buf + BRST_TMP_BUF_SIZE - 1;
    BRST_UINT i;
    BRST_UINT phase, odd;
    BRST_Dict sysinfo;

    if (!cmap)
        return NULL;

    ret += BRST_Dict_AddName(cmap, "Type", "CMap");
    ret += BRST_Dict_AddName(cmap, "CMapName", encoder->name);

    sysinfo = BRST_Dict_New(encoder->mmgr);
    if (!sysinfo)
        return NULL;

    if (BRST_Dict_Add(cmap, "CIDSystemInfo", sysinfo) != BRST_OK)
        return NULL;

    ret += BRST_Dict_Add(sysinfo, "Registry", BRST_String_New(encoder->mmgr, attr->registry, NULL));
    ret += BRST_Dict_Add(sysinfo, "Ordering", BRST_String_New(encoder->mmgr, attr->ordering, NULL));
    ret += BRST_Dict_AddNumber(sysinfo, "Supplement", attr->supplement);
    ret += BRST_Dict_AddNumber(cmap, "WMode",
        (BRST_UINT32)attr->writing_mode);

    /* create cmap data from encoding data */
    ret += BRST_Stream_WriteStr(cmap->stream,
        "%!PS-Adobe-3.0 Resource-CMap\r\n");
    ret += BRST_Stream_WriteStr(cmap->stream,
        "%%DocumentNeededResources: ProcSet (CIDInit)\r\n");
    ret += BRST_Stream_WriteStr(cmap->stream,
        "%%IncludeResource: ProcSet (CIDInit)\r\n");

    pbuf = (char*)BRST_StrCpy(buf, "%%BeginResource: CMap (", eptr);
    pbuf = (char*)BRST_StrCpy(pbuf, encoder->name, eptr);
    BRST_StrCpy(pbuf, ")\r\n", eptr);
    ret += BRST_Stream_WriteStr(cmap->stream, buf);

    pbuf    = (char*)BRST_StrCpy(buf, "%%Title: (", eptr);
    pbuf    = (char*)BRST_StrCpy(pbuf, encoder->name, eptr);
    *pbuf++ = ' ';
    pbuf    = (char*)BRST_StrCpy(pbuf, attr->registry, eptr);
    *pbuf++ = ' ';
    pbuf    = (char*)BRST_StrCpy(pbuf, attr->ordering, eptr);
    *pbuf++ = ' ';
    pbuf    = BRST_IToA(pbuf, attr->supplement, eptr);
    BRST_StrCpy(pbuf, ")\r\n", eptr);
    ret += BRST_Stream_WriteStr(cmap->stream, buf);

    ret += BRST_Stream_WriteStr(cmap->stream, "%%Version: 1.0\r\n");
    ret += BRST_Stream_WriteStr(cmap->stream, "%%EndComments\r\n");

    ret += BRST_Stream_WriteStr(cmap->stream,
        "/CIDInit /ProcSet findresource begin\r\n\r\n");

    /* Adobe CMap and CIDFont Files Specification recommends to allocate
     * five more elements to this dictionary than existing elements.
     */
    ret += BRST_Stream_WriteStr(cmap->stream, "12 dict begin\r\n\r\n");

    ret += BRST_Stream_WriteStr(cmap->stream, "begincmap\r\n\r\n");
    ret += BRST_Stream_WriteStr(cmap->stream,
        "/CIDSystemInfo 3 dict dup begin\r\n");

    pbuf = (char*)BRST_StrCpy(buf, "  /Registry (", eptr);
    pbuf = (char*)BRST_StrCpy(pbuf, attr->registry, eptr);
    BRST_StrCpy(pbuf, ") def\r\n", eptr);
    ret += BRST_Stream_WriteStr(cmap->stream, buf);

    pbuf = (char*)BRST_StrCpy(buf, "  /Ordering (", eptr);
    pbuf = (char*)BRST_StrCpy(pbuf, attr->ordering, eptr);
    BRST_StrCpy(pbuf, ") def\r\n", eptr);
    ret += BRST_Stream_WriteStr(cmap->stream, buf);

    pbuf = (char*)BRST_StrCpy(buf, "  /Supplement ", eptr);
    pbuf = BRST_IToA(pbuf, attr->supplement, eptr);
    pbuf = (char*)BRST_StrCpy(pbuf, " def\r\n", eptr);
    BRST_StrCpy(pbuf, "end def\r\n\r\n", eptr);
    ret += BRST_Stream_WriteStr(cmap->stream, buf);

    pbuf = (char*)BRST_StrCpy(buf, "/CMapName /", eptr);
    pbuf = (char*)BRST_StrCpy(pbuf, encoder->name, eptr);
    BRST_StrCpy(pbuf, " def\r\n", eptr);
    ret += BRST_Stream_WriteStr(cmap->stream, buf);

    ret += BRST_Stream_WriteStr(cmap->stream, "/CMapVersion 1.0 def\r\n");
    ret += BRST_Stream_WriteStr(cmap->stream, "/CMapType 1 def\r\n\r\n");

    if (attr->uid_offset >= 0) {
        pbuf = (char*)BRST_StrCpy(buf, "/UIDOffset ", eptr);
        pbuf = BRST_IToA(pbuf, attr->uid_offset, eptr);
        BRST_StrCpy(pbuf, " def\r\n\r\n", eptr);
        ret += BRST_Stream_WriteStr(cmap->stream, buf);
    }

    pbuf    = (char*)BRST_StrCpy(buf, "/XUID [", eptr);
    pbuf    = BRST_IToA(pbuf, attr->xuid[0], eptr);
    *pbuf++ = ' ';
    pbuf    = BRST_IToA(pbuf, attr->xuid[1], eptr);
    *pbuf++ = ' ';
    pbuf    = BRST_IToA(pbuf, attr->xuid[2], eptr);
    BRST_StrCpy(pbuf, "] def\r\n\r\n", eptr);
    ret += BRST_Stream_WriteStr(cmap->stream, buf);

    pbuf = (char*)BRST_StrCpy(buf, "/WMode ", eptr);
    pbuf = BRST_IToA(pbuf, (BRST_UINT32)attr->writing_mode, eptr);
    BRST_StrCpy(pbuf, " def\r\n\r\n", eptr);
    ret += BRST_Stream_WriteStr(cmap->stream, buf);

    /* add code-space-range */
    pbuf = BRST_IToA(buf, BRST_List_Count(attr->code_space_range), eptr);
    BRST_StrCpy(pbuf, " begincodespacerange\r\n", eptr);
    ret += BRST_Stream_WriteStr(cmap->stream, buf);

    for (i = 0; i < BRST_List_Count(attr->code_space_range); i++) {
        BRST_CidRange_Rec* range = BRST_List_ItemAt(attr->code_space_range,
            i);

        pbuf = CidRangeToHex(buf, range->from, range->to, eptr);

        BRST_StrCpy(pbuf, "\r\n", eptr);

        ret += BRST_Stream_WriteStr(cmap->stream, buf);

        if (ret != BRST_OK)
            return NULL;
    }

    BRST_StrCpy(buf, "endcodespacerange\r\n\r\n", eptr);
    ret += BRST_Stream_WriteStr(cmap->stream, buf);
    if (ret != BRST_OK)
        return NULL;

    /* add not-def-range */
    pbuf = BRST_IToA(buf, BRST_List_Count(attr->notdef_range), eptr);
    BRST_StrCpy(pbuf, " beginnotdefrange\r\n", eptr);
    ret += BRST_Stream_WriteStr(cmap->stream, buf);

    for (i = 0; i < BRST_List_Count(attr->notdef_range); i++) {
        BRST_CidRange_Rec* range = BRST_List_ItemAt(attr->notdef_range, i);

        pbuf    = CidRangeToHex(buf, range->from, range->to, eptr);
        *pbuf++ = ' ';
        pbuf    = BRST_IToA(pbuf, range->cid, eptr);
        BRST_StrCpy(pbuf, "\r\n", eptr);

        ret += BRST_Stream_WriteStr(cmap->stream, buf);

        if (ret != BRST_OK)
            return NULL;
    }

    BRST_StrCpy(buf, "endnotdefrange\r\n\r\n", eptr);
    ret += BRST_Stream_WriteStr(cmap->stream, buf);
    if (ret != BRST_OK)
        return NULL;

    /* add cid-range */
    phase = BRST_List_Count(attr->cmap_range) / 100;
    odd   = BRST_List_Count(attr->cmap_range) % 100;
    if (phase > 0)
        pbuf = BRST_IToA(buf, 100, eptr);
    else
        pbuf = BRST_IToA(buf, odd, eptr);
    BRST_StrCpy(pbuf, " begincidrange\r\n", eptr);
    ret += BRST_Stream_WriteStr(cmap->stream, buf);

    for (i = 0; i < BRST_List_Count(attr->cmap_range); i++) {
        BRST_CidRange_Rec* range = BRST_List_ItemAt(attr->cmap_range, i);

        pbuf    = CidRangeToHex(buf, range->from, range->to, eptr);
        *pbuf++ = ' ';
        pbuf    = BRST_IToA(pbuf, range->cid, eptr);
        BRST_StrCpy(pbuf, "\r\n", eptr);

        ret += BRST_Stream_WriteStr(cmap->stream, buf);

        if ((i + 1) % 100 == 0) {
            phase--;
            pbuf = (char*)BRST_StrCpy(buf, "endcidrange\r\n\r\n", eptr);

            if (phase > 0)
                pbuf = BRST_IToA(pbuf, 100, eptr);
            else
                pbuf = BRST_IToA(pbuf, odd, eptr);

            BRST_StrCpy(pbuf, " begincidrange\r\n", eptr);

            ret += BRST_Stream_WriteStr(cmap->stream, buf);
        }

        if (ret != BRST_OK)
            return NULL;
    }

    if (odd > 0)
        pbuf = (char*)BRST_StrCpy(buf, "endcidrange\r\n", eptr);

    pbuf = (char*)BRST_StrCpy(pbuf, "endcmap\r\n", eptr);
    pbuf = (char*)BRST_StrCpy(pbuf, "CMapName currentdict /CMap "
                                    "defineresource pop\r\n",
        eptr);
    pbuf = (char*)BRST_StrCpy(pbuf, "end\r\n", eptr);
    pbuf = (char*)BRST_StrCpy(pbuf, "end\r\n\r\n", eptr);
    pbuf = (char*)BRST_StrCpy(pbuf, "%%EndResource\r\n", eptr);
    BRST_StrCpy(pbuf, "%%EOF\r\n", eptr);
    ret += BRST_Stream_WriteStr(cmap->stream, buf);

    if (ret != BRST_OK)
        return NULL;

    return cmap;
}
