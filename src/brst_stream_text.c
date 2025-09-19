#include "brst_external.h"
#include "brst_types.h"
#include "brst_mmgr.h"
#include "brst_encrypt.h"
#include "brst_stream.h"
#include "private/brst_stream.h"
#include "brst_dict.h"
#include "brst_xref.h"
#include "brst_text_defines.h"
#include "brst_font.h"
#include "brst_error.h"
#include "brst_consts.h"
#include "private/brst_utils.h"
#include "brst_matrix.h"
#include "brst_text.h"
#include "private/brst_text.h"

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

    if (BRST_Stream_WriteReal(stream, value) != BRST_OK)
        return BRST_Error_Check(stream->error);

    if (BRST_Stream_WriteStr(stream, " TL\012") != BRST_OK)
        return BRST_Error_Check(stream->error);

    return ret;
}

/* Tr */
BRST_EXPORT(BRST_STATUS)
BRST_Stream_SetTextRenderingMode(BRST_Stream stream,
    BRST_TextRenderingMode mode)
{
    BRST_PTRACE(" BRST_Stream_SetTextRenderingMode\n");

    BRST_STATUS ret = BRST_Stream_Validate(stream) ? BRST_OK : BRST_INVALID_STREAM;

    if (ret != BRST_OK)
        return ret;

    if (BRST_Stream_WriteInt(stream, (BRST_INT)mode) != BRST_OK)
        return BRST_Error_Check(stream->error);

    if (BRST_Stream_WriteStr(stream, " Tr\012") != BRST_OK)
        return BRST_Error_Check(stream->error);

    return ret;
}

/* Ts */
BRST_EXPORT(BRST_STATUS)
BRST_Stream_SetTextRise(BRST_Stream stream,
    BRST_REAL value)
{
    BRST_PTRACE(" BRST_Stream_SetTextRise\n");

    BRST_STATUS ret = BRST_Stream_Validate(stream) ? BRST_OK : BRST_INVALID_STREAM;

    if (ret != BRST_OK)
        return ret;

    if (BRST_Stream_WriteReal(stream, value) != BRST_OK)
        return BRST_Error_Check(stream->error);

    if (BRST_Stream_WriteStr(stream, " Ts\012") != BRST_OK)
        return BRST_Error_Check(stream->error);

    return ret;
}

/* Td */
BRST_EXPORT(BRST_STATUS)
BRST_Stream_MoveTextPos(BRST_Stream stream,
    BRST_REAL x,
    BRST_REAL y)
{
    BRST_PTRACE(" BRST_Stream_MoveTextPos\n");

    BRST_STATUS ret = BRST_Stream_Validate(stream) ? BRST_OK : BRST_INVALID_STREAM;

    if (ret != BRST_OK)
        return ret;

    ret += BRST_Stream_WriteReal(stream, x);
    ret += BRST_Stream_WriteStr(stream, " ");
    ret += BRST_Stream_WriteReal(stream, y);
    ret += BRST_Stream_WriteStr(stream, " Td\012");

    if (ret != BRST_OK)
        return BRST_Error_Check(stream->error);

    return ret;
}

/* TD */
BRST_EXPORT(BRST_STATUS)
BRST_Stream_MoveTextPos2(BRST_Stream stream,
    BRST_REAL x,
    BRST_REAL y)
{
    BRST_PTRACE(" BRST_Stream_MoveTextPos2\n");

    BRST_STATUS ret = BRST_Stream_Validate(stream) ? BRST_OK : BRST_INVALID_STREAM;

    if (ret != BRST_OK)
        return ret;

    ret += BRST_Stream_WriteReal(stream, x);
    ret += BRST_Stream_WriteStr(stream, " ");
    ret += BRST_Stream_WriteReal(stream, y);
    ret += BRST_Stream_WriteStr(stream, " TD\012");

    if (ret != BRST_OK)
        return BRST_Error_Check(stream->error);

    return ret;
}

/* Tm */
BRST_EXPORT(BRST_STATUS)
BRST_Stream_SetTextMatrix(BRST_Stream stream,
    BRST_REAL a,
    BRST_REAL b,
    BRST_REAL c,
    BRST_REAL d,
    BRST_REAL x,
    BRST_REAL y
) {
    BRST_PTRACE(" BRST_Stream_SetTextMatrix\n");

    BRST_STATUS ret = BRST_Stream_Validate(stream) ? BRST_OK : BRST_INVALID_STREAM;

    if (ret != BRST_OK)
        return ret;

    if ((a == 0 || d == 0) && (b == 0 || c == 0))
        return BRST_Error_Raise(stream->error, BRST_INVALID_PARAMETER, 0);

    ret += BRST_Stream_WriteReal(stream, a);
    ret += BRST_Stream_WriteStr(stream, " ");
    ret += BRST_Stream_WriteReal(stream, b);
    ret += BRST_Stream_WriteStr(stream, " ");
    ret += BRST_Stream_WriteReal(stream, c);
    ret += BRST_Stream_WriteStr(stream, " ");
    ret += BRST_Stream_WriteReal(stream, d);
    ret += BRST_Stream_WriteStr(stream, " ");
    ret += BRST_Stream_WriteReal(stream, y);
    ret += BRST_Stream_WriteStr(stream, " Tm\012");

    if (ret != BRST_OK)
        return BRST_Error_Check(stream->error);

    return ret;
}

/* T* */
BRST_EXPORT(BRST_STATUS)
BRST_Stream_MoveToNextLine(BRST_Stream stream)
{
    BRST_PTRACE(" BRST_Stream_MoveToNextLine\n");

    BRST_STATUS ret = BRST_Stream_Validate(stream) ? BRST_OK : BRST_INVALID_STREAM;

    if (ret != BRST_OK)
        return ret;

    ret += BRST_Stream_WriteStr(stream, "T*\012");

    if (ret != BRST_OK)
        return BRST_Error_Check(stream->error);

    return ret;
}


// Tj
// font нужен для того, чтобы из него взять кодировку текста (если указана)
// и кодировать текст соответственно.
BRST_EXPORT(BRST_STATUS)
BRST_Stream_ShowText(BRST_Stream stream,
    BRST_Font font,
    BRST_CSTR text)
{
    BRST_PTRACE(" BRST_Stream_ShowText\n");

    BRST_STATUS ret = BRST_Stream_Validate(stream) ? BRST_OK : BRST_INVALID_STREAM;

    if (ret != BRST_OK)
        return ret;

    ret += InternalWriteText(stream, font, text);
    ret += BRST_Stream_WriteStr(stream, " Tj\012");

    if (ret != BRST_OK)
        return BRST_Error_Check(stream->error);

    return ret;
}

BRST_EXPORT(BRST_STATUS)
BRST_Stream_TextOut(BRST_Stream stream,
    BRST_Font font,
    BRST_REAL x,
    BRST_REAL y,
    BRST_CSTR text
) {
    BRST_PTRACE(" BRST_Stream_TextOut\n");

    BRST_STATUS ret = BRST_Stream_Validate(stream) ? BRST_OK : BRST_INVALID_STREAM;

    if (ret != BRST_OK)
        return ret;

    ret += BRST_Stream_MoveTextPos(stream, x, y);
    ret += BRST_Stream_ShowText(stream, font, text);

    if (ret != BRST_OK) {
        return BRST_Error_Check(stream->error);
    }
    
    return ret;
}
