#include "brst_external.h"
#include "brst_types.h"
#include "brst_mmgr.h"
#include "brst_encrypt.h"
#include "brst_stream.h"
#include "private/brst_stream.h"
#include "brst_dict.h"
#include "brst_xref.h"
#include "brst_encoder.h"
#include "private/brst_encoder.h"
#include "brst_error.h"
#include "brst_consts.h"
#include "brst_ext_gstate.h"
#include "brst_font.h"
#include "brst_shading.h"
#include "brst_page.h"
#include "private/brst_page.h"
#include "brst_font.h"
#include "private/brst_font.h"
#include "private/brst_pages.h"
#include "private/brst_gstate.h"
#include "private/brst_page_attr.h"
#include "brst_text.h"
#include "private/brst_text.h"
#include "private/brst_utils.h"
#include "private/brst_defines.h"

/* BT */
BRST_EXPORT(BRST_STATUS)
BRST_Page_BeginText(BRST_Page page)
{
    BRST_STATUS ret = BRST_Page_CheckState(page, BRST_GMODE_PAGE_DESCRIPTION);
    BRST_PageAttr attr;
    const BRST_TransMatrix INIT_MATRIX = { 1, 0, 0, 1, 0, 0 };

    BRST_PTRACE((" BRST_Page_BeginText\n"));

    if (ret != BRST_OK)
        return ret;

    attr = (BRST_PageAttr)page->attr;

    if (BRST_Stream_WriteStr(attr->stream, "BT\012") != BRST_OK)
        return BRST_Error_Check(page->error);

    attr->gmode       = BRST_GMODE_TEXT_OBJECT;
    attr->text_pos    = INIT_POS;
    attr->text_matrix = INIT_MATRIX;

    return ret;
}

/* ET */
BRST_EXPORT(BRST_STATUS)
BRST_Page_EndText(BRST_Page page)
{
    BRST_STATUS ret = BRST_Page_CheckState(page, BRST_GMODE_TEXT_OBJECT);
    BRST_PageAttr attr;

    BRST_PTRACE((" BRST_Page_EndText\n"));

    if (ret != BRST_OK)
        return ret;

    attr = (BRST_PageAttr)page->attr;

    if (BRST_Stream_WriteStr(attr->stream, "ET\012") != BRST_OK)
        return BRST_Error_Check(page->error);

    attr->text_pos = INIT_POS;
    attr->gmode    = BRST_GMODE_PAGE_DESCRIPTION;

    return ret;
}

/* TL */
BRST_EXPORT(BRST_STATUS)
BRST_Page_SetTextLeading(BRST_Page page,
    BRST_REAL value)
{
    BRST_STATUS ret = BRST_Page_CheckState(page, BRST_GMODE_PAGE_DESCRIPTION | BRST_GMODE_TEXT_OBJECT);
    BRST_PageAttr attr;

    BRST_PTRACE((" BRST_Page_SetTextLeading\n"));

    if (ret != BRST_OK)
        return ret;

    attr = (BRST_PageAttr)page->attr;

    if (BRST_Stream_WriteReal(attr->stream, value) != BRST_OK)
        return BRST_Error_Check(page->error);

    if (BRST_Stream_WriteStr(attr->stream, " TL\012") != BRST_OK)
        return BRST_Error_Check(page->error);

    attr->gstate->text_leading = value;

    return ret;
}

/* Tf */
BRST_EXPORT(BRST_STATUS)
BRST_Page_SetFontAndSize(BRST_Page page,
    BRST_Font font,
    BRST_REAL size)
{
    BRST_STATUS ret = BRST_Page_CheckState(page, BRST_GMODE_PAGE_DESCRIPTION | BRST_GMODE_TEXT_OBJECT);
    char buf[BRST_TMP_BUF_SIZE];
    char* pbuf = buf;
    char* eptr = buf + BRST_TMP_BUF_SIZE - 1;
    const char* local_name;
    BRST_PageAttr attr;

    BRST_PTRACE((" BRST_Page_SetFontAndSize\n"));

    if (ret != BRST_OK)
        return ret;

    if (!BRST_Font_Validate(font))
        return BRST_Error_Raise(page->error, BRST_PAGE_INVALID_FONT, 0);

    if (size <= 0 || size > BRST_MAX_FONTSIZE)
        return BRST_Error_Raise(page->error, BRST_PAGE_INVALID_FONT_SIZE, 0);

    if (page->mmgr != font->mmgr)
        return BRST_Error_Raise(page->error, BRST_PAGE_INVALID_FONT, 0);

    attr       = (BRST_PageAttr)page->attr;
    local_name = BRST_Page_LocalFontName(page, font);

    if (!local_name)
        return BRST_Error_Raise(page->error, BRST_PAGE_INVALID_FONT, 0);

    if (BRST_Stream_WriteEscapeName(attr->stream, local_name) != BRST_OK)
        return BRST_Error_Check(page->error);

    BRST_MemSet(buf, 0, BRST_TMP_BUF_SIZE);
    *pbuf++ = ' ';
    pbuf    = BRST_FToA(pbuf, size, eptr);
    BRST_StrCpy(pbuf, " Tf\012", eptr);

    if (BRST_Stream_WriteStr(attr->stream, buf) != BRST_OK)
        return BRST_Error_Check(page->error);

    attr->gstate->font         = font;
    attr->gstate->font_size    = size;
    attr->gstate->writing_mode = ((BRST_FontAttr)font->attr)->writing_mode;

    return ret;
}

/* Tr */
BRST_EXPORT(BRST_STATUS)
BRST_Page_SetTextRenderingMode(BRST_Page page,
    BRST_TextRenderingMode mode)
{
    BRST_STATUS ret = BRST_Page_CheckState(page, BRST_GMODE_PAGE_DESCRIPTION | BRST_GMODE_TEXT_OBJECT);
    BRST_PageAttr attr;

    BRST_PTRACE((" BRST_Page_SetTextRenderingMode\n"));

    if (ret != BRST_OK)
        return ret;

    if (mode >= BRST_RENDERING_MODE_EOF)
        return BRST_Error_Raise(page->error, BRST_PAGE_OUT_OF_RANGE,
            (BRST_STATUS)mode);

    attr = (BRST_PageAttr)page->attr;

    if (BRST_Stream_WriteInt(attr->stream, (BRST_INT)mode) != BRST_OK)
        return BRST_Error_Check(page->error);

    if (BRST_Stream_WriteStr(attr->stream, " Tr\012") != BRST_OK)
        return BRST_Error_Check(page->error);

    attr->gstate->rendering_mode = mode;

    return ret;
}

/* Ts */
BRST_EXPORT(BRST_STATUS)
BRST_Page_SetTextRaise(BRST_Page page,
    BRST_REAL value)
{
    BRST_STATUS ret = BRST_Page_CheckState(page, BRST_GMODE_PAGE_DESCRIPTION | BRST_GMODE_TEXT_OBJECT);
    BRST_PageAttr attr;

    BRST_PTRACE((" BRST_Page_SetTextRaise\n"));

    if (ret != BRST_OK)
        return ret;

    attr = (BRST_PageAttr)page->attr;

    if (BRST_Stream_WriteReal(attr->stream, value) != BRST_OK)
        return BRST_Error_Check(page->error);

    if (BRST_Stream_WriteStr(attr->stream, " Ts\012") != BRST_OK)
        return BRST_Error_Check(page->error);

    attr->gstate->text_rise = value;

    return ret;
}

/* Td */
BRST_EXPORT(BRST_STATUS)
BRST_Page_MoveTextPos(BRST_Page page,
    BRST_REAL x,
    BRST_REAL y)
{
    BRST_STATUS ret = BRST_Page_CheckState(page, BRST_GMODE_TEXT_OBJECT);
    char buf[BRST_TMP_BUF_SIZE];
    char* pbuf = buf;
    char* eptr = buf + BRST_TMP_BUF_SIZE - 1;
    BRST_PageAttr attr;

    BRST_PTRACE((" BRST_Page_MoveTextPos\n"));

    if (ret != BRST_OK)
        return ret;

    attr = (BRST_PageAttr)page->attr;

    BRST_MemSet(buf, 0, BRST_TMP_BUF_SIZE);

    pbuf    = BRST_FToA(pbuf, x, eptr);
    *pbuf++ = ' ';
    pbuf    = BRST_FToA(pbuf, y, eptr);
    BRST_StrCpy(pbuf, " Td\012", eptr);

    if (BRST_Stream_WriteStr(attr->stream, buf) != BRST_OK)
        return BRST_Error_Check(page->error);

    attr->text_matrix.x += x * attr->text_matrix.a + y * attr->text_matrix.c;
    attr->text_matrix.y += y * attr->text_matrix.d + x * attr->text_matrix.b;
    attr->text_pos.x = attr->text_matrix.x;
    attr->text_pos.y = attr->text_matrix.y;

    return ret;
}

/* TD */
BRST_EXPORT(BRST_STATUS)
BRST_Page_MoveTextPos2(BRST_Page page,
    BRST_REAL x,
    BRST_REAL y)
{
    BRST_STATUS ret = BRST_Page_CheckState(page, BRST_GMODE_TEXT_OBJECT);
    char buf[BRST_TMP_BUF_SIZE];
    char* pbuf = buf;
    char* eptr = buf + BRST_TMP_BUF_SIZE - 1;
    BRST_PageAttr attr;

    BRST_PTRACE((" BRST_Page_MoveTextPos2\n"));

    if (ret != BRST_OK)
        return ret;

    attr = (BRST_PageAttr)page->attr;

    BRST_MemSet(buf, 0, BRST_TMP_BUF_SIZE);

    pbuf    = BRST_FToA(pbuf, x, eptr);
    *pbuf++ = ' ';
    pbuf    = BRST_FToA(pbuf, y, eptr);
    BRST_StrCpy(pbuf, " TD\012", eptr);

    if (BRST_Stream_WriteStr(attr->stream, buf) != BRST_OK)
        return BRST_Error_Check(page->error);

    attr->text_matrix.x += x * attr->text_matrix.a + y * attr->text_matrix.c;
    attr->text_matrix.y += y * attr->text_matrix.d + x * attr->text_matrix.b;
    attr->text_pos.x           = attr->text_matrix.x;
    attr->text_pos.y           = attr->text_matrix.y;
    attr->gstate->text_leading = -y;

    return ret;
}

/* Tm */
BRST_EXPORT(BRST_STATUS)
BRST_Page_SetTextMatrix(BRST_Page page,
    BRST_REAL a,
    BRST_REAL b,
    BRST_REAL c,
    BRST_REAL d,
    BRST_REAL x,
    BRST_REAL y)
{
    BRST_STATUS ret = BRST_Page_CheckState(page, BRST_GMODE_TEXT_OBJECT);
    char buf[BRST_TMP_BUF_SIZE];
    char* pbuf = buf;
    char* eptr = buf + BRST_TMP_BUF_SIZE - 1;
    BRST_PageAttr attr;

    BRST_PTRACE((" BRST_Page_SetTextMatrix\n"));

    if (ret != BRST_OK)
        return ret;

    attr = (BRST_PageAttr)page->attr;

    if ((a == 0 || d == 0) && (b == 0 || c == 0))
        return BRST_Error_Raise(page->error, BRST_INVALID_PARAMETER, 0);

    BRST_MemSet(buf, 0, BRST_TMP_BUF_SIZE);

    pbuf    = BRST_FToA(pbuf, a, eptr);
    *pbuf++ = ' ';
    pbuf    = BRST_FToA(pbuf, b, eptr);
    *pbuf++ = ' ';
    pbuf    = BRST_FToA(pbuf, c, eptr);
    *pbuf++ = ' ';
    pbuf    = BRST_FToA(pbuf, d, eptr);
    *pbuf++ = ' ';
    pbuf    = BRST_FToA(pbuf, x, eptr);
    *pbuf++ = ' ';
    pbuf    = BRST_FToA(pbuf, y, eptr);
    BRST_StrCpy(pbuf, " Tm\012", eptr);

    if (BRST_Stream_WriteStr(attr->stream, buf) != BRST_OK)
        return BRST_Error_Check(page->error);

    attr->text_matrix.a = a;
    attr->text_matrix.b = b;
    attr->text_matrix.c = c;
    attr->text_matrix.d = d;
    attr->text_matrix.x = x;
    attr->text_matrix.y = y;
    attr->text_pos.x    = attr->text_matrix.x;
    attr->text_pos.y    = attr->text_matrix.y;

    return ret;
}

/* T* */
BRST_EXPORT(BRST_STATUS)
BRST_Page_MoveToNextLine(BRST_Page page)
{
    BRST_STATUS ret = BRST_Page_CheckState(page, BRST_GMODE_TEXT_OBJECT);
    BRST_PageAttr attr;

    BRST_PTRACE((" BRST_Page_MoveToNextLine\n"));

    if (ret != BRST_OK)
        return ret;

    attr = (BRST_PageAttr)page->attr;

    if (BRST_Stream_WriteStr(attr->stream, "T*\012") != BRST_OK)
        return BRST_Error_Check(page->error);

    /* calculate the reference point of text */
    attr->text_matrix.x -= attr->gstate->text_leading * attr->text_matrix.c;
    attr->text_matrix.y -= attr->gstate->text_leading * attr->text_matrix.d;

    attr->text_pos.x = attr->text_matrix.x;
    attr->text_pos.y = attr->text_matrix.y;

    return ret;
}

/* Tj */
BRST_EXPORT(BRST_STATUS)
BRST_Page_ShowText(BRST_Page page,
    const char* text)
{
    BRST_STATUS ret = BRST_Page_CheckState(page, BRST_GMODE_TEXT_OBJECT);
    BRST_PageAttr attr;
    BRST_REAL tw;

    BRST_PTRACE((" BRST_Page_ShowText\n"));

    if (ret != BRST_OK || text == NULL || text[0] == 0)
        return ret;

    attr = (BRST_PageAttr)page->attr;

    /* no font exists */
    if (!attr->gstate->font)
        return BRST_Error_Raise(page->error, BRST_PAGE_FONT_NOT_FOUND, 0);

    tw = BRST_Page_TextWidth(page, text);
    if (!tw)
        return ret;

    if (InternalWriteText(attr, text) != BRST_OK)
        return BRST_Error_Check(page->error);

    if (BRST_Stream_WriteStr(attr->stream, " Tj\012") != BRST_OK)
        return BRST_Error_Check(page->error);

    /* calculate the reference point of text */
    if (attr->gstate->writing_mode == BRST_WMODE_HORIZONTAL) {
        attr->text_pos.x += tw * attr->text_matrix.a;
        attr->text_pos.y += tw * attr->text_matrix.b;
    } else {
        attr->text_pos.x -= tw * attr->text_matrix.b;
        attr->text_pos.y -= tw * attr->text_matrix.a;
    }

    return ret;
}

/* TJ */
/* ' */
BRST_EXPORT(BRST_STATUS)
BRST_Page_ShowTextNextLine(BRST_Page page,
    const char* text)
{
    BRST_STATUS ret = BRST_Page_CheckState(page, BRST_GMODE_TEXT_OBJECT);
    BRST_PageAttr attr;
    BRST_REAL tw;

    BRST_PTRACE((" BRST_Page_ShowTextNextLine\n"));

    if (ret != BRST_OK)
        return ret;

    attr = (BRST_PageAttr)page->attr;

    /* no font exists */
    if (!attr->gstate->font)
        return BRST_Error_Raise(page->error, BRST_PAGE_FONT_NOT_FOUND, 0);

    if (text == NULL || text[0] == 0)
        return BRST_Page_MoveToNextLine(page);

    if (InternalWriteText(attr, text) != BRST_OK)
        return BRST_Error_Check(page->error);

    if (BRST_Stream_WriteStr(attr->stream, " \'\012") != BRST_OK)
        return BRST_Error_Check(page->error);

    tw = BRST_Page_TextWidth(page, text);

    /* calculate the reference point of text */
    attr->text_matrix.x -= attr->gstate->text_leading * attr->text_matrix.c;
    attr->text_matrix.y -= attr->gstate->text_leading * attr->text_matrix.d;

    attr->text_pos.x = attr->text_matrix.x;
    attr->text_pos.y = attr->text_matrix.y;

    if (attr->gstate->writing_mode == BRST_WMODE_HORIZONTAL) {
        attr->text_pos.x += tw * attr->text_matrix.a;
        attr->text_pos.y += tw * attr->text_matrix.b;
    } else {
        attr->text_pos.x -= tw * attr->text_matrix.b;
        attr->text_pos.y -= tw * attr->text_matrix.a;
    }

    return ret;
}

/* " */
BRST_EXPORT(BRST_STATUS)
BRST_Page_ShowTextNextLineEx(BRST_Page page,
    BRST_REAL word_space,
    BRST_REAL char_space,
    const char* text)
{
    BRST_STATUS ret = BRST_Page_CheckState(page, BRST_GMODE_TEXT_OBJECT);
    BRST_PageAttr attr;
    BRST_REAL tw;
    char buf[BRST_TMP_BUF_SIZE];
    char* pbuf = buf;
    char* eptr = buf + BRST_TMP_BUF_SIZE - 1;

    BRST_PTRACE((" BRST_Page_ShowTextNextLineEX\n"));

    if (ret != BRST_OK)
        return ret;

    if (word_space < BRST_MIN_WORDSPACE || word_space > BRST_MAX_WORDSPACE)
        return BRST_Error_Raise(page->error, BRST_PAGE_OUT_OF_RANGE, 0);

    if (char_space < BRST_MIN_CHARSPACE || char_space > BRST_MAX_CHARSPACE)
        return BRST_Error_Raise(page->error, BRST_PAGE_OUT_OF_RANGE, 0);

    attr = (BRST_PageAttr)page->attr;

    /* no font exists */
    if (!attr->gstate->font)
        return BRST_Error_Raise(page->error, BRST_PAGE_FONT_NOT_FOUND, 0);

    if (text == NULL || text[0] == 0)
        return BRST_Page_MoveToNextLine(page);

    BRST_MemSet(buf, 0, BRST_TMP_BUF_SIZE);
    pbuf    = BRST_FToA(pbuf, word_space, eptr);
    *pbuf++ = ' ';
    pbuf    = BRST_FToA(pbuf, char_space, eptr);
    *pbuf   = ' ';

    if (InternalWriteText(attr, buf) != BRST_OK)
        return BRST_Error_Check(page->error);

    if (InternalWriteText(attr, text) != BRST_OK)
        return BRST_Error_Check(page->error);

    if (BRST_Stream_WriteStr(attr->stream, " \"\012") != BRST_OK)
        return BRST_Error_Check(page->error);

    attr->gstate->word_space = word_space;
    attr->gstate->char_space = char_space;

    tw = BRST_Page_TextWidth(page, text);

    /* calculate the reference point of text */
    attr->text_matrix.x += attr->gstate->text_leading * attr->text_matrix.b;
    attr->text_matrix.y -= attr->gstate->text_leading * attr->text_matrix.a;

    attr->text_pos.x = attr->text_matrix.x;
    attr->text_pos.y = attr->text_matrix.y;

    if (attr->gstate->writing_mode == BRST_WMODE_HORIZONTAL) {
        attr->text_pos.x += tw * attr->text_matrix.a;
        attr->text_pos.y += tw * attr->text_matrix.b;
    } else {
        attr->text_pos.x -= tw * attr->text_matrix.b;
        attr->text_pos.y -= tw * attr->text_matrix.a;
    }

    return ret;
}

BRST_EXPORT(BRST_STATUS)
BRST_Page_TextOut(BRST_Page page,
    BRST_REAL xpos,
    BRST_REAL ypos,
    const char* text)
{
    BRST_STATUS ret = BRST_Page_CheckState(page, BRST_GMODE_TEXT_OBJECT);
    BRST_REAL x;
    BRST_REAL y;
    BRST_PageAttr attr;

    BRST_PTRACE((" BRST_Page_TextOut\n"));

    if (ret != BRST_OK)
        return ret;

    attr = (BRST_PageAttr)page->attr;
    TextPos_AbsToRel(attr->text_matrix, xpos, ypos, &x, &y);
    if ((ret = BRST_Page_MoveTextPos(page, x, y)) != BRST_OK)
        return ret;

    return BRST_Page_ShowText(page, text);
}

BRST_EXPORT(BRST_STATUS)
BRST_Page_TextRect(BRST_Page page,
    BRST_REAL left,
    BRST_REAL top,
    BRST_REAL right,
    BRST_REAL bottom,
    const char* text,
    BRST_TextAlignment align,
    BRST_UINT* len)
{
    BRST_STATUS ret = BRST_Page_CheckState(page, BRST_GMODE_TEXT_OBJECT);
    BRST_PageAttr attr;
    const char* ptr                 = text;
    BRST_BOOL pos_initialized       = BRST_FALSE;
    BRST_REAL save_char_space       = 0;
    BRST_BOOL is_insufficient_space = BRST_FALSE;
    BRST_UINT num_rest;
    BRST_Box bbox;
    BRST_BOOL char_space_changed = BRST_FALSE;

    BRST_PTRACE((" BRST_Page_TextRect\n"));

    if (ret != BRST_OK)
        return ret;

    attr = (BRST_PageAttr)page->attr;

    /* no font exists */
    if (!attr->gstate->font) {
        return BRST_Error_Raise(page->error, BRST_PAGE_FONT_NOT_FOUND, 0);
    }

    bbox = BRST_Font_BBox(attr->gstate->font);

    if (len)
        *len = 0;
    num_rest = BRST_StrLen(text, BRST_LIMIT_MAX_STRING_LEN + 1);

    if (num_rest > BRST_LIMIT_MAX_STRING_LEN) {
        return BRST_Error_Raise(page->error, BRST_STRING_OUT_OF_RANGE, 0);
    } else if (!num_rest)
        return BRST_OK;

    if (attr->gstate->text_leading == 0)
        BRST_Page_SetTextLeading(page, (bbox.top - bbox.bottom) / 1000 * attr->gstate->font_size);

    top    = top - bbox.top / 1000 * attr->gstate->font_size + attr->gstate->text_leading;
    bottom = bottom - bbox.bottom / 1000 * attr->gstate->font_size;

    if (align == BRST_TALIGN_JUSTIFY) {
        save_char_space          = attr->gstate->char_space;
        attr->gstate->char_space = 0;
    }

    for (;;) {
        BRST_REAL x, y;
        BRST_UINT line_len, tmp_len;
        BRST_REAL rw;
        BRST_BOOL LineBreak;

        attr->gstate->char_space = 0;
        line_len = tmp_len = BRST_Page_MeasureText(page, ptr, right - left, BRST_TRUE, &rw);
        if (line_len == 0) {
            is_insufficient_space = BRST_TRUE;
            break;
        }

        if (len)
            *len += line_len;
        num_rest -= line_len;

        /* Shorten tmp_len by trailing whitespace and control characters. */
        LineBreak = BRST_FALSE;
        while (tmp_len > 0 && BRST_IS_WHITE_SPACE(ptr[tmp_len - 1])) {
            tmp_len--;
            if (ptr[tmp_len] == 0x0A || ptr[tmp_len] == 0x0D) {
                LineBreak = BRST_TRUE;
            }
        }

        switch (align) {

        case BRST_TALIGN_RIGHT:
            TextPos_AbsToRel(attr->text_matrix, right - rw, top, &x, &y);
            if (!pos_initialized) {
                pos_initialized = BRST_TRUE;
            } else {
                y = 0;
            }
            if ((ret = BRST_Page_MoveTextPos(page, x, y)) != BRST_OK)
                return ret;
            break;

        case BRST_TALIGN_CENTER:
            TextPos_AbsToRel(attr->text_matrix, left + (right - left - rw) / 2, top, &x, &y);
            if (!pos_initialized) {
                pos_initialized = BRST_TRUE;
            } else {
                y = 0;
            }
            if ((ret = BRST_Page_MoveTextPos(page, x, y)) != BRST_OK)
                return ret;
            break;

        case BRST_TALIGN_JUSTIFY:
            if (!pos_initialized) {
                pos_initialized = BRST_TRUE;
                TextPos_AbsToRel(attr->text_matrix, left, top, &x, &y);
                if ((ret = BRST_Page_MoveTextPos(page, x, y)) != BRST_OK)
                    return ret;
            }

            /* Do not justify last line of paragraph or text. */
            if (LineBreak || num_rest <= 0) {
                if ((ret = BRST_Page_SetCharSpace(page, save_char_space))
                    != BRST_OK)
                    return ret;
                char_space_changed = BRST_FALSE;
            } else {
                BRST_REAL x_adjust;
                BRST_ParseText_Rec state;
                BRST_UINT i          = 0;
                BRST_UINT num_char   = 0;
                BRST_Encoder encoder = ((BRST_FontAttr)attr->gstate->font->attr)->encoder;
                const char* tmp_ptr  = ptr;
                BRST_Encoder_SetParseText(encoder, &state, (BRST_BYTE*)tmp_ptr, tmp_len);
                while (*tmp_ptr) {
                    BRST_ByteType btype = BRST_Encoder_ByteType_Internal(encoder, &state);
                    if (btype != BRST_BYTE_TYPE_TRAIL)
                        num_char++;
                    i++;
                    if (i >= tmp_len)
                        break;
                    tmp_ptr++;
                }

                x_adjust = num_char == 0 ? 0 : (right - left - rw) / (num_char - 1);
                if ((ret = BRST_Page_SetCharSpace(page, x_adjust)) != BRST_OK)
                    return ret;
                char_space_changed = BRST_TRUE;
            }
            break;

        default:
            if (!pos_initialized) {
                pos_initialized = BRST_TRUE;
                TextPos_AbsToRel(attr->text_matrix, left, top, &x, &y);
                if ((ret = BRST_Page_MoveTextPos(page, x, y)) != BRST_OK)
                    return ret;
            }
        }

        if (InternalShowTextNextLine(page, ptr, tmp_len) != BRST_OK)
            return BRST_Error_Check(page->error);

        if (num_rest <= 0)
            break;

        if (attr->text_pos.y - attr->gstate->text_leading < bottom) {
            is_insufficient_space = BRST_TRUE;
            break;
        }

        ptr += line_len;
    }

    if (char_space_changed && save_char_space != attr->gstate->char_space) {
        if ((ret = BRST_Page_SetCharSpace(page, save_char_space)) != BRST_OK)
            return ret;
    }

    if (is_insufficient_space)
        return BRST_PAGE_INSUFFICIENT_SPACE;
    else
        return BRST_OK;
}

/* Tc */
BRST_EXPORT(BRST_STATUS)
BRST_Page_SetCharSpace(BRST_Page page,
    BRST_REAL value)
{
    BRST_STATUS ret = BRST_Page_CheckState(page, BRST_GMODE_PAGE_DESCRIPTION | BRST_GMODE_TEXT_OBJECT);
    BRST_PageAttr attr;

    BRST_PTRACE((" BRST_Page_SetCharSpace\n"));

    if (ret != BRST_OK)
        return ret;

    attr = (BRST_PageAttr)page->attr;

    if (value < BRST_MIN_CHARSPACE || value > BRST_MAX_CHARSPACE)
        return BRST_Error_Raise(page->error, BRST_PAGE_OUT_OF_RANGE, 0);

    if (BRST_Stream_WriteReal(attr->stream, value) != BRST_OK)
        return BRST_Error_Check(page->error);

    if (BRST_Stream_WriteStr(attr->stream, " Tc\012") != BRST_OK)
        return BRST_Error_Check(page->error);

    attr->gstate->char_space = value;

    return ret;
}

/* Tw */
BRST_EXPORT(BRST_STATUS)
BRST_Page_SetWordSpace(BRST_Page page,
    BRST_REAL value)
{
    BRST_STATUS ret = BRST_Page_CheckState(page, BRST_GMODE_PAGE_DESCRIPTION | BRST_GMODE_TEXT_OBJECT);
    BRST_PageAttr attr;

    BRST_PTRACE((" BRST_Page_SetWordSpace\n"));

    if (ret != BRST_OK)
        return ret;

    attr = (BRST_PageAttr)page->attr;

    if (value < BRST_MIN_WORDSPACE || value > BRST_MAX_WORDSPACE)
        return BRST_Error_Raise(page->error, BRST_PAGE_OUT_OF_RANGE, 0);

    if (BRST_Stream_WriteReal(attr->stream, value) != BRST_OK)
        return BRST_Error_Check(page->error);

    if (BRST_Stream_WriteStr(attr->stream, " Tw\012") != BRST_OK)
        return BRST_Error_Check(page->error);

    attr->gstate->word_space = value;

    return ret;
}

BRST_EXPORT(BRST_TransMatrix)
BRST_Page_TextMatrix(BRST_Page page)
{
    BRST_TransMatrix DEF_MATRIX = { 1, 0, 0, 1, 0, 0 };

    BRST_PTRACE((" BRST_Page_TextMatrix\n"));
    if (BRST_Page_Validate(page)) {
        BRST_PageAttr attr = (BRST_PageAttr)page->attr;

        return attr->text_matrix;
    } else
        return DEF_MATRIX;
}

BRST_EXPORT(BRST_REAL)
BRST_Page_TextLeading(BRST_Page page)
{
    BRST_PTRACE((" BRST_Page_TextLeading\n"));

    if (BRST_Page_Validate(page)) {
        BRST_PageAttr attr = (BRST_PageAttr)page->attr;

        return attr->gstate->text_leading;
    } else
        return BRST_DEF_LEADING;
}

BRST_EXPORT(BRST_TextRenderingMode)
BRST_Page_TextRenderingMode(BRST_Page page)
{
    BRST_PTRACE((" BRST_Page_TextRenderingMode\n"));

    if (BRST_Page_Validate(page)) {
        BRST_PageAttr attr = (BRST_PageAttr)page->attr;

        return attr->gstate->rendering_mode;
    } else
        return BRST_DEF_RENDERING_MODE;
}

BRST_EXPORT(BRST_REAL)
BRST_Page_TextRaise(BRST_Page page)
{
    BRST_PTRACE((" BRST_Page_TextRaise\n"));

    if (BRST_Page_Validate(page)) {
        BRST_PageAttr attr = (BRST_PageAttr)page->attr;

        return attr->gstate->text_rise;
    } else
        return BRST_DEF_RAISE;
}

BRST_EXPORT(BRST_REAL)
BRST_Page_CharSpace(BRST_Page page)
{
    BRST_PTRACE((" BRST_Page_CharSpace\n"));

    if (BRST_Page_Validate(page)) {
        BRST_PageAttr attr = (BRST_PageAttr)page->attr;

        return attr->gstate->char_space;
    } else
        return BRST_DEF_CHARSPACE;
}

BRST_EXPORT(BRST_REAL)
BRST_Page_WordSpace(BRST_Page page)
{
    BRST_PTRACE((" BRST_Page_WordSpace\n"));

    if (BRST_Page_Validate(page)) {
        BRST_PageAttr attr = (BRST_PageAttr)page->attr;

        return attr->gstate->word_space;
    } else
        return BRST_DEF_WORDSPACE;
}

BRST_EXPORT(BRST_Point)
BRST_Page_CurrentTextPos(BRST_Page page)
{
    BRST_Point pos = { 0, 0 };

    BRST_PTRACE((" BRST_Page_CurrentTextPos\n"));

    if (BRST_Page_Validate(page)) {
        BRST_PageAttr attr = (BRST_PageAttr)page->attr;

        if (attr->gmode & BRST_GMODE_TEXT_OBJECT)
            pos = attr->text_pos;
    }

    return pos;
}

BRST_EXPORT(BRST_STATUS)
BRST_Page_CurrentTextPos2(BRST_Page page,
    BRST_Point* pos)
{
    BRST_PageAttr attr;

    BRST_PTRACE((" BRST_Page_CurrentTextPos2\n"));

    pos->x = 0;
    pos->y = 0;
    if (!BRST_Page_Validate(page))
        return BRST_INVALID_PAGE;

    attr = (BRST_PageAttr)page->attr;

    if (attr->gmode & BRST_GMODE_TEXT_OBJECT)
        *pos = attr->text_pos;

    return BRST_OK;
}

BRST_EXPORT(BRST_Font)
BRST_Page_CurrentFont(BRST_Page page)
{
    BRST_PTRACE((" BRST_Page_CurrentFont\n"));

    if (BRST_Page_Validate(page)) {
        BRST_PageAttr attr = (BRST_PageAttr)page->attr;

        return attr->gstate->font;
    } else
        return NULL;
}

BRST_EXPORT(BRST_REAL)
BRST_Page_CurrentFontSize(BRST_Page page)
{
    BRST_PTRACE((" BRST_Page_CurrentFontSize\n"));

    if (BRST_Page_Validate(page)) {
        BRST_PageAttr attr = (BRST_PageAttr)page->attr;

        return (attr->gstate->font) ? attr->gstate->font_size : 0;
    } else
        return 0;
}

BRST_EXPORT(BRST_REAL)
BRST_Page_TextWidth(BRST_Page page,
    const char* text)
{
    BRST_PageAttr attr;
    BRST_TextWidth tw;
    BRST_REAL ret = 0;
    BRST_UINT len = BRST_StrLen(text, BRST_LIMIT_MAX_STRING_LEN + 1);

    BRST_PTRACE((" BRST_Page_TextWidth\n"));

    if (!BRST_Page_Validate(page) || len == 0)
        return 0;

    attr = (BRST_PageAttr)page->attr;

    /* no font exists */
    if (!attr->gstate->font) {
        BRST_Error_Raise(page->error, BRST_PAGE_FONT_NOT_FOUND, 0);
        return 0;
    }

    tw = BRST_Font_TextWidth(attr->gstate->font, (BRST_BYTE*)text, len);

    ret += attr->gstate->word_space * tw.numspace;
    ret += tw.width * attr->gstate->font_size / 1000;
    ret += attr->gstate->char_space * tw.numchars;

    BRST_Error_Check(page->error);

    return ret;
}

BRST_EXPORT(BRST_UINT)
BRST_Page_MeasureText(BRST_Page page,
    const char* text,
    BRST_REAL width,
    BRST_BOOL wordwrap,
    BRST_REAL* real_width)
{
    BRST_PageAttr attr;
    BRST_UINT len = BRST_StrLen(text, BRST_LIMIT_MAX_STRING_LEN + 1);
    BRST_UINT ret;

    if (!BRST_Page_Validate(page) || len == 0)
        return 0;

    attr = (BRST_PageAttr)page->attr;

    BRST_PTRACE((" BRST_Page_MeasureText\n"));

    /* no font exists */
    if (!attr->gstate->font) {
        BRST_Error_Raise(page->error, BRST_PAGE_FONT_NOT_FOUND, 0);
        return 0;
    }

    ret = BRST_Font_MeasureText(attr->gstate->font, (BRST_BYTE*)text, len, width,
        attr->gstate->font_size, attr->gstate->char_space,
        attr->gstate->word_space, wordwrap, real_width);

    BRST_Error_Check(page->error);

    return ret;
}
