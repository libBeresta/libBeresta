#include "brst_config.h"
#include "brst_external.h"
#include "brst_ext_gstate.h"
#include "brst_base.h"
#include "brst_types.h"
#include "brst_mmgr.h"
#include "brst_encrypt.h"
#include "brst_stream.h"
#include "brst_dict.h"
#include "brst_xref.h"
#include "brst_encoder.h"
#include "brst_error.h"
#include "brst_consts.h"
#include "private/brst_utils.h"
#include "brst_page.h"
#include "private/brst_encrypt_dict.h"
#include "brst_outline.h"
#include "private/brst_catalog.h"
#include "private/brst_pdfa.h"
#include "brst_pdfa.h"
#include "brst_doc.h"
#include "private/brst_doc.h"
#include "private/brst_ext_gstate.h"

BRST_EXPORT(BRST_ExtGState)
BRST_Doc_Create_ExtGState(BRST_Doc pdf)
{
    BRST_ExtGState ext_gstate;

    if (!BRST_Doc_Initialized(pdf))
        return NULL;

    pdf->pdf_version = (pdf->pdf_version > BRST_VER_14 ? pdf->pdf_version : BRST_VER_14);

    ext_gstate = BRST_ExtGState_New(pdf->mmgr, pdf->xref);
    if (!ext_gstate)
        BRST_Error_Check(pdf->error);

    return ext_gstate;
}
