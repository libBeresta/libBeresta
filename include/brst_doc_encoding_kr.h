#ifndef BRST_DOC_ENCODING_KR_H
#define BRST_DOC_ENCODING_KR_H

/**

  \ingroup font
  \brief Enable Korean fonts. Application can use following Korean fonts after BRST_UseKRFonts() call:
  | Font name            |
  | ---------            |
  | DotumChe             |
  | DotumChe,Bold        |
  | DotumChe,Italic      |
  | DotumChe,BoldItalic  |
  | Dotum                |
  | Dotum,Bold           |
  | Dotum,Italic         |
  | Dotum,BoldItalic     |
  | BatangChe            |
  | BatangChe,Bold       |
  | BatangChe,Italic     |
  | BatangChe,BoldItalic |
  | Batang               |
  | Batang,Bold          |
  | Batang,Italic        |
  | Batang,BoldItalic    |

  \copydoc dox_param_pdf

  \copydoc dox_return_ok

  \copydoc dox_error_codes

  - \ref BRST_INVALID_DOCUMENT
  - \ref BRST_FAILED_TO_ALLOC_MEM
  - \ref BRST_DUPLICATE_REGISTRATION

*/
BRST_EXPORT(BRST_STATUS)
BRST_Doc_UseKRFonts(
    BRST_Doc pdf
);


/**

  \ingroup encode
  \brief Enable Korean encodings.

  Application can following Korean encodings after BRST_UseKREncodings() call:

  | Encoding       |
  | --------       |
  | KSC-EUC-H      |
  | KSC-EUC-V      |
  | KSCms-UHC-H    |
  | KSCms-UHC-HW-H |
  | KSCms-UHC-HW-V |

  \copydoc dox_param_pdf

  \copydoc dox_return_ok

  \copydoc dox_error_codes

  - \ref BRST_INVALID_DOCUMENT
  - \ref BRST_FAILED_TO_ALLOC_MEM
  - \ref BRST_DUPLICATE_REGISTRATION

*/
BRST_EXPORT(BRST_STATUS)
BRST_Doc_UseKREncodings(
    BRST_Doc pdf
);

#endif /* BRST_DOC_ENCODING_KR_H */