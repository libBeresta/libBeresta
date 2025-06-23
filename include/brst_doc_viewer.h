#ifndef BRST_DOC_VIEWER_H
#define BRST_DOC_VIEWER_H

/**

  \ingroup page
  \brief Set the first page to appear when a document is opened.

  \copydoc dox_param_pdf
  \param open_action Set a valid destination object.

  \copydoc dox_return_ok

  \copydoc dox_error_codes

  - \ref BRST_INVALID_DOCUMENT
  - \ref BRST_FAILED_TO_ALLOC_MEM
  - \ref BRST_INVALID_DESTINATION
  - \ref BRST_PAGE_MODE_OUT_OF_RANGE

*/
BRST_EXPORT(BRST_STATUS)
BRST_Doc_SetOpenAction(
    BRST_Doc         pdf,
    BRST_Destination open_action
);


BRST_EXPORT(BRST_UINT)
BRST_Doc_ViewerPreference(
    BRST_Doc pdf
);

BRST_EXPORT(BRST_STATUS)
BRST_Doc_SetViewerPreference(
    BRST_Doc  pdf,
    BRST_UINT value
);

#endif /* BRST_DOC_VIEWER_H */