#ifndef BRST_DOC_MATRIX_H
#define BRST_DOC_MATRIX_H

#include "brst_doc.h"

BRST_EXPORT(BRST_Matrix)
BRST_Doc_Matrix_Identity(
    BRST_Doc pdf
);

BRST_EXPORT(void)
BRST_Doc_Matrix_Free(
    BRST_Matrix matrix
);

/**
  \ingroup utils
  \brief Multiply transformation matrices.

  \return Transformation matrix as a result of multiplication of matrices \c m and \c n.
*/

BRST_EXPORT(BRST_Matrix)
BRST_Doc_Matrix_Multiply(
    BRST_Doc    pdf,
    BRST_Matrix m,
    BRST_Matrix n
);

BRST_EXPORT(BRST_Matrix)
BRST_Doc_Matrix_Translate(
    BRST_Doc    pdf,
    BRST_Matrix m,
    BRST_REAL   dx,
    BRST_REAL   dy
);

BRST_EXPORT(BRST_Matrix)
BRST_Doc_Matrix_Scale(
    BRST_Doc    pdf,
    BRST_Matrix m,
    BRST_REAL   sx,
    BRST_REAL   sy
);

BRST_EXPORT(BRST_Matrix)
BRST_Doc_Matrix_Rotate(
    BRST_Doc    pdf,
    BRST_Matrix m,
    BRST_REAL   angle
);

BRST_EXPORT(BRST_Matrix)
BRST_Doc_Matrix_RotateDeg(
    BRST_Doc    pdf,
    BRST_Matrix m,
    BRST_REAL   degrees
);

BRST_EXPORT(BRST_Matrix)
BRST_Doc_Matrix_Skew(
    BRST_Doc    pdf,
    BRST_Matrix m,
    BRST_REAL   a,
    BRST_REAL   b
);

#endif /* BRST_DOC_MATRIX_H */
