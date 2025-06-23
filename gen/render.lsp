(ql:quickload 'djula :silent t)

(defvar *префикс* "BRST")
(defvar *язык* :ru)

(defparameter +типы-без-префикса+
  (list "void*" "const char*" "void"))

(defparameter +подстановки+
  '(((":param_pdf"     . :en) . "Document object handle.")
    ((":param_page"    . :en) . "Page object handle.")
    ((":param_font"    . :en) . "Font object handle.")
    ((":param_encoder" . :en) . "Encoder object handle.")
    ((":param_annot"   . :en) . "Annotation object handle.")
    ((":param_outline" . :en) . "Outline object handle.")
    ((":param_image"   . :en) . "Image object handle.")
    ((":param_dst"     . :en) . "Destination object handle.")
    ((":param_embedded_file" . :en) . "Embedded file object handle.")
    ((":return_ok"     . :en) . "\\ref HPDF_OK on success, otherwise returns error code and calls error handler.")
    ((":error-codes"   . :en) . "\\par Error codes")

    ((":param_pdf"     . :ru) . "Описатель объекта документа.")
    ((":param_page"    . :ru) . "Описатель объекта страницы.")
    ((":param_font"    . :ru) . "Описатель объекта шрифта.")
    ((":param_encoder" . :ru) . "Описатель объекта раскодировщика.")
    ((":param_annot"   . :ru) . "Описатель объекта аннотации.")
    ((":param_outline" . :ru) . "Описатель объекта outline.")
    ((":param_image"   . :ru) . "Описатель объекта изображения.")
    ((":param_dst"     . :ru) . "Описатель объекта места назначения.")
    ((":param_embedded_file" . :ru) . "Описатель объекта вложенного файла.")
    ((":return_ok"     . :ru) . "\\ref HPDF_OK при успешном выполнении, иначе возвращает код ошибки и вызывает обработчик ошибок.")
    ((":error-codes"   . :ru) . "\\par Коды ошибок")))

(defparameter +заданные-подстановки+
  '(error-codes)
  "Набор переменных, используемых в шаблонах.
Этим переменным должны соответствовать значения в +подстановки+")

(defvar *типы-без-префикса*
  (let* ((hash (make-hash-table :test #'equal)))
    (mapcar #'(lambda (x) (setf (gethash x hash) t)) +типы-без-префикса+)
    hash))

(defvar *подстановки*
  (let ((hash (make-hash-table :test #'equal)))
    (mapcar #'(lambda (x) (setf (gethash (car x) hash) (cdr x))) +подстановки+)
    hash))

;; На вход получаем p-список, в котором должен быть задан текст с ключом
;; *язык* (:ru, :en и т.д.)
;; На выходе получаем либо строку, заданную указанным ключом, либо строку
;; "Текст для языка :ru не задан" // :ru, :en и т.д.
(djula:def-filter :docf (arg)
  (let* ((текст (getf arg *язык*))
	 (проверено (or текст (format nil
				      "Текст :~A не задан"
				      (string-downcase (string *язык*)))))
	 (подстановка (gethash (cons проверено *язык*) *подстановки*)))
    (or подстановка проверено)))

(djula:def-filter :pre (arg)
  (if (gethash arg *типы-без-префикса*)
      arg
      (concatenate 'string *префикс* "_" arg)))

(djula:def-filter :err (arg fn)
  (format nil "Поле ~A '~A' не задано" arg fn))

(defun do-render (template-file
		  data-file
		  &optional &key
			      (lang *язык*)
			      (output :нет))
  (mapcar #'(lambda (x)
	      (let* ((стр (string x))
		     (клч (intern стр :keyword))
		     (знч (string-downcase (concatenate 'string ":" стр)))
		     (подстановка (gethash (cons знч *язык*) *подстановки*)))
		(setf (getf djula:*default-template-arguments* клч) подстановка)))
	  +заданные-подстановки+)

  (let* ((*язык* lang)
	 (template (djula:compile-template* template-file))
	 (data (with-open-file (s data-file) (read s))))
    (let ((res (apply #'djula:render-template*
		      (cons template
			    (cons nil
				  data)))))

      (princ djula:*default-template-arguments*)
      (if (eq output :нет)
	  (princ res)
	  (alexandria:write-string-into-file
	   res
	   output
	   :if-exists :overwrite
	   :if-does-not-exist :create)))))
