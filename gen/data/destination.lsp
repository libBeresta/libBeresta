(:file "destination"
 :imports ("external" "types" "array")
 :definitions
       ((:name "Destination"
	 :original "Array"))
 :functions (
	   ;; === Destination_SetXYZ
	   (:caption "Destination_SetXYZ"
	    :group "link"
	    :ru "Демонстрация страницы, указываемой \\c dst, с позиционированием \\c left, \\c top и масштабом \\c zoom."
	    :en "Define page appearance with three parameters which are \\c left, \\c top and \\c zoom."
	    :result (:type "STATUS"
			:ru ":return_ok"
			:en ":return_ok")
	    :errors ("INVALID_DESTINATION"
		     "INVALID_PARAMETER")
	    :params ((:type "Destination"
			 :name "dst"
			 :ru ":param_dst"
			 :en ":param_dst")
			(:type "REAL"
			 :name "left"
			 :ru "Левая координата на странице для позиционирования окна"
			 :en "Left coordinate of the page to position window")
			(:type "REAL"
			 :name "top"
			 :ru "Верхняя координата на странице для позиционирования окна"
			 :en "Top coordinate of the page to position window")
			(:type "REAL"
			 :name "zoom"
			 :ru "Множитель масштабирования содержимого страницы. Значение должно быть в диапазоне от \\c 0.08 (8%) до \\c 32 (3200%)."
			 :en "Page contents magnified by zoom factor. Value must be between \\c 0.08 (8%) and \\c 32 (3200%).")))

	   ;; === Destination_SetFit
	   (:caption "Destination_SetFit"
	    :group "link"
	    :ru "Демонстрация страницы, указываемой \\c dst, с полным включение страницы в окно."
	    :en "Set page appearance to display entire page within the window"
	    :result (:type "STATUS"
			:ru ":return_ok"
			:en ":return_ok")
	    :errors ("INVALID_DESTINATION")
	    :params ((:type "Destination"
			 :name "dst"
			 :ru ":param_dst"
			 :en ":param_dst")))

	   ;; === Destination_SetFitH
	   (:caption "Destination_SetFitH"
	    :group "link"
	    :ru "Демонстрация страницы, указываемой \\c dst, с позиционированием \\c top, вместив страницу в окно по ширине."
	    :en "Define page appearance to fit page width within the window and set top position of the page \\c top parameter."
	    :result (:type "STATUS"
			:ru ":return_ok"
			:en ":return_ok")
	    :errors ("INVALID_DESTINATION"
		     "INVALID_PARAMETER")
	    :params ((:type "Destination"
			 :name "dst"
			 :ru ":param_dst"
			 :en ":param_dst")
			(:type "REAL"
			 :name "top"
			 :ru "Верхняя координата на странице для позиционирования окна"
			 :en "Top coordinate of the page to position window")))

	   ;; === Destination_SetFitV
	   (:caption "Destination_SetFitV"
	    :group "link"
	    :ru "Демонстрация страницы, указываемой \\c dst, с позиционированием \\c left, вместив страницу по высоте"
	    :en "Define page appearance to fit page height within the window and set left position of the page \\c left parameter."
	    :result (:type "STATUS"
			:ru ":return_ok"
			:en ":return_ok")
	    :errors ("INVALID_DESTINATION")
	    :params ((:type "Destination"
			 :name "dst"
			 :ru ":param_dst"
			 :en ":param_dst")
			(:type "REAL"
			 :name "left"
			 :ru "Левая координата на странице для позиционирования окна"
			 :en "Left coordinate of the page to position window")))

	   ;; === Destination_SetFitR
	   (:caption "Destination_SetFitR"
	    :group "link"
	    :ru "Демонстрация страницы, указываемой \\c dst, таким образом, чтобы вписать прямоугольник, задаваемый \\c left, \\c top, \\c right, \\c bottom, в окно."
	    :en "Define page appearance with three parameters which are \\c left, \\c top, \\c right, \\c bottom"
	    :result (:type "STATUS"
			:ru ":return_ok"
			:en ":return_ok")
	    :errors ("INVALID_DESTINATION"
		     "INVALID_PARAMETER")
	    :params ((:type "Destination"
			 :name "dst"
			 :ru ":param_dst"
			 :en ":param_dst")
			(:type "REAL"
			 :name "left"
			 :ru "Левая координата на странице для позиционирования окна"
			 :en "Left coordinate of the page to position window")
			(:type "REAL"
			 :name "bottom"
			 :ru "Нижняя координата на странице для позиционирования окна"
			 :en "Bottom coordinate of the page to position window")
			(:type "REAL"
			 :name "right"
			 :ru "Правая координата на странице для позиционирования окна"
			 :en "Right coordinate of the page to position window")
			(:type "REAL"
			 :name "top"
			 :ru "Верхняя координата на странице для позиционирования окна"
			 :en "Top coordinate of the page to position window")))

	   ;; === Destination_SetFitB
	   (:caption "Destination_SetFitB"
	    :group "link"
	    :version "1.1"
	    :ru "Демонстрация страницы, указываемой \\c dst, с полным включение охватывающего прямоугольника (bounding box) в окно."
	    :en "Set page appearance to display page bounding box within the window"
	    :result (:type "STATUS"
			:ru ":return_ok"
			:en ":return_ok")
	    :errors ("INVALID_DESTINATION")
	    :params ((:type "Destination"
			 :name "dst"
			 :ru ":param_dst"
			 :en ":param_dst")))

	   ;; === Destination_SetFitBH
	   (:caption "Destination_SetFitBH"
	    :group "link"
	    :ru "Демонстрация страницы, указываемой \\c dst, с позиционированием \\c top, вместив охватывающий прямоугольник (bounding box) страницы в окно по ширине."
	    :en "Define page appearance to fit page bounding box width within the window and set top position of the page \\c top parameter."
	    :version "1.1"
	    :result (:type "STATUS"
			:ru ":return_ok"
			:en ":return_ok")
	    :errors ("INVALID_DESTINATION"
		     "INVALID_PARAMETER")
	    :params ((:type "Destination"
			 :name "dst"
			 :ru ":param_dst"
			 :en ":param_dst")
			(:type "REAL"
			 :name "top"
			 :ru "Верхняя координата на странице для позиционирования окна"
			 :en "Top coordinate of the page to position window")))

	   ;; === Destination_SetFitBV
	   (:caption "Destination_SetFitBV"
	    :group "link"
	    :ru "Демонстрация страницы, указываемой \\c dst, с позиционированием \\c left, вместив охватывающий прямоугольник (bounding box) страницы по высоте."
	    :en "Define page appearance to fit page bounding box height within the window and set left position of the page \\c left parameter."
	    :version "1.1"
	    :result (:type "STATUS"
			:ru ":return_ok"
			:en ":return_ok")
	    :errors ("INVALID_DESTINATION")
	    :params ((:type "Destination"
			 :name "dst"
			 :ru ":param_dst"
			 :en ":param_dst")
			(:type "REAL"
			 :name "left"
			 :ru "Левая координата на странице для позиционирования окна"
			 :en "Left coordinate of the page to position window")))
	   ))
