(:file "doc_page"
 :functions
       (
;; Функция BRST_Doc_Pages_SetConfiguration
(:caption "Doc_Pages_SetConfiguration"
   :group "doc"
   :errors ("INVALID_DOCUMENT" "INVALID_PARAMETER" "INVALID_DOCUMENT_STATE" "FAILED_TO_ALLOC_MEM")
   :result (:type "STATUS"
  	           :ru ":return_ok"
               :en ":return_ok")
   :ru "Задать количество страниц, которыми может владеть объект `Pages`.

   По умолчанию объект \\ref BRST_Doc содержит один корневой объект 
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
   может содержать \c page_per_pages страниц. Таким образом, общее 
   максимальное количество страниц становится равным \a 8191 × \a page_per_pages страниц. 
   Приложению нельзя вызывать функцию  BRST_SetPageConfiguration() после 
   добавления страниц в документ." 

   :en "Specify number of pages `Pages` object can own.

  In the default setting, a \\ref BRST_Doc object has one `Pages` object as root of pages.
  All `Page` objects are created as a child of `Pages` object. Since `Pages` object can
  own only 8191 child objects, the maximum number of pages are 8191 pages. Additionally,
  the case when there are a lot of "Page" object under one "Pages" object is not good,
  since it causes performance degradation of a viewer application.

  An application can change the setting of a pages tree by invoking BRST_SetPagesConfiguration().
  If `page_per_pages` parameter is set to more than zero, a two-tier pages tree is created.
  A root `Pages` object can own 8191 `Pages` object, and each lower `Pages` object can own
  \\c page_per_pages `Page` objects. As a result, the maximum number of pages becomes
  \\a 8191 * \\a page_per_pages pages. An application cannot invoke BRST_SetPageConfiguration()
  after a page is added to document."
   :params ((:type "Doc"
            :name "pdf"
            :ru ":param_pdf"
            :en ":param_pdf")
           (:type "UINT"
            :name "page_per_pages"
            :ru "Количество страниц, которыми может владеть объект Pages."
            :en "Numbers of pages `Pages` object can own.")))

;; Функция BRST_Doc_Page_ByIndex
(:caption "Doc_Page_ByIndex"
   :group "page"
   :ru "Возвращает страницу документа, заданную номером."
   :en "Return document page, denoted by index."
   :result (:type "Page"
          :ru ":param_page"
          :en ":param_page")
   :params ((:type "Doc"
            :name "pdf"
            :ru ":param_pdf"
            :en ":param_pdf")
           (:type "UINT"
            :name "index"
            :ru "Номер возвращаемой страницы"
            :en "Page index")))

;; Функция BRST_Doc_Page_Layout
(:caption "Doc_Page_Layout"
   :group "page"
   :ru "Возвращает макет страницы. Если макет не задан, возвращает \\ref BRST_PAGE_LAYOUT_LAST."
   :en "Return page display layout on success. If page layout is not set, returns \\ref BRST_PAGE_LAYOUT_LAST."
   :errors ()
   :result (:type "PageLayout"
          :ru "Возвращает макет страницы. Если макет не задан, возвращает \\ref BRST_PAGE_LAYOUT_LAST."
          :en "Return page display layout on success. If page layout is not set, returns \\ref BRST_PAGE_LAYOUT_LAST.")
   :params ((:type "Doc"
            :name "pdf"
            :ru ":param_pdf"
            :en ":param_pdf")))

;; Функция BRST_Doc_Page_SetLayout
(:caption "Doc_Page_SetLayout"
   :group "page"
   :ru "Задает макет страницы. Если атрибут не указан, используются настройки программы просмотра."
   :en "Set page display layout. If attribute is not set, the setting of the viewer application is used."
   :errors ("INVALID_DOCUMENT" "FAILED_TO_ALLOC_MEM" "PAGE_LAYOUT_OUT_OF_RANGE")
   :result (:type "STATUS"
  	           :ru ":return_ok"
               :en ":return_ok")
   :params ((:type "Doc"
            :name "pdf"
            :ru ":param_pdf"
            :en ":param_pdf")
           (:type "PageLayout"
            :name "layout"
            :ru "\\parblock One of the following values:

    Макет                                   | Описание   
    -----                                   | --------   
    \\ref BRST_PAGE_LAYOUT_SINGLE           | Отображается только одна страница                         
    \\ref BRST_PAGE_LAYOUT_ONE_COLUMN       | Страницы отображаются в одну колонку                     
    \\ref BRST_PAGE_LAYOUT_TWO_COLUMN_LEFT  | Отображение в две колонки. Нечётные номера страниц слева 
    \\ref BRST_PAGE_LAYOUT_TWO_COLUMN_RIGHT | Отображение в две колонки. Нечётные номера страниц справа
    \\ref BRST_PAGE_LAYOUT_TWO_PAGE_LEFT    | Страницы отображаются парами, нечётные страницы слева    
    \\ref BRST_PAGE_LAYOUT_TWO_PAGE_RIGHT   | Страницы отображаются парами, нечётные страницы справа   
  \\endparblock"
            :en "\\parblock One of the following values:

    Layout                                  | Description
    -------                                 | -----------
    \\ref BRST_PAGE_LAYOUT_SINGLE           | Only one page is displayed
    \\ref BRST_PAGE_LAYOUT_ONE_COLUMN       | Display the pages in one column
    \\ref BRST_PAGE_LAYOUT_TWO_COLUMN_LEFT  | Display in two columns. Odd page number is displayed left
    \\ref BRST_PAGE_LAYOUT_TWO_COLUMN_RIGHT | Display in two columns. Odd page number is displayed right
    \\ref BRST_PAGE_LAYOUT_TWO_PAGE_LEFT    | Display the pages two at a time, with odd-numbered pages on the left
    \\ref BRST_PAGE_LAYOUT_TWO_PAGE_RIGHT   | Display the pages two at a time, with odd-numbered pages on the right
  \\endparblock")))

;; Функция BRST_Doc_Page_Mode
(:caption "Doc_Page_Mode"
   :group "page"
   :ru "Возвращает способ демонстрации страниц документа."
   :en "Return page display mode."
   :errors ()
   :result (:type "PageMode"
          :ru "Способ демонстрации страниц документа."
          :en "Page display mode.")
   :params ((:type "Doc"
            :name "pdf"
            :ru ":param_pdf"
            :en ":param_pdf")))

;; Функция BRST_Doc_Page_SetMode
(:caption "Doc_Page_SetMode"
   :group "page"
   :errors ("INVALID_DOCUMENT" "FAILED_TO_ALLOC_MEM" "PAGE_MODE_OUT_OF_RANGE")
   :result (:type "STATUS"
  	           :ru ":return_ok"
               :en ":return_ok")
   :ru "Задает способ демонстрации страниц документа."
   :en "Set page display mode."
   :params ((:type "Doc"
            :name "pdf"
            :ru ":param_pdf"
            :en ":param_pdf")
           (:type "PageMode"
            :name "mode"
            :ru "\\parblock Одно из следующих значений:
    Режим                                | Описание
    -----                                | --------
    \\ref BRST_PAGE_MODE_USE_NONE        | Ни структура документа, ни эскизы страниц не показываются
    \\ref BRST_PAGE_MODE_USE_OUTLINES    | Показывается структура документа
    \\ref BRST_PAGE_MODE_USE_THUMBS      | Показываются эскиз страниц
    \\ref BRST_PAGE_MODE_FULL_SCREEN     | Полноэкранный режим: меню, элементы управления и другие части окна скрываются
    \\ref BRST_PAGE_MODE_USE_OC          | Показывается панель необязательного содержимого
    \\ref BRST_PAGE_MODE_USE_ATTACHMENTS | Показывается панель вложений
  \\endparblock"
            :en "\\parblock One of the following values:
    Mode                                 | Description
    ----                                 | -----------
    \\ref BRST_PAGE_MODE_USE_NONE        | Neither document outline nor thumbnail images visible
    \\ref BRST_PAGE_MODE_USE_OUTLINES    | Document outline visible
    \\ref BRST_PAGE_MODE_USE_THUMBS      | Thumbnail images visible
    \\ref BRST_PAGE_MODE_FULL_SCREEN     | Full-screen mode, with no menu bar, window controls, or any other window visible
    \\ref BRST_PAGE_MODE_USE_OC          | Optional content group panel visible
    \\ref BRST_PAGE_MODE_USE_ATTACHMENTS | Attachments panel visible
  \\endparblock")))

;; Функция BRST_Doc_Page_Current
(:caption "Doc_Page_Current"
   :group "page"
   :errors ()
   :result (:type "Page"
          :ru ":param_page"
          :en ":param_page")
   :ru "Возвращается текущая страница."
   :en "Return current document page."
   :command ""
   :params ((:type "Doc"
            :name "pdf"
            :ru ":param_pdf"
            :en ":param_pdf")))

;; Функция BRST_Doc_Page_Add
(:caption "Doc_Page_Add"
   :group "page"
   :errors ("INVALID_DOCUMENT" "FAILED_TO_ALLOC_MEM")
   :result (:type "Page"
          :ru ":param_page"
          :en ":param_page")
   :ru "Создает страницу и добавляет её в конец документа."
   :en "Create page and add it to document end."
   :command ""
   :params ((:type "Doc"
            :name "pdf"
            :ru ":param_pdf"
            :en ":param_pdf")))

;; Функция BRST_Doc_Page_Insert
(:caption "Doc_Page_Insert"
   :group "page"
   :errors ("INVALID_DOCUMENT" "FAILED_TO_ALLOC_MEM" "INVALID_PAGE")
   :result (:type "Page"
          :ru ":param_page"
          :en ":param_page")
   :ru "Создает страницу и добавляет её перед страницей \\c page."
   :en "Create page and insert it before page \\c page."
   :params ((:type "Doc"
            :name "pdf"
            :ru ":param_pdf"
            :en ":param_pdf")
           (:type "Page"
            :name "page"
            :ru "Страница, перед которой вставляется вновь создаваемая страница."
            :en "Created page is inserted before this page.")))

;; Функция BRST_Doc_Page_AddLabel
(:caption "Doc_Page_AddLabel"
   :group "page"
   :errors ("INVALID_DOCUMENT" "FAILED_TO_ALLOC_MEM" "PAGE_NUM_OUT_OF_RANGE")
   :result (:type "STATUS"
  	           :ru ":return_ok"
               :en ":return_ok")
   :ru "Указание способа отображения диапазона номеров страниц в программах просмотра."
   :en "Set labeling style for page number range."
   :params ((:type "Doc"
            :name "pdf"
            :ru ":param_pdf"
            :en ":param_pdf")
           (:type "UINT"
            :name "page_num"
            :ru "Начальная страница диапазона страниц с собственной нумерацией."
            :en "Page number range with a style.")
           (:type "PageNumStyle"
            :name "style"
            :ru "Стиль нумерации диапазона страниц."
            :en "Page numbering style for page number range.")
           (:type "UINT"
            :name "first_page"
            :ru "Номер страницы, с которой может начинаться диапазон. Последовательность страниц будет начинаться с этого номера."
            :en "The value of the numeric portion for the first page label in the range.
Subsequent pages shall be numbered sequentially from this value, which shall be
greater than or equal to 1")
           (:type "CSTR"
            :name "prefix"
            :ru "Префикс метки для диапазона страниц."
            :en "The label prefix for page labels in this range.")))))
