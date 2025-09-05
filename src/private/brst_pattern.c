#include "brst_stream.h"
#include "brst_xref.h"
#include "brst_mmgr.h"
#include "brst_dict.h"
#include "brst_matrix.h"
#include "brst_array.h"
#include "brst_encrypt.h"
#include "private/brst_array.h"
#include "private/brst_dict.h"
#include "private/brst_name.h"
#include "brst_xobject.h"
#include "brst_pattern.h"
#include "brst_types.h"
#include "private/brst_utils.h"
#include "private/brst_geometry.h"
#include "brst_consts.h"

BRST_Pattern
BRST_Pattern_Tiling_New(
    BRST_MMgr mmgr,
    BRST_Xref xref,
    BRST_REAL left,
    BRST_REAL bottom,
    BRST_REAL right,
    BRST_REAL top,
    BRST_REAL xstep,
    BRST_REAL ystep,
    BRST_Matrix matrix
) {
    BRST_Dict pat;
    BRST_STATUS ret = BRST_OK;

    pat = BRST_Dict_New_Stream_Init(mmgr, xref);
    if (!pat)
        return NULL;

    pat->header.obj_class |= BRST_OSUBCLASS_PATTERN;
    ret += BRST_Dict_AddName(pat, "Type", "Pattern");

    ret += BRST_Dict_AddNumber(pat, "PatternType", 1);
    ret += BRST_Dict_AddNumber(pat, "PaintType", 2);
    ret += BRST_Dict_AddNumber(pat, "TilingType", 1);

    // TODO Проверить xstep/ystep на 0
    ret += BRST_Dict_AddNumber(pat, "XStep", xstep);
    ret += BRST_Dict_AddNumber(pat, "YStep", ystep);

    ret += BRST_Dict_Add(pat, "BBox", BRST_Box_Array_New(mmgr, BRST_ToRect(left, bottom, right, top)));
    ret += BRST_Dict_Add(pat, "Matrix", BRST_Matrix_Array_New(mmgr, matrix));

    if (ret != BRST_OK)
        return NULL;

    return pat;
}

BRST_Stream
BRST_Pattern_Stream(
    BRST_Pattern pat
) {
    return BRST_Dict_Stream(pat);
}
