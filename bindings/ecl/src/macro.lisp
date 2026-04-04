(in-package #:cl-beresta)

(defparameter +ecl-type-substitution+
  '((          PDF .  :pointer-void)     
    (          DOC .  :pointer-void)     
    (         FONT .  :pointer-void)     
    (         MMGR .  :pointer-void)     
    (         PAGE .  :pointer-void)     
    (         DICT .  :pointer-void)
    (      XObject .  :pointer-void)
    (       Stream .  :pointer-void)
    (         Date .  :pointer-void)
    (  Destination .  :pointer-void)
    (    ExtGState .  :pointer-void)
    (      Pattern .  :pointer-void)
    (       Matrix .  :pointer-void)
    (      Encoder .  :pointer-void)
    ( Dash-Pattern .  :pointer-void)
    (   PageLayout .       :int32-t)
    (     PageMode .       :int32-t)
    (      PageNum .       :int32-t)
    (      LineCap .       :int32-t)
    (     LineJoin .       :int32-t)
    (    BlendMode .       :int32-t)
    (TextAlignment .       :int32-t)
    (   ColorSpace .       :int32-t)
    (     InfoType .       :int32-t)
    (   Date-Parts .       :int32-t)
    (TextRenderingMode .   :int32-t)
    (  PageOrientation .   :int32-t)
    (   PageTransition .   :int32-t)
    (  CompressionMode .  :uint32-t)
    (    PageSizes .       :int32-t)
    ( PageNumStyle .       :int32-t)
    ( PageBoundary .       :int32-t)
    (         CSTR .       :cstring)
    (          INT .       :int32-t)
    (         UINT .      :uint32-t)
    (        INT64 .       :int64-t)
    (       UINT64 .      :uint64-t)
    (        INT32 .       :int32-t)
    (       UINT32 .      :uint32-t)
    (        INT16 .       :int16-t)
    (       UINT16 .      :uint16-t)
    (         INT8 .        :int8-t)
    (        UINT8 . :unsigned-byte)
    (         BYTE . :unsigned-byte)
    (         REAL .         :float)
    (        REAL* .  :pointer-void)
    (       DOUBLE .        :double)
    (         BOOL .       :int32-t)
    (       STATUS .      :uint32-t)
    (          CID .      :uint16-t)
    (         VOID .          :void)
    (      UNICODE .      :uint16-t)
    (  RAW-POINTER .  :pointer-void)
    ( DASH-PATTERN .  :pointer-void)
    (Error-Handler .  :pointer-void)    
    (   Alloc-Func .  :pointer-void)    
    (    Free-Func .  :pointer-void)))

(defmacro func (function-name c-name return-type parameters)
  #-ecl
  `(defcfun (,c-name ,function-name) ,return-type
     ,parameters)
  #+ecl
  (flet ((get-type (x) (or (cdr (assoc x +ecl-type-substitution+)) x)))
    (let* ((param-count (length parameters))
	   (param-list (mapcar #'first parameters))
	   (types-list (mapcar #'second parameters))
	   (types-list-mapped (mapcar #'get-type types-list))
	   (c-params (format nil
			     "~{#~A~^, ~}"
			     (loop for n upto (1- param-count)
				   collect n)))
	   (call (if (eq return-type 'void) 
		     (format nil "~A(~A)" c-name c-params)
		     (format nil "@(return)=~A(~A);" c-name c-params)))
	   (one-liner (eq return-type 'void)))
      `(defun ,function-name ,param-list
	 (ffi:c-inline ,param-list
		       ,types-list-mapped
		       ,(get-type return-type)
		       ,call
		       :one-liner ,one-liner
		       :side-effects nil)))))

(defmacro enum (name elements-list &key (prefix ""))
  (let ((value -1)
	field
	forms)
    (setf prefix (string prefix))
    (when (not (string-equal prefix ""))
      (setf prefix (concatenate 'string (string-upcase prefix) "-")))
    (dolist (item elements-list)
      (cond ((symbolp item)
	     (setf field item)
	     (incf value))
	    ((and (consp item)
		  (symbolp (setf field (first item)))
		  (integerp (setf value (second item)))
		  (endp (cddr item))))
	    (t
	     (error "Некорректный аргумент для enum~%~a" elements-list)))
      (setf field (concatenate 'string
			       prefix
			       (symbol-name field)))
      (push `(defconstant ,(intern field (symbol-package name))
	       ',value)
	    forms))
    `(progn ,@forms)))


(defmacro pointer (name)
  #-ecl
  `(defctype ,name :pointer)
  #+ecl
  `(ffi:def-foreign-type ,name :pointer-void))


(defmacro struct (name doc &rest slots)
  #+ecl
  (declare (ignore doc))
  #-ecl
  `(defcstruct ,name ,doc ,@slots)
  #+ecl
  (flet ((get-type (x) (or (cdr (assoc x +ecl-type-substitution+)) x)))
    (let ((slots-types))
      (dolist (item slots)
	(push (list (first item) (get-type (second item))) slots-types))
      `(ffi:def-struct ,name ,@slots-types))))


(defmacro synonym (name origin)
  #-ecl
  `(defctype ,name ,origin)
  #+ecl
  `(declare (ignore ,origin))
  #+ecl
  `(ffi:def-foreign-type ,name :pointer-void))

(defmacro constant (name value)
  `(defconstant ,name ,value))

(defmacro with-pdf-document ((pdf-var filename) &body body)
  `(let ((,pdf-var (doc-new-empty)))
     (unwind-protect
	  (progn
	    ,@body
	    (doc-savetofile ,pdf-var (string-to-cstring ,filename)))
       (doc-free ,pdf-var))))

(defmacro with-ttf-font ((font-var pdf-var filename
			  &optional
			    (embeddable 'TRUE)
			    (encoding "UTF-8"))
			 &body body)
  #+ecl
  (when (probe-file `,filename)
    (let ((f-name0 (gensym))
	  (f-name (gensym))
	  (font-name (gensym)))
      `(let* ((,f-name0 ,filename)
	      (,f-name (cond ((stringp ,f-name0) ,f-name0)
			     ((pathnamep ,f-name0) (namestring ,f-name0))))
	      (,font-name (doc-ttfont-loadfromfile
			   ,pdf-var
			   (string-to-cstring ,f-name)
			   ,embeddable))
	      (,font-var (doc-font ,pdf-var
				   (ffi:convert-from-foreign-string ,font-name)
				   ,encoding)))
	 ,@body))))

(defmacro include-header ()
  #+ecl
  `(ffi:clines "#include \"brst.h\""))

(defun string-to-cstring (str)  
  #+ecl
  (ext:octets-to-string
   (ext:string-to-octets str :external-format :utf-8)
   :external-format :latin-1))

(defmacro page-set-dash-pattern (page pattern num phase)
  #+ecl
  `(let* ((pattern1 ,pattern))
     (ffi:with-foreign-object (c-pattern '(:array :float ,num))
       (dotimes (i ,num)
	 (setf (ffi:deref-array c-pattern '(:array :float) i)
	       (aref pattern1 i)))
       (page-setdash ,page c-pattern ,num ,phase))))

(defmacro stream-set-dash-pattern (stream pattern num phase)
  #+ecl
  `(let* ((pattern1 ,pattern))
     (ffi:with-foreign-object (c-pattern '(:array :float ,num))
       (dotimes (i ,num)
	 (setf (ffi:deref-array c-pattern '(:array :float) i)
	       (aref pattern1 i)))
       (stream-setdash ,stream c-pattern ,num ,phase))))

(defmacro with-page-gsave ((page-var) &body body)
  `(progn
     (page-gsave ,page-var)
     ,@body
     (page-grestore ,page-var)))

(defmacro with-stream-gsave ((stream-var) &body body)
  `(progn
     (stream-gsave ,stream-var)
     ,@body
     (stream-grestore ,stream-var)))
