#include "brst_types.h"
#include "brst_encrypt.h"
#include "brst_encoder.h"
#include "brst_stream.h"
#include "brst_mmgr.h"
#include "brst_dict.h"
#include "brst_xref.h"
#include "private/brst_xref.h"
#include "brst_ext_gstate.h"
#include "brst_consts.h"
#include "brst_error.h"
#include "private/brst_utils.h"

BRST_BOOL
BRST_ExtGState_Validate(BRST_ExtGState ext_gstate)
{
    if (!ext_gstate || (ext_gstate->header.obj_class != (BRST_OSUBCLASS_EXT_GSTATE | BRST_OCLASS_DICT) && ext_gstate->header.obj_class != (BRST_OSUBCLASS_EXT_GSTATE_R | BRST_OCLASS_DICT)))
        return BRST_FALSE;

    return BRST_TRUE;
}

BRST_STATUS
ExtGState_Check(BRST_ExtGState ext_gstate)
{
    if (!BRST_ExtGState_Validate(ext_gstate))
        return BRST_INVALID_OBJECT;

    if (ext_gstate->header.obj_class == (BRST_OSUBCLASS_EXT_GSTATE_R | BRST_OCLASS_DICT))
        return BRST_Error_Raise(ext_gstate->error, BRST_EXT_GSTATE_READ_ONLY,
            0);

    return BRST_OK;
}

BRST_Dict
BRST_ExtGState_New(BRST_MMgr mmgr,
    BRST_Xref xref)
{
    BRST_Dict obj = BRST_Dict_New(mmgr);

    BRST_PTRACE((" BRST_ExtGState_New\n"));

    if (!obj)
        return NULL;

    if (BRST_Xref_Add(xref, obj) != BRST_OK)
        return NULL;

    if (BRST_Dict_AddName(obj, "Type", "ExtGState") != BRST_OK)
        return NULL;

    obj->header.obj_class |= BRST_OSUBCLASS_EXT_GSTATE;

    return obj;
}
