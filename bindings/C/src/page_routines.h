// license
#ifndef BRST_PAGE_ROUTINES_H
#define BRST_PAGE_ROUTINES_H

/**
  \ingroup page
  \brief 

  \param page Описатель объекта страницы.
  \param value 

  \return \ref BRST_OK при успешном выполнении, иначе возвращает код ошибки и вызывает обработчик ошибок.

  \par Коды ошибок
    - \ref BRST_INVALID_PAGE
    - \ref BRST_PAGE_INVALID_SIZE
    - \ref BRST_FAILED_TO_ALLOC_MEM
*/
BRST_EXPORT(BRST_STATUS)
BRST_Page_SetWidth(
   BRST_Page page,
   BRST_REAL value
);

/**
  \ingroup page
  \brief 

  \param page Описатель объекта страницы.
  \param value 

  \return \ref BRST_OK при успешном выполнении, иначе возвращает код ошибки и вызывает обработчик ошибок.

  \par Коды ошибок
    - \ref BRST_INVALID_PAGE
    - \ref BRST_PAGE_INVALID_SIZE
    - \ref BRST_FAILED_TO_ALLOC_MEM
*/
BRST_EXPORT(BRST_STATUS)
BRST_Page_SetHeight(
   BRST_Page page,
   BRST_REAL value
);

/**
  \ingroup page
  \brief 

  \param page Описатель объекта страницы.
  \param boundary 
  \param left 
  \param bottom 
  \param right 
  \param top 

  \return \ref BRST_OK при успешном выполнении, иначе возвращает код ошибки и вызывает обработчик ошибок.
*/
BRST_EXPORT(BRST_STATUS)
BRST_Page_SetBoundary(
   BRST_Page page,
   BRST_PageBoundary boundary,
   BRST_REAL left,
   BRST_REAL bottom,
   BRST_REAL right,
   BRST_REAL top
);

/**
  \ingroup page
  \brief 

  \param page Описатель объекта страницы.
  \param size 
  \param orientation 

  \return \ref BRST_OK при успешном выполнении, иначе возвращает код ошибки и вызывает обработчик ошибок.

  \par Коды ошибок
    - \ref BRST_INVALID_PAGE
    - \ref BRST_PAGE_INVALID_SIZE
    - \ref BRST_PAGE_INVALID_ORIENTATION
    - \ref BRST_FAILED_TO_ALLOC_MEM
*/
BRST_EXPORT(BRST_STATUS)
BRST_Page_SetSize(
   BRST_Page page,
   BRST_PageSizes size,
   BRST_PageOrientation orientation
);

/**
  \ingroup page
  \brief 

  \param page Описатель объекта страницы.
  \param angle 

  \return \ref BRST_OK при успешном выполнении, иначе возвращает код ошибки и вызывает обработчик ошибок.

  \par Коды ошибок
    - \ref BRST_INVALID_PAGE
    - \ref BRST_PAGE_INVALID_ROTATE_VALUE
*/
BRST_EXPORT(BRST_STATUS)
BRST_Page_SetRotate(
   BRST_Page page,
   BRST_UINT16 angle
);

/**
  \ingroup page
  \brief 

  \param page Описатель объекта страницы.
  \param type 
  \param disp_time 
  \param trans_time 

  \return \ref BRST_OK при успешном выполнении, иначе возвращает код ошибки и вызывает обработчик ошибок.
*/
BRST_EXPORT(BRST_STATUS)
BRST_Page_SetSlideShow(
   BRST_Page page,
   BRST_PageTransition type,
   BRST_REAL disp_time,
   BRST_REAL trans_time
);

/**
  \ingroup graphics
  \brief 

  \param page Описатель объекта страницы.
  \param value 

  \return \ref BRST_OK при успешном выполнении, иначе возвращает код ошибки и вызывает обработчик ошибок.
*/
BRST_EXPORT(BRST_STATUS)
BRST_Page_SetHorizontalScaling(
   BRST_Page page,
   BRST_REAL value
);

/**
  \ingroup page
  \brief 

  \param page Описатель объекта страницы.

  \return 
*/
BRST_EXPORT(BRST_UINT)
BRST_Page_GStateDepth(
   BRST_Page page
);

/**
  \ingroup page
  \brief 

  \param page Описатель объекта страницы.

  \return 
*/
BRST_EXPORT(BRST_REAL)
BRST_Page_HorizontalScaling(
   BRST_Page page
);

/**
  \ingroup page
  \brief 

  \param page Описатель объекта страницы.
  \param zoom 

  \return \ref BRST_OK при успешном выполнении, иначе возвращает код ошибки и вызывает обработчик ошибок.
*/
BRST_EXPORT(BRST_STATUS)
BRST_Page_SetZoom(
   BRST_Page page,
   BRST_REAL zoom
);

/**
  \ingroup page
  \brief 

  \param page Описатель объекта страницы.

  \return 
*/
BRST_EXPORT(BRST_REAL)
BRST_Page_Width(
   BRST_Page page
);

/**
  \ingroup page
  \brief 

  \param page Описатель объекта страницы.

  \return 
*/
BRST_EXPORT(BRST_REAL)
BRST_Page_Height(
   BRST_Page page
);

/**
  \ingroup page
  \brief 

  \param page Описатель объекта страницы.

  \return 
*/
BRST_EXPORT(BRST_UINT16)
BRST_Page_GMode(
   BRST_Page page
);

/**
  \ingroup page
  \brief 

  \param page Описатель объекта страницы.

  \return 
*/
BRST_EXPORT(BRST_MMgr)
BRST_Page_MMgr(
   BRST_Page page
);

/**
  \ingroup page
  \brief 

  \param page Описатель объекта страницы.
  \param shared_stream 

  \return \ref BRST_OK при успешном выполнении, иначе возвращает код ошибки и вызывает обработчик ошибок.
*/
BRST_EXPORT(BRST_STATUS)
BRST_Page_Insert_Shared_Content_Stream(
   BRST_Page page,
   BRST_Dict shared_stream
);

/**
  \ingroup page
  \brief 

  \param page Описатель объекта страницы.
  \param data 

  \return \ref BRST_OK при успешном выполнении, иначе возвращает код ошибки и вызывает обработчик ошибок.

  \par Коды ошибок
    - \ref BRST_INVALID_PAGE
*/
BRST_EXPORT(BRST_STATUS)
BRST_Page_RawWrite(
   BRST_Page page,
   BRST_CSTR data
);

/**
  \ingroup graphics
  \brief 

  \param page Описатель объекта страницы.
  \param ext_gstate 

  \return \ref BRST_OK при успешном выполнении, иначе возвращает код ошибки и вызывает обработчик ошибок.
*/
BRST_EXPORT(BRST_STATUS)
BRST_Page_SetExtGState(
   BRST_Page page,
   BRST_ExtGState ext_gstate
);

/**
  \ingroup link
  \brief 

  \param page Описатель объекта страницы.

  \return 

  \par Коды ошибок
    - \ref BRST_INVALID_DOCUMENT
    - \ref BRST_FAILED_TO_ALLOC_MEM
*/
BRST_EXPORT(BRST_Destination)
BRST_Page_CreateDestination(
   BRST_Page page
);

#endif /* BRST_PAGE_ROUTINES_H */
