#ifndef BRST_DOC_PAGE_PATTERN_H
#define BRST_DOC_PAGE_PATTERN_H

BRST_EXPORT(BRST_Pattern)
BRST_Doc_Page_Pattern_Tiling_Create(
    BRST_Doc    pdf,
    BRST_Page   page,
    BRST_REAL   left,
    BRST_REAL   bottom,
    BRST_REAL   right,
    BRST_REAL   top,
    BRST_REAL   xstep,
    BRST_REAL   ystep,
    BRST_Matrix matrix
);

BRST_EXPORT(BRST_Stream)
BRST_Doc_Page_Pattern_Stream(BRST_Pattern pat);

BRST_EXPORT(BRST_STATUS)
BRST_Doc_Dict_RGBPatternFill_Select(
    BRST_Doc  pdf,
    BRST_Dict dict,
    BRST_REAL r,
    BRST_REAL g,
    BRST_REAL b,
    BRST_Pattern pattern
);

BRST_STATUS
BRST_Doc_Page_Pattern_EnsureColorSpace(
    BRST_Dict       dict,
    BRST_ColorSpace cs
);

#endif /* BRST_DOC_PAGE_PATTERN_H */
