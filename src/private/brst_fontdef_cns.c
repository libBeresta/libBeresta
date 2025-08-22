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
#include "private/brst_fontdef_cns.h"
#include "private/brst_fontdef_cid.h"
#include "private/brst_utils.h"
#include "brst_consts.h"

#include "../src/private/data/cns.data"

BRST_STATUS
SimSun_Init(BRST_FontDef fontdef)
{
    BRST_STATUS ret;

    BRST_PTRACE(" BRST_FontDef_SimSun_Init\n");

    fontdef->ascent       = 859;
    fontdef->descent      = -140;
    fontdef->cap_height   = 683;
    fontdef->font_bbox    = BRST_ToBox(0, -140, 996, 855);
    fontdef->flags        = BRST_FONT_SYMBOLIC + BRST_FONT_FIXED_WIDTH + BRST_FONT_SERIF;
    fontdef->italic_angle = 0;
    fontdef->stemv        = 78;
    if ((ret = BRST_CIDFontDef_AddWidth(fontdef, SIMSUN_W_ARRAY)) != BRST_OK) {
        return ret;
    }

    fontdef->type  = BRST_FONTDEF_TYPE_CID;
    fontdef->valid = BRST_TRUE;

    return BRST_OK;
}

BRST_STATUS
SimSun_Bold_Init(BRST_FontDef fontdef)
{
    BRST_STATUS ret = SimSun_Init(fontdef);

    if (ret != BRST_OK)
        return ret;

    return BRST_CIDFontDef_ChangeStyle(fontdef, BRST_TRUE, BRST_FALSE);
}

BRST_STATUS
SimSun_Italic_Init(BRST_FontDef fontdef)
{
    BRST_STATUS ret = SimSun_Init(fontdef);

    if (ret != BRST_OK)
        return ret;

    return BRST_CIDFontDef_ChangeStyle(fontdef, BRST_FALSE, BRST_TRUE);
}

BRST_STATUS
SimSun_BoldItalic_Init(BRST_FontDef fontdef)
{
    BRST_STATUS ret = SimSun_Init(fontdef);

    if (ret != BRST_OK)
        return ret;

    return BRST_CIDFontDef_ChangeStyle(fontdef, BRST_TRUE, BRST_TRUE);
}

BRST_STATUS
SimHei_Init(BRST_FontDef fontdef)
{
    BRST_STATUS ret;

    BRST_PTRACE(" BRST_FontDef_SimHei_Init\n");

    fontdef->ascent       = 859;
    fontdef->descent      = -140;
    fontdef->cap_height   = 769;
    fontdef->font_bbox    = BRST_ToBox(-0, -140, 996, 855);
    fontdef->flags        = BRST_FONT_SYMBOLIC + BRST_FONT_FIXED_WIDTH;
    fontdef->italic_angle = 0;
    fontdef->stemv        = 78;
    if ((ret = BRST_CIDFontDef_AddWidth(fontdef, SIMHEI_W_ARRAY)) != BRST_OK) {
        return ret;
    }

    fontdef->type  = BRST_FONTDEF_TYPE_CID;
    fontdef->valid = BRST_TRUE;

    return BRST_OK;
}

BRST_STATUS
SimHei_Bold_Init(BRST_FontDef fontdef)
{
    BRST_STATUS ret = SimHei_Init(fontdef);

    if (ret != BRST_OK)
        return ret;

    return BRST_CIDFontDef_ChangeStyle(fontdef, BRST_TRUE, BRST_FALSE);
}

BRST_STATUS
SimHei_Italic_Init(BRST_FontDef fontdef)
{
    BRST_STATUS ret = SimHei_Init(fontdef);

    if (ret != BRST_OK)
        return ret;

    return BRST_CIDFontDef_ChangeStyle(fontdef, BRST_FALSE, BRST_TRUE);
}

BRST_STATUS
SimHei_BoldItalic_Init(BRST_FontDef fontdef)
{
    BRST_STATUS ret = SimHei_Init(fontdef);

    if (ret != BRST_OK)
        return ret;

    return BRST_CIDFontDef_ChangeStyle(fontdef, BRST_TRUE, BRST_TRUE);
}
