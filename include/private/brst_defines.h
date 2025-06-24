#ifndef PRIVATE_BRST_DEFINES_H
#define PRIVATE_BRST_DEFINES_H

#include "private/brst_utils.h"
#include "brst_geometry_defines.h"

#define G3CODES

/* Размер массива для объектов-списков */
#define BRST_DEF_ITEMS_PER_BLOCK    20

/* Размер буфера для потока в памяти */
#define BRST_STREAM_BUF_SIZE        4096
#define BRST_SHORT_BUF_SIZE         32

/* buffer size which is required when we convert to character string. */
#define BRST_TMP_BUF_SIZE           512

#define BRST_BYTE_OFFSET_LEN        10
#define BRST_INT_LEN                11
#define BRST_REAL_LEN               64
#define BRST_TEXT_DEFAULT_LEN       256
#define BRST_GEN_NO_LEN             5
#define BRST_DATE_TIME_STR_LEN      23

//TODO В отдельный файл?
/* Лимиты */
#define BRST_LIMIT_MAX_NAME_LEN        127
#define BRST_LIMIT_MAX_STRING_LEN      2147483646 // per PDF 1.7 spec, limit 32767 is for strings in content stream and no limit in other cases => open the limit to max Integer, old value 65535

#define BRST_LIMIT_MAX_ARRAY           8388607  // per PDF 1.7 spec, "Maximum number of indirect objects in a PDF file" is 8388607, old value 8191

#define BRST_MAX_JWW_NUM            128

#define BRST_LIMIT_MAX_INT             2147483647
#define BRST_LIMIT_MIN_INT             -2147483647

#define BRST_LIMIT_MAX_REAL             3.4E38f // per PDF 1.7 spec, Annex C, old value  32767
#define BRST_LIMIT_MIN_REAL            -3.4E38f // per PDF 1.7 spec, Annex C, old value -32767

#define BRST_LIMIT_MAX_DICT_ELEMENT    8388607  // per PDF 1.7 spec, "Maximum number of indirect objects in a PDF file" is 8388607, old value 4095
#define BRST_LIMIT_MAX_XREF_ELEMENT    8388607

#define BRST_LIMIT_MAX_GSTATE          28


/* default array size of range-table of cid-fontdef */
#define BRST_DEF_RANGE_TBL_NUM      128

/* default array size of cross-reference-table */
#define BRST_DEFAULT_XREF_ENTRY_NUM 1024

/* default array size of widths-table of cid-fontdef */
#define BRST_DEF_CHAR_WIDTHS_NUM    128


/*----------------------------------------------------------------------------*/
/*------ viewer preferences definitions --------------------------------------*/

#define BRST_HIDE_TOOLBAR    1
#define BRST_HIDE_MENUBAR    2
#define BRST_HIDE_WINDOW_UI  4
#define BRST_FIT_WINDOW      8
#define BRST_CENTER_WINDOW   16
#define BRST_PRINT_SCALING_NONE   32

/* default page-size */
#define BRST_DEF_PAGE_WIDTH         595.276F
#define BRST_DEF_PAGE_HEIGHT        841.89F

#define BRST_DEF_LEADING            0
#define BRST_DEF_WORDSPACE          0
#define BRST_DEF_CHARSPACE          0

#define BRST_DEF_RAISE              0

#define BRST_DEF_HSCALING           100



#define BRST_BS_DEF_WIDTH           1
#define BRST_DEF_RENDERING_MODE     BRST_FILL


#define BRST_MAX_DASH_PATTERN       100
#define BRST_MAX_FONTSIZE           600
#define BRST_MIN_WORDSPACE          -30
#define BRST_MAX_WORDSPACE          300
#define BRST_MIN_CHARSPACE          -30
#define BRST_MAX_CHARSPACE          300

#define BRST_MIN_HORIZONTAL_SCALING 10
#define BRST_MAX_HORIZONTAL_SCALING 300
#define BRST_MIN_MAGNIFICATION_FACTOR   0.08 // 8 percent
#define BRST_MAX_MAGNIFICATION_FACTOR  64.00 // 6400 percent

/* default array size of page-list-tablef */
#define BRST_DEF_PAGE_LIST_NUM      256

static const BRST_Point INIT_POS = {0, 0};
static const BRST_DashMode INIT_MODE = {{0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f}, 0, 0.0f};

/// Minimal page size in user units according to PDF standard
#define BRST_MIN_PAGE_MEASURE       3

/// Maximal page size in user units according to PDF standard
#define BRST_MAX_PAGE_MEASURE       14400



#endif /* PRIVATE_BRST_DEFINES_H */
