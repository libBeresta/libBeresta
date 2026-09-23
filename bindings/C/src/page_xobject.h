// license
#ifndef BRST_PAGE_XOBJECT_H
#define BRST_PAGE_XOBJECT_H

/**
  \ingroup page
  \brief Отображает объект XObject в текущем графическом контексте.

  XObject можно создать с помощью функции \ref BRST_Doc_Page_XObject_Create(), он может включать в себя
  графические команды, а также другие данные.

  Также эта функция используется \ref BRST_Page_DrawImage() для отображения изображения \ref BRST_Image.

  \param page Описатель объекта страницы.
  \param xobj Описатель объекта XObject.

  \return \ref BRST_OK при успешном выполнении, иначе возвращает код ошибки и вызывает обработчик ошибок.

  \see 
    BRST_Doc_Page_XObject_Create()
    BRST_Page_DrawImage()
    BRST_Page_GSave()
    BRST_Page_GRestore()
    BRST_Page_Concat()
*/
BRST_EXPORT(BRST_STATUS)
BRST_Page_XObject_Execute(
   BRST_Page page,
   BRST_XObject xobj
);

/**
  \ingroup page
  \brief 

  \param dict Описатель объекта словаря.
  \param xobj Описатель объекта XObject.

  \return \ref BRST_OK при успешном выполнении, иначе возвращает код ошибки и вызывает обработчик ошибок.

  \see 
    BRST_Doc_Page_XObject_Create()
    BRST_Page_DrawImage()
    BRST_Page_GSave()
    BRST_Page_GRestore()
    BRST_Page_Concat()
*/
BRST_EXPORT(BRST_STATUS)
BRST_Dict_XObject_Execute(
   BRST_Dict dict,
   BRST_XObject xobj
);

#endif /* BRST_PAGE_XOBJECT_H */
