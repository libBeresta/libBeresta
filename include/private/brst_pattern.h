#ifndef PRIVATE_BRST_PATTERN_H
#define PRIVATE_BRST_PATTERN_H

#include "brst_pattern.h"

BRST_Pattern
BRST_Pattern_Tiling_New(
    BRST_MMgr mmgr,
    BRST_Xref xref,
    BRST_REAL width,
    BRST_REAL height,
    BRST_REAL scalex,
    BRST_REAL scaley
);

BRST_Stream
BRST_Pattern_Stream(
    BRST_Pattern obj
);

#endif /* PRIVATE_BRST_PATTERN_H */