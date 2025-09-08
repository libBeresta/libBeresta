#ifndef PRIVATE_BRST_TEXT_H
#define PRIVATE_BRST_TEXT_H

BRST_STATUS
InternalWriteText  (BRST_PageAttr    attr,
                    const char      *text);

BRST_STATUS
InternalShowTextNextLine  (BRST_Page    page,
                           const char  *text,
                           BRST_UINT    len);

/*
 * Convert a user space text position from absolute to relative coordinates.
 * Absolute values are passed in xAbs and yAbs, relative values are returned
 * to xRel and yRel. The latter two must not be NULL.
 */
void
TextPos_AbsToRel (
    BRST_Matrix text_matrix,
    BRST_REAL xAbs,
    BRST_REAL yAbs,
    BRST_REAL *xRel,
    BRST_REAL *yRel
);

#endif /* PRIVATE_BRST_TEXT_H */