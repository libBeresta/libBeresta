#ifndef BRST_PDFA_H
#define BRST_PDFA_H

/* PDF-A Types */

typedef enum _BRST_PDFA_TYPE
{
    BRST_PDFA_NON_PDFA = -1,

    BRST_PDFA_1A = 0,
    BRST_PDFA_1B,
    BRST_PDFA_2A,
    BRST_PDFA_2B,
    BRST_PDFA_2U,
    BRST_PDFA_3A,
    BRST_PDFA_3B,
    BRST_PDFA_3U,
    BRST_PDFA_4,
    BRST_PDFA_4E,
    BRST_PDFA_4F
} BRST_PDFAType;

#endif /* BRST_PDFA_H */