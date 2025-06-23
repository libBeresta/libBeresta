#ifndef BRST_PAGE_XOBJECT_H
#define BRST_PAGE_XOBJECT_H

/**

  \ingroup graphics
  \brief Draw XObject using current graphics context.

  This is used by BRST_Page_DrawImage() to draw the \ref BRST_Image by first calling
  BRST_Page_GSave() and BRST_Page_Concat() and then calling BRST_Page_GRestore() 
  after BRST_Page_XObject_Execute(). It could be used manually to rotate an image.

  \copydoc dox_param_page
  \param obj XObject handle like an image.

  \copydoc dox_graphics_mode

  \arg Before \ref BRST_GMODE_PAGE_DESCRIPTION
  \arg After \ref BRST_GMODE_PAGE_DESCRIPTION

  \copydoc dox_return_ok

  \copydoc dox_pdf_cmd
  \c Do

*/
BRST_EXPORT(BRST_STATUS)
BRST_Page_XObject_Execute(
    BRST_Page    page,
    BRST_XObject obj
);

#endif /* BRST_PAGE_XOBJECT_H */