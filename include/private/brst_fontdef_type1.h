#ifndef PRIVATE_BRST_FONTDEF_TYPE1_H
#define PRIVATE_BRST_FONTDEF_TYPE1_H

typedef struct _BRST_Type1FontDefAttrRec {
    BRST_BYTE      first_char;                               /* Required */
    BRST_BYTE      last_char;                                /* Required */
    BRST_CharData* widths;                                   /* Required */
    BRST_UINT      widths_count;

    BRST_INT16     leading;
    char*          char_set;
    char           encoding_scheme[BRST_LIMIT_MAX_NAME_LEN + 1];
    BRST_UINT      length1;
    BRST_UINT      length2;
    BRST_UINT      length3;
    BRST_BOOL      is_base14font;
    BRST_BOOL      is_fixed_pitch;

    BRST_Stream    font_data;
} BRST_Type1FontDefAttr_Rec;
typedef struct _BRST_Type1FontDefAttrRec *BRST_Type1FontDefAttr;

BRST_FontDef
BRST_Type1FontDef_New(
    BRST_MMgr mmgr
);

BRST_FontDef
BRST_Type1FontDef_Load(
    BRST_MMgr   mmgr,
    BRST_Stream afm,
    BRST_Stream font_data
);

BRST_FontDef
BRST_Type1FontDef_Duplicate(
    BRST_MMgr    mmgr,
    BRST_FontDef src
);

BRST_STATUS
BRST_Type1FontDef_SetWidths(
    BRST_FontDef         fontdef,
    const BRST_CharData *widths
);

BRST_INT16
BRST_Type1FontDef_tWidthByName(
    BRST_FontDef fontdef,
    const char*  glyph_name
);

BRST_INT16
BRST_Type1FontDef_Width(
    BRST_FontDef fontdef,
    BRST_UNICODE unicode
);

#endif /* PRIVATE_BRST_FONTDEF_TYPE1_H */