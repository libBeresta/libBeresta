;; 
;; libBeresta
;; 
;; Заголовочные файлы для Embeddable Common Lisp (ecl)
;; Дмитрий Соломенников, (с) 2025
;;

(in-package #:cl-beresta)

(defctype Destination Array)

(defcfun ("BRST_Destination_SetXYZ" Destination-SetXYZ) STATUS
  (dst Destination)
  (left REAL)
  (top REAL)
  (zoom REAL))

(defcfun ("BRST_Destination_SetFit" Destination-SetFit) STATUS
  (dst Destination))

(defcfun ("BRST_Destination_SetFitH" Destination-SetFitH) STATUS
  (dst Destination)
  (top REAL))

(defcfun ("BRST_Destination_SetFitV" Destination-SetFitV) STATUS
  (dst Destination)
  (left REAL))

(defcfun ("BRST_Destination_SetR" Destination-SetR) STATUS
  (dst Destination)
  (left REAL)
  (bottom REAL)
  (right REAL)
  (top REAL))

(defcfun ("BRST_Destination_SetFitB" Destination-SetFitB) STATUS
  (dst Destination))

(defcfun ("BRST_Destination_SetFitBH" Destination-SetFitBH) STATUS
  (dst Destination)
  (top REAL))

(defcfun ("BRST_Destination_SetFitBV" Destination-SetFitBV) STATUS
  (dst Destination)
  (left REAL))
