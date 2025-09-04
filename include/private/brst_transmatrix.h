#ifndef PRIVATE_BRST_TRANSMATRIX_H
#define PRIVATE_BRST_TRANSMATRIX_H

#include "brst_mmgr.h"
#include "brst_transmatrix.h"

typedef struct _BRST_TransMatrix_Rec {
    BRST_MMgr mmgr;
    BRST_REAL a;
    BRST_REAL b;
    BRST_REAL c;
    BRST_REAL d;
    BRST_REAL x;
    BRST_REAL y;
} BRST_TransMatrix_Rec;

BRST_TransMatrix
BRST_TransMatrix_New(
    BRST_MMgr mmgr,
    BRST_REAL a,
    BRST_REAL b,
    BRST_REAL c,
    BRST_REAL d,
    BRST_REAL x,
    BRST_REAL y
);

BRST_TransMatrix
BRST_TransMatrix_Identity(
    BRST_MMgr mmgr
);

BRST_EXPORT(void)
BRST_TransMatrix_Free(
    BRST_TransMatrix matrix
);

BRST_TransMatrix
BRST_TransMatrix_Multiply(
    BRST_MMgr        mmgr,
    BRST_TransMatrix m, 
    BRST_TransMatrix n
);

BRST_TransMatrix
BRST_TransMatrix_Translate(
    BRST_MMgr        mmgr,
    BRST_TransMatrix m, 
    BRST_REAL        dx,
    BRST_REAL        dy
);

BRST_TransMatrix
BRST_TransMatrix_Scale(
    BRST_MMgr        mmgr,
    BRST_TransMatrix m, 
    BRST_REAL        sx, 
    BRST_REAL        sy
);

BRST_TransMatrix
BRST_TransMatrix_Rotate(
    BRST_MMgr        mmgr,
    BRST_TransMatrix m, 
    BRST_REAL        angle
);

BRST_TransMatrix
BRST_TransMatrix_RotateDeg(
    BRST_MMgr        mmgr,
    BRST_TransMatrix m, 
    BRST_REAL        degrees
);

BRST_TransMatrix
BRST_TransMatrix_Skew(
    BRST_MMgr        mmgr,
    BRST_TransMatrix m, 
    BRST_REAL        a, 
    BRST_REAL        b
);

#endif /* PRIVATE_BRST_TRANSMATRIX_H */
