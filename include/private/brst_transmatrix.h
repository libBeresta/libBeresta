#ifndef PRIVATE_BRST_TRANSMATRIX_H
#define PRIVATE_BRST_TRANSMATRIX_H

typedef struct _BRST_TransMatrix_Rec {
    BRST_MMgr mmgr;
    BRST_REAL a;
    BRST_REAL b;
    BRST_REAL c;
    BRST_REAL d;
    BRST_REAL x;
    BRST_REAL y;
} BRST_TransMatrix_Rec;

#endif /* PRIVATE_BRST_TRANSMATRIX_H */