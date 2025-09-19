#ifndef BRST_STREAM_TEXT_H
#define BRST_STREAM_TEXT_H

BRST_EXPORT(BRST_STATUS)
BRST_Stream_BeginText(
    BRST_Stream stream
);

BRST_EXPORT(BRST_STATUS)
BRST_Stream_EndText(
    BRST_Stream stream
);

BRST_EXPORT(BRST_STATUS)
BRST_Stream_SetTextLeading(
    BRST_Stream stream,
    BRST_REAL value
);

BRST_EXPORT(BRST_STATUS)
BRST_Stream_SetTextRenderingMode(
    BRST_Stream            stream,
    BRST_TextRenderingMode mode
);

BRST_EXPORT(BRST_STATUS)
BRST_Stream_MoveTextPos(
    BRST_Stream stream,
    BRST_REAL x,
    BRST_REAL y
);

BRST_EXPORT(BRST_STATUS)
BRST_Stream_MoveTextPos2(
    BRST_Stream stream,
    BRST_REAL x,
    BRST_REAL y
);

BRST_EXPORT(BRST_STATUS)
BRST_Stream_SetTextRise(
    BRST_Stream stream,
    BRST_REAL value
);

BRST_EXPORT(BRST_STATUS)
BRST_Stream_SetTextMatrix(
    BRST_Stream stream,
    BRST_REAL a,
    BRST_REAL b,
    BRST_REAL c,
    BRST_REAL d,
    BRST_REAL x,
    BRST_REAL y
);

BRST_EXPORT(BRST_STATUS)
BRST_Stream_MoveToNextLine(
    BRST_Stream stream
);

BRST_EXPORT(BRST_STATUS)
BRST_Stream_ShowText(
    BRST_Stream stream,
    BRST_Font font,
    BRST_CSTR text
);

BRST_EXPORT(BRST_STATUS)
BRST_Stream_TextOut(BRST_Stream stream,
    BRST_Font font,
    BRST_REAL x,
    BRST_REAL y,
    BRST_CSTR text
);

#endif /* BRST_STREAM_TEXT_H */ 