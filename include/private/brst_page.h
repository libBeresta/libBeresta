#ifndef PRIVATE_BRST_PAGE_H
#define PRIVATE_BRST_PAGE_H

/*----------------------------------------------------------------------------*/
/*----- BRST_Page ------------------------------------------------------------*/

#include "brst_ext_gstate.h"

BRST_STATUS
BRST_Page_InsertBefore(
    BRST_Page page,
    BRST_Page target
);

BRST_BOOL
BRST_Page_Validate(
    BRST_Page page
);

BRST_Page
BRST_Page_New(
    BRST_MMgr mmgr,
    BRST_Xref xref
);

void*
BRST_Page_InheritableItem(
    BRST_Page    page,
    const char  *key,
    BRST_UINT16  obj_class
);

const char*
BRST_Page_XObjectName(
    BRST_Page    page,
    BRST_XObject xobj
);

BRST_CSTR
BRST_Page_PatternName(
    BRST_Page page,
    BRST_Pattern pat
);

const char*
BRST_Page_LocalFontName(
    BRST_Page page,
    BRST_Font font
);

BRST_Box
BRST_Page_MediaBox(
    BRST_Page page
);

BRST_STATUS
BRST_Page_SetBoxValue(
    BRST_Page   page,
    const char *name,
    BRST_UINT   index,
    BRST_REAL   value
);

void
BRST_Page_SetFilter(
    BRST_Page page,
    BRST_UINT filter
);

BRST_STATUS
BRST_Page_CheckState(
    BRST_Page page,
    BRST_UINT mode
);

const char*
BRST_Page_ExtGStateName(
    BRST_Page      page,
    BRST_ExtGState gstate
);

const char*
BRST_Page_ShadingName(
    BRST_Page    page,
    BRST_Shading shading
);

#endif /* PRIVATE_BRST_PAGE_H */