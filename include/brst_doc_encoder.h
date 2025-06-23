#ifndef BRST_DOC_ENCODER_H
#define BRST_DOC_ENCODER_H

/**

  \ingroup encode
  \brief Get encoder object handle by specified encoding name.

  \copydoc dox_param_pdf
  \param encoding_name Valid encoding name

  \return Encoder object handle on success, otherwise, it returns \c NULL and call error handler

  \copydoc dox_error_codes

  - \ref BRST_INVALID_DOCUMENT
  - \ref BRST_FAILED_TO_ALLOC_MEM
  - \ref BRST_INVALID_ENCODING_NAME

*/
BRST_EXPORT(BRST_Encoder)
BRST_Doc_Encoder_Prepare(
    BRST_Doc  pdf,
    BRST_CSTR encoding_name);

/**

  \ingroup encode
  \brief Get current encoder handle of document object.

  The current encoder is set by invoking BRST_SetCurrentEncoder() and
  it is used to processing a text when application calls BRST_Info_SetInfoAttr().

  The default value is \c NULL.

  \copydoc dox_param_pdf

  \return Encoder object handle or \c NULL.

  \see BRST_Info_SetInfoAttr()
*/
BRST_EXPORT(BRST_Encoder)
BRST_Doc_Encoder_Current(
    BRST_Doc pdf
);

/**

  \ingroup encode
  \brief Set current encoder for document

  \copydoc dox_param_pdf
  \param encoding_name Valid encoding name

  \return Encoder object handle on success, otherwise returns \c NULL and calls error handler.

  \copydoc dox_error_codes

  - \ref BRST_INVALID_DOCUMENT
  - \ref BRST_FAILED_TO_ALLOC_MEM
  - \ref BRST_INVALID_ENCODING_NAME

*/
BRST_EXPORT(BRST_STATUS)
BRST_Doc_Encoder_SetCurrent(
    BRST_Doc  pdf,
    BRST_CSTR encoding_name
);

#endif /* BRST_DOC_ENCODER_H */