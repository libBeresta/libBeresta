#ifndef BRST_DOC_ENCODING_JP_H
#define BRST_DOC_ENCODING_JP_H

/**

  \ingroup font
  \brief Enable Japanese fonts. Application can use following Japanese fonts after BRST_UseJPFonts() call:

  | Font name             |
  | ---------             |
  | MS-Mincyo             |
  | MS-Mincyo,Bold        |
  | MS-Mincyo,Italic      |
  | MS-Mincyo,BoldItalic  |
  | MS-Gothic             |
  | MS-Gothic,Bold        |
  | MS-Gothic,Italic      |
  | MS-Gothic,BoldItalic  |
  | MS-PMincyo            |
  | MS-PMincyo,Bold       |
  | MS-PMincyo,Italic     |
  | MS-PMincyo,BoldItalic |
  | MS-PGothic            |
  | MS-PGothic,Bold       |
  | MS-PGothic,Italic     |
  | MS-PGothic,BoldItalic |

  \copydoc dox_param_pdf

  \copydoc dox_return_ok

  \copydoc dox_error_codes

  - \ref BRST_INVALID_DOCUMENT
  - \ref BRST_FAILED_TO_ALLOC_MEM
  - \ref BRST_DUPLICATE_REGISTRATION

*/
BRST_EXPORT(BRST_STATUS)
BRST_Doc_UseJPFonts(
    BRST_Doc pdf
);

/**

  \ingroup encode
  \brief Enable Japanese encodings.

  Application can following Japanese encodings after BRST_UseJPEncodings() call:

  | Encoding     |
  | --------     |
  | 90ms-RKSJ-H  |
  | 90ms-RKSJ-V  |
  | 90msp-RKSJ-H |
  | EUC-H        |
  | EUC-V        |

  \copydoc dox_param_pdf

  \copydoc dox_return_ok

  \copydoc dox_error_codes

  - \ref BRST_INVALID_DOCUMENT
  - \ref BRST_FAILED_TO_ALLOC_MEM
  - \ref BRST_DUPLICATE_REGISTRATION

*/
BRST_EXPORT(BRST_STATUS)
BRST_Doc_UseJPEncodings(
    BRST_Doc pdf
);

#endif /* BRST_DOC_ENCODING_JP_H */