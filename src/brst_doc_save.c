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
#include "brst_pdfa.h"
#include "private/brst_doc.h"
#include "brst_doc.h"
#include "brst_base.h"

BRST_EXPORT(BRST_STATUS)
BRST_Doc_SaveToStream(BRST_Doc pdf)
{
    BRST_PTRACE(" BRST_Doc_SaveToStream\n");

    if (!BRST_Doc_Initialized(pdf))
        return BRST_INVALID_DOCUMENT;

    if (!pdf->stream)
        pdf->stream = BRST_MemStream_New(pdf->mmgr, BRST_STREAM_BUF_SIZE);

    if (!BRST_Stream_Validate(pdf->stream))
        return BRST_Error_Raise(pdf->error, BRST_INVALID_STREAM, 0);

    BRST_MemStream_FreeData(pdf->stream);

    if (InternalSaveToStream(pdf, pdf->stream) != BRST_OK)
        return BRST_Error_Check(pdf->error);

    return BRST_OK;
}

BRST_EXPORT(BRST_STATUS)
BRST_Doc_SaveToFile(BRST_Doc pdf,
    const char* file_name)
{
    BRST_Stream stream;

    BRST_PTRACE(" BRST_SaveToFile\n");

    if (!BRST_Doc_Initialized(pdf))
        return BRST_INVALID_DOCUMENT;

    stream = BRST_FileWriter_New(pdf->mmgr, file_name);
    if (!stream)
        return BRST_Error_Check(pdf->error);

    InternalSaveToStream(pdf, stream);

    BRST_Stream_Free(stream);

    return BRST_Error_Check(pdf->error);
}
