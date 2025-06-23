(:файл "destination"
 :импорты ("external" "types" "array")
 :определения
       ((:имя "Destination"
	 :оригинал "Array"))
 :функции (
	   ;; === Destination_SetXYZ
	   (:название "Destination_SetXYZ"
	    :группа "link"
	    :ru "Демонстрация страницы, указываемой \\c dst, с позиционированием \\c left, \\c top и масштабом \\c zoom."
	    :en "Define page appearance with three parameters which are \\c left, \\c top and \\c zoom."
	    :результат (:тип "STATUS"
			:ru ":return_ok"
			:en ":return_ok")
	    :ошибки ("INVALID_DESTINATION"
		     "INVALID_PARAMETER")
	    :параметры ((:тип "Destination"
			 :имя "dst"
			 :ru ":param_dst"
			 :en ":param_dst")
			(:тип "REAL"
			 :имя "left"
			 :ru "Левая координата на странице для позиционирования окна"
			 :en "Left coordinate of the page to position window")
			(:тип "REAL"
			 :имя "top"
			 :ru "Верхняя координата на странице для позиционирования окна"
			 :en "Top coordinate of the page to position window")
			(:тип "REAL"
			 :имя "zoom"
			 :ru "Множитель мастабирования содержимого страницы. Значение должно быть в диапазоне от 0.08 (8%) до 32 (3200%)."
			 :en "Page contents magnified by zoom factor. Value must be between 0.08 (8%) and 32 (3200%).")))

	   ;; === Destination_SetFit
	   (:название "Destination_SetFit"
	    :группа "link"
	    :ru "Демонстрация страницы, указываемой \\c dst, с полным включение страницы в окно."
	    :en "Set page appearance to display entire page within the window"
	    :результат (:тип "STATUS"
			:ru ":return_ok"
			:en ":return_ok")
	    :ошибки ("INVALID_DESTINATION")
	    :параметры ((:тип "Destination"
			 :имя "dst"
			 :ru ":param_dst"
			 :en ":param_dst")))

	   ;; === Destination_SetFitH
	   (:название "Destination_SetFitH"
	    :группа "link"
	    :ru "Демонстрация страницы, указываемой \\c dst, с позиционированием \\c top, вместив страницу в окно по ширине."
	    :en "Define page appearance to fit page width within the window and set top position of the page \\c top parameter."
	    :результат (:тип "STATUS"
			:ru ":return_ok"
			:en ":return_ok")
	    :ошибки ("INVALID_DESTINATION"
		     "INVALID_PARAMETER")
	    :параметры ((:тип "Destination"
			 :имя "dst"
			 :ru ":param_dst"
			 :en ":param_dst")
			(:тип "REAL"
			 :имя "top"
			 :ru "Верхняя координата на странице для позиционирования окна"
			 :en "Top coordinate of the page to position window")))

	   ;; === Destination_SetFitV
	   (:название "Destination_SetFitV"
	    :группа "link"
	    :ru "Демонстрация страницы, указываемой \\c dst, с позиционированием \\c left, вместив страницу по высоте"
	    :en "Define page appearance to fit page height within the window and set left position of the page \\c left parameter."
	    :результат (:тип "STATUS"
			:ru ":return_ok"
			:en ":return_ok")
	    :ошибки ("INVALID_DESTINATION")
	    :параметры ((:тип "Destination"
			 :имя "dst"
			 :ru ":param_dst"
			 :en ":param_dst")
			(:тип "REAL"
			 :имя "left"
			 :ru "Левая координата на странице для позиционирования окна"
			 :en "Left coordinate of the page to position window")))

	   ;; === Destination_SetR
	   (:название "Destination_SetR"
	    :группа "link"
	    :ru "Демонстрация страницы, указываемой \\c dst, таким образом, чтобы вписать прямоугольник, задаваемый \\c left, \\c top, \\c right, \\c bottom, в окно."
	    :en "Define page appearance with three parameters which are \\c left, \\c top, \\c right, \\c bottom"
	    :результат (:тип "STATUS"
			:ru ":return_ok"
			:en ":return_ok")
	    :ошибки ("INVALID_DESTINATION"
		     "INVALID_PARAMETER")
	    :параметры ((:тип "Destination"
			 :имя "dst"
			 :ru ":param_dst"
			 :en ":param_dst")
			(:тип "REAL"
			 :имя "left"
			 :ru "Левая координата на странице для позиционирования окна"
			 :en "Left coordinate of the page to position window")
			(:тип "REAL"
			 :имя "bottom"
			 :ru "Нижняя координата на странице для позиционирования окна"
			 :en "Bottom coordinate of the page to position window")
			(:тип "REAL"
			 :имя "right"
			 :ru "Правая координата на странице для позиционирования окна"
			 :en "Right coordinate of the page to position window")
			(:тип "REAL"
			 :имя "top"
			 :ru "Верхняя координата на странице для позиционирования окна"
			 :en "Top coordinate of the page to position window")))

	   ;; === Destination_SetFitB
	   (:название "Destination_SetFitB"
	    :группа "link"
	    :версия "1.1"
	    :ru "Демонстрация страницы, указываемой \\c dst, с полным включение охватывающего прямоугольника (bounding box) в окно."
	    :en "Set page appearance to display page bounding box within the window"
	    :результат (:тип "STATUS"
			:ru ":return_ok"
			:en ":return_ok")
	    :ошибки ("INVALID_DESTINATION")
	    :параметры ((:тип "Destination"
			 :имя "dst"
			 :ru ":param_dst"
			 :en ":param_dst")))

	   ;; === Destination_SetFitBH
	   (:название "Destination_SetFitBH"
	    :группа "link"
	    :ru "Демонстрация страницы, указываемой \\c dst, с позиционированием \\c top, вместив охватывающий прямоугольник (bounding box) страницы в окно по ширине."
	    :en "Define page appearance to fit page bounding box width within the window and set top position of the page \\c top parameter."
	    :версия "1.1"
	    :результат (:тип "STATUS"
			:ru ":return_ok"
			:en ":return_ok")
	    :ошибки ("INVALID_DESTINATION"
		     "INVALID_PARAMETER")
	    :параметры ((:тип "Destination"
			 :имя "dst"
			 :ru ":param_dst"
			 :en ":param_dst")
			(:тип "REAL"
			 :имя "top"
			 :ru "Верхняя координата на странице для позиционирования окна"
			 :en "Top coordinate of the page to position window")))

	   ;; === Destination_SetFitBV
	   (:название "Destination_SetFitBV"
	    :группа "link"
	    :ru "Демонстрация страницы, указываемой \\c dst, с позиционированием \\c left, вместив охватывающий прямоугольник (bounding box) страницы по высоте."
	    :en "Define page appearance to fit page bounding box height within the window and set left position of the page \\c left parameter."
	    :версия "1.1"
	    :результат (:тип "STATUS"
			:ru ":return_ok"
			:en ":return_ok")
	    :ошибки ("INVALID_DESTINATION")
	    :параметры ((:тип "Destination"
			 :имя "dst"
			 :ru ":param_dst"
			 :en ":param_dst")
			(:тип "REAL"
			 :имя "left"
			 :ru "Левая координата на странице для позиционирования окна"
			 :en "Left coordinate of the page to position window")))
	   ))
