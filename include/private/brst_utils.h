#ifndef PRIVATE_BRST_UTILS_H
#define PRIVATE_BRST_UTILS_H

#include "brst_config.h"
#include "brst_types.h"
#include "brst_page_sizes.h"

BRST_INT
BRST_AToI(
    const char* s
);


BRST_DOUBLE
BRST_AToF(
    const char* s
);


char*
BRST_IToA(
    char*      s,
    BRST_INT32 val,
    char*      eptr
);

char*
BRST_IToA2(
    char*       s,
    BRST_UINT32 val,
    BRST_UINT   len
);

char*
BRST_FToA(
    char*     s,
    BRST_REAL val,
    char*     eptr
);

BRST_BYTE*
BRST_MemCpy(
    BRST_BYTE*       out,
    const BRST_BYTE* in,
    BRST_UINT        n
);

BRST_BYTE*
BRST_StrCpy(
    char*       out,
    const char* in,
    char*       eptr
);

BRST_INT
BRST_MemCmp(
    const BRST_BYTE* s1,
    const BRST_BYTE* s2,
    BRST_UINT        n
);

BRST_INT
BRST_StrCmp(
    const char* s1,
    const char* s2
);

const char*
BRST_StrStr(
    const char* s1,
    const char* s2,
    BRST_UINT   maxlen
);

void*
BRST_MemSet(
    void*     s,
    BRST_BYTE c,
    BRST_UINT n
);

BRST_UINT
BRST_StrLen(
    const char* s,
    BRST_INT    maxlen
);

BRST_Box
BRST_ToBox(
    BRST_INT16 left,
    BRST_INT16 bottom,
    BRST_INT16 right,
    BRST_INT16 top
);

BRST_Point
BRST_ToPoint(
    BRST_INT16 x,
    BRST_INT16 y
);

BRST_Rect
BRST_ToRect(
    BRST_REAL left,
    BRST_REAL bottom,
    BRST_REAL right,
    BRST_REAL top
);

void
BRST_UInt16Swap(
    BRST_UINT16* value
);

/**
  \ingroup utils
  \brief Return name of predefined page size
*/
const char*
BRST_PageSizeName(
    BRST_PageSizes size
);

#define BRST_NEEDS_ESCAPE(c)    (c < 0x20  || \
                                 c > 0x7e  || \
                                 c == '\\' || \
                                 c == '%'  || \
                                 c == '#'  || \
                                 c == '/'  || \
                                 c == '('  || \
                                 c == ')'  || \
                                 c == '<'  || \
                                 c == '>'  || \
                                 c == '['  || \
                                 c == ']'  || \
                                 c == '{'  || \
                                 c == '}'  )  \

#define BRST_IS_WHITE_SPACE(c)   (c == 0x00 || \
                                  c == 0x09 || \
                                  c == 0x0A || \
                                  c == 0x0C || \
                                  c == 0x0D || \
                                  c == 0x20 )  \

/*----------------------------------------------------------------------------*/
/*----- macros for debug -----------------------------------------------------*/

#ifdef LIBBRST_DEBUG_TRACE
#ifndef BRST_PTRACE_ON
#define BRST_PTRACE_ON
#endif /* BRST_PTRACE_ON */
#endif /* LIBBRST_DEBUG_TRACE */

#ifdef BRST_PTRACE_ON
#define BRST_PTRACE(ARGS)  BRST_PRINTF ARGS
#else
#define BRST_PTRACE(ARGS)  /* do nothing */
#endif /* BRST_PTRACE */

#ifdef LIBBRST_DEBUG
#define BRST_PRINT_BINARY(BUF, LEN, CAPTION) BRST_PrintBinary(BUF, LEN, CAPTION)
#else
#define BRST_PRINT_BINARY(BUF, LEN, CAPTION) /* do nothing */
#endif

#endif /* PRIVATE_BRST_UTILS_H */

