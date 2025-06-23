#ifndef BRST_DOC_OUTLINE_H
#define BRST_DOC_OUTLINE_H

/**

  \ingroup outline
  \brief Create new outline object.

  \copydoc dox_param_pdf
  \param parent Outline object handle which comes to the parent of the created outline object. If \c NULL, the outline is created as a root outline.
  \param title Caption of the outline object.
  \param encoder Encoding object handle applied to the title. If \c NULL, PDFDocEncoding is used.

  \return Created outline object handle on success, otherwise, it returns \c NULL and calls error handler.

  \copydoc dox_error_codes

  - \ref BRST_INVALID_DOCUMENT
  - \ref BRST_FAILED_TO_ALLOC_MEM
  - \ref BRST_INVALID_OUTLINE

  \todo Clarify which object is returned when encoder is \c NULL

*/
BRST_EXPORT(BRST_Outline)
BRST_Doc_Outline_Create(
    BRST_Doc     pdf,
    BRST_Outline parent,
    BRST_CSTR    title,
    BRST_Encoder encoder
);

#endif /* BRST_DOC_OUTLINE_H */