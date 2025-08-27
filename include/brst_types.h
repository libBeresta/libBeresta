#ifndef BRST_TYPES_H
#define BRST_TYPES_H

#include "brst_external.h"
#include <stdlib.h>

/*----------------------------------------------------------------------------*/
/*----- type definition ------------------------------------------------------*/

typedef void*              BRST_RAW_POINTER;

typedef const char*        BRST_CSTR;

/*  native OS integer types */
typedef signed int         BRST_INT;
typedef unsigned int       BRST_UINT;

/*  64bit integer types */
typedef signed long long   BRST_INT64;
typedef unsigned long long BRST_UINT64;

/*  32bit integer types */
typedef signed int         BRST_INT32;
typedef unsigned int       BRST_UINT32;

/*  16bit integer types */
typedef signed short       BRST_INT16;
typedef unsigned short     BRST_UINT16;

/*  8bit integer types */
typedef signed char        BRST_INT8;
typedef unsigned char      BRST_UINT8;

/*  8bit binary types */
typedef unsigned char      BRST_BYTE;

/*  float type (32bit IEEE754) */
typedef float              BRST_REAL;

/*  double type (64bit IEEE754) */
typedef double             BRST_DOUBLE;

/*  boolean type (0: False, !0: True) */
typedef signed int         BRST_BOOL;

/*  error-no type (32bit unsigned integer) */
typedef unsigned long      BRST_STATUS;

/*  character-code type (16bit) */
typedef BRST_UINT16        BRST_CID;
typedef BRST_UINT16        BRST_UNICODE;

typedef const BRST_REAL*   BRST_DASH_PATTERN;

/*  BRST_Point struct */
typedef struct _BRST_Point {
    BRST_REAL x;
    BRST_REAL y;
} BRST_Point;

typedef struct _BRST_Rect {
    BRST_REAL left;
    BRST_REAL bottom;
    BRST_REAL right;
    BRST_REAL top;
} BRST_Rect;

/*  BRST_Point3D struct */
typedef struct _BRST_Point3D {
    BRST_REAL x;
    BRST_REAL y;
    BRST_REAL z;
} BRST_Point3D;

typedef struct _BRST_Rect BRST_Box;

typedef void*
(BRST_STDCALL *BRST_Alloc_Func) (
    BRST_UINT size
);

typedef void
(BRST_STDCALL *BRST_Free_Func) (
    void* ptr
);

#endif /*  BRST_TYPES_H */