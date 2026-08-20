#ifndef BRST_TEXT_DEFINES_H
#define BRST_TEXT_DEFINES_H

#include "brst_types.h"

/*----------------------------------------------------------------------------*/
/*------ The text rendering mode ---------------------------------------------*/

typedef enum _BRST_TextRenderingMode {
    BRST_TEXT_RENDERING_MODE_FILL = 0,
    BRST_TEXT_RENDERING_MODE_STROKE,
    BRST_TEXT_RENDERING_MODE_FILL_THEN_STROKE,
    BRST_TEXT_RENDERING_MODE_INVISIBLE,
    BRST_TEXT_RENDERING_MODE_FILL_CLIPPING,
    BRST_TEXT_RENDERING_MODE_STROKE_CLIPPING,
    BRST_TEXT_RENDERING_MODE_FILL_STROKE_CLIPPING,
    BRST_TEXT_RENDERING_MODE_CLIPPING,
    BRST_TEXT_RENDERING_MODE_EOF
} BRST_TextRenderingMode;


typedef enum _BRST_TextAlignment {
    BRST_TEXT_ALIGN_LEFT = 0,
    BRST_TEXT_ALIGN_RIGHT,
    BRST_TEXT_ALIGN_CENTER,
    BRST_TEXT_ALIGN_JUSTIFY
} BRST_TextAlignment;

typedef enum _BRST_WritingMode {
    /// Horizontal writing mode
    BRST_WRITING_MODE_HORIZONTAL = 0,
    /// Vertical writing mode
    BRST_WRITING_MODE_VERTICAL,
    /// Last writing mode in enumeration
    BRST_WRITING_MODE_EOF
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