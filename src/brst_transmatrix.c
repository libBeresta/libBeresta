#include "brst_types.h"
#include "brst_mmgr.h"
#include "brst_doc.h"
#include "brst_base.h"
#include "brst_matrix.h"
#include "private/brst_matrix.h"

BRST_Matrix
BRST_Doc_Matrix_Identity(BRST_Doc pdf) {
    return BRST_Matrix_Identity(BRST_Doc_MMgr(pdf));
}

BRST_Matrix
BRST_Doc_Matrix_Multiply(BRST_Doc pdf, BRST_Matrix m, BRST_Matrix n)
{
    return BRST_Matrix_Multiply(BRST_Doc_MMgr(pdf), m, n);
}

BRST_Matrix
BRST_Doc_Matrix_Translate(BRST_Doc pdf, BRST_Matrix m, BRST_REAL dx, BRST_REAL dy) {
    return BRST_Matrix_Translate(BRST_Doc_MMgr(pdf), m, dx, dy);
}

BRST_Matrix
BRST_Doc_Matrix_Scale(BRST_Doc pdf, BRST_Matrix m, BRST_REAL sx, BRST_REAL sy) {
    return BRST_Matrix_Scale(BRST_Doc_MMgr(pdf), m, sx, sy);
}

BRST_Matrix
BRST_Doc_Matrix_Rotate(BRST_Doc pdf, BRST_Matrix m, BRST_REAL angle) {
    return BRST_Matrix_Rotate(BRST_Doc_MMgr(pdf), m, angle);
}

BRST_Matrix
BRST_Doc_Matrix_RotateDeg(BRST_Doc pdf, BRST_Matrix m, BRST_REAL degrees) {
    return BRST_Matrix_RotateDeg(BRST_Doc_MMgr(pdf), m, degrees);
}

BRST_Matrix
BRST_Doc_Matrix_Skew(BRST_Doc pdf, BRST_Matrix m, BRST_REAL a, BRST_REAL b) {
    return BRST_Matrix_Skew(BRST_Doc_MMgr(pdf), m, a, b);
}

void BRST_Doc_Matrix_Free(BRST_Matrix matrix) {
    BRST_Matrix_Free(matrix);
}

