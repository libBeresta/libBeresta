#include "brst_external.h"
#include "brst_types.h"
#include "brst_mmgr.h"
#include "brst_encrypt.h"
#include "brst_stream.h"
#include "private/brst_stream.h"
#include "brst_xref.h"
#include "brst_dict.h"
#include "private/brst_dict.h"
#include "brst_encoder.h"
#include "private/brst_encoder.h"
#include "brst_error.h"
#include "brst_consts.h"
#include "brst_ext_gstate.h"
#include "brst_font.h"
#include "brst_shading.h"
#include "brst_doc.h"
#include "brst_pdfa.h"
#include "brst_page.h"
#include "brst_destination.h"
#include "private/brst_catalog.h"
#include "brst_outline.h"
#include "private/brst_encrypt_dict.h"
#include "private/brst_doc.h"
#include "private/brst_page.h"
#include "brst_base.h"
#include "brst_image.h"
#include "private/brst_gstate.h"
#include "private/brst_page_attr.h"
#include "private/brst_array.h"
#include "private/brst_name.h"
#include "brst_doc_page_xobject.h"
#include "brst_xobject.h"
#include "private/brst_xobject.h"


BRST_EXPORT(BRST_Pattern)
BRST_Doc_Page_Pattern_Tiling_Create(
    BRST_Doc pdf,
    BRST_Page page,
    BRST_REAL width,
    BRST_REAL height,
    BRST_REAL scalex,
    BRST_REAL scaley
) {
    return BRST_Pattern_Tiling_New(page->mmgr, pdf->xref, width, height, scalex, scaley);
}

BRST_EXPORT(BRST_Stream)
BRST_XObject_Stream(BRST_Pattern pat) {
    return BRST_Pattern_Stream(pat);
}
