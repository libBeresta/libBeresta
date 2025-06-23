#ifndef PRIVATE_BRST_PROXY_H
#define PRIVATE_BRST_PROXY_H

#include "brst_mmgr.h"
#include "private/brst_object.h"

typedef struct _BRST_Proxy_Rec {
    BRST_Obj_Header  header;
    void             *obj;
} BRST_Proxy_Rec;

typedef struct _BRST_Proxy_Rec* BRST_Proxy;

BRST_Proxy
BRST_Proxy_New(
    BRST_MMgr mmgr,
    void*     obj
);

#endif /* PRIVATE_BRST_PROXY_H */
