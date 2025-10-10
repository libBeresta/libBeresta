;; 
;; libBeresta
;; 
;; Заголовочные файлы для Embeddable Common Lisp (ecl)
;; Дмитрий Соломенников, (с) 2025
;;
;; Текст лицензии см. в файле ЛИЦЕНЗИЯ в корне проекта
;;
(in-package #:cl-beresta)

(ffi:def-foreign-type CSTR :CSTRING)
(ffi:def-foreign-type INT :INT32-T)
(ffi:def-foreign-type UINT :UINT32-T)
(ffi:def-foreign-type UINT* :POINTER-VOID)
(ffi:def-foreign-type INT64 :INT64-T)
(ffi:def-foreign-type UINT64 :UINT64-T)
(ffi:def-foreign-type INT32 :INT32-T)
(ffi:def-foreign-type UINT32 :UINT32-T)
(ffi:def-foreign-type INT16 :INT16-T)
(ffi:def-foreign-type UINT16 :UINT16-T)
(ffi:def-foreign-type INT8 :INT8-T)
(ffi:def-foreign-type UINT8 :UNSIGNED-BYTE)
(ffi:def-foreign-type BYTE :UNSIGNED-BYTE)
(ffi:def-foreign-type REAL :FLOAT)
(ffi:def-foreign-type REAL* :POINTER-VOID)
(ffi:def-foreign-type DOUBLE :DOUBLE)
(ffi:def-foreign-type BOOL :INT32-T)
(ffi:def-foreign-type STATUS :UINT32-T)
(ffi:def-foreign-type CID :UINT16-T)
(ffi:def-foreign-type void :VOID)
(ffi:def-foreign-type UNICODE :UINT16-T)
(ffi:def-foreign-type RAW-POINTER :POINTER-VOID)
(ffi:def-foreign-type Point* :POINTER-VOID)
(ffi:def-foreign-type DASH-PATTERN :POINTER-VOID)
(ffi:def-foreign-type Error-Handler :POINTER-VOID)
(ffi:def-foreign-type Alloc-Func :POINTER-VOID)
(ffi:def-foreign-type Free-Func :POINTER-VOID)