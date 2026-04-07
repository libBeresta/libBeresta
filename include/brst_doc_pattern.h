#ifndef BRST_DOC_PATTERN_H
#define BRST_DOC_PATTERN_H

BRST_EXPORT(BRST_Pattern)
BRST_Doc_Pattern_Tiling_Create(
    BRST_Doc    pdf,
    BRST_REAL   left,
    BRST_REAL   bottom,
    BRST_REAL   right,
    BRST_REAL   top,
    BRST_REAL   xstep,
    BRST_REAL   ystep,
    BRST_Matrix matrix
);

BRST_EXPORT(BRST_Stream)
BRST_Doc_Pattern_Stream(
    BRST_Pattern pat
);

#endif /* BRST_DOC_PATTERN_H */