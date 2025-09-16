#include "brst_types.h"
#include "brst_encrypt.h"
#include "brst_mmgr.h"
#include "brst_stream.h"
#include "private/brst_stream.h"
#include "brst_encoder.h"
#include "private/brst_encoder.h"
#include "brst_dict.h"
#include "brst_page.h"
#include "brst_xref.h"
#include "brst_font.h"
#include "private/brst_font.h"
#include "brst_geometry_defines.h"
#include "brst_matrix.h"
#include "private/brst_matrix.h"
#include "private/brst_gstate.h"
#include "private/brst_pages.h"
#include "brst_doc.h"
#include "private/brst_page_attr.h"
#include "brst_ext_gstate.h"
#include "brst_shading.h"
#include "brst_page.h"
#include "brst_text.h"
#include "private/brst_text.h"
#include "brst_pattern.h"
#include "private/brst_page.h"
#include "private/brst_defines.h"
#include "private/brst_utils.h"
#include "brst_consts.h"

/*
 * Convert a user space text position from absolute to relative coordinates.
 * Absolute values are passed in xAbs and yAbs, relative values are returned
 * to xRel and yRel. The latter two must not be NULL.
 */
void TextPos_AbsToRel(BRST_Matrix text_matrix,
    BRST_REAL xAbs,
    BRST_REAL yAbs,
    BRST_REAL* xRel,
    BRST_REAL* yRel)
{
    if (text_matrix->a == 0) {
        *xRel = (yAbs - text_matrix->y - (xAbs - text_matrix->x) * text_matrix->d / text_matrix->c) / text_matrix->b;
        *yRel = (xAbs - text_matrix->x) / text_matrix->c;
    } else {
        BRST_REAL y = (yAbs - text_matrix->y - (xAbs - text_matrix->x) * text_matrix->b / text_matrix->a) / (text_matrix->d - text_matrix->c * text_matrix->b / text_matrix->a);
        *xRel       = (xAbs - text_matrix->x - y * text_matrix->c) / text_matrix->a;
        *yRel       = y;
    }
}

BRST_STATUS
InternalShowTextNextLine(BRST_Page page,
    const char* text,
    BRST_UINT len)
{
    BRST_STATUS ret;
    BRST_PageAttr attr;
    BRST_REAL tw;
    BRST_FontAttr font_attr;

    BRST_PTRACE(" ShowTextNextLine\n");

    attr      = (BRST_PageAttr)page->attr;
    font_attr = (BRST_FontAttr)attr->gstate->font->attr;

    if (font_attr->type == BRST_FONT_TYPE0_TT || font_attr->type == BRST_FONT_TYPE0_CID) {
        BRST_Encoder encoder = font_attr->encoder;

        if ((ret = BRST_Stream_WriteStr(attr->stream, "<")) != BRST_OK)
            return ret;

        if (encoder->encode_text_fn == NULL) {
            if ((ret = BRST_Stream_WriteBinary(attr->stream, (BRST_BYTE*)text,
                     len, NULL))
                != BRST_OK)
                return ret;
        } else {
            char* encoded;
            BRST_UINT length;

            encoded = (encoder->encode_text_fn)(encoder, text, len, &length);
            ret     = BRST_Stream_WriteBinary(attr->stream, (BRST_BYTE*)encoded,
                    length, NULL);
            free(encoded);

            if (ret != BRST_OK)
                return ret;
        }

        if ((ret = BRST_Stream_WriteStr(attr->stream, ">")) != BRST_OK)
            return ret;
    } else if ((ret = BRST_Stream_WriteEscapeText2(attr->stream, text,
                    len))
        != BRST_OK)
        return ret;

    if ((ret = BRST_Stream_WriteStr(attr->stream, " \'\012")) != BRST_OK)
        return ret;

    tw = BRST_Page_TextWidth(page, text);

    /* calculate the reference point of text */
    attr->text_matrix->x -= attr->gstate->text_leading * attr->text_matrix->c;
    attr->text_matrix->y -= attr->gstate->text_leading * attr->text_matrix->d;

    attr->text_pos.x = attr->text_matrix->x;
    attr->text_pos.y = attr->text_matrix->y;

    if (attr->gstate->writing_mode == BRST_WMODE_HORIZONTAL) {
        attr->text_pos.x += tw * attr->text_matrix->a;
        attr->text_pos.y += tw * attr->text_matrix->b;
    } else {
        attr->text_pos.x -= tw * attr->text_matrix->b;
        attr->text_pos.y -= tw * attr->text_matrix->a;
    }

    return ret;
}

BRST_STATUS
InternalWriteText(BRST_PageAttr attr,
    const char* text)
{
    BRST_FontAttr font_attr = (BRST_FontAttr)attr->gstate->font->attr;
    BRST_STATUS ret;

    BRST_PTRACE(" InternalWriteText\n");

    if (font_attr->type == BRST_FONT_TYPE0_TT || font_attr->type == BRST_FONT_TYPE0_CID) {
        BRST_Encoder encoder;
        BRST_UINT len;

        if ((ret = BRST_Stream_WriteStr(attr->stream, "<")) != BRST_OK)
            return ret;

        encoder = font_attr->encoder;
        len     = BRST_StrLen(text, BRST_LIMIT_MAX_STRING_LEN);

        if (encoder->encode_text_fn == NULL) {
            if ((ret = BRST_Stream_WriteBinary(attr->stream, (BRST_BYTE*)text,
                     len, NULL))
                != BRST_OK)
                return ret;
        } else {
            char* encoded;
            BRST_UINT length;

            encoded = (encoder->encode_text_fn)(encoder, text, len, &length);

            ret = BRST_Stream_WriteBinary(attr->stream, (BRST_BYTE*)encoded,
                length, NULL);

            free(encoded);

            if (ret != BRST_OK)
                return ret;
        }

        return BRST_Stream_WriteStr(attr->stream, ">");
    }

    return BRST_Stream_WriteEscapeText(attr->stream, text);
}
