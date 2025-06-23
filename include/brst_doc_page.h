#ifndef BRST_DOC_PAGE_H
#define BRST_DOC_PAGE_H

/**

  \ingroup doc
  \brief Specify number of pages `Pages` object can own.

  In the default setting, a \ref BRST_Doc object has one `Pages` object as root of pages.
  All `Page` objects are created as a child of `Pages` object. Since `Pages` object can
  own only 8191 child objects, the maximum number of pages are 8191 pages. Additionally,
  the case when there are a lot of "Page" object under one "Pages" object is not good,
  since it causes performance degradation of a viewer application.

  An application can change the setting of a pages tree by invoking BRST_SetPagesConfiguration().
  If `page_per_pages` parameter is set to more than zero, a two-tier pages tree is created.
  A root `Pages` object can own 8191 `Pages` object, and each lower `Pages` object can own
  \c page_per_pages `Page` objects. As a result, the maximum number of pages becomes
  \a 8191 * \a page_per_pages pages. An application cannot invoke BRST_SetPageConfiguration()
  after a page is added to document.

  \copydoc dox_param_pdf
  \param page_per_pages Numbers of pages `Pages` object can own.

  \copydoc dox_return_ok

  \copydoc dox_error_codes

  - \ref BRST_INVALID_DOCUMENT
  - \ref BRST_INVALID_PARAMETER
  - \ref BRST_INVALID_DOCUMENT_STATE
  - \ref BRST_FAILED_TO_ALLOC_MEM

*/
BRST_EXPORT(BRST_STATUS)
BRST_Doc_Pages_SetConfiguration(
    BRST_Doc  pdf,
    BRST_UINT page_per_pages
);


BRST_EXPORT(BRST_Page)
BRST_Doc_Page_ByIndex(
    BRST_Doc  pdf,
    BRST_UINT index
);

/**

  \ingroup page
  \brief Return page display layout.

  \copydoc dox_param_pdf

  \return Page display layout on success. If page layout is not set, returns \ref BRST_PAGE_LAYOUT_EOF.

*/
BRST_EXPORT(BRST_PageLayout)
BRST_Doc_Page_Layout(
    BRST_Doc pdf
);

/**

  \ingroup page
  \brief Set page display layout. If attribute is not set, the setting of the viewer application is used.

  \copydoc dox_param_pdf
  \param layout \parblock One of the following values:

    Layout                                 | Description
    -------                                | -----------
    \ref BRST_PAGE_LAYOUT_SINGLE           | Only one page is displayed
    \ref BRST_PAGE_LAYOUT_ONE_COLUMN       | Display the pages in one column
    \ref BRST_PAGE_LAYOUT_TWO_COLUMN_LEFT  | Display in two columns. Odd page number is displayed left
    \ref BRST_PAGE_LAYOUT_TWO_COLUMN_RIGHT | Display in two columns. Odd page number is displayed right
  \endparblock

  \copydoc dox_return_ok

  \copydoc dox_error_codes

  - \ref BRST_INVALID_DOCUMENT
  - \ref BRST_FAILED_TO_ALLOC_MEM
  - \ref BRST_PAGE_LAYOUT_OUT_OF_RANGE

*/
BRST_EXPORT(BRST_STATUS)
BRST_Doc_Page_SetLayout(
    BRST_Doc        pdf,
    BRST_PageLayout layout
);

/**

  \ingroup page
  \brief Return page display mode.

  \copydoc dox_param_pdf

  \return Page display mode on success.

*/
BRST_EXPORT(BRST_PageMode)
BRST_Doc_Page_Mode(
    BRST_Doc pdf
);

/**

  \ingroup page
  \brief Set document display mode.

  \copydoc dox_param_pdf
  \param mode \parblock One of the following values:

    Mode                            | Description
    -----                           |-------------
    \ref BRST_PAGE_MODE_USE_NONE    | Display the document with neither outline nor thumbnail.
    \ref BRST_PAGE_MODE_USE_OUTLINE | Display the document with outline pane.
    \ref BRST_PAGE_MODE_USE_THUMBS  | Display the document with thumbnail pane.
    \ref BRST_PAGE_MODE_FULL_SCREEN | Display the document with full screen mode.
  \endparblock

  \copydoc dox_return_ok

  \copydoc dox_error_codes

  - \ref BRST_INVALID_DOCUMENT
  - \ref BRST_FAILED_TO_ALLOC_MEM
  - \ref BRST_PAGE_MODE_OUT_OF_RANGE

*/
BRST_EXPORT(BRST_STATUS)
BRST_Doc_Page_SetMode(
    BRST_Doc      pdf,
    BRST_PageMode mode
);

/**

  \ingroup page
  \brief Get handle of current page object

  \copydoc dox_param_pdf

  \return Current page object on success, otherwise returns \c NULL.

*/
BRST_EXPORT(BRST_Page)
BRST_Doc_Page_Current(
    BRST_Doc pdf
);

/**

  \ingroup page
  \brief Create new page and add it after the last page of document

  \copydoc dox_param_pdf

  \return Handle of created page object on success, otherwise, it returns error code and error handler is called.

  \copydoc dox_error_codes

  - \ref BRST_INVALID_DOCUMENT
  - \ref BRST_FAILED_TO_ALLOC_MEM

*/
BRST_EXPORT(BRST_Page)
BRST_Doc_Page_Add(
    BRST_Doc pdf
);

/**

  \ingroup page
  \brief Create new page and insert it just before specified page.

  \copydoc dox_param_pdf
  \param page Specify page handle object to insert newly created page right before.

  \return Handle of created \ref BRST_Page object on success, otherwise, returns \c NULL and error-handler is called.

  \copydoc dox_error_codes

  - \ref BRST_INVALID_DOCUMENT
  - \ref BRST_FAILED_TO_ALLOC_MEM
  - \ref BRST_INVALID_PAGE - An invalid page handle was set.

*/
BRST_EXPORT(BRST_Page)
BRST_Doc_Page_Insert(
    BRST_Doc  pdf,
    BRST_Page page
);

/**

  \ingroup page
  \brief Add page labeling range for document.

  The page label is shown in the thumbnails view.

  \copydoc dox_param_pdf
  \param page_num First page applies labeling range
  \param style \parblock One of the following numbering styles:

  - \ref BRST_PAGE_NUM_STYLE_DECIMAL Arabic numerals (1 2 3 4)
  - \ref BRST_PAGE_NUM_STYLE_UPPER_ROMAN Uppercase roman numerals (I II III IV)
  - \ref BRST_PAGE_NUM_STYLE_LOWER_ROMAN Lowercase roman numerals (i ii iii iv)
  - \ref BRST_PAGE_NUM_STYLE_UPPER_LETTERS Uppercase letters (A B C D)
  - \ref BRST_PAGE_NUM_STYLE_LOWER_LETTERS Lowercase letters (a b c d)
  \endparblock
  \param first_page First page number to use
  \param prefix Prefix for the page label (\c NULL is allowed.)

  \copydoc dox_return_ok

  \copydoc dox_error_codes

  - \ref BRST_INVALID_DOCUMENT
  - \ref BRST_FAILED_TO_ALLOC_MEM Memory allocation failed.
  - \ref BRST_PAGE_NUM_STYLE_OUT_OF_RANGE An invalid page numbering style is specified.

  \par Sample
  \code{.c}
  BRST_AddPageLabel(pdf, 0, BRST_PAGE_NUM_STYLE_LOWER_ROMAN, 1, "");
  BRST_AddPageLabel(pdf, 4, BRST_PAGE_NUM_STYLE_DECIMAL, 1, "");
  BRST_AddPageLabel(pdf, 7, BRST_PAGE_NUM_STYLE_DECIMAL, 8, "A-");
  \endcode

  \par Output
  Pages in document will be labeled as follows:

  \verbatim
  i, ii, iii, iv, 1, 2, 3, A-8, A-9, ...
  \endverbatim

*/
BRST_EXPORT(BRST_STATUS)
BRST_Doc_Page_AddLabel(
    BRST_Doc          pdf,
    BRST_UINT         page_num,
    BRST_PageNumStyle style,
    BRST_UINT         first_page,
    BRST_CSTR         prefix
);

#endif /* BRST_DOC_PAGE_H */