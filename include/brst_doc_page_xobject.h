#ifndef BRST_DOC_PAGE_XOBJECT_H
#define BRST_DOC_PAGE_XOBJECT_H

#include "brst_stream.h"

BRST_EXPORT(BRST_XObject)
BRST_Doc_Page_XObject_CreateFromImage(
    BRST_Doc   pdf,
    BRST_Page  page,
    BRST_Rect  rect,
    BRST_Image image,
    BRST_BOOL  zoom
);

BRST_EXPORT(BRST_XObject)
BRST_Doc_Page_XObject_CreateAsWhiteRect(
    BRST_Doc  pdf,
    BRST_Page page,
    BRST_Rect rect
);

BRST_EXPORT(BRST_XObject)
BRST_Doc_Page_XObject_Create(
    BRST_Doc  pdf,
    BRST_Page page,
    BRST_REAL width,
    BRST_REAL height,
    BRST_REAL scalex,
    BRST_REAL scaley
);

#endif /* BRST_PAGE_XOBJECT_H */