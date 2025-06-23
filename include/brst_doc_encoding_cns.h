#ifndef BRST_DOC_ENCODING_CNS_H
#define BRST_DOC_ENCODING_CNS_H

/**

  \ingroup font
  \brief Enable simplified Chinese fonts. Application can use following simplified Chinese fonts after BRST_UseCNSFonts() call:
    | Font name         |
    | ---------         |
    | SimSun            |
    | SimSun,Bold       |
    | SimSun,Italic     |
    | SimSun,BoldItalic |
    | SimHei            |
    | SimHei,Bold       |
    | SimHei,Italic     |
    | SimHei,BoldItalic |

  \copydoc dox_param_pdf

  \copydoc dox_return_ok

  \copydoc dox_error_codes

  - \ref BRST_INVALID_DOCUMENT
  - \ref BRST_FAILED_TO_ALLOC_MEM
  - \ref BRST_DUPLICATE_REGISTRATION

*/
BRST_EXPORT(BRST_STATUS)
BRST_Doc_UseCNSFonts(
    BRST_Doc pdf
);

/**

  \ingroup encode
  \brief Enable simplified Chinese encodings.

  Application can following simplified Chinese encodings after BRST_UseCNSEncodings() call:

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
BRST_Doc_UseCNSEncodings(
    BRST_Doc pdf
);

#endif /* BRST_DOC_ENCODING_CNS_H */
