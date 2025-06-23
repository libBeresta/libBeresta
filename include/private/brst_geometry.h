#ifndef PRIVATE_BRST_GEOMETRY_H
#define PRIVATE_BRST_GEOMETRY_H
/**
  \ingroup utils
  \brief Multiply transformation matrices.

  \return Transformation matrix as a result of multiplication of matrices \c m and \c n.
*/

BRST_TransMatrix
BRST_Matrix_Multiply(
    BRST_TransMatrix m, 
    BRST_TransMatrix n
);

BRST_TransMatrix
BRST_Matrix_Translate(
    BRST_TransMatrix m, 
    BRST_REAL        dx,
    BRST_REAL        dy
);

BRST_TransMatrix
BRST_Matrix_Scale(
    BRST_TransMatrix m, 
    BRST_REAL        sx, 
    BRST_REAL        sy
);

BRST_TransMatrix
BRST_Matrix_Rotate(
    BRST_TransMatrix m, 
    BRST_REAL        angle
);

BRST_TransMatrix
BRST_Matrix_RotateDeg(
    BRST_TransMatrix m, 
    BRST_REAL        degrees
);

BRST_TransMatrix
BRST_Matrix_Skew(
    BRST_TransMatrix m, 
    BRST_REAL        a, 
    BRST_REAL        b
);

static char*
QuarterCircleA(
    char*     pbuf,
    char*     eptr,
    BRST_REAL x,
    BRST_REAL y,
    BRST_REAL ray
);

static char*
QuarterCircleB(
    char*     pbuf,
    char*     eptr,
    BRST_REAL x,
    BRST_REAL y,
    BRST_REAL ray
);

static char*
QuarterCircleC(
    char*     pbuf,
    char*     eptr,
    BRST_REAL x,
    BRST_REAL y,
    BRST_REAL ray
);

static char*
QuarterCircleD(
    char*     pbuf,
    char*     eptr,
    BRST_REAL x,
    BRST_REAL y,
    BRST_REAL ray
);

#endif /* PRIVATE_BRST_GEOMETRY_H */