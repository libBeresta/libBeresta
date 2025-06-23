#ifndef BRST_DOC_SAVE_H
#define BRST_DOC_SAVE_H

/**

  \ingroup doc
  \brief Saves the current document to a temporary stream of a document object.

  \copydoc dox_param_pdf

  \copydoc dox_return_ok

  \copydoc dox_error_codes

  - \ref BRST_INVALID_DOCUMENT
  - \ref BRST_FAILED_TO_ALLOC_MEM

*/
BRST_EXPORT(BRST_STATUS)
BRST_Doc_SaveToStream(
    BRST_Doc pdf
);
/**

  \ingroup doc
  \brief Saves the current document to file.

  \copydoc dox_param_pdf
  \param filename The name of file to save.

  \copydoc dox_return_ok

  \copydoc dox_error_codes

  - \ref BRST_INVALID_DOCUMENT
  - \ref BRST_FAILED_TO_ALLOC_MEM
  - \ref BRST_FILE_IO_ERROR

*/
BRST_EXPORT(BRST_STATUS)
BRST_Doc_SaveToFile(
    BRST_Doc  pdf,
    BRST_CSTR filename
);

#endif /* BRST_DOC_SAVE_H */