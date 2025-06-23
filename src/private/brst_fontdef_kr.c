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
#include "private/brst_fontdef_kr.h"
#include "private/brst_fontdef_cid.h"
#include "private/brst_utils.h"
#include "brst_consts.h"

#include "../src/private/data/kr.data"

BRST_STATUS
DotumChe_Init(BRST_FontDef fontdef)
{
    BRST_STATUS ret;

    BRST_PTRACE((" BRST_FontDef_DotumChe_Init\n"));

    fontdef->ascent       = 858;
    fontdef->descent      = -141;
    fontdef->cap_height   = 679;
    fontdef->font_bbox    = BRST_ToBox(0, -150, 1000, 863);
    fontdef->flags        = BRST_FONT_SYMBOLIC + BRST_FONT_FIXED_WIDTH;
    fontdef->italic_angle = 0;
    fontdef->stemv        = 78;
    if ((ret = BRST_CIDFontDef_AddWidth(fontdef, DotumChe_W_ARRAY)) != BRST_OK) {
        return ret;
    }

    fontdef->type  = BRST_FONTDEF_TYPE_CID;
    fontdef->valid = BRST_TRUE;

    return BRST_OK;
}

BRST_STATUS
DotumChe_Bold_Init(BRST_FontDef fontdef)
{
    BRST_STATUS ret = DotumChe_Init(fontdef);

    if (ret != BRST_OK)
        return ret;

    return BRST_CIDFontDef_ChangeStyle(fontdef, BRST_TRUE, BRST_FALSE);
}

BRST_STATUS
DotumChe_Italic_Init(BRST_FontDef fontdef)
{
    BRST_STATUS ret = DotumChe_Init(fontdef);

    if (ret != BRST_OK)
        return ret;

    return BRST_CIDFontDef_ChangeStyle(fontdef, BRST_FALSE, BRST_TRUE);
}

BRST_STATUS
DotumChe_BoldItalic_Init(BRST_FontDef fontdef)
{
    BRST_STATUS ret = DotumChe_Init(fontdef);

    if (ret != BRST_OK)
        return ret;

    return BRST_CIDFontDef_ChangeStyle(fontdef, BRST_TRUE, BRST_TRUE);
}

BRST_STATUS
Dotum_Init(BRST_FontDef fontdef)
{
    BRST_STATUS ret;

    BRST_PTRACE((" BRST_FontDef_Dotum_Init\n"));

    fontdef->ascent       = 858;
    fontdef->descent      = -141;
    fontdef->cap_height   = 679;
    fontdef->font_bbox    = BRST_ToBox(0, -150, 1000, 863);
    fontdef->flags        = BRST_FONT_SYMBOLIC;
    fontdef->italic_angle = 0;
    fontdef->stemv        = 78;
    if ((ret = BRST_CIDFontDef_AddWidth(fontdef, Dotum_W_ARRAY)) != BRST_OK) {
        return ret;
    }

    fontdef->type  = BRST_FONTDEF_TYPE_CID;
    fontdef->valid = BRST_TRUE;

    return BRST_OK;
}

BRST_STATUS
Dotum_Bold_Init(BRST_FontDef fontdef)
{
    BRST_STATUS ret = Dotum_Init(fontdef);

    if (ret != BRST_OK)
        return ret;

    return BRST_CIDFontDef_ChangeStyle(fontdef, BRST_TRUE, BRST_FALSE);
}

BRST_STATUS
Dotum_Italic_Init(BRST_FontDef fontdef)
{
    BRST_STATUS ret = Dotum_Init(fontdef);

    if (ret != BRST_OK)
        return ret;

    return BRST_CIDFontDef_ChangeStyle(fontdef, BRST_FALSE, BRST_TRUE);
}

BRST_STATUS
Dotum_BoldItalic_Init(BRST_FontDef fontdef)
{
    BRST_STATUS ret = Dotum_Init(fontdef);

    if (ret != BRST_OK)
        return ret;

    return BRST_CIDFontDef_ChangeStyle(fontdef, BRST_TRUE, BRST_TRUE);
}

BRST_STATUS
BatangChe_Init(BRST_FontDef fontdef)
{
    BRST_STATUS ret;

    BRST_PTRACE((" BRST_FontDef_BatangChe_Init\n"));

    fontdef->ascent       = 858;
    fontdef->descent      = -141;
    fontdef->cap_height   = 769;
    fontdef->font_bbox    = BRST_ToBox(-0, -154, 1000, 861);
    fontdef->flags        = BRST_FONT_SYMBOLIC + BRST_FONT_FIXED_WIDTH + BRST_FONT_SERIF;
    fontdef->italic_angle = 0;
    fontdef->stemv        = 78;
    if ((ret = BRST_CIDFontDef_AddWidth(fontdef, BatangChe_W_ARRAY)) != BRST_OK) {
        return ret;
    }

    fontdef->type  = BRST_FONTDEF_TYPE_CID;
    fontdef->valid = BRST_TRUE;

    return BRST_OK;
}

BRST_STATUS
BatangChe_Bold_Init(BRST_FontDef fontdef)
{
    BRST_STATUS ret = BatangChe_Init(fontdef);

    if (ret != BRST_OK)
        return ret;

    return BRST_CIDFontDef_ChangeStyle(fontdef, BRST_TRUE, BRST_FALSE);
}

BRST_STATUS
BatangChe_Italic_Init(BRST_FontDef fontdef)
{
    BRST_STATUS ret = BatangChe_Init(fontdef);

    if (ret != BRST_OK)
        return ret;

    return BRST_CIDFontDef_ChangeStyle(fontdef, BRST_FALSE, BRST_TRUE);
}

BRST_STATUS
BatangChe_BoldItalic_Init(BRST_FontDef fontdef)
{
    BRST_STATUS ret = BatangChe_Init(fontdef);

    if (ret != BRST_OK)
        return ret;

    return BRST_CIDFontDef_ChangeStyle(fontdef, BRST_TRUE, BRST_TRUE);
}

BRST_STATUS
Batang_Init(BRST_FontDef fontdef)
{
    BRST_STATUS ret;

    BRST_PTRACE((" BRST_FontDef_Batang_Init\n"));

    fontdef->ascent       = 858;
    fontdef->descent      = -141;
    fontdef->cap_height   = 679;
    fontdef->font_bbox    = BRST_ToBox(0, -154, 1000, 861);
    fontdef->flags        = BRST_FONT_SYMBOLIC + BRST_FONT_SERIF;
    fontdef->italic_angle = 0;
    fontdef->stemv        = 78;
    if ((ret = BRST_CIDFontDef_AddWidth(fontdef, Batang_W_ARRAY)) != BRST_OK) {
        return ret;
    }

    fontdef->type  = BRST_FONTDEF_TYPE_CID;
    fontdef->valid = BRST_TRUE;

    return BRST_OK;
}

BRST_STATUS
Batang_Bold_Init(BRST_FontDef fontdef)
{
    BRST_STATUS ret = Batang_Init(fontdef);

    if (ret != BRST_OK)
        return ret;

    return BRST_CIDFontDef_ChangeStyle(fontdef, BRST_TRUE, BRST_FALSE);
}

BRST_STATUS
Batang_Italic_Init(BRST_FontDef fontdef)
{
    BRST_STATUS ret = Batang_Init(fontdef);

    if (ret != BRST_OK)
        return ret;

    return BRST_CIDFontDef_ChangeStyle(fontdef, BRST_FALSE, BRST_TRUE);
}

BRST_STATUS
Batang_BoldItalic_Init(BRST_FontDef fontdef)
{
    BRST_STATUS ret = Batang_Init(fontdef);

    if (ret != BRST_OK)
        return ret;

    return BRST_CIDFontDef_ChangeStyle(fontdef, BRST_TRUE, BRST_TRUE);
}
