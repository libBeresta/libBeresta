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
    BRST_Matrix matrix
);

BRST_EXPORT(BRST_Stream)
BRST_Doc_Page_Pattern_Stream(BRST_Pattern pat);

#endif /* BRST_DOC_PAGE_PATTERN_H */