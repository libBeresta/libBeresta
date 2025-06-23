#ifndef BRST_ERROR_HANDLER_H
#define BRST_ERROR_HANDLER_H

#include "brst_external.h"
#include "brst_types.h"

/*---------------------------------------------------------------------------*/
typedef void
(BRST_STDCALL *BRST_Error_Handler) (
    BRST_STATUS      error_no,
    BRST_STATUS      detail_no,
    BRST_RAW_POINTER user_data
);

#endif /* BRST_ERROR_HANDLER_H */
