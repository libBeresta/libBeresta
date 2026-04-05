#include <math.h>
#include <stdlib.h>
#include "brst_consts.h"
#include "private/brst_defines.h"
#include "private/brst_utils.h"

/*---------------------------------------------------------------------------*/

BRST_INT
BRST_AToI(const char* s)
{
    BRST_BOOL flg = BRST_FALSE;
    BRST_INT v    = 0;

    if (!s) {
        return 0;
    }

    /* increment pointer until the character of 's' is not
     * white-space-character.
     */
    while (*s) {
        if (BRST_IS_WHITE_SPACE(*s))
            s++;
        else {
            if (*s == '-') {
                flg = BRST_TRUE;
                s++;
            }
            break;
        }
    }

    while (*s >= '0' && *s <= '9') {
        v *= 10;
        v += *s - '0';
        s++;
    }

    if (flg)
        v *= -1;

    return v;
}

BRST_DOUBLE
BRST_AToF(const char* s)
{
    BRST_BOOL flg = BRST_FALSE;
    BRST_INT i    = 0;
    BRST_DOUBLE v;
    BRST_INT tmp = 1;

    /* increment pointer until the character of 's' is not
     * white-space-character.
     */
    while (*s) {
        if (BRST_IS_WHITE_SPACE(*s))
            s++;
        else {
            if (*s == '-') {
                flg = BRST_TRUE;
                s++;
            }
            break;
        }
    }

    while (*s >= '0' && *s <= '9') {
        if (i > 3276)
            break;

        i *= 10;
        i += *s - '0';
        s++;
    }

    if (*s == '.') {
        s++;
        while (*s >= '0' && *s <= '9') {
            if (i > 214748364)
                break;

            i *= 10;
            i += *s - '0';
            s++;
            tmp *= 10;
        }
    }

    v = (BRST_DOUBLE)i / tmp;

    if (flg)
        v *= -1;

    return v;
}

char* BRST_IToA(char* s,
    BRST_INT32 val,
    char* eptr)
{
    char* t;
    char buf[BRST_INT_LEN + 1];

    if (val < 0) {
        if (val < BRST_LIMIT_MIN_INT)
            val = BRST_LIMIT_MIN_INT;
        *s++ = '-';
        val  = -val;
    } else if (val > BRST_LIMIT_MAX_INT) {
        val = BRST_LIMIT_MAX_INT;
    } else if (val == 0) {
        *s++ = '0';
    }

    t    = buf + BRST_INT_LEN;
    *t-- = 0;

    while (val > 0) {
        *t = (char)((char)(val % 10) + '0');
        val /= 10;
        t--;
    }

    t++;
    while (s < eptr && *t != 0)
        *s++ = *t++;
    *s = 0;

    return s;
}

char* BRST_IToA2(char* s,
    BRST_UINT32 val,
    BRST_UINT len)
{
    char* t;
    char* u;

    if (val > BRST_LIMIT_MAX_INT)
        val = BRST_LIMIT_MAX_INT;

    u  = s + len - 1;
    *u = 0;
    t  = u - 1;
    while (val > 0 && t >= s) {
        *t = (char)((char)(val % 10) + '0');
        val /= 10;
        t--;
    }

    while (s <= t)
        *t-- = '0';

    return s + len - 1;
}

char* BRST_FToA(char* s,
    BRST_REAL val,
    char* eptr)
{
    BRST_REAL int_val;
    BRST_REAL fpart_val;
    BRST_REAL dig;
    char buf[BRST_REAL_LEN + 1];
    char* sptr = s;
    char* t;
    BRST_INT32 logVal;
    BRST_UINT32 prec;

    if (val > BRST_LIMIT_MAX_REAL)
        val = BRST_LIMIT_MAX_REAL;
    else if (val < BRST_LIMIT_MIN_REAL)
        val = BRST_LIMIT_MIN_REAL;

    t    = buf;
    *t++ = 0;

    if (val < 0) {
        *s++ = '-';
        val  = -val;
    }

    /* compute the decimal precision to write at least 5 significant figures */
    logVal = (BRST_INT32)(val > 1e-20 ? log10(val) : 0.);
    if (logVal >= 0) {
        prec = 5;
    } else {
        prec = -logVal + 5;
    }

    /* separate an integer part and a fractional part. */
    fpart_val = modff(val, &int_val);

    /* process integer part */
    do {
        dig  = modff(int_val / 10.0f, &int_val);
        *t++ = (char)(dig * 10.0 + 0.5) + '0';
    } while (int_val > 0);

    /* copy to destination buffer */
    t--;
    while (s <= eptr && *t != 0)
        *s++ = *t--;

    /* process fractional part */
    *s++ = '.';
    if (fpart_val != 0.0) {
        BRST_UINT32 i;
        for (i = 0; i < prec; i++) {
            fpart_val = modff(fpart_val * 10.0f, &int_val);
            *s++      = (char)(int_val + 0.5) + '0';
        }
    }

    /* delete an excessive decimal portion. */
    s--;
    while (s > sptr) {
        if (*s == '0')
            *s = 0;
        else {
            if (*s == '.')
                *s = 0;
            break;
        }
        s--;
    }

    return (*s == 0) ? s : ++s;
}

BRST_BYTE*
BRST_MemCopy(BRST_BYTE* out,
    const BRST_BYTE* in,
    BRST_UINT n)
{
    while (n > 0) {
        *out++ = *in++;
        n--;
    }

    return out;
}

BRST_BYTE*
BRST_StrCopy(char* out,
    const char* in,
    char* eptr)
{
    if (in != NULL) {
        while (eptr > out && *in != 0)
            *out++ = *in++;
    }

    *out = 0;

    return (BRST_BYTE*)out;
}

BRST_INT
BRST_MemCmp(const BRST_BYTE* s1,
    const BRST_BYTE* s2,
    BRST_UINT n)
{
    if (n == 0)
        return 0;

    while (*s1 == *s2) {
        n--;
        if (n == 0)
            return 0;
        s1++;
        s2++;
    }

    return *s1 - *s2;
}

BRST_INT
BRST_StrCmp(const char* s1,
    const char* s2)
{
    if (!s1 || !s2) {
        if (!s1 && s2)
            return -1;
        else
            return 1;
    }

    while (*s1 == *s2) {
        s1++;
        s2++;
        if (*s1 == 0 || *s2 == 0)
            break;
    }

    return (BRST_BYTE)*s1 - (BRST_BYTE)*s2;
}

void* BRST_MemSet(void* s,
    BRST_BYTE c,
    BRST_UINT n)
{
    BRST_BYTE* b = (BRST_BYTE*)s;

    while (n > 0) {
        *b = c;
        b++;
        n--;
    }

    return b;
}

BRST_UINT
BRST_StrLen(const char* s,
    BRST_INT maxlen)
{
    BRST_INT len = 0;

    if (!s)
        return 0;

    while (*s != 0 && (maxlen < 0 || len < maxlen)) {
        s++;
        len++;
    }

    return (BRST_UINT)len;
}

const char*
BRST_StrStr(const char* s1,
    const char* s2,
    BRST_UINT maxlen)
{
    BRST_UINT len = BRST_StrLen(s2, -1);

    if (!s1)
        return NULL;

    if (len == 0)
        return s1;

    if (maxlen == 0)
        maxlen = BRST_StrLen(s1, -1);

    if (maxlen < len)
        return NULL;

    maxlen -= len;
    maxlen++;

    while (maxlen > 0) {
        if (BRST_MemCmp((BRST_BYTE*)s1, (BRST_BYTE*)s2, len) == 0)
            return s1;

        s1++;
        maxlen--;
    }

    return NULL;
}

BRST_Box
BRST_ToBox(BRST_INT16 left,
    BRST_INT16 bottom,
    BRST_INT16 right,
    BRST_INT16 top)
{
    BRST_Box box;

    box.left   = left;
    box.bottom = bottom;
    box.right  = right;
    box.top    = top;

    return box;
}

BRST_Point
BRST_ToPoint(BRST_INT16 x,
    BRST_INT16 y)
{
    BRST_Point point;

    point.x = x;
    point.y = y;

    return point;
}

BRST_Rect
BRST_ToRect(BRST_REAL left,
    BRST_REAL bottom,
    BRST_REAL right,
    BRST_REAL top)
{
    BRST_Rect rect;

    rect.left   = left;
    rect.bottom = bottom;
    rect.right  = right;
    rect.top    = top;

    return rect;
}

void BRST_UInt16Swap(BRST_UINT16* value)
{
    BRST_BYTE u[2];

    BRST_MemCopy(u, (BRST_BYTE*)value, 2);
    *value = (BRST_UINT16)((BRST_UINT16)u[0] << 8 | (BRST_UINT16)u[1]);
}

const char*
BRST_PageSizeName(BRST_PageSizes size)
{
    return BRST_PREDEFINED_PAGE_SIZE_NAMES[size];
}
