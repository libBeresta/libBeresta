;; 
;; libBeresta
;; 
;; Заголовочные файлы для Embeddable Common Lisp (ecl)
;; Дмитрий Соломенников, (с) 2025
;;

(in-package #:cl-beresta)

(include-header)

(func Doc-SetCompressionMode 
     "BRST_Doc_SetCompressionMode" 
      STATUS 
  ((pdf Doc)
   (mode CompressionMode)))
