#ifndef BRST_DOC_XOBJECT_H
#define BRST_DOC_XOBJECT_H

#include "brst_stream.h"

BRST_EXPORT(BRST_XObject)
BRST_Doc_XObject_New(
    BRST_Doc  pdf,
    BRST_REAL width,
    BRST_REAL height,
    BRST_REAL scalex,
    BRST_REAL scaley
);

BRST_EXPORT(BRST_XObject)
BRST_Doc_XObject_NewFromImage(
    BRST_Doc   pdf,
    BRST_Rect  rect,
    BRST_Image image,
    BRST_BOOL  zoom
);

BRST_EXPORT(BRST_XObject)
BRST_Doc_XObject_NewAsWhiteRect(
    BRST_Doc  pdf,
    BRST_Rect rect
);

#endif /* BRST_DOC_XOBJECT_H */