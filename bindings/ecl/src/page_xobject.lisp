;; 
;; libBeresta
;; 
;; Заголовочные файлы для Embeddable Common Lisp (ecl)
;; Дмитрий Соломенников, (с) 2025-2026
;;

(in-package #:cl-beresta)

(include-header)

(func Page-XObject-Execute 
     "BRST_Page_XObject_Execute" 
      STATUS 
  ((page Page)
   (xobj XObject)))

(func Dict-XObject-Execute 
     "BRST_Dict_XObject_Execute" 
      STATUS 
  ((dict Dict)
   (xobj XObject)))
