#ifndef PRIVATE_BRST_ERROR_H
#define PRIVATE_BRST_ERROR_H

#include "brst_error.h"
#include "brst_types.h"
#include "brst_error_handler.h"

struct BRST_Error_Rec;
typedef struct BRST_Error_Rec* BRST_Error;

BRST_Error
BRST_Error_New();

void 
BRST_Error_Free();

/*  BRST_Error_Init
 *
 *  if error_fn is NULL, the default-handlers are set as error-handler.
 *  user_data is used to identify the object which threw an error.
 *
 */
void
BRST_Error_Init(
    BRST_Error error,
    void*      user_data
);

void
BRST_Error_Reset(
    BRST_Error error
);

BRST_STATUS
BRST_Error_Code(
    BRST_Error error
);

BRST_STATUS
BRST_Error_DetailCode(
    BRST_Error error
);

BRST_STATUS
BRST_Error_Set(
    BRST_Error  error,
    BRST_STATUS error_no,
    BRST_STATUS detail_no
);

BRST_STATUS
BRST_Error_Raise(
    BRST_Error  error,
    BRST_STATUS error_no,
    BRST_STATUS detail_no
);

void BRST_Error_SetHandler(
    BRST_Error error,
    BRST_Error_Handler error_fn
);

BRST_Error_Handler
BRST_Error_ErrorFn(
    BRST_Error error
);

void*
BRST_Error_UserData(
    BRST_Error error
);

#endif /* PRIVATE_BRST_ERROR_H */