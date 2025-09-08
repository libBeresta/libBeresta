#include "brst_types.h"
#include "brst_consts.h"
#include "brst_mmgr.h"
#include "brst_matrix.h"
#include "private/brst_c.h"
#include "private/brst_matrix.h"
#include "private/brst_utils.h"

BRST_Matrix
BRST_Matrix_New(
    BRST_MMgr mmgr,
    BRST_REAL a,
    BRST_REAL b,
    BRST_REAL c,
    BRST_REAL d,
    BRST_REAL x,
    BRST_REAL y
) {
    BRST_PTRACE(" BRST_Matrix_New\n");

    BRST_Matrix matrix = BRST_GetMem(mmgr, sizeof(BRST_Matrix_Rec));

    if (!matrix) {
        return matrix;
    }

    BRST_MemSet(matrix, 0, sizeof(BRST_Matrix_Rec));
    matrix->mmgr = mmgr;

    matrix->a = a;
    matrix->b = b;
    matrix->c = c;
    matrix->d = d;
    matrix->x = x;
    matrix->y = y;

    return matrix;
}

BRST_Matrix
BRST_Matrix_Identity(
    BRST_MMgr mmgr
) {
    return BRST_Matrix_New(mmgr, 1, 0, 0, 1, 0, 0);
}

BRST_Matrix
BRST_Matrix_Multiply(BRST_MMgr mmgr, BRST_Matrix m, BRST_Matrix n)
{
    // Такая матрица не имеет геометрического смысла, 
    // мы ее инициализируем в процессе расчетов.
    BRST_Matrix r = BRST_Matrix_New(mmgr, 0, 0, 0, 0, 0, 0);

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

BRST_Matrix
BRST_Matrix_Translate(BRST_MMgr mmgr, BRST_Matrix m, BRST_REAL dx, BRST_REAL dy)
{
    BRST_Matrix translate =  BRST_Matrix_New(mmgr, 1, 0, 0, 1, dx, dy);
    BRST_Matrix res = BRST_Matrix_Multiply(mmgr, m, translate);
    BRST_Matrix_Free(translate);
    return res;
}

BRST_Matrix
BRST_Matrix_Scale(BRST_MMgr mmgr, BRST_Matrix m, BRST_REAL sx, BRST_REAL sy)
{
    BRST_Matrix scale =  BRST_Matrix_New(mmgr, sx, 0, 0, sy, 0, 0);
    BRST_Matrix res = BRST_Matrix_Multiply(mmgr, m, scale);
    BRST_Matrix_Free(scale);
    return res;
}

BRST_Matrix
BRST_Matrix_Rotate(BRST_MMgr mmgr, BRST_Matrix m, BRST_REAL angle)
{
    BRST_Matrix rotate = BRST_Matrix_New(mmgr, BRST_COS(angle), BRST_SIN(angle), -BRST_SIN(angle), BRST_COS(angle), 0, 0);
    BRST_Matrix res = BRST_Matrix_Multiply(mmgr, rotate, m);
    BRST_Matrix_Free(rotate);
    return res;
}

BRST_Matrix
BRST_Matrix_RotateDeg(BRST_MMgr mmgr, BRST_Matrix m, BRST_REAL degrees)
{
    BRST_REAL angle = degrees * BRST_PI / 180.0;

    BRST_Matrix rotate =  BRST_Matrix_New(mmgr, BRST_COS(angle), BRST_SIN(angle), -BRST_SIN(angle), BRST_COS(angle), 0, 0);
    BRST_Matrix res = BRST_Matrix_Multiply(mmgr, m, rotate);
    BRST_Matrix_Free(rotate);
    return res;
}

BRST_Matrix
BRST_Matrix_Skew(BRST_MMgr mmgr, BRST_Matrix m, BRST_REAL a, BRST_REAL b)
{
    BRST_Matrix skew =  BRST_Matrix_New(mmgr, 1, BRST_TAN(a), BRST_TAN(b), 1, 0, 0);
    BRST_Matrix res = BRST_Matrix_Multiply(mmgr, m, skew);
    BRST_Matrix_Free(skew);
    return res;
}

void BRST_Matrix_Free(BRST_Matrix matrix)
{
    BRST_PTRACE(" BRST_Matrix_Free\n");
    if (!matrix) {
        return;
    }
    BRST_FreeMem(matrix->mmgr, matrix);
}

