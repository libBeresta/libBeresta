#include "brst_types.h"
#include "brst_mmgr.h"
#include "brst_encrypt.h"
#include "brst_encoder.h"
#include "brst_stream.h"
#include "private/brst_encoder.h"
#include "private/brst_utils.h"

#include "../src/private/data/unicode.glyph.data"

const char*
BRST_UnicodeToGlyphName(BRST_UNICODE unicode)
{
    const BRST_UnicodeGlyphPair* map = BRST_UNICODE_GLYPH_NAME_MAP;

    BRST_PTRACE((" BRST_UnicodeToGlyphName\n"));

    while (map->unicode <= unicode) {
        if (map->unicode == unicode)
            return map->glyph_name;
        map++;
    }

    return BRST_UNICODE_GLYPH_NAME_MAP[0].glyph_name;
}

BRST_UNICODE
BRST_GlyphNameToUnicode(const char* glyph_name)
{
    const BRST_UnicodeGlyphPair* map = BRST_UNICODE_GLYPH_NAME_MAP;

    BRST_PTRACE((" BRST_GlyphNameToUnicode\n"));

    while (map->unicode != 0xFFFF) {
        if (BRST_StrCmp(glyph_name, map->glyph_name) == 0)
            return map->unicode;
        map++;
    }

    return 0x0000;
}
