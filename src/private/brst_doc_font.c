#include "brst_types.h"
#include "brst_mmgr.h"
#include "brst_encrypt.h"
#include "brst_stream.h"
#include "brst_dict.h"
#include "brst_xref.h"
#include "brst_encoder.h"
#include "brst_page.h"
#include "brst_destination.h"
#include "brst_outline.h"
#include "brst_font.h"
#include "private/brst_encrypt_dict.h"
#include "private/brst_catalog.h"
#include "brst_pdfa.h"
#include "brst_doc.h"
#include "private/brst_doc.h"
#include "brst_base.h"
#include "brst_error.h"
#include "brst_fontdef.h"
#include "brst_font.h"
#include "private/brst_font.h"
#include "private/brst_fontdef.h"
#include "private/brst_fontdef_ttf.h"
#include "private/brst_fontdef_type1.h"
#include "private/brst_doc_fontdef.h"
#include "private/brst_doc_font.h"
#include "brst_consts.h"
#include "private/brst_utils.h"

const char*
LoadTTFontFromStream(BRST_Doc pdf,
    BRST_Stream font_data,
    BRST_BOOL embedding,
    const char* file_name)
{
    BRST_FontDef def;

    BRST_PTRACE(" LoadTTFontFromStream\n");
    BRST_UNUSED(file_name);

    def = BRST_TTFontDef_Load(pdf->mmgr, font_data, embedding);
    if (def) {
        BRST_FontDef tmpdef = BRST_Doc_FindFontDef(pdf, def->base_font);
        if (tmpdef) {
            BRST_FontDef_Free(def);
            return tmpdef->base_font;
        }

        if (BRST_List_Add(pdf->fontdef_list, def) != BRST_OK) {
            BRST_FontDef_Free(def);
            return NULL;
        }
    } else
        return NULL;

    if (embedding) {
        if (pdf->ttfont_tag[0] == 0) {
            BRST_MemCopy(pdf->ttfont_tag, (BRST_BYTE*)"BRSTAA", 6);
        } else {
            BRST_INT i;

            for (i = 5; i >= 0; i--) {
                pdf->ttfont_tag[i] += 1;
                if (pdf->ttfont_tag[i] > 'Z')
                    pdf->ttfont_tag[i] = 'A';
                else
                    break;
            }
        }

        BRST_TTFontDef_SetTagName(def, (char*)pdf->ttfont_tag);
    }

    return def->base_font;
}

const char*
LoadTTFontFromStream2(BRST_Doc pdf,
    BRST_Stream font_data,
    BRST_UINT index,
    BRST_BOOL embedding,
    const char* file_name)
{
    BRST_FontDef def;

    BRST_PTRACE(" LoadTTFontFromStream2\n");
    BRST_UNUSED(file_name);

    def = BRST_TTFontDef_Load2(pdf->mmgr, font_data, index, embedding);
    if (def) {
        BRST_FontDef tmpdef = BRST_Doc_FindFontDef(pdf, def->base_font);
        if (tmpdef) {
            BRST_FontDef_Free(def);
            return tmpdef->base_font;
        }

        if (BRST_List_Add(pdf->fontdef_list, def) != BRST_OK) {
            BRST_FontDef_Free(def);
            return NULL;
        }
    } else
        return NULL;

    if (embedding) {
        if (pdf->ttfont_tag[0] == 0) {
            BRST_MemCopy(pdf->ttfont_tag, (BRST_BYTE*)"BRSTAA", 6);
        } else {
            BRST_INT i;

            for (i = 5; i >= 0; i--) {
                pdf->ttfont_tag[i] += 1;
                if (pdf->ttfont_tag[i] > 'Z')
                    pdf->ttfont_tag[i] = 'A';
                else
                    break;
            }
        }

        BRST_TTFontDef_SetTagName(def, (char*)pdf->ttfont_tag);
    }

    return def->base_font;
}

const char*
LoadType1FontFromStream(BRST_Doc pdf,
    BRST_Stream afmdata,
    BRST_Stream pfmdata)
{
    BRST_FontDef def;

    BRST_PTRACE(" BRST_LoadType1FontFromStream\n");

    if (!BRST_Doc_Initialized(pdf))
        return NULL;

    def = BRST_Type1FontDef_Load(pdf->mmgr, afmdata, pfmdata);
    if (def) {
        BRST_FontDef tmpdef = BRST_Doc_FindFontDef(pdf, def->base_font);
        if (tmpdef) {
            BRST_FontDef_Free(def);
            BRST_Error_Set(pdf->error, BRST_FONT_EXISTS, 0);
            return NULL;
        }

        if (BRST_List_Add(pdf->fontdef_list, def) != BRST_OK) {
            BRST_FontDef_Free(def);
            return NULL;
        }
        return def->base_font;
    }
    return NULL;
}

BRST_Font
BRST_Doc_FindFont(BRST_Doc pdf,
    const char* font_name,
    const char* encoding_name)
{
    BRST_UINT i;
    BRST_Font font;

    BRST_PTRACE(" BRST_Doc_FindFont\n");

    for (i = 0; i < BRST_List_Count(pdf->font_mgr); i++) {
        BRST_FontAttr attr;

        font = (BRST_Font)BRST_List_ItemAt(pdf->font_mgr, i);
        attr = (BRST_FontAttr)font->attr;

        if (BRST_StrCmp(attr->fontdef->base_font, font_name) == 0 && BRST_StrCmp(attr->encoder->name, encoding_name) == 0)
            return font;
    }

    return NULL;
}
