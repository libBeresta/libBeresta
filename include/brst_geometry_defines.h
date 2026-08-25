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
    BRST_BUTT_CAP = 0,
    BRST_ROUND_CAP,
    BRST_PROJECTING_SQUARE_CAP,
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
    BRST_BORDERSTYLE_SOLID,
    /// Dashed rectangle
    BRST_BORDERSTYLE_DASHED,
    /// Embossed rectangle
    BRST_BORDERSTYLE_BEVELED,
    /// Engraved rectangle
    BRST_BORDERSTYLE_INSET,
    /// Single line under the bottom of the annotation
    BRST_BORDERSTYLE_UNDERLINED,
    BRST_BORDERSTYLE_EOF
} BRST_BSSubtype;

/*----- blend modes ----------------------------------------------------------*/

typedef enum _BRST_BlendMode {
    BRST_BLENDMODE_NORMAL = 0,
    BRST_BLENDMODE_COMPATIBLE = BRST_BLENDMODE_NORMAL,
    BRST_BLENDMODE_MULTIPLY,
    BRST_BLENDMODE_SCREEN,
    BRST_BLENDMODE_OVERLAY,
    BRST_BLENDMODE_DARKEN,
    BRST_BLENDMODE_LIGHTEN,
    BRST_BLENDMODE_COLOR_DODGE,
    BRST_BLENDMODE_COLOR_BURN,
    BRST_BLENDMODE_HARD_LIGHT,
    BRST_BLENDMODE_SOFT_LIGHT,
    BRST_BLENDMODE_DIFFERENCE,
    BRST_BLENDMODE_EXCLUSION,
    BRST_BLENDMODE_EOF
} BRST_BlendMode;

typedef enum _BRST_ColorSpace {
    BRST_COLORSPACE_DEVICEGRAY = 0,
    BRST_COLORSPACE_DEVICERGB,
    BRST_COLORSPACE_DEVICECMYK,
    BRST_COLORSPACE_CALGRAY,
    BRST_COLORSPACE_CALRGB,
    BRST_COLORSPACE_LAB,
    BRST_COLORSPACE_ICCBASED,
    BRST_COLORSPACE_SEPARATION,
    BRST_COLORSPACE_DEVICEN,
    BRST_COLORSPACE_INDEXED,
    BRST_COLORSPACE_PATTERN,
    BRST_COLORSPACE_EOF
} BRST_ColorSpace;

/*---------------------------------------------------------------------------*/
/*------ dash mode ----------------------------------------------------------*/

typedef struct _BRST_DashMode {
    BRST_REAL ptn[8];
    BRST_UINT num_ptn;
    BRST_REAL phase;
} BRST_DashMode;

static const BRST_RGBColor DEF_RGB_COLOR = {0, 0, 0};
static const BRST_CMYKColor DEF_CMYK_COLOR = {0, 0, 0, 0};
static const BRST_DashMode DEF_DASH_MODE = {{0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f}, 0, 0.0f};

#define BRST_DEF_LINEWIDTH          1
#define BRST_DEF_LINECAP            BRST_BUTT_CAP
#define BRST_DEF_LINEJOIN           BRST_MITER_JOIN
#define BRST_DEF_MITERLIMIT         10
#define BRST_DEF_FLATNESS           1

#endif /* BRST_GEOMETRY_DEFINES_H */
