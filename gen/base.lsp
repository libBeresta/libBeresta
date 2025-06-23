(:файл "base"
 :функции
       ;; === NewEx
       ((:название "NewEx"
	 :группа "doc"
	 :ru "Создает и настраивает экземпляр документа"
	 :en "Create an instance of a document object and initialize it"
	 :см ("New()"
	      "Free()")
	 :результат (:тип "Doc"
		     :ru "Дескриптор объекта документа при успехе и \\c NULL при неудаче."
		     :en "A handle of document object on success and \\c NULL on failure.")
	 :параметры ((:тип "Error_Handler"
		      :имя "user_error_fn"
		      :ru "Пользовательский обработчик ошибок, вызываемые при возникновении ошибок."
		      :en "User-defined error handler which is invoked when an error occurred.")
		     (:тип "Alloc_Func"
		      :имя "user_alloc_fn"
		      :ru "Пользовательская функция распределения памяти. Если указано \\c NULL, используется функция `malloc()`."
		      :en "User-defined memory allocation function. If \\c NULL is specified, `malloc()` is used.")
		     (:тип "Free_Func"
		      :имя "user_free_fn"
		      :ru "Пользовательская функция высвобождения памяти. Елси указано \\c NULL, используется функция `free()`."
		      :en "User-defined memory freeing function. If \\c NULL is specified, `free()` is used.")
		     (:тип "UINT"
		      :имя "mem_pool_buf_size"
		      :ru "\\parblock \\c libBeresto по умолчанию не использует пул памяти.

Функция выделения памяти по требованию вызывается из приложения.

Если параметр установлен в ненулевое значение, управление памятью производится следующим образом:
- память выделяется блоками размера \\c mem_pool_buf_size.
- менеджер памяти отдает приложению память запрошенного размера
  и объединяет оставшуюся память для использования при следующем запросе.
- если размер запрошенной памяти больше, чем оставшаяся память,
  выделяется новый блок памяти.
- неиспользуемая память не освобождается незамедлительно, высвобождение
  производится при вызове BRST_Free().
\\endparblock"
		      :en "\\parblock \\c libHaru does not use memory pool by default.

A memory allocation function is called on demand from an application.

If this parameter set to non-zero value, memory management will be done as following:
- Memory is allocated per \\c mem_pool_buf_size.
- Memory manager gives memory of requested size to an
  application, and pools remaining memory to use at next
  request.
- If the size of requested memory is larger than the
  remaining memory, a new memory block is allocated.
- Unused memory is not released immediately. It is released
  all together when HPDF_Free() is invoked.
  \\endparblock"
			   (:тип "RAW_POINTER"
			    :имя "user_data"
			    :ru "Указатель на пользовательские данные, используемый в обработчике ошибок."
			    :en "User-defined void pointer. This pointer is used by error handling."))))

	;; === Version
	(:название "Version"
	 :группа "doc"
	 :ru "Возвращает версию библиотеки"
	 :en "Returns library version"
	 :результат (:тип "CSTR"
		     :ru "Версия библиотеки"
		     :en "Library version")
	 :параметры ())

	;; === New
	(:название "New"
	 :группа "doc"
	 :ru "Создает объект документа и настраивает его"
	 :en "Create document and set it up"
	 :параметры ((:тип "Error_Handler"
		      :имя "user_error_fn"
		      :ru "Пользовательская функция обработки, вызываемая при возникновении ошибки."
		      :en "User-defined error handler which is invoked when an error occurred.")
		     (:тип "RAW_POINTER"
		      :имя "user_data"
		      :ru "Указатель на пользовательские данные, передаваемые в обработчик ошибок."
		      :en "User-defined void pointer. This pointer is used by error handling."))
	 :результат (:тип "Doc"
		     :ru "Дескриптор объекта документа при успехе и \\c NULL при неудаче."
		     :en "A handle of document object on success and \\c NULL on failure.")
	 :см ("New()"
	      "Free()"))

	;; === Doc_Init
	(:название "HPDF_Doc_Initialize"
	 :группа "doc"
	 :ru "Настраивает документ. Если документ \\c doc уже настроен, он предварительно очищается"
	 :en "Create a new document. If \\c doc object already has a document, the current document is revoked."
	 :параметры ((:тип "Doc"
		      :имя "pdf"
		      :ru ":param_pdf"
		      :en ":param_pdf"))
	 :результат (:тип "STATUS"
		     :ru ":return_ok"
		     :en ":return_ok")
	 :см ("Doc_Destroy()")
	 :ошибки ("INVALID_DOCUMENT"
		  "FAILED_TO_ALLOC_MEM"))

	;; === Doc_Destroy
	(:название "Doc_Destroy"
	 :группа "doc"
	 :ru "Очищает внутренние структуры документа."
	 :en "Releases inner document structures."
	 :параметры ((:тип "Doc"
		      :имя "pdf"
		      :ru ":param_pdf"
		      :en ":param_pdf"))
	 :результат (:тип "void"
		     :ru "Нет"
		     :en "No")
	 :см ("Doc_Initialize()"
	      "Doc_Destroy_All()"))

	;; === Doc_Initialized
	(:название "Doc_Initialized"
	 :группа "doc"
	 :ru "Проверяет, что описатель объекта документа корректен."
	 :en "Checks if document handle is valid."
	 :параметры ((:тип "Doc"
		      :имя "pdf"
		      :ru ":param_pdf"
		      :en ":param_pdf"))
	 :результат (:тип "BOOL"
		     :ru "\\ref BRST_TRUE если описатель документа корректен, иначе возвращает \\ref BRST_FALSE, устанавливает код ошибки и вызывает обработчик ошибок."
		     :en "\\ref BRST_TRUE if the specified document handle is valid. Otherwise return \\ref BRST_FALSE, set error code and call error handler.")
	 :ошибки ("INVALID_DOCUMENT")
	 :см ("Doc_Initialize()"))

	;; === Doc_Destroy_All
	(:название "Doc_Destroy_All"
	 :группа "doc"
	 :ru "Очищает внутренние структуры документа.

Функция высвобождает загруженные ресурсы (вроде шрифтов и кодировок)."
	 :en "Releases inner document structures and frees loaded resources (such as fonts and encodings)"
	 :параметры ((:тип "Doc"
		      :имя "pdf"
		      :ru ":param_pdf"
		      :en ":param_pdf"))
	 :результат (:тип "void"
		     :ru "Нет"
		     :en "No")
	 :см ("Doc_Initialize()"
	      "Doc_Destroy()"))

	;; === Doc_Contents
	(:название "Doc_Contents"
	 :группа "doc"
	 :ru "Копирует содержимое документа в предоставленный буфер"
	 :en "Copy document data to given buffer"
	 :параметры ((:тип "Doc"
		      :имя "pdf"
		      :ru ":param_pdf"
		      :en ":param_pdf")
		     (:тип "BYTE*"
		      :имя "buf"
		      :ru "Указатель на подготовленный буфер"
		      :en "Output buffer pointer")
		     (:тип "UINT32*"
		      :имя "size"
		      :ru "Размер данных в выходном буфере"
		      :en "Output buffer size"))
	 :результат (:тип "STATUS"
		     :ru "\\ref BRST_OK если удалось записать содержимое документа в буфер, иначе возвращает код ошибки."
		     :en "\\ref BRST_OK on success copying. Otherwise returns error code.")
	 :ошибки ("INVALID_DOCUMENT"))
	
	;; === Doc_MMgr
	(:название "Doc_MMgr"
	 :группа "doc"
	 :ru "Возвращает менеджер памяти документа"
	 :en "Returns document's memory manager"
	 :параметры ((:тип "Doc"
		      :имя "pdf"
		      :ru ":param_pdf"
		      :en ":param_pdf")
		     )
	 :результат (:тип "MMgr"
		     :ru "Менеджер памяти документа, если он установлен."
		     :en "Document's memory manager"))
	))
