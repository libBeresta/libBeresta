#ifndef BRST_DOC_ENCODING_UTF_H
#define BRST_DOC_ENCODING_UTF_H

/**

  \ingroup encode
  \brief Enable UTF-8 encoding.

  Application can include UTF-8 encoded Unicode text (up to 3-byte UTF-8 sequences).

  \note UTF-8 encoding works only with TrueType fonts.

  \copydoc dox_param_pdf

  \copydoc dox_return_ok

  \copydoc dox_error_codes

  - \ref BRST_INVALID_DOCUMENT
  - \ref BRST_FAILED_TO_ALLOC_MEM
  - \ref BRST_DUPLICATE_REGISTRATION

*/
BRST_EXPORT(BRST_STATUS)
BRST_Doc_UseUTFEncodings(
    BRST_Doc pdf
);

#endif /* BRST_DOC_ENCODING_UTF_H */