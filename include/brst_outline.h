#ifndef BRST_OUTLINE_H
#define BRST_OUTLINE_H

#include "brst_types.h"
#include "brst_dict.h"
#include "brst_destination.h"

#define BRST_OUTLINE_CLOSED     0
#define BRST_OUTLINE_OPENED     1

typedef BRST_Dict BRST_Outline;

/**

  \ingroup outline
  \brief Set whether this outline node is opened when the outline is displayed for the first time.

  \copydoc dox_param_outline
  \param opened Specify whether outline node is opened or not.

  \copydoc dox_return_ok

  \copydoc dox_error_codes

  - \ref BRST_INVALID_OUTLINE
  - \ref BRST_FAILED_TO_ALLOC_MEM

*/
BRST_EXPORT(BRST_STATUS)
BRST_Outline_SetOpened(
    BRST_Outline outline,
    BRST_BOOL    opened
);

/**

  \ingroup outline
  \brief Set target destination object to jump to when outline object is clicked.

  \copydoc dox_param_outline
  \param dst Destination object handle

  \copydoc dox_return_ok

  \copydoc dox_error_codes

  - \ref BRST_INVALID_OUTLINE
  - \ref BRST_FAILED_TO_ALLOC_MEM
  - \ref BRST_INVALID_DESTINATION

*/
BRST_EXPORT(BRST_STATUS)
BRST_Outline_SetDestination(
    BRST_Outline     outline,
    BRST_Destination dst
);

#endif /* BRST_OUTLINE_H */