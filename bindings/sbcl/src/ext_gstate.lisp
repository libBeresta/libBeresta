;; 
;; libBeresta
;; 
;; Заголовочные файлы для Embeddable Common Lisp (ecl)
;; Дмитрий Соломенников, (с) 2025
;;

(in-package #:cl-beresta)

(defctype ExtGState Dict)

(defcfun ("BRST_ExtGState_SetAlphaStroke" ExtGState-SetAlphaStroke) STATUS
  (ext-gstate ExtGState)
  (value REAL))

(defcfun ("BRST_ExtGState_SetAlphaFill" ExtGState-SetAlphaFill) STATUS
  (ext-gstate ExtGState)
  (value REAL))

(defcfun ("BRST_ExtGState_SetBlendMode" ExtGState-SetBlendMode) STATUS
  (ext-gstate ExtGState)
  (mode BlendMode))
