#include "brst_types.h"
#include "brst_mmgr.h"
#include "brst_doc.h"
#include "brst_base.h"
#include "brst_transmatrix.h"
#include "private/brst_transmatrix.h"

BRST_TransMatrix
BRST_Doc_TransMatrix_Identity(BRST_Doc pdf) {
    return BRST_TransMatrix_Identity(BRST_Doc_MMgr(pdf));
}

BRST_TransMatrix
BRST_Doc_TransMatrix_Multiply(BRST_Doc pdf, BRST_TransMatrix m, BRST_TransMatrix n)
{
    return BRST_TransMatrix_Multiply(BRST_Doc_MMgr(pdf), m, n);
}

BRST_TransMatrix
BRST_Doc_TransMatrix_Translate(BRST_Doc pdf, BRST_TransMatrix m, BRST_REAL dx, BRST_REAL dy) {
    return BRST_TransMatrix_Translate(BRST_Doc_MMgr(pdf), m, dx, dy);
}

BRST_TransMatrix
BRST_Doc_TransMatrix_Scale(BRST_Doc pdf, BRST_TransMatrix m, BRST_REAL sx, BRST_REAL sy) {
    return BRST_TransMatrix_Scale(BRST_Doc_MMgr(pdf), m, sx, sy);
}

BRST_TransMatrix
BRST_Doc_TransMatrix_Rotate(BRST_Doc pdf, BRST_TransMatrix m, BRST_REAL angle) {
    return BRST_TransMatrix_Rotate(BRST_Doc_MMgr(pdf), m, angle);
}

BRST_TransMatrix
BRST_Doc_TransMatrix_RotateDeg(BRST_Doc pdf, BRST_TransMatrix m, BRST_REAL degrees) {
    return BRST_TransMatrix_RotateDeg(BRST_Doc_MMgr(pdf), m, degrees);
}

BRST_TransMatrix
BRST_Doc_TransMatrix_Skew(BRST_Doc pdf, BRST_TransMatrix m, BRST_REAL a, BRST_REAL b) {
    return BRST_TransMatrix_Skew(BRST_Doc_MMgr(pdf), m, a, b);
}

void BRST_Doc_TransMatrix_Free(BRST_TransMatrix matrix) {
    BRST_TransMatrix_Free(matrix);
}

