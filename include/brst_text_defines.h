#ifndef BRST_TEXT_DEFINES_H
#define BRST_TEXT_DEFINES_H

#include "brst_types.h"

/*----------------------------------------------------------------------------*/
/*------ The text rendering mode ---------------------------------------------*/

typedef enum _BRST_TextRenderingMode {
    BRST_FILL = 0,
    BRST_STROKE,
    BRST_FILL_THEN_STROKE,
    BRST_INVISIBLE,
    BRST_FILL_CLIPPING,
    BRST_STROKE_CLIPPING,
    BRST_FILL_STROKE_CLIPPING,
    BRST_CLIPPING,
    BRST_RENDERING_MODE_EOF
} BRST_TextRenderingMode;


typedef enum _BRST_TextAlignment {
    BRST_TALIGN_LEFT = 0,
    BRST_TALIGN_RIGHT,
    BRST_TALIGN_CENTER,
    BRST_TALIGN_JUSTIFY
} BRST_TextAlignment;

typedef enum _BRST_WritingMode {
    /// Horizontal writing mode
    BRST_WMODE_HORIZONTAL = 0,
    /// Vertical writing mode
    BRST_WMODE_VERTICAL,
    /// Last writing mode in enumeration
    BRST_WMODE_EOF
} BRST_WritingMode;

/*---------------------------------------------------------------------------*/
/*------ text width struct --------------------------------------------------*/

typedef struct _BRST_TextWidth {
    BRST_UINT numchars;

    /* don't use this value (it may be change in the feature).
       use numspace as alternated. */
    BRST_UINT numwords;

    BRST_UINT width;
    BRST_UINT numspace;
} BRST_TextWidth;

#endif /* BRST_TEXT_DEFINES_H */