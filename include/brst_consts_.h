
/*----------------------------------------------------------------------------*/



/*----- default values -------------------------------------------------------*/

#define BRST_UNICODE_HEADER_LEN     2

/* length of each item defined in PDF */
#define BRST_OBJ_ID_LEN             7

/* default value of Graphic State */
#define BRST_DEF_FONT               "Helvetica"
#define BRST_DEF_PAGE_LAYOUT        BRST_PAGE_LAYOUT_SINGLE
#define BRST_DEF_PAGE_MODE          BRST_PAGE_MODE_USE_NONE
#define BRST_DEF_FONTSIZE           10
#define BRST_DEF_PAGE_NUM           1


/*---------------------------------------------------------------------------*/
/*------ limitation of object implementation (PDF1.4) -----------------------*/



#define BRST_LIMIT_MAX_DEVICE_N        8
#define BRST_LIMIT_MAX_DEVICE_N_V15    32
#define BRST_LIMIT_MAX_CID             65535

/*---------------------------------------------------------------------------*/
/*------ limitation of various properties -----------------------------------*/

#define BRST_MAX_ZOOMSIZE           10
#define BRST_MAX_LEADING            300
#define BRST_MAX_LINEWIDTH          100


/*----------------------------------------------------------------------------*/
/**
  \brief Predefined value for calculations with millimeters. Equals to 72.0/25.4 (72 points pre inch per mm).
*/
#define BRST_MM                             2.834646

/**
  \brief Predefined value for calculations with inches
*/
#define BRST_IN                             72.00000

#endif /* _BRST_CONSTS_H */
