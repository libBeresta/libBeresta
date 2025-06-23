#ifndef BRST_DOC_PAGE_XOBJECT_H
#define BRST_DOC_PAGE_XOBJECT_H

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

#endif /* BRST_PAGE_XOBJECT_H */