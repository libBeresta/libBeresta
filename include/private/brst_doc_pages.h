#ifndef PRIVATE_BRST_DOC_PAGES_H
#define PRIVATE_BRST_DOC_PAGES_H

BRST_Pages
BRST_Doc_Pages_Current(
    BRST_Doc pdf
);

BRST_Pages
BRST_Doc_Pages_AddTo(
    BRST_Doc   pdf,
    BRST_Pages parent
);

BRST_STATUS
BRST_Doc_Pages_SetCurrent(
    BRST_Doc   pdf,
    BRST_Pages pages
);

#endif /* PRIVATE_BRST_DOC_PAGES_H */