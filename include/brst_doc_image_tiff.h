#ifndef BRST_DOC_IMAGE_TIFF_H
#define BRST_DOC_IMAGE_TIFF_H

BRST_EXPORT(BRST_Image)
BRST_Doc_Image_Raw1Bit_LoadFromMem(
    BRST_Doc         pdf,
    const BRST_BYTE* buf,
    BRST_UINT        width,
    BRST_UINT        height,
    BRST_UINT        line_width,
    BRST_BOOL        black_is1,
    BRST_BOOL        top_is_first
);

/**

  \ingroup image
  \brief Load raw format image.

  This function loads image data from file without any conversion, it is usually faster than the other functions.

  \copydoc dox_param_pdf
  \param filename Path to image file
  \param width Width of image file
  \param height Height of image file
  \param color_space One of \ref BRST_CS_DEVICE_GRAY, \ref BRST_CS_DEVICE_RGB or \ref BRST_CS_DEVICE_CMYK values.

  \return Image object handle on success, otherwise, it returns \c NULL and call error handler.

  \copydoc dox_error_codes

  - \ref BRST_INVALID_DOCUMENT
  - \ref BRST_FAILED_TO_ALLOC_MEM
  - \ref BRST_INVALID_COLOR_SPACE
  - \ref BRST_INVALID_IMAGE
  - \ref BRST_FILE_IO_ERROR

  \see \ref colorspaces, BRST_LoadRawImageFromMem()
*/
BRST_EXPORT(BRST_Image)
BRST_Doc_Image_Raw_LoadFromFile(
    BRST_Doc        pdf,
    BRST_CSTR       filename,
    BRST_UINT       width,
    BRST_UINT       height,
    BRST_ColorSpace color_space
);

/**

  \ingroup image
  \brief Load raw format image.

  This function loads image data from buffer without any conversion, it is usually faster than the other functions.

  \copydoc dox_param_pdf
  \param buf Pointer to image data
  \param width Width of image file
  \param height Height of image file
  \param color_space One of \ref BRST_CS_DEVICE_GRAY, \ref BRST_CS_DEVICE_RGB or \ref BRST_CS_DEVICE_CMYK values.
  \param bits_per_component Bit size of each color component. Valid values are \a 1, \a 2, \a 4 and \a 8.

  \return Image object handle on success, otherwise, it returns \c NULL and call error handler.

  \copydoc dox_error_codes

  - \ref BRST_INVALID_DOCUMENT
  - \ref BRST_FAILED_TO_ALLOC_MEM
  - \ref BRST_INVALID_COLOR_SPACE
  - \ref BRST_INVALID_IMAGE

  \see \ref colorspaces, BRST_LoadRawImageFromFile()

*/
BRST_EXPORT(BRST_Image)
BRST_Doc_Image_Raw_LoadFromMem(
    BRST_Doc         pdf,
    const BRST_BYTE* buf,
    BRST_UINT        width,
    BRST_UINT        height,
    BRST_ColorSpace  color_space,
    BRST_UINT        bits_per_component
);

#endif /* BRST_DOC_IMAGE_TIFF_H */