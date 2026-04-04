;; 
;; libBeresta
;; 
;; Заголовочные файлы для Embeddable Common Lisp (ecl)
;; Дмитрий Соломенников, (с) 2025
;;

(in-package #:cl-beresta)

(include-header)

(enum InfoType (
  
  INFO-CREATION-DATE
  INFO-MOD-DATE
  INFO-AUTHOR
  INFO-CREATOR
  INFO-PRODUCER
  INFO-TITLE
  INFO-SUBJECT
  INFO-KEYWORDS
  INFO-TRAPPED
  INFO-GTS-PDFX))

(func Doc-SetInfoAttr 
     "BRST_Doc_SetInfoAttr" 
      STATUS 
  ((pdf Doc)
   (type InfoType)
   (value CSTR)))

(func Doc-SetInfoDateAttr 
     "BRST_Doc_SetInfoDateAttr" 
      STATUS 
  ((pdf Doc)
   (type InfoType)
   (value Date)))
