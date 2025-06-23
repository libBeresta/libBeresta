#ifndef PRIVATE_BRST_FONTDEF_CID_H
#define PRIVATE_BRST_FONTDEF_CID_H

typedef struct _BRST_CIDFontDefAttrRec {
    BRST_List  widths;
    BRST_INT16 DW;
    BRST_INT16 DW2[2];
} BRST_CIDFontDefAttr_Rec;
typedef struct _BRST_CIDFontDefAttrRec   *BRST_CIDFontDefAttr;

typedef BRST_STATUS (*BRST_FontDef_InitFunc) (BRST_FontDef fontdef);

typedef struct _BRST_CID_Width {
    BRST_UINT16 cid;
    BRST_INT16  width;
} BRST_CID_Width;
typedef struct _BRST_CID_Width BRST_CID_Width;

BRST_FontDef
BRST_CIDFontDef_New(
    BRST_MMgr             mmgr,
    char*                 name,
    BRST_FontDef_InitFunc init_fn
);

BRST_STATUS
BRST_CIDFontDef_AddWidth(
    BRST_FontDef          fontdef,
    const BRST_CID_Width* widths
);

BRST_INT16
BRST_CIDFontDef_CIDWidth(
    BRST_FontDef fontdef,
    BRST_UINT16  cid
);

BRST_STATUS
BRST_CIDFontDef_ChangeStyle(
    BRST_FontDef fontdef,
    BRST_BOOL    bold,
    BRST_BOOL    italic
);

#endif /* PRIVATE_BRST_FONTDEF_CID_H */