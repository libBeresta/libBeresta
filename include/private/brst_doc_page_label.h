#ifndef PRIVATE_BRST_DOC_PAGE_LABEL_H
#define PRIVATE_BRST_DOC_PAGE_LABEL_H

BRST_Dict
BRST_PageLabel_New(
    BRST_Doc          pdf,
    BRST_PageNumStyle style,
    BRST_INT          first_page,
    const char*       prefix
);

#endif /* PRIVATE_BRST_DOC_PAGE_LABEL_H */