#ifndef BRST_DOC_STREAM_H
#define BRST_DOC_STREAM_H

/**

  \ingroup doc
  \brief Gets the size of the temporary stream of the document.

  \copydoc dox_param_pdf

  \return \parblock One of the values:
  - Size of the temporary stream on success.
  - \ref BRST_FALSE if temporary stream is invalid or document is invalid
  - \ref BRST_INVALID_DOCUMENT
  \endparblock

  \see
    BRST_HasDoc()
    BRST_Stream_Validate()

*/
BRST_EXPORT(BRST_UINT32)
BRST_Doc_Stream_Size(
    BRST_Doc pdf
);

/**

  \ingroup doc
  \brief Copies the data from the temporary stream of the document into buffer \c buf.

  \copydoc dox_param_pdf
  \param buf Pointer to the buffer.
  \param size The size of buffer.
  After BRST_ReadFromStream() is executed, the number of bytes read is set into \c size.

  \return \ref BRST_OK or \ref BRST_STREAM_EOF on success, otherwise, it returns error-code and error-handler is invoked.

  \copydoc dox_error_codes

  - \ref BRST_INVALID_DOCUMENT
  - \ref BRST_INVALID_OPERATION
  - \ref BRST_INVALID_PARAMETER

  \note Even if the result of BRST_ReadFromStream() is \ref BRST_STREAM_EOF, if the value of \c size parameter is more than 0, data is read into the buffer.

*/
BRST_EXPORT(BRST_STATUS)
BRST_Doc_Stream_Read(
    BRST_Doc     pdf,
    BRST_BYTE*   buf,
    BRST_UINT32* size
);

/**

  \ingroup doc
  \brief Rewind temporary stream of the document.

  \copydoc dox_param_pdf

  \copydoc dox_return_ok

  \copydoc dox_error_codes

  - \ref BRST_INVALID_DOCUMENT
  - \ref BRST_INVALID_OPERATION

*/
BRST_EXPORT(BRST_STATUS)
BRST_Doc_Stream_Reset(
    BRST_Doc pdf
);

#endif /* BRST_DOC_STREAM_H */