#ifndef BRST_IMAGE_H
#define BRST_IMAGE_H

#include "brst_dict.h"

typedef BRST_Dict BRST_Image;

BRST_EXPORT(BRST_STATUS)
BRST_Image_AddSMask(
    BRST_Image image,
    BRST_Image smask
);

/**

  \ingroup image
  \brief Get size of the image of an image object.

  \copydoc dox_param_image

  \return \ref BRST_Point structure which includes image size, otherwise it returns `BRST_Point{0, 0}`.

*/
BRST_EXPORT(BRST_Point)
BRST_Image_Size(
    BRST_Image image
);

/**

  \ingroup image
  \brief Get size of the image of an image object to parameter.

  In contrast with BRST_Image_Size() this function returns \ref BRST_OK on success and writes size value to \c size parameter.

  \copydoc dox_param_image
  \param size Variable to return size of image to.

  \copydoc dox_return_ok

  \copydoc dox_error_codes

  - \ref BRST_INVALID_IMAGE

*/
BRST_EXPORT(BRST_STATUS)
BRST_Image_Size2(
    BRST_Image  image,
    BRST_Point* size
);

/**

  \ingroup image
  \brief Get image width of an image object.

  \copydoc dox_param_image

  \return Image width on success, otherwise it returns \c 0.

*/
BRST_EXPORT(BRST_UINT)
BRST_Image_Width(
    BRST_Image image
);

/**

  \ingroup image
  \brief Get image height of an image object.

  \copydoc dox_param_image

  \return Image height on success, otherwise it returns \c 0.

*/
BRST_EXPORT(BRST_UINT)
BRST_Image_Height(
    BRST_Image image
);

/**

  \ingroup image
  \brief Get bit count used to describe each color component.

  \copydoc dox_param_image

  \return Bit count on success, otherwise it returns \c 0.

*/
BRST_EXPORT(BRST_UINT)
BRST_Image_BitsPerComponent(
    BRST_Image image
);

/**

  \ingroup image
  \brief Get image color space name.

  \copydoc dox_param_image

  \return Color space name on success, otherwise it returns \c NULL.

  \see \ref colorspaces

*/
BRST_EXPORT(BRST_CSTR)
BRST_Image_ColorSpace(
    BRST_Image image
);

/**

  \ingroup image
  \brief Sets transparent color of the image by the RGB range values.

  The color within the range is displayed as a transparent color. The \c image must have RGB color space.

  \copydoc dox_param_image
  \param rmin, rmax Lower and upper limits of red color. Must be in a range \c 0 and \c 255.
  \param gmin, gmax Lower and upper limits of green color. Must be in a range \c 0 and \c 255.
  \param bmin, bmax Lower and upper limits of blue color. Must be in a range \c 0 and \c 255.

  \copydoc dox_return_ok

  \copydoc dox_error_codes

  - \ref BRST_INVALID_IMAGE
  - \ref BRST_INVALID_COLOR_SPACE
  - \ref BRST_FAILED_TO_ALLOC_MEM
  - \ref BRST_INVALID_PARAMETER

*/
BRST_EXPORT(BRST_STATUS)
BRST_Image_SetColorMask(
    BRST_Image image,
    BRST_UINT  rmin,
    BRST_UINT  rmax,
    BRST_UINT  gmin,
    BRST_UINT  gmax,
    BRST_UINT  bmin,
    BRST_UINT  bmax
);

/**

  \ingroup image
  \brief Set image mask

  \copydoc dox_param_image
  \param mask_image Specify image object handle which is used as image mask. This image must be 1-bit gray-scale color image.

  \copydoc dox_return_ok

  \copydoc dox_error_codes

  - \ref BRST_INVALID_IMAGE
  - \ref BRST_INVALID_BIT_PER_COMPONENT
  - \ref BRST_FAILED_TO_ALLOC_MEM

*/
BRST_EXPORT(BRST_STATUS)
BRST_Image_SetMaskImage(
    BRST_Image image,
    BRST_Image mask_image
);

#endif /* BRST_IMAGE_H */