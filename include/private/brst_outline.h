#ifndef PRIVATE_BRST_OUTLINE_H
#define PRIVATE_BRST_OUTLINE_H

BRST_Outline
BRST_OutlineRoot_New(
    BRST_MMgr mmgr,
    BRST_Xref xref
);

BRST_Outline
BRST_Outline_New(
    BRST_MMgr    mmgr,
    BRST_Outline parent,
    const char*  title,
    BRST_Encoder encoder,
    BRST_Xref    xref
);

BRST_Outline
BRST_Outline_First(
    BRST_Outline outline
);

BRST_Outline
BRST_Outline_Last(
    BRST_Outline outline
);

BRST_Outline
BRST_Outline_Prev(
    BRST_Outline outline
);

BRST_Outline
BRST_Outline_Next(
    BRST_Outline outline
);

BRST_Outline
BRST_Outline_Parent(
    BRST_Outline outline
);

BRST_BOOL
BRST_Outline_Opened(
    BRST_Outline outline
);

BRST_BOOL
BRST_Outline_Validate(
    BRST_Outline outline
);

#endif /* PRIVATE_BRST_OUTLINE_H */
