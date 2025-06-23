#ifndef __HANDLER_H
#define __HANDLER_H

#include "brst.h"
#include <setjmp.h>
#include <stdio.h>

jmp_buf env;

BRST_HANDLER(void)
demo_error_handler(BRST_STATUS error_no, BRST_STATUS detail_no,
    void* user_data)
{
    printf("ERROR: error_no=0x%04X, detail_no=%u\n", (BRST_UINT)error_no,
        (BRST_UINT)detail_no);
    longjmp(env, 1);
}

#endif /* __HANDLER_H */
