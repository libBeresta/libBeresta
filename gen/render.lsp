(ql:quickload 'djula :silent t)

(defvar *prefix* "BRST")
(defvar *language* :ru)

(defparameter +no-prefix-types+
  (list "void*" "const char*" "void"))

(defparameter +substitutes+
  '(((":param_pdf"     . :en) . "Document object handle.")
    ((":param_page"    . :en) . "Page object handle.")
    ((":param_font"    . :en) . "Font object handle.")
    ((":param_ext_gstate" . :en) . "Extended graphics state object handle.")
    ((":param_rect"    . :en) . "Rectangle object.")
    ((":param_date"    . :en) . "Date object handle.")
    ((":param_dict"    . :en) . "Dictionary object handle.")
    ((":param_encoder" . :en) . "Encoder object handle.")
    ((":param_annot"   . :en) . "Annotation object handle.")
    ((":param_outline" . :en) . "Outline object handle.")
    ((":param_image"   . :en) . "Image object handle.")
    ((":param_matrix"  . :en) . "Matrix object handle.")
    ((":param_stream"  . :en) . "Stream object handle.")
    ((":param_xobject" . :en) . "XObject object handle.")
    ((":param_dst"     . :en) . "Destination object handle.")
    ((":param_embedded_file" . :en) . "Embedded file object handle.")
    ((":return_ok"     . :en) . "\\ref BRST_OK on success, otherwise returns error code and calls error handler.")
    ((":error-codes"   . :en) . "\\par Error codes")

    ((":param_pdf"     . :ru) . "Описатель объекта документа.")
    ((":param_page"    . :ru) . "Описатель объекта страницы.")
    ((":param_font"    . :ru) . "Описатель объекта шрифта.")
    ((":param_ext_gstate" . :en) . "Описатель объекта расширенного графического состояния.")
    ((":param_rect"    . :ru) . "Объект прямоугольника.")
    ((":param_date"    . :ru) . "Описатель объекта даты.")
    ((":param_dict"    . :ru) . "Описатель объекта словаря.")
    ((":param_encoder" . :ru) . "Описатель объекта кодировщика.")
    ((":param_annot"   . :ru) . "Описатель объекта аннотации.")
    ((":param_outline" . :ru) . "Описатель объекта outline.")
    ((":param_image"   . :ru) . "Описатель объекта изображения.")
    ((":param_matrix"  . :ru) . "Описатель объекта матрицы преобразования.")
    ((":param_stream"  . :ru) . "Описатель объекта потока.")
    ((":param_xobject" . :ru) . "Описатель объекта XObject.")
    ((":param_dst"     . :ru) . "Описатель объекта места назначения.")
    ((":param_embedded_file" . :ru) . "Описатель объекта вложенного файла.")
    ((":return_ok"     . :ru) . "\\ref BRST_OK при успешном выполнении, иначе возвращает код ошибки и вызывает обработчик ошибок.")
    ((":error-codes"   . :ru) . "\\par Коды ошибок")))

(defparameter +ecl-types+
  '((       "string" .       ":cstring")
    (         "int8" .          ":byte")
    (        "uint8" . ":unsigned-byte")
    (        "int16" .       ":int16-t")
    (       "uint16" .      ":uint16-t")
    (        "int32" .       ":int32-t")
    (       "uint32" .      ":uint32-t")
    (        "int64" .       ":int64-t")
    (       "uint64" .      ":uint64-t")
    (      "pointer" .  ":pointer-void")
    (        "float" .         ":float")
    (       "double" .        ":double")
    (         "void" .          ":void")


    (          "PDF" .  ":pointer-void")     
    (          "DOC" .  ":pointer-void")     
    (         "MMGR" .  ":pointer-void")     
    (         "PAGE" .  ":pointer-void")     
    (         "DICT" .  ":pointer-void")
    (      "ENCODER" .  ":pointer-void")
    (         "CSTR" .       ":cstring")
    (          "INT" .       ":int32-t")
    (         "UINT" .      ":uint32-t")
    (        "UINT*" .  ":pointer-void")
    (        "INT64" .       ":int64-t")
    (       "UINT64" .      ":uint64-t")
    (        "INT32" .       ":int32-t")
    (       "UINT32" .      ":uint32-t")
    (        "INT16" .       ":int16-t")
    (       "UINT16" .      ":uint16-t")
    (         "INT8" .        ":int8-t")
    (        "UINT8" . ":unsigned-byte")
    (         "BYTE" . ":unsigned-byte")
    (        "BYTE*" . ":pointer-void")
    (         "REAL" .         ":float")
    (        "REAL*" .  ":pointer-void")
    (       "DOUBLE" .        ":double")
    (         "BOOL" .       ":int32-t")
    (       "STATUS" .      ":uint32-t")
    (          "CID" .      ":uint16-t")
    (         "void" .          ":void")
    (      "UNICODE" .      ":uint16-t")
    (  "RAW-POINTER" .  ":pointer-void")
    (       "Point*" .  ":pointer-void")
    ( "DASH-PATTERN" .  ":pointer-void")
    ("Error-Handler" .  ":pointer-void")    
    (   "Alloc-Func" .  ":pointer-void")    
    ("Free-Func"     .  ":pointer-void")))

(defparameter +given-substitutes+
  '(error-codes)
  "Набор переменных, используемых в шаблонах.
Этим переменным должны соответствовать значения в +подстановки+")

(defvar *ecl-types*
  (let* ((hash (make-hash-table :test #'equal)))
    (mapcar #'(lambda (x) (setf (gethash (string-upcase (car x)) hash) (string-upcase (cdr x)))) +ecl-types+)
    hash))

(defvar *no-prefix-types*
   (let* ((hash (make-hash-table :test #'equal)))
    (mapcar #'(lambda (x) (setf (gethash x hash) t)) +no-prefix-types+)
     hash))

(defvar *substitutes*
  (let ((hash (make-hash-table :test #'equal)))
    (mapcar #'(lambda (x) (setf (gethash (car x) hash) (cdr x))) +substitutes+)
    hash))

;; На вход получаем p-список, в котором должен быть задан текст с ключом
;; *язык* (:ru, :en и так далее)
;; На выходе получаем либо строку, заданную указанным ключом, либо строку
;; "Текст для языка :ru не задан" // :ru, :en и так далее
(djula:def-filter :docf (arg)
  (let* ((text (getf arg *language*))
	 (checked (or text (format nil
				      ":~A is not set"
				      (string-downcase (string *language*)))))
	 (substitute (gethash (cons checked *language*) *substitutes*)))
    (or substitute checked)))

(djula:def-filter :pre (arg)
  (if (gethash arg *no-prefix-types*)
      arg
      (concatenate 'string *prefix* "_" arg)))

(djula:def-filter :err (arg fn)
  (format nil "Field ~A '~A' is not given" arg fn))

(djula:def-filter :ecltype (arg)
  (let ((tp (gethash (string-upcase arg) *ecl-types*)))
    (or tp arg)))

(djula:def-filter :under (arg)
  (map 'string #'(lambda (c) (if (char= c #\_) #\- c)) arg))

(djula:def-filter :hex0 (arg)
   (if (string= (subseq arg 0 (min (length arg) 2)) "0x")
	   (concatenate 'string "#" (subseq arg 1))
	   arg))

(defun do-render (template-file
		  data-file
		  &optional &key
			      (lang *language*)
			      (output :no))
  (mapcar #'(lambda (x)
	      (let* ((str (string x))
		     (key (intern str :keyword))
		     (val (string-downcase (concatenate 'string ":" str)))
		     (substitute (gethash (cons val *language*) *substitutes*)))
		(setf (getf djula:*default-template-arguments* key) substitute)))
	  +given-substitutes+)

  (let* ((*language* lang)
	 (template (djula:compile-template* template-file))
	 (data (with-open-file (s data-file) (read s))))
    (let ((res (apply #'djula:render-template*
		      (cons template
			    (cons nil
				  data)))))

      ;;(princ djula:*default-template-arguments*)
      (if (eq output :no)
	  (princ res)
	  (alexandria:write-string-into-file
	   res
	   output
	   :if-exists :overwrite
	   :if-does-not-exist :create)))))
