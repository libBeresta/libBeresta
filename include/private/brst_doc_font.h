#ifndef PRIVATE_BRST_DOC_FONT_H
#define PRIVATE_BRST_DOC_FONT_H

const char*
LoadTTFontFromStream(
    BRST_Doc pdf,
    BRST_Stream font_data,
    BRST_BOOL embedding,
    const char* file_name
);

const char*
LoadTTFontFromStream2(
    BRST_Doc pdf,
    BRST_Stream font_data,
    BRST_UINT index,
    BRST_BOOL embedding,
    const char* file_name
);

const char*
LoadType1FontFromStream(
    BRST_Doc pdf,
    BRST_Stream afmdata,
    BRST_Stream pfmdata
);

BRST_Font
BRST_Doc_FindFont(
	BRST_Doc    pdf,
	const char *font_name,
	const char *encoding_name
);

#endif /* PRIVATE_BRST_DOC_FONT_H */