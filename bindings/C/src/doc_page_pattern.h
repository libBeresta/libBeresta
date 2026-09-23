// license
#ifndef BRST_DOC_PAGE_PATTERN_H
#define BRST_DOC_PAGE_PATTERN_H

/**
  \ingroup 
  \brief 

  \param pdf Описатель объекта документа.
  \param left 
  \param bottom 
  \param right 
  \param top 
  \param xstep 
  \param ystep 
  \param m Описатель объекта матрицы преобразования.

  \return 
*/
BRST_EXPORT(BRST_Pattern)
BRST_Doc_Pattern_Tiling_Create(
   BRST_Doc pdf,
   BRST_REAL left,
   BRST_REAL bottom,
   BRST_REAL right,
   BRST_REAL top,
   BRST_REAL xstep,
   BRST_REAL ystep,
   BRST_Matrix m
);

/**
  \ingroup 
  \brief 

  \param pattern 

  \return 
*/
BRST_EXPORT(BRST_Stream)
BRST_Doc_Pattern_Stream(
   BRST_Pattern pattern
);

/**
  \ingroup 
  \brief 

  \param pdf Описатель объекта документа.
  \param dict Описатель объекта словаря.
  \param r 
  \param g 
  \param b 
  \param pattern :param_pattern

  \return \ref BRST_OK при успешном выполнении, иначе возвращает код ошибки и вызывает обработчик ошибок.
*/
BRST_EXPORT(BRST_STATUS)
BRST_Doc_Dict_RGBPatternFill_Select(
   BRST_Doc pdf,
   BRST_Dict dict,
   BRST_REAL r,
   BRST_REAL g,
   BRST_REAL b,
   BRST_Pattern pattern
);

/**
  \ingroup 
  \brief 

  \param pdf Описатель объекта документа.
  \param dict Описатель объекта словаря.
  \param r 
  \param g 
  \param b 
  \param pattern :param_pattern

  \return \ref BRST_OK при успешном выполнении, иначе возвращает код ошибки и вызывает обработчик ошибок.
*/
BRST_EXPORT(BRST_STATUS)
BRST_Doc_Dict_RGBPatternFillUint_Select(
   BRST_Doc pdf,
   BRST_Dict dict,
   BRST_UINT8 r,
   BRST_UINT8 g,
   BRST_UINT8 b,
   BRST_Pattern pattern
);

/**
  \ingroup 
  \brief 

  \param pdf Описатель объекта документа.
  \param dict Описатель объекта словаря.
  \param rgb 
  \param pattern :param_pattern

  \return \ref BRST_OK при успешном выполнении, иначе возвращает код ошибки и вызывает обработчик ошибок.
*/
BRST_EXPORT(BRST_STATUS)
BRST_Doc_Dict_RGBPatternFillHex_Select(
   BRST_Doc pdf,
   BRST_Dict dict,
   BRST_UINT8 rgb,
   BRST_Pattern pattern
);

/**
  \ingroup 
  \brief 

  \param pdf Описатель объекта документа.
  \param page Описатель объекта страницы.
  \param r 
  \param g 
  \param b 
  \param pattern :param_pattern

  \return \ref BRST_OK при успешном выполнении, иначе возвращает код ошибки и вызывает обработчик ошибок.
*/
BRST_EXPORT(BRST_STATUS)
BRST_Doc_Page_RGBPatternFill_Select(
   BRST_Doc pdf,
   BRST_Page page,
   BRST_REAL r,
   BRST_REAL g,
   BRST_REAL b,
   BRST_Pattern pattern
);

/**
  \ingroup 
  \brief 

  \param pdf Описатель объекта документа.
  \param page Описатель объекта страницы.
  \param r 
  \param g 
  \param b 
  \param pattern :param_pattern

  \return \ref BRST_OK при успешном выполнении, иначе возвращает код ошибки и вызывает обработчик ошибок.
*/
BRST_EXPORT(BRST_STATUS)
BRST_Doc_Page_RGBPatternFillUint_Select(
   BRST_Doc pdf,
   BRST_Page page,
   BRST_UINT8 r,
   BRST_UINT8 g,
   BRST_UINT8 b,
   BRST_Pattern pattern
);

/**
  \ingroup 
  \brief 

  \param pdf Описатель объекта документа.
  \param page Описатель объекта страницы.
  \param rgb 
  \param pattern :param_pattern

  \return \ref BRST_OK при успешном выполнении, иначе возвращает код ошибки и вызывает обработчик ошибок.
*/
BRST_EXPORT(BRST_STATUS)
BRST_Doc_Page_RGBPatternFillHex_Select(
   BRST_Doc pdf,
   BRST_Page page,
   BRST_UINT8 rgb,
   BRST_Pattern pattern
);

#endif /* BRST_DOC_PAGE_PATTERN_H */
