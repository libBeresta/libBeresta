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
#include "brst_base.h"
#include "brst_doc_stream.h"

BRST_UINT32
BRST_Doc_Stream_Size(BRST_Doc pdf)
{
    BRST_PTRACE(" BRST_Doc_Stream_Size\n");

    if (!BRST_Doc_Initialized(pdf))
        return BRST_INVALID_DOCUMENT;

    if (!BRST_Stream_Validate(pdf->stream))
        return 0;

    return BRST_Stream_Size(pdf->stream);
}

BRST_STATUS
BRST_Doc_Stream_Read(BRST_Doc pdf,
    BRST_BYTE* buf,
    BRST_UINT32* size)
{
    BRST_PTRACE(" BRST_Doc_Stream_Read\n");

    BRST_UINT isize = *size;
    BRST_STATUS ret;

    if (!BRST_Doc_Initialized(pdf))
        return BRST_INVALID_DOCUMENT;

    if (!BRST_Stream_Validate(pdf->stream))
        return BRST_Error_Raise(pdf->error, BRST_INVALID_OPERATION, 0);

    if (*size == 0)
        return BRST_Error_Raise(pdf->error, BRST_INVALID_PARAMETER, 0);

    ret = BRST_Stream_Read(pdf->stream, buf, &isize);

    *size = isize;

    if (ret != BRST_OK)
        BRST_Error_Check(pdf->error);

    return ret;
}

BRST_STATUS
BRST_Doc_Stream_Reset(BRST_Doc pdf)
{
    BRST_PTRACE(" BRST_Doc_Stream_Reset\n");

    if (!BRST_Doc_Initialized(pdf))
        return BRST_INVALID_DOCUMENT;

    if (!BRST_Stream_Validate(pdf->stream))
        return BRST_Error_Raise(pdf->error, BRST_INVALID_OPERATION, 0);

    return BRST_Stream_Seek(pdf->stream, 0, BRST_SEEK_SET);
}
