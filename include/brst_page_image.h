#ifndef BRST_PAGE_IMAGE_H
#define BRST_PAGE_IMAGE_H

/**

  \ingroup graphics
  \brief Show an image in one operation.

  \copydoc dox_param_page
  \param image Image object handle
  \param x, y Lower-left point of the region where image is displayed.
  \param width Width of the region where image is displayed.
  \param height Height of the region where image is displayed.

  \copydoc dox_graphics_mode

  \arg Before \ref BRST_GMODE_PAGE_DESCRIPTION
  \arg After \ref BRST_GMODE_PAGE_DESCRIPTION

  \copydoc dox_return_ok

*/
BRST_EXPORT(BRST_STATUS)
BRST_Page_DrawImage(
    BRST_Page  page,
    BRST_Image image,
    BRST_REAL  x,
    BRST_REAL  y,
    BRST_REAL  width,
    BRST_REAL  height
);

#endif /* BRST_PAGE_IMAGE_H */