#ifndef __HANDLER_H
#define __HANDLER_H

#include "brst.h"
#include <setjmp.h>

BRST_HANDLER(void)
demo_error_handler(BRST_STATUS error_no,
    BRST_STATUS detail_no,
    void* user_data);

static jmp_buf env;

#endif /* __HANDLER_H */