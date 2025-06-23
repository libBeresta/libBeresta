#ifndef BRST_UNICODE_GLYPH_H
#define BRST_UNICODE_GLYPH_H

BRST_CSTR
BRST_UnicodeToGlyphName(
    BRST_UNICODE unicode
);

BRST_UNICODE
BRST_GlyphNameToUnicode(
    BRST_CSTR glyph_name
);

#endif /* BRST_UNICODE_GLYPH_H */