#ifndef PRIVATE_BRST_PATTERN_H
#define PRIVATE_BRST_PATTERN_H

#include "brst_pattern.h"

typedef enum _BRST_Pattern_Kind {
    // PatternType = 1, PaintType = 1
    BRST_PATTERN_TILING_COLORED,
    // PatternType = 1, PaintType = 2
    BRST_PATTERN_TILING_NON_COLORED,
    // PatternType = 2
    BRST_PATTERN_SHADING
} BRST_Pattern_Kind;

BRST_Pattern
BRST_Pattern_Tiling_New(
    BRST_MMgr   mmgr,
    BRST_Xref   xref,
    BRST_REAL   left,
    BRST_REAL   bottom,
    BRST_REAL   right,
    BRST_REAL   top,
    BRST_REAL   xstep,
    BRST_REAL   ystep,
    BRST_Matrix matrix
);

BRST_Stream
BRST_Pattern_Stream(
    BRST_Pattern obj
);

#endif /* PRIVATE_BRST_PATTERN_H */