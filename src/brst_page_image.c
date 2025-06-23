#include "brst_external.h"
#include "brst_types.h"
#include "brst_mmgr.h"
#include "brst_encrypt.h"
#include "brst_stream.h"
#include "brst_dict.h"
#include "brst_xref.h"
#include "private/brst_defines.h"
#include "brst_consts.h"
#include "brst_text_defines.h"
#include "brst_font.h"
#include "brst_page.h"
#include "brst_destination.h"
#include "brst_base.h"
#include "private/brst_pages.h"
#include "private/brst_gstate.h"
#include "private/brst_destination.h"
#include "brst_image.h"
#include "brst_geometry.h"
#include "brst_page_xobject.h"
#include "private/brst_utils.h"

BRST_EXPORT(BRST_STATUS)
BRST_Page_DrawImage(BRST_Page page,
    BRST_Image image,
    BRST_REAL x,
    BRST_REAL y,
    BRST_REAL width,
    BRST_REAL height)
{
    BRST_STATUS ret;

    if ((ret = BRST_Page_GSave(page)) != BRST_OK)
        return ret;

    if ((ret = BRST_Page_Concat(page, width, 0, 0, height, x, y)) != BRST_OK)
        return ret;

    if ((ret = BRST_Page_XObject_Execute(page, image)) != BRST_OK)
        return ret;

    return BRST_Page_GRestore(page);
}
