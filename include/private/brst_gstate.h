#ifndef PRIVATE_BRST_GSTATE_H
#define PRIVATE_BRST_GSTATE_H

struct _BRST_GState_Rec;
typedef struct _BRST_GState_Rec* BRST_GState;

typedef struct _BRST_GState_Rec {
    BRST_Matrix             trans_matrix;
    BRST_REAL               line_width;
    BRST_LineCap            line_cap;
    BRST_LineJoin           line_join;
    BRST_REAL               miter_limit;
    BRST_DashMode           dash_mode;
    BRST_REAL               flatness;

    BRST_REAL               char_space;
    BRST_REAL               word_space;
    BRST_REAL               h_scaling;
    BRST_REAL               text_leading;
    BRST_TextRenderingMode  rendering_mode;
    BRST_REAL               text_rise;

    BRST_ColorSpace         cs_fill;
    BRST_ColorSpace         cs_stroke;
    BRST_RGBColor           rgb_fill;
    BRST_RGBColor           rgb_stroke;
    BRST_CMYKColor          cmyk_fill;
    BRST_CMYKColor          cmyk_stroke;
    BRST_REAL               gray_fill;
    BRST_REAL               gray_stroke;

    BRST_Dict               pattern;

    BRST_Font               font;
    BRST_REAL               font_size;
    BRST_WritingMode        writing_mode;

    BRST_GState             prev;
    BRST_UINT               depth;
} BRST_GState_Rec;

BRST_GState
BRST_GState_New(
    BRST_MMgr   mmgr,
    BRST_GState current
);

BRST_GState
BRST_GState_Free(
    BRST_MMgr   mmgr,
    BRST_GState gstate
);

#endif /* PRIVATE_BRST_GSTATE_H */