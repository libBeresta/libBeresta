;; 
;; libBeresta
;; 
;; Заголовочные файлы для Embeddable Common Lisp (ecl)
;; Дмитрий Соломенников, (с) 2025
;;

(in-package #:cl-beresta)

(include-header)

(func Doc-Create-ExtGState 
     "BRST_Doc_Create_ExtGState" 
      ExtGState 
  ((pdf Doc)))
