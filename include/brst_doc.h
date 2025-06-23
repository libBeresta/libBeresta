#ifndef BRST_DOC_H
#define BRST_DOC_H

typedef enum _BRST_PdfVer {
    BRST_VER_12 = 0,
    BRST_VER_13,
    BRST_VER_14,
    BRST_VER_15,
    BRST_VER_16,
    BRST_VER_17,
    BRST_VER_20,
    BRST_VER_EOF
} BRST_PDFVer;

struct _BRST_Doc_Rec;
typedef struct _BRST_Doc_Rec *BRST_Doc;

#endif /* BRST_DOC_H */