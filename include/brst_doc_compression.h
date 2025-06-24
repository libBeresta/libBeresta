#ifndef BRST_DOC_COMPRESSION_H
#define BRST_DOC_COMPRESSION_H
/**

  \ingroup security
  \brief Set compression mode.

  \copydoc dox_param_pdf
  \param mode \parblock One or more of the following values, combined together using binary \c OR:
  | Mode                    | Description                                                 |
  | ----                    | -----------                                                 |
  | \ref BRST_COMP_NONE     | No compression                                              |
  | \ref BRST_COMP_TEXT     | Compress the contents stream of the page                    |
  | \ref BRST_COMP_IMAGE    | Compress the streams of the image objects.                  |
  | \ref BRST_COMP_METADATA | Other stream data (fonts, cmaps and so on) compressed.      |
  | \ref BRST_COMP_ALL      | All stream data compressed <br/>(combination of \ref BRST_COMP_TEXT, \ref BRST_COMP_IMAGE and \ref BRST_COMP_METADATA). |
  \endparblock

  \copydoc dox_return_ok

  \copydoc dox_error_codes

  - \ref BRST_INVALID_DOCUMENT
  - \ref BRST_INVALID_COMPRESSION_MODE
  - \ref BRST_FAILED_TO_ALLOC_MEM

*/

BRST_EXPORT(BRST_STATUS)
BRST_Doc_SetCompressionMode(
    BRST_Doc  pdf,
    BRST_UINT mode
);
#endif /* BRST_DOC_COMPRESSION_H */