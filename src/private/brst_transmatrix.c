#include "brst_types.h"
#include "brst_consts.h"
#include "brst_mmgr.h"
#include "brst_transmatrix.h"
#include "private/brst_c.h"
#include "private/brst_transmatrix.h"
#include "private/brst_utils.h"

BRST_TransMatrix
BRST_TransMatrix_New(
    BRST_MMgr mmgr,
    BRST_REAL a,
    BRST_REAL b,
    BRST_REAL c,
    BRST_REAL d,
    BRST_REAL x,
    BRST_REAL y
) {
    BRST_PTRACE(" BRST_TransMatrix_New\n");

    BRST_TransMatrix matrix = BRST_GetMem(mmgr, sizeof(BRST_TransMatrix_Rec));

    if (!matrix) {
        return matrix;
    }

    BRST_MemSet(matrix, 0, sizeof(BRST_TransMatrix_Rec));
    matrix->mmgr = mmgr;

    matrix->a = a;
    matrix->b = b;
    matrix->c = c;
    matrix->d = d;
    matrix->x = x;
    matrix->y = y;

    return matrix;
}

BRST_TransMatrix
BRST_TransMatrix_Identity(
    BRST_MMgr mmgr
) {
    return BRST_TransMatrix_New(mmgr, 1, 0, 0, 1, 0, 0);
}

BRST_TransMatrix
BRST_TransMatrix_Multiply(BRST_MMgr mmgr, BRST_TransMatrix m, BRST_TransMatrix n)
{
    // Такая матрица не имеет геометрического смысла, 
    // мы ее инициализируем в процессе расчетов.
    BRST_TransMatrix r = BRST_TransMatrix_New(mmgr, 0, 0, 0, 0, 0, 0);

    /*

    | a' b' 0 |   | a" b" 0 |   | a'a" b'c" 0'x"  a'b" b'd" 0'y"  a'0" b'0" 0'1" |
    | c' d' 0 | x | c" d" 0 | = | c'a" d'c" 0'x"  c'b" d'd" 0'y"  c'0" d'0" 0'1" |
    | x' y' 1 |   | x" y" 1 |   | x'a" y'c" 1'x"  x'b" y'd" 1'y"  x'0" y'0" 1'1" |

    | m.a m.b 0 |   | n.a n.b 0 |   | m.a*n.a+m.b*n.c      m.a*n.b+m.b*n.d      0 |
    | m.c m.d 0 | x | n.c n.d 0 | = | m.c*n.a+m.d*n.c      m.c*n.b+m.d*n.d      0 |
    | m.x m.y 1 |   | n.x n.y 1 |   | m.x*n.a+m.y*n.c+n.x  m.x*n.b+m.y*n.d+*n.y 1 |

    */

    r->a = m->a * n->a + m->b * n->c;
    r->b = m->a * n->b + m->b * n->d;
    r->c = m->c * n->a + m->d * n->c;
    r->d = m->c * n->b + m->d * n->d;
    r->x = m->x * n->a + m->y * n->c + n->x;
    r->y = m->x * n->b + m->y * n->d + n->y;

    return r;
}

BRST_TransMatrix
BRST_TransMatrix_Translate(BRST_MMgr mmgr, BRST_TransMatrix m, BRST_REAL dx, BRST_REAL dy)
{
    BRST_TransMatrix translate =  BRST_TransMatrix_New(mmgr, 1, 0, 0, 1, dx, dy);
    BRST_TransMatrix res = BRST_TransMatrix_Multiply(mmgr, m, translate);
    BRST_TransMatrix_Free(translate);
    return res;
}

BRST_TransMatrix
BRST_TransMatrix_Scale(BRST_MMgr mmgr, BRST_TransMatrix m, BRST_REAL sx, BRST_REAL sy)
{
    BRST_TransMatrix scale =  BRST_TransMatrix_New(mmgr, sx, 0, 0, sy, 0, 0);
    BRST_TransMatrix res = BRST_TransMatrix_Multiply(mmgr, m, scale);
    BRST_TransMatrix_Free(scale);
    return res;
}

BRST_TransMatrix
BRST_TransMatrix_Rotate(BRST_MMgr mmgr, BRST_TransMatrix m, BRST_REAL angle)
{
    BRST_TransMatrix rotate = BRST_TransMatrix_New(mmgr, BRST_COS(angle), BRST_SIN(angle), -BRST_SIN(angle), BRST_COS(angle), 0, 0);
    BRST_TransMatrix res = BRST_TransMatrix_Multiply(mmgr, rotate, m);
    BRST_TransMatrix_Free(rotate);
    return res;
}

BRST_TransMatrix
BRST_TransMatrix_RotateDeg(BRST_MMgr mmgr, BRST_TransMatrix m, BRST_REAL degrees)
{
    BRST_REAL angle = degrees * BRST_PI / 180.0;

    BRST_TransMatrix rotate =  BRST_TransMatrix_New(mmgr, BRST_COS(angle), BRST_SIN(angle), -BRST_SIN(angle), BRST_COS(angle), 0, 0);
    BRST_TransMatrix res = BRST_TransMatrix_Multiply(mmgr, m, rotate);
    BRST_TransMatrix_Free(rotate);
    return res;
}

BRST_TransMatrix
BRST_TransMatrix_Skew(BRST_MMgr mmgr, BRST_TransMatrix m, BRST_REAL a, BRST_REAL b)
{
    BRST_TransMatrix skew =  BRST_TransMatrix_New(mmgr, 1, BRST_TAN(a), BRST_TAN(b), 1, 0, 0);
    BRST_TransMatrix res = BRST_TransMatrix_Multiply(mmgr, m, skew);
    BRST_TransMatrix_Free(skew);
    return res;
}

void BRST_TransMatrix_Free(BRST_TransMatrix matrix)
{
    BRST_PTRACE(" BRST_TransMatrix_Free\n");
    if (!matrix) {
        return;
    }
    BRST_FreeMem(matrix->mmgr, matrix);
}

