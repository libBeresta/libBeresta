#ifndef PRIVATE_BRST_MATRIX_H
#define PRIVATE_BRST_MATRIX_H

#include "brst_mmgr.h"
#include "brst_matrix.h"

typedef struct _BRST_Matrix_Rec {
    BRST_MMgr mmgr;
    BRST_REAL a;
    BRST_REAL b;
    BRST_REAL c;
    BRST_REAL d;
    BRST_REAL x;
    BRST_REAL y;
} BRST_Matrix_Rec;

BRST_Matrix
BRST_Matrix_New(
    BRST_MMgr mmgr,
    BRST_REAL a,
    BRST_REAL b,
    BRST_REAL c,
    BRST_REAL d,
    BRST_REAL x,
    BRST_REAL y
);

BRST_Matrix
BRST_Matrix_Identity(
    BRST_MMgr mmgr
);

BRST_EXPORT(void)
BRST_Matrix_Free(
    BRST_Matrix matrix
);

BRST_Matrix
BRST_Matrix_Multiply(
    BRST_MMgr   mmgr,
    BRST_Matrix m, 
    BRST_Matrix n
);

BRST_Matrix
BRST_Matrix_Translate(
    BRST_MMgr   mmgr,
    BRST_Matrix m, 
    BRST_REAL   dx,
    BRST_REAL   dy
);

BRST_Matrix
BRST_Matrix_Scale(
    BRST_MMgr   mmgr,
    BRST_Matrix m, 
    BRST_REAL   sx, 
    BRST_REAL   sy
);

BRST_Matrix
BRST_Matrix_Rotate(
    BRST_MMgr   mmgr,
    BRST_Matrix m, 
    BRST_REAL   angle
);

BRST_Matrix
BRST_Matrix_RotateDeg(
    BRST_MMgr   mmgr,
    BRST_Matrix m, 
    BRST_REAL   degrees
);

BRST_Matrix
BRST_Matrix_Skew(
    BRST_MMgr   mmgr,
    BRST_Matrix m, 
    BRST_REAL   a, 
    BRST_REAL   b
);

#endif /* PRIVATE_BRST_TRANSMATRIX_H */
