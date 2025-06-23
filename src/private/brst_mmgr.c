#include "brst_types.h"
#include "brst_mmgr.h"
#include "brst_error.h"
#include "private/brst_mmgr.h"
#include "private/brst_utils.h"
#include "private/brst_error.h"
#include "brst_consts.h"
#include "private/brst_c.h"

typedef struct _BRST_MPool_Node_Rec {
    BRST_BYTE* buf;
    BRST_UINT size;
    BRST_UINT used_size;
    BRST_MPool_Node next_node;
} BRST_MPool_Node_Rec;

typedef struct _BRST_MMgr_Rec {
    BRST_Error error;
    BRST_Alloc_Func alloc_fn;
    BRST_Free_Func free_fn;
    BRST_MPool_Node mpool;
    BRST_UINT buf_size;

#ifdef LIBBRST_MEM_DEBUG
    BRST_UINT alloc_cnt;
    BRST_UINT free_cnt;
#endif /* LIBBRST_MEM_DEBUG */
} BRST_MMgr_Rec;

static void* BRST_STDCALL
InternalGetMem(BRST_UINT size);

static void BRST_STDCALL
InternalFreeMem(void* aptr);

BRST_MMgr
BRST_MMgr_New(BRST_Error error,
    BRST_UINT buf_size,
    BRST_Alloc_Func alloc_fn,
    BRST_Free_Func free_fn)
{
    BRST_MMgr mmgr;

    BRST_PTRACE((" BRST_MMgr_New\n"));

    if (alloc_fn)
        mmgr = (BRST_MMgr)alloc_fn(sizeof(BRST_MMgr_Rec));
    else
        mmgr = (BRST_MMgr)InternalGetMem(sizeof(BRST_MMgr_Rec));

    BRST_PTRACE(("+%p mmgr-new\n", mmgr));

    if (mmgr != NULL) {
        /* initialize mmgr object */
        mmgr->error = error;

#ifdef LIBBRST_MEM_DEBUG
        mmgr->alloc_cnt = 0;
        mmgr->free_cnt  = 0;
#endif /* LIBBRST_MEM_DEBUG */
        /*
         *  if alloc_fn and free_fn are specified, these function is
         *  used. if not, default function (maybe these will be "malloc" and
         *  "free") is used.
         */
        if (alloc_fn && free_fn) {
            mmgr->alloc_fn = alloc_fn;
            mmgr->free_fn  = free_fn;
        } else {
            mmgr->alloc_fn = InternalGetMem;
            mmgr->free_fn  = InternalFreeMem;
        }

        /*
         *  if buf_size parameter is specified, this object is configured
         *  to be using memory-pool.
         *
         */
        if (!buf_size)
            mmgr->mpool = NULL;
        else {
            BRST_MPool_Node node;

            node = (BRST_MPool_Node)mmgr->alloc_fn(sizeof(BRST_MPool_Node_Rec) + buf_size);

            BRST_PTRACE(("+%p mmgr-node-new\n", node));

            if (node == NULL) {
                BRST_Error_Set(error, BRST_FAILED_TO_ALLOC_MEM, BRST_NOERROR);

                mmgr->free_fn(mmgr);
                mmgr = NULL;
            } else {
                mmgr->mpool     = node;
                node->buf       = (BRST_BYTE*)node + sizeof(BRST_MPool_Node_Rec);
                node->size      = buf_size;
                node->used_size = 0;
                node->next_node = NULL;
            }

#ifdef LIBBRST_MEM_DEBUG
            if (mmgr) {
                mmgr->alloc_cnt += 1;
            }
#endif /* LIBBRST_MEM_DEBUG */
        }

        if (mmgr) {
            mmgr->buf_size = buf_size;
        }
    } else
        BRST_Error_Set(error, BRST_FAILED_TO_ALLOC_MEM, BRST_NOERROR);

    return mmgr;
}

void BRST_MMgr_Free(BRST_MMgr mmgr)
{
    BRST_MPool_Node node;

    BRST_PTRACE((" BRST_MMgr_Free\n"));

    if (mmgr == NULL)
        return;

    node = mmgr->mpool;

    /* delete all nodes recursively */
    while (node != NULL) {
        BRST_MPool_Node tmp = node;
        node                = tmp->next_node;

        BRST_PTRACE(("-%p mmgr-node-free\n", tmp));
        mmgr->free_fn(tmp);

#ifdef LIBBRST_MEM_DEBUG
        mmgr->free_cnt++;
#endif /* LIBBRST_MEM_DEBUG */
    }

#ifdef LIBBRST_MEM_DEBUG
    BRST_PRINTF("# BRST_MMgr alloc-cnt=%u, free-cnt=%u\n",
        mmgr->alloc_cnt, mmgr->free_cnt);

    if (mmgr->alloc_cnt != mmgr->free_cnt)
        BRST_PRINTF("# ERROR #\n");
#endif /* LIBBRST_MEM_DEBUG */

    BRST_PTRACE(("-%p mmgr-free\n", mmgr));
    mmgr->free_fn(mmgr);
}

BRST_Error
BRST_MMgr_Error(
    BRST_MMgr mmgr)
{
    if (!mmgr)
        return NULL;
    return mmgr->error;
}

void* BRST_GetMem(BRST_MMgr mmgr,
    BRST_UINT size)
{
    void* ptr;

    if (mmgr->mpool) {
        BRST_MPool_Node node = mmgr->mpool;

#ifdef BRST_ALINMENT_SIZ
        size = (size + (BRST_ALINMENT_SIZ - 1)) / BRST_ALINMENT_SIZ;
        size *= BRST_ALINMENT_SIZ;
#endif

        if (node->size - node->used_size >= size) {
            ptr = (BRST_BYTE*)node->buf + node->used_size;
            node->used_size += size;
            return ptr;
        } else {
            BRST_UINT tmp_buf_size = (mmgr->buf_size < size) ? size : mmgr->buf_size;

            node = (BRST_MPool_Node)mmgr->alloc_fn(sizeof(BRST_MPool_Node_Rec)
                + tmp_buf_size);
            BRST_PTRACE(("+%p mmgr-new-node\n", node));

            if (!node) {
                BRST_Error_Set(mmgr->error, BRST_FAILED_TO_ALLOC_MEM,
                    BRST_NOERROR);
                return NULL;
            }

            node->size = tmp_buf_size;
        }

        node->next_node = mmgr->mpool;
        mmgr->mpool     = node;
        node->used_size = size;
        node->buf       = (BRST_BYTE*)node + sizeof(BRST_MPool_Node_Rec);
        ptr             = node->buf;
    } else {
        ptr = mmgr->alloc_fn(size);
        BRST_PTRACE(("+%p mmgr-alloc_fn size=%u\n", ptr, size));

        if (ptr == NULL)
            BRST_Error_Set(mmgr->error, BRST_FAILED_TO_ALLOC_MEM, BRST_NOERROR);
    }

#ifdef LIBBRST_MEM_DEBUG
    if (ptr)
        mmgr->alloc_cnt++;
#endif /* LIBBRST_MEM_DEBUG */

    return ptr;
}

void BRST_FreeMem(BRST_MMgr mmgr,
    void* aptr)
{
    if (!aptr)
        return;

    if (!mmgr->mpool) {
        BRST_PTRACE(("-%p mmgr-free-mem\n", aptr));
        mmgr->free_fn(aptr);

#ifdef LIBBRST_MEM_DEBUG
        mmgr->free_cnt++;
#endif /* LIBBRST_MEM_DEBUG */
    }

    return;
}

static void* BRST_STDCALL
InternalGetMem(BRST_UINT size)
{
    return BRST_MALLOC(size);
}

static void BRST_STDCALL
InternalFreeMem(void* aptr)
{
    BRST_FREE(aptr);
}
