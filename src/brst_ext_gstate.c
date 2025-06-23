#include "brst_external.h"
#include "brst_types.h"
#include "brst_mmgr.h"
#include "brst_encrypt.h"
#include "brst_stream.h"
#include "brst_dict.h"
#include "brst_xref.h"
#include "brst_error.h"
#include "brst_consts.h"
#include "private/brst_utils.h"
#include "brst_ext_gstate.h"
#include "private/brst_ext_gstate.h"
#include "private/brst_dict.h"

static const char* const BRST_BM_NAMES[] = {
    "Normal",
    "Multiply",
    "Screen",
    "Overlay",
    "Darken",
    "Lighten",
    "ColorDodge",
    "ColorBurn",
    "HardLight",
    "SoftLight",
    "Difference",
    "Exclusion"
};

BRST_EXPORT(BRST_STATUS)
BRST_ExtGState_SetAlphaStroke(BRST_ExtGState ext_gstate,
    BRST_REAL value)
{
    BRST_STATUS ret = ExtGState_Check(ext_gstate);

    if (ret != BRST_OK)
        return ret;

    if (value < 0 || value > 1.0f)
        return BRST_Error_Raise(ext_gstate->error,
            BRST_EXT_GSTATE_OUT_OF_RANGE, 0);

    return BRST_Dict_AddReal(ext_gstate, "CA", value);
}

BRST_EXPORT(BRST_STATUS)
BRST_ExtGState_SetAlphaFill(BRST_ExtGState ext_gstate,
    BRST_REAL value)
{
    BRST_STATUS ret = ExtGState_Check(ext_gstate);

    if (ret != BRST_OK)
        return ret;

    if (value < 0 || value > 1.0f)
        return BRST_Error_Raise(ext_gstate->error,
            BRST_EXT_GSTATE_OUT_OF_RANGE, 0);

    return BRST_Dict_AddReal(ext_gstate, "ca", value);
}

BRST_EXPORT(BRST_STATUS)
BRST_ExtGState_SetBlendMode(BRST_ExtGState ext_gstate,
    BRST_BlendMode bmode)
{
    BRST_STATUS ret = ExtGState_Check(ext_gstate);

    if (ret != BRST_OK)
        return ret;

    if ((int)bmode < 0 || (int)bmode > (int)BRST_BM_EOF)
        return BRST_Error_Raise(ext_gstate->error,
            BRST_EXT_GSTATE_OUT_OF_RANGE, 0);

    return BRST_Dict_AddName(ext_gstate, "BM", BRST_BM_NAMES[(int)bmode]);
}

/*
BRST_STATUS
BRST_ExtGState_SetStrokeAdjustment  (BRST_ExtGState   ext_gstate,
                                     BRST_BOOL        value)
{
    BRST_STATUS ret = ExtGState_Check (ext_gstate);

    if (ret != BRST_OK)
        return ret;

    return BRST_Dict_AddBoolean (ext_gstate, "SA", value);
}
*/
