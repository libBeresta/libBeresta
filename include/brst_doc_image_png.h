#ifndef BRST_DOC_IMAGE_PNG_H
#define BRST_DOC_IMAGE_PNG_H

/**

  \ingroup image
  \brief Load PNG image from buffer.

  \copydoc dox_param_pdf
  \param buf Pointer to the image data.
  \param size Size of the data in buffer.

  \return Image object handle on success, otherwise, it returns \c NULL and calls error handler.

  \copydoc dox_error_codes

  - \ref BRST_INVALID_DOCUMENT
  - \ref BRST_FAILED_TO_ALLOC_MEM
  - \ref BRST_INVALID_PNG_IMAGE

*/
BRST_EXPORT(BRST_Image)
BRST_Doc_Image_Png_LoadFromMem(
    BRST_Doc         pdf,
    const BRST_BYTE* buf,
    BRST_UINT        size
);

/**

  \ingroup image
  \brief Load external PNG image file.

  \copydoc dox_param_pdf
  \param filename Path to PNG image file.

  \return Image object handle on success, otherwise, it returns \c NULL and calls error handler.

  \copydoc dox_error_codes

  - \ref BRST_INVALID_DOCUMENT
  - \ref BRST_FAILED_TO_ALLOC_MEM
  - \ref BRST_UNSUPPORTED_FUNC
  - \ref BRST_LIBPNG_ERROR
  - \ref BRST_INVALID_PNG_IMAGE

*/
BRST_EXPORT(BRST_Image)
BRST_Doc_Image_Png_LoadFromFile(
    BRST_Doc  pdf,
    BRST_CSTR filename
);

/**

  \ingroup image
  \brief Load external PNG image file.

  Unlike BRST_LoadPngImageFromFile(), BRST_LoadPngImageFromFile2() does not load
  all the data immediately (only size and color properties are loaded).
  The main data are loaded just before the image object is written to PDF, and then loaded data is deleted.

  \copydoc dox_param_pdf
  \param filename Path to PNG image file.

  \return Image object handle on success, otherwise, it returns \c NULL and calls error handler.

  \copydoc dox_error_codes

  - \ref BRST_INVALID_DOCUMENT
  - \ref BRST_FAILED_TO_ALLOC_MEM
  - \ref BRST_UNSUPPORTED_FUNC
  - \ref BRST_LIBPNG_ERROR
  - \ref BRST_INVALID_PNG_IMAGE

*/
BRST_EXPORT(BRST_Image)
BRST_Doc_Image_Png_LoadFromFile2(
    BRST_Doc  pdf,
    BRST_CSTR filename
);

#endif /* BRST_DOC_IMAGE_PNG_H */