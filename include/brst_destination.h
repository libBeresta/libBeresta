#ifndef BRST_DESTINATION_H
#define BRST_DESTINATION_H

#include "brst_external.h"
#include "brst_types.h"
#include "brst_array.h"

typedef BRST_Array BRST_Destination;
 
/**

  \ingroup link
  \brief Define page appearance with three parameters which are \c left, \c top and \c zoom.

  \copydoc dox_param_dst
  \param left The left coordinate of the page.
  \param top  The top coordinate of the page.
  \param zoom The page magnified factor. Value must be between 0.08 (8%) to 32 (3200%).

  \copydoc dox_return_ok

  \copydoc dox_error_codes

  - \ref BRST_INVALID_DESTINATION
  - \ref BRST_INVALID_PARAMETER

*/
BRST_EXPORT(BRST_STATUS)
BRST_Destination_SetXYZ(
    BRST_Destination dst,
    BRST_REAL        left,
    BRST_REAL        top,
    BRST_REAL        zoom
);

/**

  \ingroup link
  \brief Set page appearance to display entire page within the window.

  \copydoc dox_param_dst

  \copydoc dox_return_ok

  \copydoc dox_error_codes

  - \ref BRST_INVALID_DESTINATION

*/
BRST_EXPORT(BRST_STATUS)
BRST_Destination_SetFit(
    BRST_Destination dst
);

/**

  \ingroup link
  \brief Define page appearance to fit page width within the window and set top position of the page \c top parameter.

  \copydoc dox_param_dst
  \param top Top coordinate of the page.

  \copydoc dox_return_ok

  \copydoc dox_error_codes

  - \ref BRST_INVALID_DESTINATION
  - \ref BRST_INVALID_PARAMETER

*/
BRST_EXPORT(BRST_STATUS)
BRST_Destination_SetFitH(
    BRST_Destination dst,
    BRST_REAL        top
);

/**

  \ingroup link
  \brief Define page appearance to fit page height within the window and set left position of the page \c left parameter.

  \copydoc dox_param_dst
  \param left Left coordinate of the page.

  \copydoc dox_return_ok

  \copydoc dox_error_codes

  - \ref BRST_INVALID_DESTINATION
  - \ref BRST_INVALID_PARAMETER

*/
BRST_EXPORT(BRST_STATUS)
BRST_Destination_SetFitV(
    BRST_Destination dst,
    BRST_REAL        left
);

/**

  \ingroup link
  \brief Define page appearance to fit page within the rectangle specified by \c left, \c bottom, \c right and \c top.

  \copydoc dox_param_dst
  \param left Left coordinate of the page.
  \param bottom Bottom coordinate of the page.
  \param right Right coordinate of the page.
  \param top Top coordinate of the page.

  \copydoc dox_return_ok

  \copydoc dox_error_codes

  - \ref BRST_INVALID_DESTINATION
  - \ref BRST_INVALID_PARAMETER

*/
BRST_EXPORT(BRST_STATUS)
BRST_Destination_SetFitR(
    BRST_Destination dst,
    BRST_REAL        left,
    BRST_REAL        bottom,
    BRST_REAL        right,
    BRST_REAL        top
);

/**

  \ingroup link
  \brief Define page appearance to fit page bounding box  within the window.

  \copydoc dox_param_dst

  \copydoc dox_return_ok

  \copydoc dox_error_codes

  - \ref BRST_INVALID_DESTINATION

*/
BRST_EXPORT(BRST_STATUS)
BRST_Destination_SetFitB(
    BRST_Destination dst
);

/**

  \ingroup link
  \brief Define page appearance to fit page bounding box width within the window and set top position of page to value of \c top parameter.

  \copydoc dox_param_dst
  \param top Top coordinate of the page.

  \copydoc dox_return_ok

  \copydoc dox_error_codes

  - \ref BRST_INVALID_DESTINATION
  - \ref BRST_INVALID_PARAMETER

*/
BRST_EXPORT(BRST_STATUS)
BRST_Destination_SetFitBH(
    BRST_Destination dst,
    BRST_REAL        top
);

/**

  \ingroup link
  \brief Define page appearance to fit page bounding box height within the window and set left position of page to value of \c left parameter.

  \copydoc dox_param_dst
  \param left Left coordinate of the page.

  \copydoc dox_return_ok

  \copydoc dox_error_codes

  - \ref BRST_INVALID_DESTINATION
  - \ref BRST_INVALID_PARAMETER

*/
BRST_EXPORT(BRST_STATUS)
BRST_Destination_SetFitBV(
    BRST_Destination dst,
    BRST_REAL        left
);

#endif /* BRST_DESTINATION_H */