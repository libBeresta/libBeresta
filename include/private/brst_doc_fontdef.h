#ifndef PRIVATE_BRST_DOC_FONTDEF_H
#define PRIVATE_BRST_DOC_FONTDEF_H

BRST_FontDef
BRST_Doc_FontDef(
    BRST_Doc    pdf,
    const char* font_name
);

BRST_STATUS
BRST_Doc_RegisterFontDef(
    BRST_Doc     pdf,
    BRST_FontDef fontdef
);

BRST_FontDef
BRST_Doc_FindFontDef(
	BRST_Doc    pdf,
	const char *font_name
);

BRST_FontDef
BRST_Doc_FindFontDef(
    BRST_Doc pdf,
    const char* font_name
);

void
CleanupFontDefList(
    BRST_Doc pdf
);

void
FreeFontDefList(
    BRST_Doc pdf
);

#endif /* PRIVATE_BRST_DOC_FONTDEF_H */