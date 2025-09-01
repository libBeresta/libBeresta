#ifndef PRIVATE_BRST_XOBJECT_H
#define PRIVATE_BRST_XOBJECT_H

#include "brst_xobject.h"

BRST_XObject
BRST_XObject_New(
    BRST_MMgr mmgr,
    BRST_Xref xref,
    BRST_REAL width,
    BRST_REAL height,
    BRST_REAL scalex,
    BRST_REAL scaley
);

BRST_Stream
BRST_XObject_Stream(
    BRST_XObject obj
);

#endif /* PRIVATE_BRST_XOBJECT_H */