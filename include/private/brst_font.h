#ifndef BRST_FONT_INTERNAL_H
#define BRST_FONT_INTERNAL_H

typedef struct _BRST_FontDef_Rec  *BRST_FontDef;

typedef void (*BRST_FontDef_FreeFunc) (BRST_FontDef fontdef);
typedef void (*BRST_FontDef_CleanFunc) (BRST_FontDef fontdef);
typedef BRST_STATUS (*BRST_FontDef_InitFunc) (BRST_FontDef fontdef);


typedef enum _BRST_FontType {
    BRST_FONT_TYPE1 = 0,
    BRST_FONT_TRUETYPE,
    BRST_FONT_TYPE3,
    BRST_FONT_TYPE0_CID,
    BRST_FONT_TYPE0_TT,
    BRST_FONT_CID_TYPE0,
    BRST_FONT_CID_TYPE2,
    BRST_FONT_MMTYPE1
} BRST_FontType;

typedef BRST_TextWidth
(*BRST_Font_TextWidths_Func) (
    BRST_Font        font,
    const BRST_BYTE* text,
    BRST_UINT        len
);

typedef BRST_UINT
(*BRST_Font_MeasureText_Func) (
    BRST_Font        font,
    const BRST_BYTE* text,
    BRST_UINT        len,
    BRST_REAL        width,
    BRST_REAL        fontsize,
    BRST_REAL        charspace,
    BRST_REAL        wordspace,
    BRST_BOOL        wordwrap,
    BRST_REAL*       real_width);

typedef struct _BRST_FontAttr_Rec {
    BRST_FontType               type;
    BRST_WritingMode            writing_mode;
    BRST_Font_TextWidths_Func   text_width_fn;
    BRST_Font_MeasureText_Func  measure_text_fn;
    BRST_FontDef                fontdef;
    BRST_Encoder                encoder;

    /* if the encoding-type is BRST_ENCODER_TYPE_SINGLE_BYTE, the width of
     * each characters are cashed in 'widths'.
     * when BRST_ENCODER_TYPE_DOUBLE_BYTE the width is calculate each time.
     */
    BRST_INT16*                 widths;
    BRST_BYTE*                  used;

    BRST_Xref                   xref;
    BRST_Font                   descendant_font;
    BRST_Dict                   map_stream;
    BRST_Dict                   cmap_stream;
} BRST_FontAttr_Rec;

typedef BRST_Dict BRST_Font;

struct _BRST_FontAttr_Rec;
typedef struct _BRST_FontAttr_Rec* BRST_FontAttr;

BRST_Font
BRST_Type1Font_New(
    BRST_MMgr    mmgr,
    BRST_FontDef fontdef,
    BRST_Encoder encoder,
    BRST_Xref    xref
);

BRST_Font
BRST_TTFont_New(
    BRST_MMgr    mmgr,
    BRST_FontDef fontdef,
    BRST_Encoder encoder,
    BRST_Xref    xref
);

BRST_Font
BRST_Type0Font_New(
    BRST_MMgr    mmgr,
    BRST_FontDef fontdef,
    BRST_Encoder encoder,
    BRST_Xref    xref
);

BRST_BOOL
BRST_Font_Validate(
    BRST_Font font
);

#endif /* BRST_FONT_INTERNAL_H */
