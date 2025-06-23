#ifndef BRST_GEOMETRY_DEFINES_H
#define BRST_GEOMETRY_DEFINES_H

#include "brst_external.h"
#include "brst_types.h"

/*---------------------------------------------------------------------------*/
/*----- BRST_RGBColor struct ------------------------------------------------*/

typedef struct _BRST_RGBColor {
    BRST_REAL r;
    BRST_REAL g;
    BRST_REAL b;
} BRST_RGBColor;

/*---------------------------------------------------------------------------*/
/*----- BRST_CMYKColor struct -----------------------------------------------*/

typedef struct _BRST_CMYKColor {
    BRST_REAL c;
    BRST_REAL m;
    BRST_REAL y;
    BRST_REAL k;
} BRST_CMYKColor;

/*---------------------------------------------------------------------------*/
/*------ The line cap style -------------------------------------------------*/

typedef enum _BRST_LineCap {
    BRST_BUTT_END = 0,
    BRST_ROUND_END,
    BRST_PROJECTING_SQUARE_END,
    BRST_LINECAP_EOF
} BRST_LineCap;

/*----------------------------------------------------------------------------*/
/*------ The line join style -------------------------------------------------*/

typedef enum _BRST_LineJoin {
    BRST_MITER_JOIN = 0,
    BRST_ROUND_JOIN,
    BRST_BEVEL_JOIN,
    BRST_LINEJOIN_EOF
} BRST_LineJoin;

/*----------------------------------------------------------------------------*/
/*------ border stype --------------------------------------------------------*/

typedef enum _BRST_BSSubtype {
    /// Solid rectangle
    BRST_BS_SOLID,
    /// Dashed rectangle
    BRST_BS_DASHED,
    /// Embossed rectangle
    BRST_BS_BEVELED,
    /// Engraved rectangle
    BRST_BS_INSET,
    /// Single line under the bottom of the annotation
    BRST_BS_UNDERLINED
} BRST_BSSubtype;

/*----- blend modes ----------------------------------------------------------*/

typedef enum _BRST_BlendMode {
    BRST_BM_NORMAL,
    BRST_BM_MULTIPLY,
    BRST_BM_SCREEN,
    BRST_BM_OVERLAY,
    BRST_BM_DARKEN,
    BRST_BM_LIGHTEN,
    BRST_BM_COLOR_DODGE,
    BRST_BM_COLOR_BUM,
    BRST_BM_HARD_LIGHT,
    BRST_BM_SOFT_LIGHT,
    BRST_BM_DIFFERENCE,
    BRST_BM_EXCLUSHON,
    BRST_BM_EOF
} BRST_BlendMode;

typedef enum _BRST_ColorSpace {
    BRST_CS_DEVICE_GRAY = 0,
    BRST_CS_DEVICE_RGB,
    BRST_CS_DEVICE_CMYK,
    BRST_CS_CAL_GRAY,
    BRST_CS_CAL_RGB,
    BRST_CS_LAB,
    BRST_CS_ICC_BASED,
    BRST_CS_SEPARATION,
    BRST_CS_DEVICE_N,
    BRST_CS_INDEXED,
    BRST_CS_PATTERN,
    BRST_CS_EOF
} BRST_ColorSpace;

/*---------------------------------------------------------------------------*/
/*------ dash mode ----------------------------------------------------------*/

typedef struct _BRST_DashMode {
    BRST_REAL ptn[8];
    BRST_UINT num_ptn;
    BRST_REAL phase;
} BRST_DashMode;

/*---------------------------------------------------------------------------*/
/*----- BRST_TransMatrix struct ---------------------------------------------*/

typedef struct _BRST_TransMatrix {
    BRST_REAL a;
    BRST_REAL b;
    BRST_REAL c;
    BRST_REAL d;
    BRST_REAL x;
    BRST_REAL y;
} BRST_TransMatrix;

static const BRST_TransMatrix IDENTITY_MATRIX = {1, 0, 0, 1, 0, 0};
static const BRST_RGBColor DEF_RGB_COLOR = {0, 0, 0};
static const BRST_CMYKColor DEF_CMYK_COLOR = {0, 0, 0, 0};
static const BRST_DashMode DEF_DASH_MODE = {{0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f}, 0, 0.0f};

#define BRST_DEF_LINEWIDTH          1
#define BRST_DEF_LINECAP            BRST_BUTT_END
#define BRST_DEF_LINEJOIN           BRST_MITER_JOIN
#define BRST_DEF_MITERLIMIT         10
#define BRST_DEF_FLATNESS           1

#endif /* BRST_GEOMETRY_DEFINES_H */
