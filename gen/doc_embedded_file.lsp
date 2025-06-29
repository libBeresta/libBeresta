(:файл "doc_embedded_file"
 :функции
       ((:название "Doc_AttachFile"
	 :группа "doc"
	 :ошибки ("FAILED_TO_ALLOC_MEM")
	 :результат (:тип "EmbeddedFile"
		     :ru "Описатель объекта вложенного файла при успехе или \\c NULL при возникновении ошибки."
		     :en "Embedded file object desctiptor on success or \\c NULL on failure.")
	 :ru "Функция позволяет вложить файл в PDF-документ."
	 :en "Function attaches file to a PDF document."
	 :параметры ((:тип "Doc"
		      :имя "pdf"
		      :ru ":param_pdf"
		      :en ":param_pdf")
		     (:тип "CSTR"
		      :имя "file"
		      :ru "Имя файла, вкладываемого в PDF."
		      :en "Attached file name")))))
