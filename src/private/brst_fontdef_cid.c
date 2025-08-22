#include "brst_types.h"
#include "brst_encoder.h"
#include "brst_stream.h"
#include "brst_mmgr.h"
#include "brst_dict.h"
#include "brst_error.h"
#include "private/brst_error.h"
#include "private/brst_list.h"
#include "private/brst_defines.h"
#include "brst_fontdef.h"
#include "private/brst_fontdef.h"
#include "private/brst_fontdef_cid.h"
#include "private/brst_utils.h"
#include "brst_consts.h"

void BRST_CIDFontDef_FreeWidth(BRST_FontDef fontdef);

void BRST_CIDFontDef_FreeFunc(BRST_FontDef fontdef);

/*----------------------------------------------------------------------*/
/*----- BRST_CIDFontDef ------------------------------------------------*/

void BRST_CIDFontDef_FreeWidth(BRST_FontDef fontdef)
{
    BRST_CIDFontDefAttr attr = (BRST_CIDFontDefAttr)fontdef->attr;
    BRST_UINT i;

    BRST_PTRACE(" BRST_FontDef_Validate\n");

    for (i = 0; i < BRST_List_Count(attr->widths); i++) {
        BRST_CID_Width* w = (BRST_CID_Width*)BRST_List_ItemAt(attr->widths, i);

        BRST_FreeMem(fontdef->mmgr, w);
    }

    BRST_List_Free(attr->widths);
    attr->widths = NULL;

    fontdef->valid = BRST_FALSE;
}

BRST_FontDef
BRST_CIDFontDef_New(BRST_MMgr mmgr,
    char* name,
    BRST_FontDef_InitFunc init_fn)
{
    BRST_FontDef fontdef;
    BRST_CIDFontDefAttr fontdef_attr;

    BRST_PTRACE(" BRST_CIDFontDef_New\n");

    if (!mmgr)
        return NULL;

    fontdef = BRST_GetMem(mmgr, sizeof(BRST_FontDef_Rec));
    if (!fontdef)
        return NULL;

    BRST_MemSet(fontdef, 0, sizeof(BRST_FontDef_Rec));
    fontdef->sig_bytes = BRST_FONTDEF_SIG_BYTES;
    BRST_StrCpy(fontdef->base_font, name, fontdef->base_font + BRST_LIMIT_MAX_NAME_LEN);
    fontdef->mmgr    = mmgr;
    fontdef->error   = BRST_MMgr_Error(mmgr);
    fontdef->type    = BRST_FONTDEF_TYPE_UNINITIALIZED;
    fontdef->free_fn = BRST_CIDFontDef_FreeFunc;
    fontdef->init_fn = init_fn;
    fontdef->valid   = BRST_FALSE;
    fontdef_attr     = BRST_GetMem(mmgr, sizeof(BRST_CIDFontDefAttr_Rec));
    if (!fontdef_attr) {
        BRST_FreeMem(fontdef->mmgr, fontdef);
        return NULL;
    }

    fontdef->attr = fontdef_attr;
    BRST_MemSet((BRST_BYTE*)fontdef_attr, 0,
        sizeof(BRST_CIDFontDefAttr_Rec));

    fontdef_attr->widths = BRST_List_New(mmgr, BRST_DEF_CHAR_WIDTHS_NUM);
    if (!fontdef_attr->widths) {
        BRST_FreeMem(fontdef->mmgr, fontdef);
        BRST_FreeMem(fontdef->mmgr, fontdef_attr);
        return NULL;
    }

    fontdef->missing_width = 500;
    fontdef_attr->DW       = 1000;
    fontdef_attr->DW2[0]   = 880;
    fontdef_attr->DW2[1]   = -1000;

    return fontdef;
}

BRST_INT16
BRST_CIDFontDef_CIDWidth(BRST_FontDef fontdef,
    BRST_UINT16 cid)
{
    BRST_CIDFontDefAttr attr = (BRST_CIDFontDefAttr)fontdef->attr;
    BRST_UINT i;

    BRST_PTRACE(" BRST_CIDFontDef_CIDWidth\n");

    for (i = 0; i < BRST_List_Count(attr->widths); i++) {
        BRST_CID_Width* w = (BRST_CID_Width*)BRST_List_ItemAt(attr->widths,
            i);

        if (w->cid == cid)
            return w->width;
    }

    /* Not found in pdf_cid_width array. */
    return attr->DW;
}

void BRST_CIDFontDef_FreeFunc(BRST_FontDef fontdef)
{
    BRST_CIDFontDefAttr attr = (BRST_CIDFontDefAttr)fontdef->attr;

    BRST_PTRACE(" BRST_CIDFontDef_FreeFunc\n");

    BRST_CIDFontDef_FreeWidth(fontdef);
    BRST_FreeMem(fontdef->mmgr, attr);
}

BRST_STATUS
BRST_CIDFontDef_AddWidth(BRST_FontDef fontdef,
    const BRST_CID_Width* widths)
{
    BRST_CIDFontDefAttr attr = (BRST_CIDFontDefAttr)fontdef->attr;

    BRST_PTRACE(" BRST_CIDFontDef_AddWidth\n");

    while (widths->cid != 0xFFFF) {
        BRST_CID_Width* w = BRST_GetMem(fontdef->mmgr,
            sizeof(BRST_CID_Width));
        BRST_STATUS ret;

        if (!w)
            return BRST_Error_Code(fontdef->error);

        w->cid   = widths->cid;
        w->width = widths->width;

        if ((ret = BRST_List_Add(attr->widths, w)) != BRST_OK) {
            BRST_FreeMem(fontdef->mmgr, w);

            return ret;
        }

        widths++;
    }

    return BRST_OK;
}

BRST_STATUS
BRST_CIDFontDef_ChangeStyle(BRST_FontDef fontdef,
    BRST_BOOL bold,
    BRST_BOOL italic)
{
    BRST_PTRACE(" BRST_CIDFontDef_ChangeStyle\n");

    if (!fontdef || !fontdef->attr)
        return BRST_INVALID_FONTDEF_DATA;

    if (bold) {
        fontdef->stemv *= 2;
        fontdef->flags |= BRST_FONT_FOURCE_BOLD;
    }

    if (italic) {
        fontdef->italic_angle -= 11;
        fontdef->flags |= BRST_FONT_ITALIC;
    }

    return BRST_OK;
}
