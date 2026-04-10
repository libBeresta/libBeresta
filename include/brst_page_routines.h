#ifndef BRST_PAGE_ROUTINES_H
#define BRST_PAGE_ROUTINES_H

#include "brst_external.h"
#include "brst_types.h"
#include "brst_dict.h"

#ifdef LIBBRST_ISO_216_ONLY
#include "brst_page_sizes_iso_216.h"
#else
#include "brst_page_sizes.h"
#endif

#include "brst_mmgr.h"
#include "brst_destination.h"

BRST_EXPORT(BRST_MMgr)
BRST_Page_MMgr(BRST_Page page);

/**

  \ingroup page
  \brief Change page width.

  \copydoc dox_param_page
  \param value New page width. Valid values are between \c 3 and \c 14400.

  \copydoc dox_return_ok

  \copydoc dox_error_codes

  - \ref BRST_INVALID_PAGE
  - \ref BRST_PAGE_INVALID_SIZE
  - \ref BRST_FAILED_TO_ALLOC_MEM

*/
BRST_EXPORT(BRST_STATUS)
BRST_Page_SetWidth(
    BRST_Page   page,
    BRST_REAL   value
);

/**

  \ingroup page
  \brief Change page height.

  \copydoc dox_param_page
  \param value New page height. Valid values are between \c 3 and \c 14400.

  \copydoc dox_return_ok

  \copydoc dox_error_codes

  - \ref BRST_INVALID_PAGE
  - \ref BRST_PAGE_INVALID_SIZE
  - \ref BRST_FAILED_TO_ALLOC_MEM

*/
BRST_EXPORT(BRST_STATUS)
BRST_Page_SetHeight(
    BRST_Page page,
    BRST_REAL value
);

BRST_EXPORT(BRST_STATUS)
BRST_Page_SetBoundary(
    BRST_Page         page,
    BRST_PageBoundary boundary,
    BRST_REAL         left,
    BRST_REAL         bottom,
    BRST_REAL         right,
    BRST_REAL         top
);

/**

  \ingroup page
  \brief Change page size and direction to a predefined ones.

  \copydoc dox_param_page
  \param size Specify a predefined page size value. See \ref _BRST_PageSizes.
  \param direction Specify the direction of the page.

  \copydoc dox_return_ok

  \copydoc dox_error_codes

  - \ref BRST_INVALID_PAGE
  - \ref BRST_PAGE_INVALID_SIZE
  - \ref BRST_PAGE_INVALID_DIRECTION
  - \ref BRST_FAILED_TO_ALLOC_MEM

*/
BRST_EXPORT(BRST_STATUS)
BRST_Page_SetSize(
    BRST_Page            page,
    BRST_PageSizes       size,
    BRST_PageOrientation orientation
);

/**

  \ingroup page
  \brief Set rotation angle of the page.

  \copydoc dox_param_page
  \param angle Specify the rotation angle of the page. It must be a multiple of \c 90 degrees.

  \copydoc dox_return_ok

  \copydoc dox_error_codes

  - \ref BRST_INVALID_PAGE
  - \ref BRST_PAGE_INVALID_ROTATE_VALUE

*/
BRST_EXPORT(BRST_STATUS)
BRST_Page_SetRotate(
    BRST_Page   page,
    BRST_UINT16 angle
);

/**

  \ingroup page
  \brief Configure slide transition of the page.

  \copydoc dox_param_page
  \param type The transition style. See \ref BRST_TransitionStyle.
  \param disp_time Page display duration (in seconds).
  \param trans_time Transition effect duration (in seconds). Default is 1 second.

  \copydoc dox_return_ok

*/
BRST_EXPORT(BRST_STATUS)
BRST_Page_SetSlideShow(
    BRST_Page            page,
    BRST_TransitionStyle type,
    BRST_REAL            disp_time,
    BRST_REAL            trans_time
);

/**

  \ingroup graphics
  \brief Set text horizontal scaling.

  \copydoc dox_param_page
  \param value Value of horizontal scaling (initially \c 100).

  \copydoc dox_graphics_mode

  \arg Before \ref BRST_GMODE_PAGE_DESCRIPTION or \ref BRST_GMODE_TEXT_OBJECT
  \arg After \ref BRST_GMODE_PAGE_DESCRIPTION or \ref BRST_GMODE_TEXT_OBJECT

  \copydoc dox_return_ok

  \todo Deprecate and rename function

  \copydoc dox_pdf_cmd
  \c Tz

*/
BRST_EXPORT(BRST_STATUS)
BRST_Page_SetHorizontalScaling(
    BRST_Page page,
    BRST_REAL value
);

/**

  \ingroup page
  \brief Get page current graphics state stack depth.

  \copydoc dox_param_page

  \return Page current graphics state stack depth on success, otherwise it returns \c 0.

  \see \ref BRST_LIMIT_MAX_GSTATE, BRST_GState_New()

*/
BRST_EXPORT(BRST_UINT)
BRST_Page_GStateDepth(
    BRST_Page page
);

/**

  \ingroup page
  \brief Get page current horizontal scaling value for text showing.

  \copydoc dox_param_page

  \return Page current horizontal scaling value for text showing on success, otherwise it returns \ref BRST_DEF_HSCALING.

  \todo Deprecate and rename function

*/
BRST_EXPORT(BRST_REAL)
BRST_Page_HorizontalScaling(
    BRST_Page page
);

BRST_EXPORT(BRST_STATUS)
BRST_Page_SetZoom(
    BRST_Page page,
    BRST_REAL zoom
);

/**

  \ingroup page
  \brief Get page width.

  \copydoc dox_param_page

  \return Page width on success, otherwise returns \c 0.

*/
BRST_EXPORT(BRST_REAL)
BRST_Page_Width(
    BRST_Page page
);

/**

  \ingroup page
  \brief Get page height.

  \copydoc dox_param_page

  \return Page height on success, otherwise returns \c 0.

*/
BRST_EXPORT(BRST_REAL)
BRST_Page_Height(
    BRST_Page page
);

/**

  \ingroup page
  \brief Get current graphics mode.

  \copydoc dox_param_page

  \return Current graphics mode of the page on success, otherwise returns \c 0.

*/
BRST_EXPORT(BRST_UINT16)
BRST_Page_GMode(
    BRST_Page page
);

/**

  \ingroup page
  \brief Get current position for path painting.

  Application can call BRST_Page_CurrentPos() only when graphics mode is \ref BRST_GMODE_PATH_OBJECT.

  \copydoc dox_param_page

  \return \ref BRST_Point struct with current position for path painting of the page. Otherwise it returns `BRST_Point{0, 0}`.

  \copydoc dox_error_codes

  - \ref BRST_INVALID_PAGE

*/
BRST_EXPORT(BRST_Point)
BRST_Page_CurrentPos(
    BRST_Page page
);


BRST_EXPORT(BRST_STATUS)
BRST_Page_CurrentPos2(
    BRST_Page   page,
    BRST_Point* pos
);

BRST_EXPORT(BRST_MMgr)
BRST_Page_MMgr(
    BRST_Page page
);

/**

  \ingroup page
  \brief Create new content stream on the page.

  The call can return a reference to the new content stream in \c new_stream.
  This reference can be used on a later pages to call BRST_Page_Insert_Shared_Content_Stream().

  The use case is when you need to place a considerable amount of identical content on multiple pages.
  On the first occurrence of the content, call BRST_Page_New_Content_Stream() before you start creating
  the content in order to place the content in a separate stream.
  Call BRST_Page_New_Content_Stream() again after you have finished the content.
  Then, on subsequent pages, call BRST_Page_Insert_Shared_Content_Stream() to place the content on that page.

  \copydoc dox_param_page
  \param new_stream Reference to \ref BRST_Dict identifying new stream.

  \copydoc dox_return_ok

  \see BRST_Page_Insert_Shared_Content_Stream()

*/
BRST_EXPORT(BRST_STATUS)
BRST_Page_New_Content_Stream(
    BRST_Page  page,
    BRST_Dict* new_stream
);

/**

  \ingroup page
  \brief Insert content stream to the page.

  \copydoc dox_param_page
  \param shared_stream Reference to \ref BRST_Dict, previously created by BRST_Page_New_Content_Stream()

  \copydoc dox_return_ok

  \see BRST_Page_Insert_Shared_Content_Stream()

*/
BRST_EXPORT(BRST_STATUS)
BRST_Page_Insert_Shared_Content_Stream(
    BRST_Page page,
    BRST_Dict shared_stream
);

/**
  \ingroup page
  \brief Write raw commands to page stream
  This command allow user to write some data to page stream unconditionally.

  \copydoc dox_param_page
  \param data Data to be written to page stream

  \copydoc dox_return_ok

  \copydoc dox_error_codes

  - \ref BRST_INVALID_PAGE

  \warning This command is dangerous! Use it with caution, library does not validate input.

*/
BRST_EXPORT(BRST_STATUS)
BRST_Page_RawWrite(
    BRST_Page page,
    BRST_CSTR data
);

/**

  \ingroup graphics
  \brief Apply graphics state to page

  \copydoc dox_param_page
  \param ext_gstate Extended graphics state object handle.

  \copydoc dox_graphics_mode
  \arg Before \ref BRST_GMODE_PAGE_DESCRIPTION
  \arg After \ref BRST_GMODE_PAGE_DESCRIPTION

  \copydoc dox_return_ok

  \copydoc dox_pdf_cmd
  \c gs

*/
BRST_EXPORT(BRST_STATUS)
BRST_Page_SetExtGState(
    BRST_Page      page,
    BRST_ExtGState ext_gstate
);


/**

  \ingroup link
  \brief Create new destination object for the page.

  \copydoc dox_param_page

  \return New destination object handle. If it failed, it returns \c NULL.

  \copydoc dox_error_codes

  - \ref BRST_INVALID_DOCUMENT
  - \ref BRST_FAILED_TO_ALLOC_MEM

*/
BRST_EXPORT(BRST_Destination)
BRST_Page_CreateDestination(
    BRST_Page page
);

#endif /* BRST_PAGE_ROUTINES_H */
