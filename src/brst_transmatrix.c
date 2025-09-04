BRST_TransMatrix
BRST_TransMatrix_New(
    BRST_Doc  pdf,
    BRST_REAL a,
    BRST_REAL b,
    BRST_REAL c,
    BRST_REAL d,
    BRST_REAL x,
    BRST_REAL y
) {
    BRST_PTRACE(" BRST_TransMatrix_New\n");

    BRST_MMgr mmgr = BRST_Doc_MMgr(pdf);
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
    BRST_Doc pdf
) {
    return BRST_TransMatrix_New(pdf, 1, 0, 0, 1, 0, 0);
}

BRST_TransMatrix
BRST_TransMatrix_Multiply(BRST_Doc pdf, BRST_TransMatrix m, BRST_TransMatrix n)
{
    // Такая матрица не имеет геометрического смысла, 
    // мы ее инициализируем в процессе расчетов.
    BRST_TransMatrix r = BRST_TransMatrix_New(pdf, 0, 0, 0, 0, 0, 0);

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
BRST_TransMatrix_Translate(BRST_Doc pdf, BRST_TransMatrix m, BRST_REAL dx, BRST_REAL dy)
{
    BRST_TransMatrix translate =  BRST_TransMatrix_New(pdf, 1, 0, 0, 1, dx, dy);
    return BRST_TransMatrix_Multiply(m, translate);
}

BRST_TransMatrix
BRST_TransMatrix_Scale(BRST_Doc pdf, BRST_TransMatrix m, BRST_REAL sx, BRST_REAL sy)
{
    BRST_TransMatrix scale =  BRST_TransMatrix_New(pdf, sx, 0, 0, sy, 0, 0);
    return BRST_TransMatrix_Multiply(m, scale);
}

BRST_TransMatrix
BRST_TransMatrix_Rotate(BRST_Doc pdf, BRST_TransMatrix m, BRST_REAL angle)
{
    BRST_TransMatrix rotate =  BRST_TransMatrix_New(pdf, cos(angle), sin(angle), -sin(angle), cos(angle), 0, 0);
    return BRST_TransMatrix_Multiply(rotate, m);
}

BRST_TransMatrix
BRST_TransMatrix_RotateDeg(BRST_Doc pdf, BRST_TransMatrix m, BRST_REAL degrees)
{
    BRST_REAL angle = degrees * BRST_PI / 180.0;

    BRST_TransMatrix rotate =  BRST_TransMatrix_New(pdf, cos(angle), sin(angle), -sin(angle), cos(angle), 0, 0);
    return BRST_TransMatrix_Multiply(m, rotate);
}

BRST_TransMatrix
BRST_TransMatrix_Skew(BRST_Doc pdf, BRST_TransMatrix m, BRST_REAL a, BRST_REAL b)
{
    BRST_TransMatrix skew =  BRST_TransMatrix_New(pdf, 1, tan(a), tan(b), 1, 0, 0);
    return BRST_TransMatrix_Multiply(m, skew);
}

void BRST_TransMatrix_Free(BRST_TransMatrix matrix)
{
    BRST_PTRACE(" BRST_TransMatrix_Free\n");
    if (!matrix) {
        return;
    }
    BRST_FreeMem(matrix->mmgr, matrix);
}

