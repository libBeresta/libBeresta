#include "brst_external.h"
#include "brst_types.h"
#include "brst_mmgr.h"
#include "brst_encrypt.h"
#include "brst_stream.h"
#include "brst_xref.h"
#include "brst_encoder.h"
#include "brst_error.h"
#include "brst_consts.h"
#include "brst_ext_gstate.h"
#include "brst_font.h"
#include "brst_shading.h"
#include "brst_page.h"
#include "brst_destination.h"
#include "private/brst_catalog.h"
#include "private/brst_encrypt_dict.h"
#include "private/brst_page.h"
#include "brst_xobject.h"
#include "private/brst_xobject.h"
#include "brst_base.h"
#include "private/brst_gstate.h"
#include "private/brst_page_attr.h"

/* Do */
BRST_EXPORT(BRST_STATUS)
BRST_Page_XObject_Execute(BRST_Page page,
    BRST_XObject obj)
{
    BRST_STATUS ret = BRST_Page_CheckState(page, BRST_GMODE_PAGE_DESCRIPTION);
    BRST_PageAttr attr;
    const char* local_name;

    BRST_PTRACE(" BRST_Page_XObject_Execute\n");

    if (ret != BRST_OK)
        return ret;

    if (!obj || obj->header.obj_class != (BRST_OSUBCLASS_XOBJECT | BRST_OCLASS_DICT))
        return BRST_Error_Raise(page->error, BRST_INVALID_OBJECT, 0);

    if (page->mmgr != obj->mmgr)
        return BRST_Error_Raise(page->error, BRST_PAGE_INVALID_XOBJECT, 0);

    attr       = (BRST_PageAttr)page->attr;
    local_name = BRST_Page_XObjectName(page, obj);

    if (!local_name)
        return BRST_Error_Raise(page->error, BRST_PAGE_INVALID_XOBJECT, 0);

    if (BRST_Stream_WriteEscapeName(attr->stream, local_name) != BRST_OK)
        return BRST_Error_Check(page->error);

    if (BRST_Stream_WriteStr(attr->stream, " Do\012") != BRST_OK)
        return BRST_Error_Check(page->error);

    return ret;
}

