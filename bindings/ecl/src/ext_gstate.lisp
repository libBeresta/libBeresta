;; 
;; libBeresta
;; 
;; Заголовочные файлы для Embeddable Common Lisp (ecl)
;; Дмитрий Соломенников, (с) 2025
;;

(in-package #:cl-beresta)

(include-header)

(synonym ExtGState Dict)

(func ExtGState-SetAlphaStroke 
     "BRST_ExtGState_SetAlphaStroke" 
      STATUS 
  ((ext-gstate ExtGState)
   (value REAL)))

(func ExtGState-SetAlphaFill 
     "BRST_ExtGState_SetAlphaFill" 
      STATUS 
  ((ext-gstate ExtGState)
   (value REAL)))

(func ExtGState-SetBlendMode 
     "BRST_ExtGState_SetBlendMode" 
      STATUS 
  ((ext-gstate ExtGState)
   (mode BlendMode)))
