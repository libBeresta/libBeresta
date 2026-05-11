(:file "image"
 :definitions
       ((:name "Image"
         :original "Dict"))
 :functions (
	     ;; BRST_Image_AddSMask
	     (:caption "Image_AddSMask"
              :group "image"
              :errors ()
              :result (:type "STATUS"
                       :ru ":return_ok"
                       :en ":return_ok")
              :ru "Добавляет мягкую маску (SMask) к изображению."
              :en "Adds a soft mask (SMask) to the image."
              :params ((:type "Image"
			:name "image"
			:ru ":param_image"
			:en ":param_image")
                       (:type "Image"
			:name "smask"
			:ru ":param_image"
			:en ":param_image")))

	     ;; Disabled until `Point` struct reworked
	     ;;
	     ;; BRST_Image_Size
	     ;; (:caption "Image_Size"
             ;;  :group "image"
             ;;  :errors ()
             ;;  :result (:type "Point"
             ;;           :ru "Возвращает структуру BRST_Point с размером изображения, либо {0, 0} при ошибке."
             ;;           :en "Returns a BRST_Point structure with image size, or {0, 0} on error.")
             ;;  :ru "Получает размер изображения."
             ;;  :en "Gets the size of the image."
             ;;  :params ((:type "Image"
	     ;; 		:name "image"
	     ;; 		:ru ":param_image"
	     ;; 		:en ":param_image")))

	     ;; BRST_Image_Size2
	     ;; (:caption "Image_Size2"
             ;;  :group "image"
             ;;  :errors ()
             ;;  :result (:type "STATUS"
             ;;           :ru ":return_ok"
             ;;           :en ":return_ok")
             ;;  :ru "Получает размер изображения и записывает его в параметр size. Возвращает BRST_OK при успехе."
             ;;  :en "Gets the size of the image and writes it to the size parameter. Returns BRST_OK on success."
             ;;  :params ((:type "Image"
	     ;; 		:name "image"
	     ;; 		:ru ":param_image"
	     ;; 		:en ":param_image")
             ;;           (:type "Point*"
	     ;; 		:name "size"
	     ;; 		:ru "Переменная для возврата размера изображения."
	     ;; 		:en "Variable to return image size to.")))

	     ;; BRST_Image_Width
	     (:caption "Image_Width"
              :group "image"
              :errors ()
              :result (:type "UINT"
                       :ru "Ширина изображения, либо 0 при ошибке."
                       :en "Image width, or 0 on error.")
              :ru "Получает ширину изображения."
              :en "Gets the width of the image."
              :params ((:type "Image"
			:name "image"
			:ru ":param_image"
			:en ":param_image")))

	     ;; BRST_Image_Height
	     (:caption "Image_Height"
              :group "image"
              :errors ()
              :result (:type "UINT"
                       :ru "Высота изображения, либо 0 при ошибке."
                       :en "Image height, or 0 on error.")
              :ru "Получает высоту изображения."
              :en "Gets the height of the image."
              :params ((:type "Image"
			:name "image"
			:ru ":param_image"
			:en ":param_image")))

	     ;; BRST_Image_BitsPerComponent
	     (:caption "Image_BitsPerComponent"
              :group "image"
              :errors ()
              :result (:type "UINT"
                       :ru "Количество бит на компонент цвета, либо 0 при ошибке."
                       :en "Bits per color component, or 0 on error.")
              :ru "Получает количество бит, используемых для описания каждого цветового компонента."
              :en "Gets the bit count used to describe each color component."
              :params ((:type "Image"
			:name "image"
			:ru ":param_image"
			:en ":param_image")))

	     ;; BRST_Image_ColorSpace
	     (:caption "Image_ColorSpace"
              :group "image"
              :errors ()
              :result (:type "CSTR"
                       :ru "Имя цветового пространства, либо NULL при ошибке."
                       :en "Color space name, or NULL on error.")
              :ru "Получает имя цветового пространства изображения."
              :en "Gets the image color space name."
              :params ((:type "Image"
			:name "image"
			:ru ":param_image"
			:en ":param_image")))

	     ;; BRST_Image_SetColorMask
	     (:caption "Image_SetColorMask"
              :group "image"
              :errors ()
              :result (:type "STATUS"
                       :ru ":return_ok"
                       :en ":return_ok")
              :ru "Устанавливает прозрачный цвет изображения по диапазону значений RGB. Изображение должно иметь цветовое пространство RGB."
              :en "Sets the transparent color of the image by the RGB range values. The image must have RGB color space."
              :params ((:type "Image"
			:name "image"
			:ru ":param_image"
			:en ":param_image")
                       (:type "UINT"
			:name "rmin" 
			:ru "Нижний предел красного цвета. Должен быть в диапазоне от 0 до 255." 
			:en "Lower limit of red color. Must be in range 0 to 255.")
                       (:type "UINT"
			:name "rmax"
			:ru "Верхний предел красного цвета. Должен быть в диапазоне от 0 до 255." 
			:en "Upper limit of red color. Must be in range 0 to 255.")
                       (:type "UINT"
			:name "gmin" 
			:ru "Нижний предел зелёного цвета. Должен быть в диапазоне от 0 до 255."
			:en "Lower limit of green color. Must be in range 0 to 255.")
                       (:type "UINT"
			:name "gmax"
			:ru "Верхний предел зелёного цвета. Должен быть в диапазоне от 0 до 255."
			:en "Upper limit of green color. Must be in range 0 to 255.")
                       (:type "UINT"
			:name "bmin" 
			:ru "Нижний предел синего цвета. Должен быть в диапазоне от 0 до 255."
			:en "Lower limit of blue color. Must be in range 0 to 255.")
                       (:type "UINT"
			:name "bmax"
			:ru "Верхний предел синего цвета. Должен быть в диапазоне от 0 до 255."
			:en "Upper limit of blue color. Must be in range 0 to 255.")))

	     ;; BRST_Image_SetMaskImage
	     (:caption "Image_SetMaskImage"
              :group "image"
              :errors ()
              :result (:type "STATUS"
                       :ru ":return_ok"
                       :en ":return_ok")
              :ru "Устанавливает маску изображения. Маска должна быть 1-битным серым изображением."
              :en "Sets an image mask. The mask image must be a 1-bit gray-scale image."
              :params ((:type "Image"
			:name "image"
			:ru ":param_image"
			:en ":param_image")
                       (:type "Image"
			:name "mask_image" 
			:ru "Задаёт дескриптор объекта изображения, используемого как маска. Это изображение должно быть 1-битным серым." 
			:en "Specifies an image object handle to be used as an image mask. This image must be a 1-bit gray-scale image.")))
	     ))
