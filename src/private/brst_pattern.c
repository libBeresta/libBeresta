#include "brst_stream.h"
#include "brst_xref.h"
#include "brst_mmgr.h"
#include "brst_dict.h"
#include "brst_array.h"
#include "brst_encrypt.h"
#include "private/brst_array.h"
#include "private/brst_dict.h"
#include "private/brst_name.h"
#include "brst_xobject.h"
#include "brst_types.h"
#include "private/brst_utils.h"
#include "private/brst_geometry.h"
#include "brst_consts.h"

BRST_Pattern
BRST_Pattern_Tiling_New(
    BRST_MMgr mmgr,
    BRST_Xref xref,
    BRST_REAL width,
    BRST_REAL height,
    BRST_REAL scalex,
    BRST_REAL scaley
) {
    BRST_Dict xobj;
    BRST_STATUS ret = BRST_OK;

    xobj = BRST_Dict_New_Stream_Init(mmgr, xref);
    if (!xobj)
        return NULL;

    xobj->header.obj_class |= BRST_OSUBCLASS_XOBJECT;
    ret += BRST_Dict_AddName(xobj, "Type", "XObject");
    ret += BRST_Dict_AddName(xobj, "Subtype", "Form");
    ret += BRST_Dict_Add(xobj, "BBox", BRST_Box_Array_New(mmgr, BRST_ToRect(0, 0, width, height)));

    BRST_TransMatrix sm = BRST_Matrix_Scale(IDENTITY_MATRIX, scalex, scaley);
    ret += BRST_Dict_Add(xobj, "Matrix", BRST_Matrix_Array_New(mmgr, sm));

    /* В стандарте написано, что элемент Resources не является обязательным,
       но очень рекомендуется его иметь и настроить.
     */

    BRST_Dict resource = BRST_Dict_New(mmgr);
    if (!resource)
        return NULL;

    ret += BRST_Dict_Add(xobj, "Resources", resource);

    BRST_Array procset = BRST_Array_New(mmgr);
    if (!procset)
        return NULL;

    ret += BRST_Dict_Add(resource, "ProcSet", procset);
    ret += BRST_Array_Add(procset, BRST_Name_New(mmgr, "PDF"));

    if (ret != BRST_OK)
        return NULL;

    return xobj;
}

BRST_Stream
BRST_XObject_Stream(
    BRST_XObject obj
) {
    return BRST_Dict_Stream(obj);
}
