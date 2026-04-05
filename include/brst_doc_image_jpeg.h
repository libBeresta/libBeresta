#ifndef BRST_DOC_IMAGE_JPEG_H
#define BRST_DOC_IMAGE_JPEG_H

/**

  \ingroup image
  \brief Load external JPEG image file.

  \copydoc dox_param_pdf
  \param filename Path to JPEG image file.

  \return Image object handle on success, otherwise, it returns \c NULL and calls error handler.

  \copydoc dox_error_codes

  - \ref BRST_INVALID_DOCUMENT
  - \ref BRST_FAILED_TO_ALLOC_MEM
  - \ref BRST_INVALID_JPEG_DATA
  - \ref BRST_UNSUPPORTED_JPEG_FORMAT

  \see BRST_LoadJpegImageFromMem()

*/
BRST_EXPORT(BRST_Image)
BRST_Doc_Image_Jpeg_LoadFromFile(
    BRST_Doc  pdf,
    BRST_CSTR filename
);

/**
  \ingroup image
  \brief Load JPEG image from buffer.

  \copydoc dox_param_pdf
  \param buf Pointer to the image data.
  \param size Size of the data in buffer.

  \return Image object handle on success, otherwise, it returns \c NULL and calls error handler.

  \copydoc dox_error_codes

  - \ref BRST_INVALID_DOCUMENT
  - \ref BRST_FAILED_TO_ALLOC_MEM
  - \ref BRST_INVALID_JPEG_DATA
  - \ref BRST_UNSUPPORTED_JPEG_FORMAT

  \see BRST_LoadJpegImageFromFile()

*/
BRST_EXPORT(BRST_Image)
BRST_Doc_Image_Jpeg_LoadFromMemory(
    BRST_Doc         pdf,
    const BRST_BYTE* buf,
    BRST_UINT        size
);

#endif /* BRST_DOC_IMAGE_JPEG_H */