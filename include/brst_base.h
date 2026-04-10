#ifndef BRST_BASE_H
#define BRST_BASE_H

#include "brst_external.h"
#include "brst_types.h"
#include "brst_doc.h"
#include "brst_error_handler.h"
#include "brst_mmgr.h"
#include "brst_dict.h"
#include "brst_page.h"

#ifdef LIBBRST_ISO_216_ONLY
#include "brst_page_sizes_iso_216.h"
#else
#include "brst_page_sizes.h"
#endif


BRST_EXPORT(const char *)
BRST_Version(
    void
);

/**

  \ingroup doc
  \brief Create an instance of a document object and initialize it.

  \param user_error_fn User-defined error handler which is invoked when an error occurred.
  \param user_alloc_fn User-defined memory allocation function. If \c NULL is specified, `malloc()` is used.
  \param user_free_fn  User-defined memory freeing function. If \c NULL is specified, `free()` is used.
  \param mem_pool_buf_size \parblock \c libBeresta does not use memory pool by default.

  A memory allocation function is called on demand from an application.

  If this parameter set to non-zero value, memory management will be done as following:
  - Memory is allocated per \c mem_pool_buf_size.
  - Memory manager gives memory of requested size to an application, and pools remaining memory to use at next request.
  - If the size of requested memory is larger than the remaining memory, a new memory block is allocated.
  - Unused memory is not released immediately. It is released all together when BRST_Free() is invoked.
  \endparblock
  \param user_data User-defined void pointer. This pointer is used by error handling.

  \return A handle of document object on success and \c NULL on failure.

  \see
    BRST_Doc_New()
    BRST_Doc_Free()

*/
BRST_EXPORT(BRST_Doc)
BRST_Doc_New_Ex(
    BRST_Error_Handler user_error_fn,
    BRST_Alloc_Func    user_alloc_fn,
    BRST_Free_Func     user_free_fn,
    BRST_UINT          mem_pool_buf_size,
    BRST_RAW_POINTER   user_data
);

/**

  \ingroup doc
  \brief Create an instance of a document object and initialize it.

  \param user_error_fn User-defined error handler which is invoked when an error occurred.
  \param user_data User-defined void pointer. This pointer is used by error handling.

  \return A handle of document object on success and \c NULL on failure.

  \see
    BRST_Doc_New_Ex()
    BRST_Doc_Free()

  \note Same as \code{.c}
  BRST_Doc_New_Ex(user_error_fn, NULL, NULL, 0, user_data)
  \endcode

*/
BRST_EXPORT(BRST_Doc)
BRST_Doc_New(
    BRST_Error_Handler user_error_fn,
    void*              user_data
);

BRST_EXPORT(BRST_Doc)
BRST_Doc_New_Empty(
);

/**

  \ingroup doc
  \brief Revoke a document object and all resources.

  \copydoc dox_param_pdf

  \see
    BRST_Doc_New()
    BRST_Doc_New_Ex()

*/
BRST_EXPORT(void)
BRST_Doc_Free(
    BRST_Doc pdf
);

/**

  \ingroup doc
  \brief Create a new document. If \c doc object already has a document, the current document is revoked.

  \copydoc dox_param_pdf

  \copydoc dox_return_ok

  \copydoc dox_error_codes

  - \ref BRST_INVALID_DOCUMENT
  - \ref BRST_FAILED_TO_ALLOC_MEM

  \see
    BRST_Doc_Destroy()

*/
BRST_EXPORT(BRST_STATUS)
BRST_Doc_Initialize(
    BRST_Doc pdf
);

/**

  \ingroup doc
  \brief Revoke the current document.

  BRST_Doc_Destroy() keeps and recycles loaded resources (such as fonts and encodings) when new document requires these resources.

  \copydoc dox_param_pdf

  \see
    BRST_Doc_Initialize()
    BRST_Doc_Destroy_All()

*/
BRST_EXPORT(void)
BRST_Doc_Destroy(
    BRST_Doc pdf
);

/**

  \ingroup doc
  \brief Check if document handle is valid

  \copydoc dox_param_pdf

  \return \ref BRST_TRUE if the specified document handle is valid. Otherwise return \ref BRST_FALSE, set error code and call error handler.

  \copydoc dox_error_codes

  - \ref BRST_INVALID_DOCUMENT

  \see
    BRST_Doc_Initialize()

*/
BRST_EXPORT(BRST_BOOL)
BRST_Doc_Initialized(
    BRST_Doc pdf
);

/**

  \ingroup doc
  \brief Revoke the current document.

  BRST_Doc_Destroy_All() revokes the current document and all resources.

  \copydoc dox_param_pdf

  \see
    BRST_Doc_Initialize()
    BRST_Doc_Destroy()

*/
BRST_EXPORT(void)
BRST_Doc_Destroy_All(
    BRST_Doc pdf
);

BRST_EXPORT(BRST_STATUS)
BRST_Doc_Contents(
    BRST_Doc     pdf,
    BRST_BYTE*   buf,
    BRST_UINT32* size
);

BRST_EXPORT(BRST_MMgr)
BRST_Doc_MMgr(
    BRST_Doc doc
);

BRST_EXPORT(BRST_REAL)
BRST_PageSize_Width(
    BRST_PageSizes size,
    BRST_PageOrientation orientation
);

BRST_EXPORT(BRST_REAL)
BRST_PageSize_Height(
    BRST_PageSizes size,
    BRST_PageOrientation orientation
);

#endif /* BRST_BASE_H */
