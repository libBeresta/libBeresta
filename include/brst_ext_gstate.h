#ifndef BRST_EXT_GSTATE_H
#define BRST_EXT_GSTATE_H

#include "brst_external.h"
#include "brst_types.h"
#include "brst_dict.h"
#include "brst_geometry_defines.h"

typedef BRST_Dict BRST_ExtGState;

BRST_EXPORT(BRST_STATUS)
BRST_ExtGState_SetAlphaStroke(
    BRST_ExtGState ext_gstate,
    BRST_REAL      value
);

BRST_EXPORT(BRST_STATUS)
BRST_ExtGState_SetAlphaFill(
    BRST_ExtGState ext_gstate,
    BRST_REAL      value
);

BRST_EXPORT(BRST_STATUS)
BRST_ExtGState_SetBlendMode(
    BRST_ExtGState ext_gstate,
    BRST_BlendMode mode
);

#endif /* BRST_EXT_GSTATE_H */