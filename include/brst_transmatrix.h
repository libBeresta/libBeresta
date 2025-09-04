#ifndef BRST_TRANSMATRIX_H
#define BRST_TRANSMATRIX_H

struct _BRST_TransMatrix_Rec;
typedef struct _BRST_TransMatrix_Rec* BRST_TransMatrix;

BRST_EXPORT(BRST_TransMatrix)
BRST_TransMatrix_Identity(
    BRST_Doc pdf
);

BRST_EXPORT(BRST_TransMatrix)
BRST_TransMatrix_New(
    BRST_Doc  pdf,
    BRST_REAL a,
    BRST_REAL b,
    BRST_REAL c,
    BRST_REAL d,
    BRST_REAL x,
    BRST_REAL y
);

BRST_EXPORT(void)
BRST_TransMatrix_Free(
    BRST_TransMatrix matrix
);

/**
  \ingroup utils
  \brief Multiply transformation matrices.

  \return Transformation matrix as a result of multiplication of matrices \c m and \c n.
*/

BRST_EXPORT(BRST_TransMatrix)
BRST_TransMatrix_Multiply(
    BRST_Doc         pdf,
    BRST_TransMatrix m, 
    BRST_TransMatrix n
);

BRST_EXPORT(BRST_TransMatrix)
BRST_TransMatrix_Translate(
    BRST_Doc         pdf,
    BRST_TransMatrix m, 
    BRST_REAL        dx,
    BRST_REAL        dy
);

BRST_EXPORT(BRST_TransMatrix)
BRST_TransMatrix_Scale(
    BRST_Doc         pdf,
    BRST_TransMatrix m, 
    BRST_REAL        sx, 
    BRST_REAL        sy
);

BRST_EXPORT(BRST_TransMatrix)
BRST_TransMatrix_Rotate(
    BRST_Doc         pdf,
    BRST_TransMatrix m, 
    BRST_REAL        angle
);

BRST_EXPORT(BRST_TransMatrix)
BRST_TransMatrix_RotateDeg(
    BRST_Doc         pdf,
    BRST_TransMatrix m, 
    BRST_REAL        degrees
);

BRST_EXPORT(BRST_TransMatrix)
BRST_TransMatrix_Skew(
    BRST_Doc         pdf,
    BRST_TransMatrix m, 
    BRST_REAL        a, 
    BRST_REAL        b
);

#endif /* BRST_TRANSMATRIX_H */