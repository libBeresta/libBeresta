#include "brst_external.h"
#include "brst_types.h"
#include "brst_mmgr.h"
#include "brst_encrypt.h"
#include "brst_stream.h"
#include "private/brst_stream.h"
#include "brst_dict.h"
#include "brst_xref.h"
#include "brst_error.h"
#include "brst_consts.h"
#include "private/brst_utils.h"

BRST_EXPORT(BRST_STATUS)
BRST_Stream_BeginText(BRST_Stream stream)
{
    BRST_PTRACE((" BRST_Stream_BeginText\n"));

    BRST_STATUS ret = BRST_Stream_Validate(stream) ? BRST_OK : BRST_INVALID_STREAM;

    if (ret != BRST_OK)
        return ret;

    if (BRST_Stream_WriteStr(stream, "BT\012") != BRST_OK)
        return BRST_Error_Check(stream->error);

    return ret;
}

BRST_EXPORT(BRST_STATUS)
BRST_Stream_EndText(BRST_Stream stream)
{
    BRST_PTRACE((" BRST_Stream_EndText\n"));

    BRST_STATUS ret = BRST_Stream_Validate(stream) ? BRST_OK : BRST_INVALID_STREAM;

    if (ret != BRST_OK)
        return ret;

    if (BRST_Stream_WriteStr(stream, "ET\012") != BRST_OK)
        return BRST_Error_Check(stream->error);

    return ret;
}

BRST_EXPORT(BRST_STATUS)
BRST_Stream_SetTextLeading(BRST_Stream stream,
   BRST_REAL value
)
{
    BRST_PTRACE((" BRST_Stream_SetTextLeading\n"));

    BRST_STATUS ret = BRST_Stream_Validate(stream) ? BRST_OK : BRST_INVALID_STREAM;

    if (ret != BRST_OK)
        return ret;

    printf("HIA: value = %f\n", value);
    if (BRST_Stream_WriteReal(stream, value) != BRST_OK)
        return BRST_Error_Check(stream->error);

    if (BRST_Stream_WriteStr(stream, " TL\012") != BRST_OK)
        return BRST_Error_Check(stream->error);

    return ret;
}
