#ifndef PRIVATE_BRST_MMGR_H
#define PRIVATE_BRST_MMGR_H

#include "brst_types.h"
#include "brst_mmgr.h"
#include "brst_error.h"

typedef struct _BRST_MPool_Node_Rec* BRST_MPool_Node;

/*  BRST_MMgr_New
 *
 *  create new BRST_MMgr object. When memory allocation goes wrong,
 *  it returns NULL and error handling function will be called.
 *  if buf_size is non-zero, mmgr is configured to be using memory-pool
 */
BRST_MMgr
BRST_MMgr_New(
    BRST_Error      error,
    BRST_UINT       buf_size,
    BRST_Alloc_Func alloc_fn,
    BRST_Free_Func  free_fn
);

void
BRST_MMgr_Free(
    BRST_MMgr mmgr
);

void*
BRST_GetMem(
    BRST_MMgr mmgr,
    BRST_UINT size
);

void
BRST_FreeMem(
    BRST_MMgr mmgr,
    void*     aptr
);

BRST_Error
BRST_MMgr_Error(
    BRST_MMgr mmgr
);

#endif /* PRIVATE_BRST_MMGR_H */