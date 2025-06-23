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
#include "private/brst_fontdef_jp.h"
#include "private/brst_fontdef_cid.h"
#include "private/brst_utils.h"
#include "brst_consts.h"

#include "../src/private/data/jp.data"

BRST_STATUS
MS_Gothic_Init(BRST_FontDef fontdef)
{
    BRST_STATUS ret;

    BRST_PTRACE((" BRST_FontDef_MS_Gothic_Init\n"));

    fontdef->ascent       = 859;
    fontdef->descent      = -140;
    fontdef->cap_height   = 769;
    fontdef->font_bbox    = BRST_ToBox(-0, -136, 1000, 859);
    fontdef->flags        = BRST_FONT_SYMBOLIC + BRST_FONT_FIXED_WIDTH;
    fontdef->italic_angle = 0;
    fontdef->stemv        = 78;
    if ((ret = BRST_CIDFontDef_AddWidth(fontdef, MS_Gothic_W_ARRAY)) != BRST_OK) {
        return ret;
    }

    fontdef->type  = BRST_FONTDEF_TYPE_CID;
    fontdef->valid = BRST_TRUE;

    return BRST_OK;
}

BRST_STATUS
MS_Gothic_Bold_Init(BRST_FontDef fontdef)
{
    BRST_STATUS ret = MS_Gothic_Init(fontdef);

    if (ret != BRST_OK)
        return ret;

    return BRST_CIDFontDef_ChangeStyle(fontdef, BRST_TRUE, BRST_FALSE);
}

BRST_STATUS
MS_Gothic_Italic_Init(BRST_FontDef fontdef)
{
    BRST_STATUS ret = MS_Gothic_Init(fontdef);

    if (ret != BRST_OK)
        return ret;

    return BRST_CIDFontDef_ChangeStyle(fontdef, BRST_FALSE, BRST_TRUE);
}

BRST_STATUS
MS_Gothic_BoldItalic_Init(BRST_FontDef fontdef)
{
    BRST_STATUS ret = MS_Gothic_Init(fontdef);

    if (ret != BRST_OK)
        return ret;

    return BRST_CIDFontDef_ChangeStyle(fontdef, BRST_TRUE, BRST_TRUE);
}

BRST_STATUS
MS_PGothic_Init(BRST_FontDef fontdef)
{
    BRST_STATUS ret;

    BRST_PTRACE((" BRST_FontDef_MS_PGothic_Init\n"));

    fontdef->ascent       = 859;
    fontdef->descent      = -140;
    fontdef->cap_height   = 679;
    fontdef->font_bbox    = BRST_ToBox(-121, -136, 996, 859);
    fontdef->flags        = BRST_FONT_SYMBOLIC;
    fontdef->italic_angle = 0;
    fontdef->stemv        = 78;
    if ((ret = BRST_CIDFontDef_AddWidth(fontdef, MS_PGothic_W_ARRAY)) != BRST_OK) {
        return ret;
    }

    fontdef->type  = BRST_FONTDEF_TYPE_CID;
    fontdef->valid = BRST_TRUE;

    return BRST_OK;
}

BRST_STATUS
MS_PGothic_Bold_Init(BRST_FontDef fontdef)
{
    BRST_STATUS ret = MS_PGothic_Init(fontdef);

    if (ret != BRST_OK)
        return ret;

    return BRST_CIDFontDef_ChangeStyle(fontdef, BRST_TRUE, BRST_FALSE);
}

BRST_STATUS
MS_PGothic_Italic_Init(BRST_FontDef fontdef)
{
    BRST_STATUS ret = MS_PGothic_Init(fontdef);

    if (ret != BRST_OK)
        return ret;

    return BRST_CIDFontDef_ChangeStyle(fontdef, BRST_FALSE, BRST_TRUE);
}

BRST_STATUS
MS_PGothic_BoldItalic_Init(BRST_FontDef fontdef)
{
    BRST_STATUS ret = MS_PGothic_Init(fontdef);

    if (ret != BRST_OK)
        return ret;

    return BRST_CIDFontDef_ChangeStyle(fontdef, BRST_TRUE, BRST_TRUE);
}

BRST_STATUS
MS_Mincho_Init(BRST_FontDef fontdef)
{
    BRST_STATUS ret;

    BRST_PTRACE((" BRST_FontDef_MS_Mincho_Init\n"));

    fontdef->ascent       = 859;
    fontdef->descent      = -140;
    fontdef->cap_height   = 769;
    fontdef->font_bbox    = BRST_ToBox(-0, -136, 1000, 859);
    fontdef->flags        = BRST_FONT_SYMBOLIC + BRST_FONT_FIXED_WIDTH + BRST_FONT_SERIF;
    fontdef->italic_angle = 0;
    fontdef->stemv        = 78;
    if ((ret = BRST_CIDFontDef_AddWidth(fontdef, MS_Mincho_W_ARRAY)) != BRST_OK) {
        return ret;
    }

    fontdef->type  = BRST_FONTDEF_TYPE_CID;
    fontdef->valid = BRST_TRUE;

    return BRST_OK;
}

BRST_STATUS
MS_Mincho_Bold_Init(BRST_FontDef fontdef)
{
    BRST_STATUS ret = MS_Mincho_Init(fontdef);

    if (ret != BRST_OK)
        return ret;

    return BRST_CIDFontDef_ChangeStyle(fontdef, BRST_TRUE, BRST_FALSE);
}

BRST_STATUS
MS_Mincho_Italic_Init(BRST_FontDef fontdef)
{
    BRST_STATUS ret = MS_Mincho_Init(fontdef);

    if (ret != BRST_OK)
        return ret;

    return BRST_CIDFontDef_ChangeStyle(fontdef, BRST_FALSE, BRST_TRUE);
}

BRST_STATUS
MS_Mincho_BoldItalic_Init(BRST_FontDef fontdef)
{
    BRST_STATUS ret = MS_Mincho_Init(fontdef);

    if (ret != BRST_OK)
        return ret;

    return BRST_CIDFontDef_ChangeStyle(fontdef, BRST_TRUE, BRST_TRUE);
}

BRST_STATUS
MS_PMincho_Init(BRST_FontDef fontdef)
{
    BRST_STATUS ret;

    BRST_PTRACE((" BRST_FontDef_MS_PMincho_Init\n"));

    fontdef->ascent       = 859;
    fontdef->descent      = -140;
    fontdef->cap_height   = 679;
    fontdef->font_bbox    = BRST_ToBox(-82, -136, 996, 859);
    fontdef->flags        = BRST_FONT_SYMBOLIC + BRST_FONT_SERIF;
    fontdef->italic_angle = 0;
    fontdef->stemv        = 78;
    if ((ret = BRST_CIDFontDef_AddWidth(fontdef, MS_PMincho_W_ARRAY)) != BRST_OK) {
        return ret;
    }

    fontdef->type  = BRST_FONTDEF_TYPE_CID;
    fontdef->valid = BRST_TRUE;

    return BRST_OK;
}

BRST_STATUS
MS_PMincho_Bold_Init(BRST_FontDef fontdef)
{
    BRST_STATUS ret = MS_PMincho_Init(fontdef);

    if (ret != BRST_OK)
        return ret;

    return BRST_CIDFontDef_ChangeStyle(fontdef, BRST_TRUE, BRST_FALSE);
}

BRST_STATUS
MS_PMincho_Italic_Init(BRST_FontDef fontdef)
{
    BRST_STATUS ret = MS_PMincho_Init(fontdef);

    if (ret != BRST_OK)
        return ret;

    return BRST_CIDFontDef_ChangeStyle(fontdef, BRST_FALSE, BRST_TRUE);
}

BRST_STATUS
MS_PMincho_BoldItalic_Init(BRST_FontDef fontdef)
{
    BRST_STATUS ret = MS_PMincho_Init(fontdef);

    if (ret != BRST_OK)
        return ret;

    return BRST_CIDFontDef_ChangeStyle(fontdef, BRST_TRUE, BRST_TRUE);
}
