#ifndef BRST_DOC_ENCODING_CNT_H
#define BRST_DOC_ENCODING_CNT_H

/**

  \ingroup font
  \brief Enable traditional Chinese fonts. Application can use following traditional Chinese fonts after BRST_UseCNTFonts() call:

    | Font name          |
    | ---------          |
    | MingLiU            |
    | MingLiU,Bold       |
    | MingLiU,Italic     |
    | MingLiU,BoldItalic |

  \copydoc dox_param_pdf

  \copydoc dox_return_ok

  \copydoc dox_error_codes

  - \ref BRST_INVALID_DOCUMENT
  - \ref BRST_FAILED_TO_ALLOC_MEM
  - \ref BRST_DUPLICATE_REGISTRATION

*/
BRST_EXPORT(BRST_STATUS)
BRST_Doc_UseCNTFonts(
    BRST_Doc pdf
);

/**

  \ingroup encode
  \brief Enable traditional Chinese encodings.

  Application can following traditional Chinese encodings after BRST_UseCNTEncodings() call:

  | Encoding  |
  | --------  |
  | GB-EUC-H  |
  | GB-EUC-V  |
  | GBK-EUC-H |
  | GBK-EUC-V |


  \copydoc dox_param_pdf

  \copydoc dox_return_ok

  \copydoc dox_error_codes

  - \ref BRST_INVALID_DOCUMENT
  - \ref BRST_FAILED_TO_ALLOC_MEM
  - \ref BRST_DUPLICATE_REGISTRATION

*/
BRST_EXPORT(BRST_STATUS)
BRST_Doc_UseCNTEncodings(
    BRST_Doc pdf
);

#endif /* BRST_DOC_ENCODING_CNT_H */