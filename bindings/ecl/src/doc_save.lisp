;; 
;; libBeresta
;; 
;; Заголовочные файлы для Embeddable Common Lisp (ecl)
;; Дмитрий Соломенников, (с) 2025
;;

(in-package #:cl-beresta)

(include-header)

(func Doc-SaveToStream 
     "BRST_Doc_SaveToStream" 
      STATUS 
  ((pdf Doc)))

(func Doc-SaveToFile 
     "BRST_Doc_SaveToFile" 
      STATUS 
  ((pdf Doc)
   (filename CSTR)))
