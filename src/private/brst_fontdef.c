#include "brst_types.h"
#include "brst_encrypt.h"
#include "brst_encoder.h"
#include "brst_stream.h"
#include "brst_mmgr.h"
#include "private/brst_mmgr.h"
#include "brst_dict.h"
#include "brst_fontdef.h"
#include "brst_error.h"
#include "private/brst_defines.h"
#include "private/brst_fontdef.h"
#include "private/brst_utils.h"
#include "brst_consts.h"

void BRST_FontDef_Cleanup(BRST_FontDef fontdef)
{
    if (!fontdef)
        return;

    BRST_PTRACE(" BRST_FontDef_Cleanup\n");

    if (fontdef->clean_fn)
        fontdef->clean_fn(fontdef);

    fontdef->descriptor = NULL;
}

void BRST_FontDef_Free(BRST_FontDef fontdef)
{
    if (!fontdef)
        return;

    BRST_PTRACE(" BRST_FontDef_Free\n");

    if (fontdef->free_fn)
        fontdef->free_fn(fontdef);
    BRST_FreeMem(fontdef->mmgr, fontdef);
}

BRST_BOOL
BRST_FontDef_Validate(BRST_FontDef fontdef)
{
    BRST_PTRACE(" BRST_FontDef_Validate\n");

    if (!fontdef || fontdef->sig_bytes != BRST_FONTDEF_SIG_BYTES)
        return BRST_FALSE;
    else
        return BRST_TRUE;
}
