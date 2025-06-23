#include "brst_external.h"
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
#include "private/brst_outline.h"
#include "brst_base.h"

BRST_EXPORT(BRST_Outline)
BRST_Doc_Outline_Create(
    BRST_Doc pdf,
    BRST_Outline parent,
    BRST_CSTR title,
    BRST_Encoder encoder)
{
    BRST_Outline outline;

    if (!BRST_Doc_Initialized(pdf))
        return NULL;

    if (!parent) {
        if (pdf->outlines) {
            parent = pdf->outlines;
        } else {
            pdf->outlines = BRST_OutlineRoot_New(pdf->mmgr, pdf->xref);

            if (pdf->outlines) {
                BRST_STATUS ret = BRST_Dict_Add(pdf->catalog, "Outlines",
                    pdf->outlines);
                if (ret != BRST_OK) {
                    BRST_Error_Check(pdf->error);
                    pdf->outlines = NULL;
                    return NULL;
                }

                parent = pdf->outlines;
            } else {
                BRST_Error_Check(pdf->error);
                return NULL;
            }
        }
    }

    if (!BRST_Outline_Validate(parent) || pdf->mmgr != parent->mmgr) {
        BRST_Error_Raise(pdf->error, BRST_INVALID_OUTLINE, 0);
        return NULL;
    }

    outline = BRST_Outline_New(pdf->mmgr, parent, title, encoder, pdf->xref);
    if (!outline)
        BRST_Error_Check(pdf->error);

    return outline;
}
