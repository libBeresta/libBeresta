#include "brst_types.h"
#include "brst_encrypt.h"
#include "brst_encoder.h"
#include "brst_stream.h"
#include "brst_mmgr.h"
#include "brst_xref.h"
#include "brst_dict.h"
#include "private/brst_dict.h"
#include "brst_font.h"
#include "private/brst_utils.h"
#include "brst_consts.h"

BRST_BOOL
BRST_Font_Validate(BRST_Font font)
{
    BRST_PTRACE((" BRST_Font_Validate\n"));

    if (!font || !font->attr || font->header.obj_class != (BRST_OSUBCLASS_FONT | BRST_OCLASS_DICT))
        return BRST_FALSE;

    return BRST_TRUE;
}
