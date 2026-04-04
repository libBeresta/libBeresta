// license
#ifndef BRST_DOC_H
#define BRST_DOC_H

struct _BRST_Doc_Rec;
typedef struct _BRST_Doc_Rec* BRST_Doc;

/**
 Версия стандарта PDF документа
 */
typedef enum _BRST_PdfVer { 
    /// Стартовая версия PDF
    BRST_VER_10,
    /// Версия 1.1
    BRST_VER_11,
    /// Версия 1.2
    BRST_VER_12,
    /// Версия 1.3
    BRST_VER_13,
    /// Версия 1.4
    BRST_VER_14,
    /// Версия 1.5
    BRST_VER_15,
    /// Версия 1.6
    BRST_VER_16,
    /// Версия 1.7
    BRST_VER_17,
    /// Версия 2.0
    BRST_VER_20,
    BRST_PDFVER_LAST
} BRST_PdfVer;

#endif /* BRST_DOC_H */
