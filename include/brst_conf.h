/*
 * << Haru Free PDF Library >> -- brst_conf.h
 *
 * URL: http://libharu.org
 *
 * Copyright (c) 1999-2006 Takeshi Kanno <takeshi_kanno@est.hi-ho.ne.jp>
 * Copyright (c) 2007-2009 Antony Dovgal <tony@daylessday.org>
 *
 * Permission to use, copy, modify, distribute and sell this software
 * and its documentation for any purpose is hereby granted without fee,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear
 * in supporting documentation.
 * It is provided "as is" without express or implied warranty.
 *
 */

#ifndef _BRST_CONF_H
#define _BRST_CONF_H

#include <stdlib.h>
#include <stdio.h>
#if defined(_MSC_VER)
#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES 1
#endif /* _USE_MATH_DEFINES */
#endif
#ifndef __USE_XOPEN
#define __USE_XOPEN /* for M_PI */
#endif /* __USE_XOPEN */
#include <math.h>

/*----------------------------------------------------------------------------*/
/*----- standard C library functions -----------------------------------------*/

#define BRST_FFLUSH                 fflush
#define BRST_PRINTF                 printf
#define BRST_SIN                    sin
#define BRST_COS                    cos

/*----------------------------------------------------------------------------*/
/*----- parameters in relation to performance --------------------------------*/

/* default array size of page-list-tablef */
#define BRST_DEF_PAGE_LIST_NUM      256

/* default buffer size of memory-pool-object */
#define BRST_MPOOL_BUF_SIZ          8192
#define BRST_MIN_MPOOL_BUF_SIZ      256
#define BRST_MAX_MPOOL_BUF_SIZ      1048576

/* alignment size of memory-pool-object
 */
#define BRST_ALIGNMENT_SIZE            sizeof(int)

#define G3CODES

#endif /* _BRST_CONF_H */

