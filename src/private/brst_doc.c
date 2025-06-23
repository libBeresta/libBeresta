#include "brst_types.h"
#include "brst_mmgr.h"
#include "brst_encrypt.h"
#include "brst_stream.h"
#include "brst_dict.h"
#include "brst_xref.h"
#include "brst_encoder.h"
#include "brst_ext_gstate.h"
#include "brst_shading.h"
#include "brst_font.h"
#include "brst_page.h"
#include "private/brst_page.h"
#include "brst_destination.h"
#include "brst_outline.h"
#include "private/brst_encrypt_dict.h"
#include "private/brst_catalog.h"
#include "brst_pdfa.h"
#include "brst_doc.h"
#include "private/brst_doc.h"
#include "private/brst_pdfa.h"
#include "private/brst_doc_encryption.h"
#include "brst_base.h"
#include "brst_error.h"
#include "brst_fontdef.h"
#include "private/brst_fontdef.h"
#include "brst_consts.h"
#include "private/brst_utils.h"

static const char* const BRST_VERSION_STR[] = {
    "%PDF-1.2\012%\267\276\255\252\012",
    "%PDF-1.3\012%\267\276\255\252\012",
    "%PDF-1.4\012%\267\276\255\252\012",
    "%PDF-1.5\012%\267\276\255\252\012",
    "%PDF-1.6\012%\267\276\255\252\012",
    "%PDF-1.7\012%\267\276\255\252\012",
    "%PDF-2.0\012%\267\276\255\252\012"
};

static BRST_STATUS
WriteHeader(BRST_Doc pdf,
    BRST_Stream stream)
{
    BRST_UINT idx = (BRST_INT)pdf->pdf_version;

    BRST_PTRACE((" WriteHeader\n"));

    if (BRST_Stream_WriteStr(stream, BRST_VERSION_STR[idx]) != BRST_OK)
        return BRST_Error_Code(pdf->error);

    return BRST_OK;
}

static BRST_STATUS
PrepareTrailer(BRST_Doc pdf)
{
    BRST_PTRACE((" PrepareTrailer\n"));

    if (BRST_Dict_Add(pdf->trailer, "Root", pdf->catalog) != BRST_OK)
        return BRST_Error_Code(pdf->error);

    if (BRST_Dict_Add(pdf->trailer, "Info", pdf->info) != BRST_OK)
        return BRST_Error_Code(pdf->error);

    return BRST_OK;
}

BRST_STATUS
InternalSaveToStream(BRST_Doc pdf,
    BRST_Stream stream)
{
    BRST_STATUS ret;

    /* Add metadata in case of PDF/A document */
    if (pdf->pdfa_type != BRST_PDFA_NON_PDFA && (ret = BRST_PDFA_AddXmpMetadata(pdf)) != BRST_OK)
        return ret;

    if ((ret = WriteHeader(pdf, stream)) != BRST_OK)
        return ret;

    /* prepare trailer */
    if ((ret = PrepareTrailer(pdf)) != BRST_OK)
        return ret;

    /* prepare encryption */
    if (pdf->encrypt_on) {
        BRST_Encrypt e = BRST_EncryptDict_Attr(pdf->encrypt_dict);

        if ((ret = BRST_Doc_PrepareEncryption(pdf)) != BRST_OK)
            return ret;

        if ((ret = BRST_Xref_WriteToStream(pdf->xref, stream, e)) != BRST_OK)
            return ret;
    } else {
        if ((ret = BRST_Xref_WriteToStream(pdf->xref, stream, NULL)) != BRST_OK)
            return ret;
    }

    return BRST_OK;
}

BRST_BOOL
BRST_Doc_Validate(BRST_Doc pdf)
{
    BRST_PTRACE((" BRST_Doc_Validate\n"));

    if (!pdf || pdf->sig_bytes != BRST_SIG_BYTES)
        return BRST_FALSE;
    else
        return BRST_TRUE;
}

BRST_STATUS
BRST_Doc_SetCurrentPage(BRST_Doc pdf,
    BRST_Page page)
{
    BRST_PTRACE((" BRST_Doc_SetCurrentPage\n"));

    if (!BRST_Doc_Initialized(pdf))
        return BRST_INVALID_DOCUMENT;

    if (!BRST_Page_Validate(page))
        return BRST_Error_Set(pdf->error, BRST_INVALID_PAGE, 0);

    /* check whether the page belong to the pdf */
    if (pdf->mmgr != page->mmgr)
        return BRST_Error_Set(pdf->error, BRST_INVALID_PAGE, 0);

    pdf->cur_page = page;

    return BRST_OK;
}

BRST_Dict
GetInfo(BRST_Doc pdf)
{
    if (!BRST_Doc_Initialized(pdf))
        return NULL;

    if (!pdf->info) {
        pdf->info = BRST_Dict_New(pdf->mmgr);

        if (!pdf->info || BRST_Xref_Add(pdf->xref, pdf->info) != BRST_OK)
            pdf->info = NULL;
    }

    return pdf->info;
}
