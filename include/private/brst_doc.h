#ifndef PRIVATE_BRST_DOC_H
#define PRIVATE_BRST_DOC_H

#include "brst_types.h"
#include "brst_doc.h"

#define BRST_SIG_BYTES 0x41504446L // APDF

typedef struct _BRST_Doc_Rec {
    BRST_UINT32       sig_bytes;
    BRST_PDFVer       pdf_version;

    BRST_MMgr         mmgr;
    BRST_Catalog      catalog;
    BRST_Outline      outlines;
    BRST_Xref         xref;
    BRST_Pages        root_pages;
    BRST_Pages        cur_pages;
    BRST_Page         cur_page;
    BRST_List         page_list;

    BRST_Error        error;
    BRST_Dict         info;
    BRST_Dict         trailer;

    BRST_List         font_mgr;
    BRST_BYTE         ttfont_tag[6];

    /* list for loaded fontdefs */
    BRST_List         fontdef_list;

    /* list for loaded encodings */
    BRST_List         encoder_list;

    BRST_Encoder      cur_encoder;

    /* default compression mode */
    BRST_BOOL         compression_mode;

    BRST_BOOL         encrypt_on;
    BRST_EncryptDict  encrypt_dict;

    BRST_Encoder      def_encoder;

    BRST_UINT         page_per_pages;
    BRST_UINT         cur_page_num;

    /* buffer for saving into memory stream */
    BRST_Stream       stream;

    /* PDF/A conformance */
    BRST_PDFAType     pdfa_type;
    BRST_List         xmp_extensions;
} BRST_Doc_Rec;


BRST_BOOL
BRST_Doc_Validate(
    BRST_Doc pdf
);

BRST_Dict
GetInfo(
    BRST_Doc pdf
);

BRST_STATUS
InternalSaveToStream(
    BRST_Doc pdf,
    BRST_Stream stream
);


#endif /* PRIVATE_BRST_DOC_H */
