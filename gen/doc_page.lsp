(:файл "doc_page"
 :функции
       (
;; Функция BRST_Doc_Pages_SetConfiguration
(:название "Doc_Pages_SetConfiguration"
   :группа "doc"
   :ошибки ("INVALID_DOCUMENT" "INVALID_PARAMETER" "INVALID_DOCUMENT_STATE" "FAILED_TO_ALLOC_MEM")
   :результат (:тип "STATUS"
          :ru ""
          :en "")
   :ru ""
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
   :параметры ((:тип "Doc"
            :имя "pdf"
            :ru ":param_pdf"
            :en ":param_pdf")
           (:тип "UINT"
            :имя "page_per_pages"
            :ru ""
            :en "Numbers of pages `Pages` object can own.")))

;; Функция BRST_Doc_Page_ByIndex
(:название "Doc_Page_ByIndex"
   :группа "page"
   :ошибки ()
   :результат (:тип "Page"
          :ru ""
          :en "")
   :ru ""
   :en ""
   :параметры ((:тип "Doc"
            :имя "pdf"
            :ru ":param_pdf"
            :en ":param_pdf")
           (:тип "UINT"
            :имя "index"
            :ru ""
            :en "")))

;; Функция BRST_Doc_Page_Layout
(:название "Doc_Page_Layout"
   :группа "page"
   :ошибки ()
   :результат (:тип "PageLayout"
          :ru ""
          :en "Page display layout on success. If page layout is not set, returns \\ref BRST_PAGE_LAYOUT_LAST.")
   :ru ""
   :en "Return page display layout."
   :параметры ((:тип "Doc"
            :имя "pdf"
            :ru ":param_pdf"
            :en ":param_pdf")))

;; Функция BRST_Doc_Page_SetLayout
(:название "Doc_Page_SetLayout"
   :группа "page"
   :ошибки ("INVALID_DOCUMENT" "FAILED_TO_ALLOC_MEM" "PAGE_LAYOUT_OUT_OF_RANGE")
   :результат (:тип "STATUS"
          :ru ""
          :en "")
   :ru ""
   :en ""
   :команда ""
   :параметры ((:тип "Doc"
            :имя "pdf"
            :ru ":param_pdf"
            :en ":param_pdf")
           (:тип "PageLayout"
            :имя "layout"
            :ru ""
            :en "")))

;; Функция BRST_Doc_Page_Mode
(:название "Doc_Page_Mode"
   :группа "page"
   :ошибки ()
   :результат (:тип "PageMode"
          :ru ""
          :en "")
   :ru ""
   :en ""
   :команда ""
   :параметры ((:тип "Doc"
            :имя "pdf"
            :ru ":param_pdf"
            :en ":param_pdf")))

;; Функция BRST_Doc_Page_SetMode
(:название "Doc_Page_SetMode"
   :группа "page"
   :ошибки ("INVALID_DOCUMENT" "FAILED_TO_ALLOC_MEM" "PAGE_MODE_OUT_OF_RANGE")
   :результат (:тип "STATUS"
          :ru ""
          :en "")
   :ru ""
   :en ""
   :команда ""
   :параметры ((:тип "Doc"
            :имя "pdf"
            :ru ":param_pdf"
            :en ":param_pdf")
           (:тип "PageMode"
            :имя "mode"
            :ru ""
            :en "")))

;; Функция BRST_Doc_Page_Current
(:название "Doc_Page_Current"
   :группа "page"
   :ошибки ()
   :результат (:тип "Page"
          :ru ""
          :en "")
   :ru ""
   :en ""
   :команда ""
   :параметры ((:тип "Doc"
            :имя "pdf"
            :ru ":param_pdf"
            :en ":param_pdf")))

;; Функция BRST_Doc_Page_Add
(:название "Doc_Page_Add"
   :группа "page"
   :ошибки ("INVALID_DOCUMENT" "FAILED_TO_ALLOC_MEM")
   :результат (:тип "Page"
          :ru ""
          :en "")
   :ru ""
   :en ""
   :команда ""
   :параметры ((:тип "Doc"
            :имя "pdf"
            :ru ":param_pdf"
            :en ":param_pdf")))

;; Функция BRST_Doc_Page_Insert
(:название "Doc_Page_Insert"
   :группа "page"
   :ошибки ("INVALID_DOCUMENT" "FAILED_TO_ALLOC_MEM" "INVALID_PAGE")
   :результат (:тип "Page"
          :ru ""
          :en "")
   :ru ""
   :en ""
   :команда ""
   :параметры ((:тип "Doc"
            :имя "pdf"
            :ru ":param_pdf"
            :en ":param_pdf")
           (:тип "Page"
            :имя "page"
            :ru ""
            :en "")))

;; Функция BRST_Doc_Page_AddLabel
(:название "Doc_Page_AddLabel"
   :группа "page"
   :ошибки ("INVALID_DOCUMENT" "FAILED_TO_ALLOC_MEM" "PAGE_NUM_OUT_OF_RANGE")
   :результат (:тип "STATUS"
          :ru ""
          :en "")
   :ru ""
   :en ""
   :команда ""
   :параметры ((:тип "Doc"
            :имя "pdf"
            :ru ":param_pdf"
            :en ":param_pdf")
           (:тип "UINT"
            :имя "page_num"
            :ru ""
            :en "")
           (:тип "PageNumStyle"
            :имя "style"
            :ru ""
            :en "")
           (:тип "UINT"
            :имя "first_page"
            :ru ""
            :en "")
           (:тип "CSTR"
            :имя "prefix"
            :ru ""
            :en "")))))