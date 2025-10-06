(:файл "doc_annotation"
 :функции
       ((:название "Doc_Page_CreateWidgetAnnot_WhiteOnlyWhilePrint"
	 :группа "annotation"
	 :параметры ((:тип "Doc"
		      :имя "pdf"
		      :ru ":param_pdf"
		      :en ":param_pdf")
		     (:тип "Page"
		      :имя "page"
		      :ru ":param_page"
		      :en ":param_page")
		     (:тип "Rect"
		      :имя "rect"
		      :ru ":param_rect"
		      :en ":param_rect"))
	 :результат (:тип "Annotation"
		     :ru "TODO уточнить. Аннотация в виде белого прямоугольника."
		     :en "TODO refine. White rectangle widget annotation.")))

       ;; BRST_Page_CreateTextAnnot
       (:название "Page_CreateTextAnnot"
	:группа "link"
	:ошибки ("BRST_INVALID_DOCUMENT"
		 "BRST_FAILED_TO_ALLOC_MEM"
		 "BRST_INVALID_ENCODER")
	:результат (:тип "Annotation"
		    :ru ":param_annot"
		    :en ":param_annot")
	:ru "Создание новой текстового пометки на странице."
	:en "Create new text annotation object for the page."
	:параметры ((:тип "Page"
                     :имя "page"
                     :ру ":param_page"
                     :en ":param_page")
                    (:тип "Rect"
                     :имя "rect"
                     :ру "Прямоугольник размещения пометки"
                     :en "Rectangle where annotation is displayed.")
                    (:тип "CSTR"
                     :имя "text"
                     :ру "Текст пометки."
                     :en "Text to be displayed.")
                    (:тип "Encoder"
                     :имя "encoder"
                     :ру "Кодировщик текста"
                     :en "Handle of encoder used to encode text. If NULL, uses PDFDocEncoding.")))

       ;; BRST_Page_CreateFreeTextAnnot

       (:название "Page_CreateFreeTextAnnot"
	:группа "link"
	:ошибки ((BRST_INVALID_DOCUMENT "Неверный документ")
		 (BRST_FAILED_TO_ALLOC_MEM "Ошибка выделения памяти")
		 (BRST_INVALID_ENCODER "Неверный кодировщик"))
	:результат (:тип "Annotation"
		    :ru "Новый объект аннотации"
		    :en "New annotation object.")
	:ru "Создание новой свободной текстовой аннотации на странице."
	:en "Create new free-text annotation object for the page."
	:параметры ((:тип "Page"
                     :имя "page"
                     :ру ":param_page"
                     :en ":param_page")
                    (:тип "Rect"
                     :имя "rect"
                     :ру "Прямоугольник размещения аннотации"
                     :en "Rectangle where annotation is displayed.")
                    (:тип "CSTR"
                     :имя "text"
                     :ру "Текст аннотации"
                     :en "Text to be displayed.")
                    (:тип "Encoder"
                     :имя "encoder"
                     :ру "Обработчик кодировки текста"
                     :en "Handle of encoder used to encode text. If NULL, uses PDFDocEncoding.")))

       ;; BRST_Page_CreateLineAnnot

       (:название "Page_CreateLineAnnot"
	:группа "link"
	:ошибки ((BRST_INVALID_DOCUMENT "Неверный документ")
		 (BRST_FAILED_TO_ALLOC_MEM "Ошибка выделения памяти")
		 (BRST_INVALID_ENCODER "Неверный кодировщик"))
	:результат (:тип "Annotation"
		    :ru "Новый объект аннотации"
		    :en "New annotation object.")
	:ru "Создание линейной аннотации на странице."
	:en "Create new line annotation object for the page."
	:параметры ((:тип "Page"
                     :имя "page"
                     :ру ":param_page"
                     :en ":param_page")
                    (:тип "CSTR"
                     :имя "text"
                     :ру "Текст аннотации"
                     :en "Text to be displayed.")
                    (:тип "Encoder"
                     :имя "encoder"
                     :ру "Обработчик кодировки текста"
                     :en "Handle of encoder used to encode text. If NULL, uses PDFDocEncoding.")))

       ;; BRST_Page_CreateWidgetAnnot

       (:название "Page_CreateWidgetAnnot"
	:группа "link"
	:ошибки ((BRST_INVALID_DOCUMENT "Неверный документ")
		 (BRST_FAILED_TO_ALLOC_MEM "Ошибка выделения памяти"))
	:результат (:тип "Annotation"
		    :ru "Новый объект аннотации"
		    :en "New annotation object.")
	:ru "Создание интерактивного элемента формы на странице."
	:en "Create widget annotation object for the page."
	:параметры ((:тип "Page"
                     :имя "page"
                     :ру ":param_page"
                     :en ":param_page")
                    (:тип "Rect"
                     :имя "rect"
                     :ру "Прямоугольник размещения аннотации"
                     :en "Rectangle where annotation is displayed.")))

       5. BRST_Page_CreateLinkAnnot

       (:название "Page_CreateLinkAnnot"
	:группа "link"
	:ошибки ((BRST_INVALID_PAGE "Неверная страница")
		 (BRST_FAILED_TO_ALLOC_MEM "Ошибка выделения памяти")
		 (BRST_INVALID_DESTINATION "Неверная цель перехода"))
	:результат (:тип "Annotation"
		    :ru "Новый объект аннотации"
		    :en "New annotation object.")
	:ru "Создание аннотации гиперссылки на странице."
	:en "Create new link annotation object for the page."
	:параметры ((:тип "Page"
                     :имя "page"
                     :ру ":param_page"
                     :en ":param_page")
                    (:тип "Rect"
                     :имя "rect"
                     :ру "Зона нажатия аннотации"
                     :en "Clickable rectangle area.")
                    (:тип "Destination"
                     :имя "dst"
                     :ру "Цель перехода"
                     :en "Handle of destination object to jump to.")))

       ;; BRST_Page_CreateURILinkAnnot

       (:название "Page_CreateURILinkAnnot"
	:группа "link"
	:ошибки ((BRST_INVALID_PAGE "Неверная страница")
		 (BRST_FAILED_TO_ALLOC_MEM "Ошибка выделения памяти"))
	:результат (:тип "Annotation"
		    :ru "Новый объект аннотации"
		    :en "New annotation object.")
	:ru "Создание аннотации внешней ссылки на страницу."
	:en "Create new external link annotation object for the page."
	:параметры ((:тип "Page"
                     :имя "page"
                     :ру ":param_page"
                     :en ":param_page")
                    (:тип "Rect"
                     :имя "rect"
                     :ру "Зона нажатия аннотации"
                     :en "Clickable rectangle area.")
                    (:тип "CSTR"
                     :имя "uri"
                     :ру "Адрес ресурса"
                     :en "URI address to navigate to.")))

       ;; BRST_Page_CreateHighlightAnnot

       (:название "Page_CreateHighlightAnnot"
	:группа "link"
	:ошибки ((BRST_INVALID_DOCUMENT "Неверный документ")
		 (BRST_FAILED_TO_ALLOC_MEM "Ошибка выделения памяти")
		 (BRST_INVALID_ENCODER "Неверный кодировщик"))
	:результат (:тип "Annotation"
		    :ru "Новый объект аннотации"
		    :en "New annotation object.")
	:ru "Создание аннотации с выделением текста на странице."
	:en "Create new highlight annotation object for the page."
	:параметры ((:тип "Page"
                     :имя "page"
                     :ру ":param_page"
                     :en ":param_page")
                    (:тип "Rect"
                     :имя "rect"
                     :ру "Прямоугольник размещения аннотации"
                     :en "Rectangle where annotation is displayed.")
                    (:тип "CSTR"
                     :имя "text"
                     :ру "Текст аннотации"
                     :en "Text to be displayed.")
                    (:тип "Encoder"
                     :имя "encoder"
                     :ру "Обработчик кодировки текста"
                     :en "Handle of encoder used to encode text. If NULL, uses PDFDocEncoding.")))

       ;; BRST_Page_CreateUnderlineAnnot

       (:название "Page_CreateUnderlineAnnot"
	:группа "link"
	:ошибки ((BRST_INVALID_DOCUMENT "Неверный документ")
		 (BRST_FAILED_TO_ALLOC_MEM "Ошибка выделения памяти")
		 (BRST_INVALID_ENCODER "Неверный кодировщик"))
	:результат (:тип "Annotation"
		    :ru "Новый объект аннотации"
		    :en "New annotation object.")
	:ru "Создание аннотации подчеркивания текста на странице."
	:en "Create underline annotation object for the page."
	:параметры ((:тип "Page"
                     :имя "page"
                     :ру ":param_page"
                     :en ":param_page")
                    (:тип "Rect"
                     :имя "rect"
                     :ру "Прямоугольник размещения аннотации"
                     :en "Rectangle where annotation is displayed.")
                    (:тип "CSTR"
                     :имя "text"
                     :ру "Текст аннотации"
                     :en "Text to be displayed.")
                    (:тип "Encoder"
                     :имя "encoder"
                     :ру "Обработчик кодировки текста"
                     :en "Handle of encoder used to encode text. If NULL, uses PDFDocEncoding.")))

       9. BRST_Page_CreateSquigglyAnnot

       (:название "Page_CreateSquigglyAnnot"
	:группа "link"
	:ошибки ((BRST_INVALID_DOCUMENT "Неверный документ")
		 (BRST_FAILED_TO_ALLOC_MEM "Ошибка выделения памяти")
		 (BRST_INVALID_ENCODER "Неверный кодировщик"))
	:результат (:тип "Annotation"
		    :ru "Новый объект аннотации"
		    :en "New annotation object.")
	:ru "Создание волнистого подчёркивания текста на странице."
	:en "Create squiggly underline annotation object for the page."
	:параметры ((:тип "Page"
                     :имя "page"
                     :ру ":param_page"
                     :en ":param_page")
                    (:тип "Rect"
                     :имя "rect"
                     :ру "Прямоугольник размещения аннотации"
                     :en "Rectangle where annotation is displayed.")
                    (:тип "CSTR"
                     :имя "text"
                     :ру "Текст аннотации"
                     :en "Text to be displayed.")
                    (:тип "Encoder"
                     :имя "encoder"
                     :ру "Обработчик кодировки текста"
                     :en "Handle of encoder used to encode text. If NULL, uses PDFDocEncoding.")))

       ;; BRST_Page_CreateStrikeOutAnnot

       (:название "Page_CreateStrikeOutAnnot"
	:группа "link"
	:ошибки ((BRST_INVALID_DOCUMENT "Неверный документ")
		 (BRST_FAILED_TO_ALLOC_MEM "Ошибка выделения памяти")
		 (BRST_INVALID_ENCODER "Неверный кодировщик"))
	:результат (:тип "Annotation"
		    :ru "Новый объект аннотации"
		    :en "New annotation object.")
	:ru "Создание зачёркнутого текста на странице."
	:en "Create strike-out annotation object for the page."
	:параметры ((:тип "Page"
                     :имя "page"
                     :ру ":param_page"
                     :en ":param_page")
                    (:тип "Rect"
                     :имя "rect"
                     :ру "Прямоугольник размещения аннотации"
                     :en "Rectangle where annotation is displayed.")
                    (:тип "CSTR"
                     :имя "text"
                     :ру "Текст аннотации"
                     :en "Text to be displayed.")
                    (:тип "Encoder"
                     :имя "encoder"
                     :ру "Обработчик кодировки текста"
                     :en "Handle of encoder used to encode text. If NULL, uses PDFDocEncoding.")))

       ;; BRST_Page_CreatePopupAnnot

       (:название "Page_CreatePopupAnnot"
	:группа "link"
	:ошибки ((BRST_INVALID_DOCUMENT "Неверный документ")
		 (BRST_FAILED_TO_ALLOC_MEM "Ошибка выделения памяти"))
	:результат (:тип "Annotation"
		    :ru "Новый объект аннотации"
		    :en "New annotation object.")
	:ru "Создание всплывающего окна аннотации на странице."
	:en "Create popup annotation object for the page."
	:параметры ((:тип "Page"
                     :имя "page"
                     :ру ":param_page"
                     :en ":param_page")
                    (:тип "Rect"
                     :имя "rect"
                     :ру "Прямоугольник размещения аннотации"
                     :en "Rectangle where annotation is displayed.")
                    (:тип "Annotation"
                     :имя "parent"
                     :ру "Родительская аннотация"
                     :en "Parent annotation handle.")))

       ;; BRST_Page_CreateStampAnnot

       (:название "Page_CreateStampAnnot"
	:группа "link"
	:ошибки ((BRST_INVALID_DOCUMENT "Неверный документ")
		 (BRST_FAILED_TO_ALLOC_MEM "Ошибка выделения памяти")
		 (BRST_INVALID_ENCODER "Неверный кодировщик"))
	:результат (:тип "Annotation"
		    :ru "Новый объект аннотации"
		    :en "New annotation object.")
	:ru "Создание штамп-аннотации на странице."
	:en "Create stamp annotation object for the page."
	:параметры ((:тип "Page"
                     :имя "page"
                     :ру ":param_page"
                     :en ":param_page")
                    (:тип "Rect"
                     :имя "rect"
                     :ру "Прямоугольник размещения аннотации"
                     :en "Rectangle where annotation is displayed.")
                    (:тип "StampAnnotName"
                     :имя "name"
                     :ру "Имя штампа"
                     :en "Name of stamp annotation.")
                    (:тип "CSTR"
                     :имя "text"
                     :ру "Текст аннотации"
                     :en "Text to be displayed.")
                    (:тип "Encoder"
                     :имя "encoder"
                     :ру "Обработчик кодировки текста"
                     :en "Handle of encoder used to encode text. If NULL, uses PDFDocEncoding.")))

       ;; BRST_Page_CreateProjectionAnnot

       (:название "Page_CreateProjectionAnnot"
	:группа "link"
	:ошибки ((BRST_INVALID_DOCUMENT "Неверный документ")
		 (BRST_FAILED_TO_ALLOC_MEM "Ошибка выделения памяти")
		 (BRST_INVALID_ENCODER "Неверный кодировщик"))
	:результат (:тип "Annotation"
		    :ru "Новый объект аннотации"
		    :en "New annotation object.")
	:ru "Создание проекции аннотации на странице."
	:en "Create projection annotation object for the page."
	:параметры ((:тип "Page"
                     :имя "page"
                     :ру ":param_page"
                     :en ":param_page")
                    (:тип "Rect"
                     :имя "rect"
                     :ру "Прямоугольник размещения аннотации"
                     :en "Rectangle where annotation is displayed.")
                    (:тип "CSTR"
                     :имя "text"
                     :ру "Текст аннотации"
                     :en "Text to be displayed.")
                    (:тип "Encoder"
                     :имя "encoder"
                     :ру "Обработчик кодировки текста"
                     :en "Handle of encoder used to encode text. If NULL, uses PDFDocEncoding.")))

       ;; BRST_Page_CreateSquareAnnot

       (:название "Page_CreateSquareAnnot"
	:группа "link"
	:ошибки ((BRST_INVALID_DOCUMENT "Неверный документ")
		 (BRST_FAILED_TO_ALLOC_MEM "Ошибка выделения памяти")
		 (BRST_INVALID_ENCODER "Неверный кодировщик"))
	:результат (:тип "Annotation"
		    :ru "Новый объект аннотации"
		    :en "New annotation object.")
	:ru "Создание квадратной аннотации на странице."
	:en "Create square annotation object for the page."
	:параметры ((:тип "Page"
                     :имя "page"
                     :ру ":param_page"
                     :en ":param_page")
                    (:тип "Rect"
                     :имя "rect"
                     :ру "Прямоугольник размещения аннотации"
                     :en "Rectangle where annotation is displayed.")
                    (:тип "CSTR"
                     :имя "text"
                     :ру "Текст аннотации"
                     :en "Text to be displayed.")
                    (:тип "Encoder"
                     :имя "encoder"
                     :ру "Обработчик кодировки текста"
                     :en "Handle of encoder used to encode text. If NULL, uses PDFDocEncoding.")))

       ;; BRST_Page_CreateCircleAnnot

       (:название "Page_CreateCircleAnnot"
	:группа "link"
	:ошибки ((BRST_INVALID_DOCUMENT "Неверный документ")
		 (BRST_FAILED_TO_ALLOC_MEM "Ошибка выделения памяти")
		 (BRST_INVALID_ENCODER "Неверный кодировщик"))
	:результат (:тип "Annotation"
		    :ru "Новый объект аннотации"
		    :en "New annotation object.")
	:ru "Создание круглой аннотации на странице."
	:en "Create circle annotation object for the page."
	:параметры ((:тип "Page"
                     :имя "page"
                     :ру ":param_page"
                     :en ":param_page")
                    (:тип "Rect"
                     :имя "rect"
                     :ру "Прямоугольник размещения аннотации"
                     :en "Rectangle where annotation is displayed.")
                    (:тип "CSTR"
                     :имя "text"
                     :ру "Текст аннотации"
                     :en "Text to be displayed.")
                    (:тип "Encoder"
                     :имя "encoder"
                     :ру "Обработчик кодировки текста"
                     :en "Handle of encoder used to encode text. If NULL, uses PDFDocEncoding.")))

       ;; BRST_LinkAnnot_SetHighlightMode

       (:название "LinkAnnot_SetHighlightMode"
	:группа "link"
	:ошибки ((BRST_INVALID_ANNOTATION "Неверная аннотация")
		 (BRST_FAILED_TO_ALLOC_MEM "Ошибка выделения памяти"))
	:результат (:тип "STATUS"
		    :ru ":return_ok"
		    :en ":return_ok")
	:ru "Установка стиля подсветки для 


             ))
