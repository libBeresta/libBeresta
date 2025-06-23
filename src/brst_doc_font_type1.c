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
#include "brst_pdfa.h"
#include "brst_doc.h"
#include "brst_fontdef.h"
#include "private/brst_defines.h"
#include "private/brst_catalog.h"
#include "private/brst_doc.h"
#include "brst_font.h"
#include "private/brst_doc_font.h"
#include "brst_base.h"

BRST_EXPORT(const char*)
BRST_Doc_Type1Font_LoadFromFile(BRST_Doc pdf,
    const char* afm_file_name,
    const char* data_file_name)
{
    BRST_Stream afm;
    BRST_Stream pfm = NULL;
    const char* ret;

    BRST_PTRACE((" BRST_Doc_Type1Font_LoadFromFile\n"));

    if (!BRST_Doc_Initialized(pdf))
        return NULL;

    /* create file stream */
    afm = BRST_FileReader_New(pdf->mmgr, afm_file_name);

    if (data_file_name)
        pfm = BRST_FileReader_New(pdf->mmgr, data_file_name);

    if (BRST_Stream_Validate(afm) && (!data_file_name || BRST_Stream_Validate(pfm))) {

        ret = LoadType1FontFromStream(pdf, afm, pfm);
    } else
        ret = NULL;

    /* destroy file stream */
    if (afm)
        BRST_Stream_Free(afm);

    if (pfm)
        BRST_Stream_Free(pfm);

    if (!ret)
        BRST_Error_Check(pdf->error);

    return ret;
}
