;; 
;; libBeresta
;; 
;; Заголовочные файлы для Embeddable Common Lisp (ecl)
;; Дмитрий Соломенников, (с) 2025
;;

(in-package #:cl-beresta)

(defctype CSTR :string)
(defctype INT :int32)
(defctype UINT :uint32)
(defctype UINT* :pointer)
(defctype INT64 :int64)
(defctype UINT64 :uint64)
(defctype INT32 :int32)
(defctype UINT32 :uint32)
(defctype INT16 :int16)
(defctype UINT16 :uint16)
(defctype INT8 :int8)
(defctype UINT8 :uint8)
(defctype BYTE :uint8)
(defctype REAL :float)
(defctype REAL* :pointer)
(defctype DOUBLE :double)
(defctype BOOL :int32)
(defctype STATUS :uint32)
(defctype CID :uint16)
(defctype void :void)
(defctype UNICODE :uint16)
(defctype RAW-POINTER :pointer)
(defctype Point* :pointer)
(defctype DASH-PATTERN :pointer)
(defctype Error-Handler :pointer)
(defctype Alloc-Func :pointer)
(defctype Free-Func :pointer)