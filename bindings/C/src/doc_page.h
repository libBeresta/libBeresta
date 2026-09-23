// license
#ifndef BRST_DOC_PAGE_H
#define BRST_DOC_PAGE_H

/**
  \ingroup doc
  \brief Задать количество страниц, которыми может владеть объект `Pages`.

   По умолчанию объект \ref BRST_Doc содержит один корневой объект 
   `Pages`. Все страницы создаются как дочерние элементы 
   объекта `Pages`. Так как объект `Pages` может содержать не более 8191 
   дочерних элементов, максимальное количество страниц равно 8191. 
   Включение большого количества страниц в один объект `Pages`
   нежелательно, поскольку это снижает производительность приложения 
   просмотра. 

   Приложение может изменить размер дерева страниц с помощью функции 
   BRST_SetPagesConfiguration(). Если параметр `page_per_pages` больше 
   нуля, создаётся двухуровневое дерево страниц. Корневой 
   объект `Pages` может содержать 8191 дочерних объекта `Pages`, каждый из которых 
   может содержать c page_per_pages страниц. Таким образом, общее 
   максимальное количество страниц становится равным a 8191 × a page_per_pages страниц. 
   Приложению нельзя вызывать функцию  BRST_SetPageConfiguration() после 
   добавления страниц в документ.

  \param pdf Описатель объекта документа.
  \param page_per_pages Количество страниц, которыми может владеть объект Pages.

  \return \ref BRST_OK при успешном выполнении, иначе возвращает код ошибки и вызывает обработчик ошибок.

  \par Коды ошибок
    - \ref BRST_INVALID_DOCUMENT
    - \ref BRST_INVALID_PARAMETER
    - \ref BRST_INVALID_DOCUMENT_STATE
    - \ref BRST_FAILED_TO_ALLOC_MEM
*/
BRST_EXPORT(BRST_STATUS)
BRST_Doc_Pages_SetConfiguration(
   BRST_Doc pdf,
   BRST_UINT page_per_pages
);

/**
  \ingroup page
  \brief Возвращает страницу документа, заданную номером.

  \param pdf Описатель объекта документа.
  \param index Номер возвращаемой страницы

  \return Описатель объекта страницы.
*/
BRST_EXPORT(BRST_Page)
BRST_Doc_Page_ByIndex(
   BRST_Doc pdf,
   BRST_UINT index
);

/**
  \ingroup page
  \brief Возвращает макет страницы. Если макет не задан, возвращает \ref BRST_PAGE_LAYOUT_LAST.

  \param pdf Описатель объекта документа.

  \return Возвращает макет страницы. Если макет не задан, возвращает \ref BRST_PAGE_LAYOUT_LAST.
*/
BRST_EXPORT(BRST_PageLayout)
BRST_Doc_Page_Layout(
   BRST_Doc pdf
);

/**
  \ingroup page
  \brief Задает макет страницы. Если атрибут не указан, используются настройки программы просмотра.

  \param pdf Описатель объекта документа.
  \param layout \parblock One of the following values:

    Макет                                   | Описание   
    -----                                   | --------   
    \ref BRST_PAGE_LAYOUT_SINGLE           | Отображается только одна страница                         
    \ref BRST_PAGE_LAYOUT_ONE_COLUMN       | Страницы отображаются в одну колонку                     
    \ref BRST_PAGE_LAYOUT_TWO_COLUMN_LEFT  | Отображение в две колонки. Нечётные номера страниц слева 
    \ref BRST_PAGE_LAYOUT_TWO_COLUMN_RIGHT | Отображение в две колонки. Нечётные номера страниц справа
    \ref BRST_PAGE_LAYOUT_TWO_PAGE_LEFT    | Страницы отображаются парами, нечётные страницы слева    
    \ref BRST_PAGE_LAYOUT_TWO_PAGE_RIGHT   | Страницы отображаются парами, нечётные страницы справа   
  \endparblock

  \return \ref BRST_OK при успешном выполнении, иначе возвращает код ошибки и вызывает обработчик ошибок.

  \par Коды ошибок
    - \ref BRST_INVALID_DOCUMENT
    - \ref BRST_FAILED_TO_ALLOC_MEM
    - \ref BRST_PAGE_LAYOUT_OUT_OF_RANGE
*/
BRST_EXPORT(BRST_STATUS)
BRST_Doc_Page_SetLayout(
   BRST_Doc pdf,
   BRST_PageLayout layout
);

/**
  \ingroup page
  \brief Возвращает способ демонстранции страниц документа.

  \param pdf Описатель объекта документа.

  \return Способ демонстрации страниц документа.
*/
BRST_EXPORT(BRST_PageMode)
BRST_Doc_Page_Mode(
   BRST_Doc pdf
);

/**
  \ingroup page
  \brief Задает способ демонстранции страниц документа.

  \param pdf Описатель объекта документа.
  \param mode \parblock Одно из следующих значений:
    Режим                                | Описание
    -----                                | --------
    \ref BRST_PAGE_MODE_USE_NONE        | Ни структура документа, ни эскизы страниц не показываются
    \ref BRST_PAGE_MODE_USE_OUTLINES    | Показывается структура документа
    \ref BRST_PAGE_MODE_USE_THUMBS      | Показываются эскиз страниц
    \ref BRST_PAGE_MODE_FULL_SCREEN     | Полноэкранный режим: меню, элементы управления и другие части окна скрываются
    \ref BRST_PAGE_MODE_USE_OC          | Показывается панель необязательного содержимого
    \ref BRST_PAGE_MODE_USE_ATTACHMENTS | Показывается панель вложений
  \endparblock

  \return \ref BRST_OK при успешном выполнении, иначе возвращает код ошибки и вызывает обработчик ошибок.

  \par Коды ошибок
    - \ref BRST_INVALID_DOCUMENT
    - \ref BRST_FAILED_TO_ALLOC_MEM
    - \ref BRST_PAGE_MODE_OUT_OF_RANGE
*/
BRST_EXPORT(BRST_STATUS)
BRST_Doc_Page_SetMode(
   BRST_Doc pdf,
   BRST_PageMode mode
);

/**
  \ingroup page
  \brief Возвращается текущая страница.

  \param pdf Описатель объекта документа.

  \return Описатель объекта страницы.
*/
BRST_EXPORT(BRST_Page)
BRST_Doc_Page_Current(
   BRST_Doc pdf
);

/**
  \ingroup page
  \brief Создает страницу и добавляет её в конец документа.

  \param pdf Описатель объекта документа.

  \return Описатель объекта страницы.

  \par Коды ошибок
    - \ref BRST_INVALID_DOCUMENT
    - \ref BRST_FAILED_TO_ALLOC_MEM
*/
BRST_EXPORT(BRST_Page)
BRST_Doc_Page_Add(
   BRST_Doc pdf
);

/**
  \ingroup page
  \brief Создает страницу и добавляет её перед страницей \c page.

  \param pdf Описатель объекта документа.
  \param page Страница, перед которой вставляется вновь создаваемая страница.

  \return Описатель объекта страницы.

  \par Коды ошибок
    - \ref BRST_INVALID_DOCUMENT
    - \ref BRST_FAILED_TO_ALLOC_MEM
    - \ref BRST_INVALID_PAGE
*/
BRST_EXPORT(BRST_Page)
BRST_Doc_Page_Insert(
   BRST_Doc pdf,
   BRST_Page page
);

/**
  \ingroup page
  \brief Указание способа отображения диапазона номеров страниц в программах просмотра.

  \param pdf Описатель объекта документа.
  \param page_num Начальная страница диапазона страниц с собственной нумерацией.
  \param style Стиль нумерации диапазона страниц.
  \param first_page Номер страницы, с которой может начинаться диапазон. Последовательность страниц будет начинаться с этого номера.
  \param prefix Префикс метки для диапазона страниц.

  \return \ref BRST_OK при успешном выполнении, иначе возвращает код ошибки и вызывает обработчик ошибок.

  \par Коды ошибок
    - \ref BRST_INVALID_DOCUMENT
    - \ref BRST_FAILED_TO_ALLOC_MEM
    - \ref BRST_PAGE_NUM_OUT_OF_RANGE
*/
BRST_EXPORT(BRST_STATUS)
BRST_Doc_Page_AddLabel(
   BRST_Doc pdf,
   BRST_UINT page_num,
   BRST_PageNumStyle style,
   BRST_UINT first_page,
   BRST_CSTR prefix
);

#endif /* BRST_DOC_PAGE_H */
