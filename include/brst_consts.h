#ifndef BRST_CONSTS_H
#define BRST_CONSTS_H

#define  BRST_TRUE                  1
#define  BRST_FALSE                 0

#define  BRST_OK                    0
#define  BRST_NOERROR               0

#define  BRST_PI                    3.14159265358979323846f

/*----------------------------------------------------------------------------*/
/*----- permission flags (only Revision 2 is supported)-----------------------*/

#define BRST_ENABLE_READ         0
#define BRST_ENABLE_PRINT        4
#define BRST_ENABLE_EDIT_ALL     8
#define BRST_ENABLE_COPY         16
#define BRST_ENABLE_EDIT         32

#define BRST_MAX_GENERATION_NUM        65535

/*----------------------------------------------------------------------------*/
/*----- Graphics mode --------------------------------------------------------*/

#define   BRST_GMODE_PAGE_DESCRIPTION       0x0001
#define   BRST_GMODE_PATH_OBJECT            0x0002
#define   BRST_GMODE_TEXT_OBJECT            0x0004
#define   BRST_GMODE_CLIPPING_PATH          0x0008
#define   BRST_GMODE_SHADING                0x0010
#define   BRST_GMODE_INLINE_IMAGE           0x0020
#define   BRST_GMODE_EXTERNAL_OBJECT        0x0040

/*---------------------------------------------------------------------------*/
/*----- compression mode ----------------------------------------------------*/

#define  BRST_COMP_MODE_NONE            0x00
#define  BRST_COMP_MODE_TEXT            0x01
#define  BRST_COMP_MODE_IMAGE           0x02
#define  BRST_COMP_MODE_METADATA        0x04
#define  BRST_COMP_MODE_ALL             0x0F
/* #define  BRST_COMP_BEST_COMPRESS   0x10
 * #define  BRST_COMP_BEST_SPEED      0x20
 */
#define  BRST_COMP_MODE_MASK            0xFF

/*----------------------------------------------------------------------------*/
/*------ viewer preferences definitions --------------------------------------*/

#define BRST_HIDE_TOOLBAR    1
#define BRST_HIDE_MENUBAR    2
#define BRST_HIDE_WINDOW_UI  4
#define BRST_FIT_WINDOW      8
#define BRST_CENTER_WINDOW   16
#define BRST_PRINT_SCALING_NONE 32
#define BRST_DISPLAY_DOC_TITLE 64


/**
  \brief Предопределенное значение для вычислений в миллиметрах, равно 72.0/25.4 (72 точки на дюйм на мм).
*/
#define BRST_MM                             2.834646f

/**
  \brief Предопределенное значение для вычислений в дюймах (72 точки на дюйм)
*/
#define BRST_IN                             72.00000f

#define KAPPA                     0.552284749830793f

#endif /* BRST_CONSTS_H */
