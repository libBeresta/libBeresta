#include "brst_external.h"
#include "brst_types.h"
#include "brst_encrypt.h"
#include "brst_mmgr.h"
#include "brst_dict.h"
#include "brst_xref.h"
#include "brst_pattern.h"
#include "brst_matrix.h"
#include "brst_encoder.h"
#include "brst_doc.h"
#include "brst_pdfa.h"
#include "brst_page.h"
#include "brst_destination.h"
#include "private/brst_catalog.h"
#include "brst_outline.h"
#include "private/brst_encrypt_dict.h"
#include "private/brst_doc.h"
#include "private/brst_pattern.h"

BRST_EXPORT(BRST_Pattern)
BRST_Doc_Pattern_Tiling_New(
    BRST_Doc pdf,
    BRST_REAL left,
    BRST_REAL bottom,
    BRST_REAL right,
    BRST_REAL top,
    BRST_REAL xstep,
    BRST_REAL ystep,
    BRST_Matrix matrix
) {
    return BRST_Pattern_Tiling_New(pdf->mmgr, pdf->xref, left, bottom, right, top, xstep, ystep, matrix);
}

BRST_EXPORT(BRST_Stream)
BRST_Doc_Pattern_Stream(BRST_Pattern pat) {
    return BRST_Pattern_Stream(pat);
}
