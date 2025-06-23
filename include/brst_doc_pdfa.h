#ifndef BRST_DOC_PDFA_H
#define BRST_DOC_PDFA_H

#include "brst_pdfa.h"

BRST_EXPORT(BRST_STATUS)
BRST_Doc_PDFA_SetConformance(
    BRST_Doc      pdf,
    BRST_PDFAType pdfa_type
);

BRST_EXPORT(BRST_STATUS)
BRST_Doc_PDFA_AddXmpExtension(
    BRST_Doc  pdf,
    BRST_CSTR xmp_description
);

BRST_EXPORT(BRST_STATUS)
BRST_Doc_PDFA_AppendOutputIntents(
    BRST_Doc  pdf,
    BRST_CSTR iccname,
    BRST_Dict iccdict
);
#endif /* BRST_DOC_PDFA_H */