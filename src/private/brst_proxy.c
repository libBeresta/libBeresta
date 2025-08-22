#include "brst_mmgr.h"
#include "private/brst_utils.h"
#include "private/brst_proxy.h"
#include "private/brst_object.h"

BRST_Proxy
BRST_Proxy_New(BRST_MMgr mmgr,
    void* obj)
{
    BRST_Proxy p = BRST_GetMem(mmgr, sizeof(BRST_Proxy_Rec));

    BRST_PTRACE(" BRST_Proxy_New\n");

    if (p) {
        BRST_MemSet(&p->header, 0, sizeof(BRST_Obj_Header));
        p->header.obj_class = BRST_OCLASS_PROXY;
        p->obj              = obj;
    }

    return p;
}
