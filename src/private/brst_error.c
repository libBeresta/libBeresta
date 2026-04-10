#include "brst_consts.h"
#include "brst_types.h"
#include "brst_error.h"
#include "private/brst_error.h"
#include "private/brst_utils.h"
#include "private/brst_c.h"

struct _BRST_Error_Rec {
    BRST_STATUS error_no;
    BRST_STATUS detail_no;
    BRST_Error_Handler error_fn;
    void* user_data;
} BRST_Error_Rec;

BRST_Error BRST_Error_New()
{
    BRST_Error error = (BRST_Error)BRST_MALLOC(sizeof(BRST_Error_Rec));
    if (error) {
        BRST_MemSet(error, 0, sizeof(BRST_Error_Rec));
        return error;
    } else {
        return 0;
    }
}

void BRST_Error_Free(BRST_Error error)
{
    if (error)
        BRST_FREE(error);
}

void BRST_Error_Init(BRST_Error error,
    void* user_data)
{
    BRST_MemSet(error, 0, sizeof(BRST_Error_Rec));

    error->user_data = user_data;
}

BRST_STATUS
BRST_Error_Code(BRST_Error error)
{
    return error->error_no;
}

BRST_Error_Handler
BRST_Error_ErrorFn(BRST_Error error)
{
    return error->error_fn;
}

void* BRST_Error_UserData(BRST_Error error)
{
    return error->user_data;
}

BRST_STATUS
BRST_Error_DetailCode(BRST_Error error)
{
    return error->detail_no;
}

void BRST_Error_Copy(BRST_Error dst,
    BRST_Error src)
{
    dst->error_no  = src->error_no;
    dst->detail_no = src->detail_no;
    dst->error_fn  = src->error_fn;
    dst->user_data = src->user_data;
}

BRST_STATUS
BRST_Error_Set(BRST_Error error,
    BRST_STATUS error_no,
    BRST_STATUS detail_no)
{
    BRST_PTRACE(" BRST_Error_Set: error_no=0x%04X "
                 "detail_no=0x%04X\n",
        (BRST_UINT)error_no, (BRST_UINT)detail_no);

    error->error_no  = error_no;
    error->detail_no = detail_no;

    return error_no;
}

BRST_STATUS
BRST_Error_Raise(BRST_Error error,
    BRST_STATUS error_no,
    BRST_STATUS detail_no)
{
    BRST_Error_Set(error, error_no, detail_no);

    return BRST_Error_Check(error);
}

void BRST_Error_Reset(BRST_Error error)
{
    error->error_no  = BRST_NOERROR;
    error->detail_no = BRST_NOERROR;
}

void BRST_Error_SetHandler(BRST_Error error,
    BRST_Error_Handler error_fn)
{
    error->error_fn = error_fn;
}
