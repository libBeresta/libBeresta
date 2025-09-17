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


#endif /* BRST_STREAM_TEXT_H */ 