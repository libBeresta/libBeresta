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

BRST_EXPORT(BRST_STATUS)
BRST_Doc_SetCompressionMode(BRST_Doc pdf,
    BRST_UINT mode)
{
#ifdef LIBBRST_HAVE_ZLIB
    if (!BRST_Doc_Validate(pdf))
        return BRST_INVALID_DOCUMENT;

    if (mode != (mode & BRST_COMP_MASK))
        return BRST_Error_Raise(pdf->error, BRST_INVALID_COMPRESSION_MODE, 0);

    pdf->compression_mode = mode;

    return BRST_OK;

#else /* LIBBRST_HAVE_ZLIB */

    return BRST_INVALID_COMPRESSION_MODE;

#endif /* LIBBRST_HAVE_ZLIB */
}
