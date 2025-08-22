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
#include "brst_doc.h"
#include "brst_consts.h"
#include "brst_ext_gstate.h"
#include "brst_font.h"
#include "brst_shading.h"
#include "brst_doc.h"
#include "brst_pdfa.h"
#include "brst_page.h"
#include "brst_destination.h"
#include "private/brst_catalog.h"
#include "brst_outline.h"
#include "private/brst_encrypt_dict.h"
#include "brst_base.h"
#include "private/brst_doc.h"
#include "private/brst_doc_fontdef.h"
#include "private/brst_doc_font.h"
#include "private/brst_fontdef.h"
#include "private/brst_fontdef_type1.h"
#include "private/brst_fontdef_ttf.h"
#include "private/brst_fontdef_cid.h"
#include "brst_doc_encoder.h"
#include "private/brst_utils.h"

BRST_EXPORT(BRST_Font)
BRST_Doc_Font(BRST_Doc pdf,
    const char* font_name,
    const char* encoding_name)
{
    BRST_FontDef fontdef = NULL;
    BRST_Encoder encoder = NULL;
    BRST_Font font;

    BRST_PTRACE(" BRST_Doc_Font\n");

    if (!BRST_Doc_Initialized(pdf))
        return NULL;

    if (!font_name) {
        BRST_Error_Raise(pdf->error, BRST_INVALID_FONT_NAME, 0);
        return NULL;
    }

    /* if encoding-name is not specified, find default-encoding of fontdef
     */
    if (!encoding_name) {
        fontdef = BRST_Doc_FontDef(pdf, font_name);

        if (fontdef) {
            BRST_Type1FontDefAttr attr = (BRST_Type1FontDefAttr)fontdef->attr;

            if (fontdef->type == BRST_FONTDEF_TYPE_TYPE1 && BRST_StrCmp(attr->encoding_scheme, BRST_ENCODING_FONT_SPECIFIC) == 0)
                encoder = BRST_Doc_Encoder_Prepare(pdf, BRST_ENCODING_FONT_SPECIFIC);
            else
                encoder = BRST_Doc_Encoder_Prepare(pdf, BRST_ENCODING_STANDARD);
        } else {
            BRST_Error_Check(pdf->error);
            return NULL;
        }

        if (!encoder) {
            BRST_Error_Check(pdf->error);
            return NULL;
        }

        font = BRST_Doc_FindFont(pdf, font_name, encoder->name);
    } else {
        font = BRST_Doc_FindFont(pdf, font_name, encoding_name);
    }

    if (font)
        return font;

    if (!fontdef) {
        fontdef = BRST_Doc_FontDef(pdf, font_name);

        if (!fontdef) {
            BRST_Error_Check(pdf->error);
            return NULL;
        }
    }

    if (!encoder) {
        encoder = BRST_Doc_Encoder_Prepare(pdf, encoding_name);

        if (!encoder)
            return NULL;
    }

    switch (fontdef->type) {
    case BRST_FONTDEF_TYPE_TYPE1:
        font = BRST_Type1Font_New(pdf->mmgr, fontdef, encoder, pdf->xref);

        if (font)
            BRST_List_Add(pdf->font_mgr, font);

        break;
    case BRST_FONTDEF_TYPE_TRUETYPE:
        if (encoder->type == BRST_ENCODER_TYPE_DOUBLE_BYTE)
            font = BRST_Type0Font_New(pdf->mmgr, fontdef, encoder,
                pdf->xref);
        else
            font = BRST_TTFont_New(pdf->mmgr, fontdef, encoder, pdf->xref);

        if (font)
            BRST_List_Add(pdf->font_mgr, font);

        break;
    case BRST_FONTDEF_TYPE_CID:
        font = BRST_Type0Font_New(pdf->mmgr, fontdef, encoder, pdf->xref);

        if (font)
            BRST_List_Add(pdf->font_mgr, font);

        break;
    default:
        BRST_Error_Raise(pdf->error, BRST_UNSUPPORTED_FONT_TYPE, 0);
        return NULL;
    }

    if (!font)
        BRST_Error_Check(pdf->error);

    if (font && (pdf->compression_mode & BRST_COMP_METADATA))
        font->filter = BRST_STREAM_FILTER_FLATE_DECODE;

    return font;
}
