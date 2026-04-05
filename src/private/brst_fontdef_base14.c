#include "brst_types.h"
#include "brst_encoder.h"
#include "brst_stream.h"
#include "brst_mmgr.h"
#include "private/brst_mmgr.h"
#include "brst_dict.h"
#include "private/brst_defines.h"
#include "brst_error.h"
#include "private/brst_error.h"
#include "brst_fontdef.h"
#include "private/brst_fontdef.h"
#include "private/brst_fontdef_type1.h"
#include "private/brst_utils.h"
#include "brst_consts.h"

/*----------------------------------------------------------------------------*/
/*------ base14 fonts --------------------------------------------------------*/

#define BRST_FONT_COURIER "Courier"
#define BRST_FONT_COURIER_BOLD "Courier-Bold"
#define BRST_FONT_COURIER_OBLIQUE "Courier-Oblique"
#define BRST_FONT_COURIER_BOLD_OBLIQUE "Courier-BoldOblique"
#define BRST_FONT_HELVETICA "Helvetica"
#define BRST_FONT_HELVETICA_BOLD "Helvetica-Bold"
#define BRST_FONT_HELVETICA_OBLIQUE "Helvetica-Oblique"
#define BRST_FONT_HELVETICA_BOLD_OBLIQUE "Helvetica-BoldOblique"
#define BRST_FONT_TIMES_ROMAN "Times-Roman"
#define BRST_FONT_TIMES_BOLD "Times-Bold"
#define BRST_FONT_TIMES_ITALIC "Times-Italic"
#define BRST_FONT_TIMES_BOLD_ITALIC "Times-BoldItalic"
#define BRST_FONT_SYMBOL "Symbol"
#define BRST_FONT_ZAPF_DINGBATS "ZapfDingbats"

typedef struct _BRST_Base14FontDefData {
    const char* font_name;
    const BRST_CharData* widths_table;
    BRST_BOOL is_font_specific;
    BRST_INT16 ascent;
    BRST_INT16 descent;
    BRST_UINT16 x_height;
    BRST_UINT16 cap_height;
    BRST_Box bbox;
} BRST_Base14FontDefData;

#include "../src/private/data/base14.data"

static const BRST_Base14FontDefData BRST_BUILTIN_FONTS[] = {
    { BRST_FONT_COURIER,
        CHAR_DATA_COURIER,
        BRST_FALSE,
        629,
        -157,
        426,
        562,
        { -23, -250, 715, 805 } },
    { BRST_FONT_COURIER_BOLD,
        CHAR_DATA_COURIER_BOLD,
        BRST_FALSE,
        629,
        -157,
        439,
        562,
        { -113, -250, 749, 801 } },
    { BRST_FONT_COURIER_OBLIQUE,
        CHAR_DATA_COURIER_OBLIQUE,
        BRST_FALSE,
        629,
        -157,
        426,
        562,
        { -27, -250, 849, 805 } },
    { BRST_FONT_COURIER_BOLD_OBLIQUE,
        CHAR_DATA_COURIER_BOLD_OBLIQUE,
        BRST_FALSE,
        629,
        -157,
        439,
        562,
        { -57, -250, 869, 801 } },
    { BRST_FONT_HELVETICA,
        CHAR_DATA_HELVETICA,
        BRST_FALSE,
        718,
        -207,
        523,
        718,
        { -166, -225, 1000, 931 } },
    { BRST_FONT_HELVETICA_BOLD,
        CHAR_DATA_HELVETICA_BOLD,
        BRST_FALSE,
        718,
        -207,
        532,
        718,
        { -170, -228, 1003, 962 } },
    { BRST_FONT_HELVETICA_OBLIQUE,
        CHAR_DATA_HELVETICA_OBLIQUE,
        BRST_FALSE,
        718,
        -207,
        532,
        718,
        { -170, -225, 1116, 931 } },
    { BRST_FONT_HELVETICA_BOLD_OBLIQUE,
        CHAR_DATA_HELVETICA_BOLD_OBLIQUE,
        BRST_FALSE,
        718,
        -207,
        532,
        718,
        { -174, -228, 1114, 962 } },
    { BRST_FONT_TIMES_ROMAN,
        CHAR_DATA_TIMES_ROMAN,
        BRST_FALSE,
        683,
        -217,
        450,
        662,
        { -168, -218, 1000, 898 } },
    { BRST_FONT_TIMES_BOLD,
        CHAR_DATA_TIMES_BOLD,
        BRST_FALSE,
        683,
        -217,
        461,
        676,
        { -168, -218, 1000, 935 } },
    { BRST_FONT_TIMES_ITALIC,
        CHAR_DATA_TIMES_ITALIC,
        BRST_FALSE,
        683,
        -217,
        441,
        653,
        { -169, -217, 1010, 883 } },
    { BRST_FONT_TIMES_BOLD_ITALIC,
        CHAR_DATA_TIMES_BOLD_ITALIC,
        BRST_FALSE,
        683,
        -217,
        462,
        669,
        { -200, -218, 996, 921 } },
    { BRST_FONT_SYMBOL,
        CHAR_DATA_SYMBOL,
        BRST_TRUE,
        0,
        0,
        0,
        0,
        { -180, -293, 1090, 1010 } },
    { BRST_FONT_ZAPF_DINGBATS,
        CHAR_DATA_ZAPF_DINGBATS,
        BRST_TRUE,
        0,
        0,
        0,
        0,
        { -1, -143, 981, 820 } },
    { NULL,
        NULL,
        BRST_FALSE,
        0,
        0,
        0,
        0,
        { 0, 0, 0, 0 } },
};

/*---------------------------------------------------------------------------*/

const BRST_Base14FontDefData*
BRST_Base14FontDef_FindBuiltinData(const char* font_name);

/*---------------------------------------------------------------------------*/
/*----- PDF_Base14FontDef ---------------------------------------------------*/

const BRST_Base14FontDefData*
BRST_Base14FontDef_FindBuiltinData(const char* font_name)
{
    BRST_UINT i = 0;

    while (BRST_BUILTIN_FONTS[i].font_name) {
        if (BRST_StrCmp(BRST_BUILTIN_FONTS[i].font_name, font_name) == 0)
            break;

        i++;
    }

    return &BRST_BUILTIN_FONTS[i];
}

BRST_FontDef
BRST_Base14FontDef_New(BRST_MMgr mmgr,
    const char* font_name)
{
    BRST_FontDef fontdef;
    BRST_STATUS ret;
    const BRST_Base14FontDefData* data;
    char* eptr;
    BRST_Type1FontDefAttr attr;

    fontdef = BRST_Type1FontDef_New(mmgr);
    if (!fontdef)
        return NULL;

    data = BRST_Base14FontDef_FindBuiltinData(font_name);

    if (!data->font_name) {
        BRST_Error_Set(BRST_MMgr_Error(mmgr), BRST_INVALID_FONT_NAME, 0);
        BRST_FontDef_Free(fontdef);
        return NULL;
    }

    eptr = fontdef->base_font + BRST_LIMIT_MAX_NAME_LEN;
    BRST_StrCopy(fontdef->base_font, data->font_name, eptr);

    attr                = (BRST_Type1FontDefAttr)fontdef->attr;
    attr->is_base14font = BRST_TRUE;

    if (data->is_font_specific)
        BRST_StrCopy(attr->encoding_scheme, BRST_ENCODING_FONT_SPECIFIC,
            attr->encoding_scheme + BRST_LIMIT_MAX_NAME_LEN);

    ret = BRST_Type1FontDef_SetWidths(fontdef, data->widths_table);

    if (ret != BRST_OK) {
        BRST_FontDef_Free(fontdef);
        return NULL;
    }

    fontdef->font_bbox  = data->bbox;
    fontdef->ascent     = data->ascent;
    fontdef->descent    = data->descent;
    fontdef->x_height   = data->x_height;
    fontdef->cap_height = data->cap_height;

    fontdef->valid = BRST_TRUE;

    return fontdef;
}
