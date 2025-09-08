#include "brst_types.h"
#include "brst_mmgr.h"
#include "brst_encrypt.h"
#include "brst_stream.h"
#include "brst_xref.h"
#include "brst_dict.h"
#include "private/brst_dict.h"
#include "brst_matrix.h"
#include "brst_array.h"
#include "private/brst_array.h"
#include "private/brst_xref.h"
#include "brst_encoder.h"
#include "brst_page.h"
#include "brst_destination.h"
#include "brst_outline.h"
#include "private/brst_encrypt_dict.h"
#include "private/brst_catalog.h"
#include "brst_pdfa.h"
#include "brst_doc.h"
#include "private/brst_doc.h"
#include "brst_base.h"
#include "brst_error.h"
#include "brst_fontdef.h"
#include "private/brst_defines.h"
#include "private/brst_fontdef.h"
#include "private/brst_fontdef_base14.h"
#include "brst_consts.h"
#include "private/brst_utils.h"

BRST_FontDef
BRST_Doc_FindFontDef(BRST_Doc pdf,
    const char* font_name)
{
    BRST_List list = pdf->fontdef_list;
    BRST_UINT i;

    BRST_PTRACE(" BRST_Doc_FindFontDef\n");

    for (i = 0; i < BRST_List_Count(list); i++) {
        BRST_FontDef def = (BRST_FontDef)BRST_List_ItemAt(list, i);

        if (BRST_StrCmp(font_name, def->base_font) == 0) {
            if (def->type == BRST_FONTDEF_TYPE_UNINITIALIZED) {
                if (!def->init_fn || def->init_fn(def) != BRST_OK)
                    return NULL;
            }

            return def;
        }
    }

    return NULL;
}

BRST_STATUS
BRST_Doc_RegisterFontDef(BRST_Doc pdf,
    BRST_FontDef fontdef)
{
    BRST_STATUS ret;

    BRST_PTRACE(" BRST_Doc_RegisterFontDef\n");

    if (!fontdef)
        return BRST_Error_Set(pdf->error, BRST_INVALID_OBJECT, 0);

    if (BRST_Doc_FindFontDef(pdf, fontdef->base_font) != NULL) {
        BRST_FontDef_Free(fontdef);
        return BRST_Error_Set(pdf->error, BRST_DUPLICATE_REGISTRATION, 0);
    }

    if ((ret = BRST_List_Add(pdf->fontdef_list, fontdef)) != BRST_OK) {
        BRST_FontDef_Free(fontdef);
        return BRST_Error_Set(pdf->error, ret, 0);
    }

    return BRST_OK;
}

BRST_FontDef
BRST_Doc_FontDef(BRST_Doc pdf,
    const char* font_name)
{
    BRST_STATUS ret;
    BRST_FontDef def;

    BRST_PTRACE(" BRST_Doc_FontDef\n");

    if (!BRST_Doc_Initialized(pdf))
        return NULL;

    def = BRST_Doc_FindFontDef(pdf, font_name);

    if (!def) {
        def = BRST_Base14FontDef_New(pdf->mmgr, font_name);

        if (!def)
            return NULL;

        if ((ret = BRST_List_Add(pdf->fontdef_list, def)) != BRST_OK) {
            BRST_FontDef_Free(def);
            BRST_Error_Raise(pdf->error, ret, 0);
            def = NULL;
        }
    }

    return def;
}

void FreeFontDefList(BRST_Doc pdf)
{
    BRST_List list = pdf->fontdef_list;
    BRST_UINT i;

    BRST_PTRACE(" BRST_Doc_FreeFontDefList\n");

    for (i = 0; i < BRST_List_Count(list); i++) {
        BRST_FontDef def = (BRST_FontDef)BRST_List_ItemAt(list, i);

        BRST_FontDef_Free(def);
    }

    BRST_List_Free(list);

    pdf->fontdef_list = NULL;
}

void CleanupFontDefList(BRST_Doc pdf)
{
    BRST_List list = pdf->fontdef_list;
    BRST_UINT i;

    BRST_PTRACE(" CleanupFontDefList\n");

    for (i = 0; i < BRST_List_Count(list); i++) {
        BRST_FontDef def = (BRST_FontDef)BRST_List_ItemAt(list, i);

        BRST_FontDef_Cleanup(def);
    }
}
