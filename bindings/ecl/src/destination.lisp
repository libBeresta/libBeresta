;; 
;; libBeresta
;; 
;; Заголовочные файлы для Embeddable Common Lisp (ecl)
;; Дмитрий Соломенников, (с) 2025
;;

(in-package #:cl-beresta)

(include-header)

(synonym Destination Array)

(func Destination-SetXYZ 
     "BRST_Destination_SetXYZ" 
      STATUS 
  ((dst Destination)
   (left REAL)
   (top REAL)
   (zoom REAL)))

(func Destination-SetFit 
     "BRST_Destination_SetFit" 
      STATUS 
  ((dst Destination)))

(func Destination-SetFitH 
     "BRST_Destination_SetFitH" 
      STATUS 
  ((dst Destination)
   (top REAL)))

(func Destination-SetFitV 
     "BRST_Destination_SetFitV" 
      STATUS 
  ((dst Destination)
   (left REAL)))

(func Destination-SetFitR 
     "BRST_Destination_SetFitR" 
      STATUS 
  ((dst Destination)
   (left REAL)
   (bottom REAL)
   (right REAL)
   (top REAL)))

(func Destination-SetFitB 
     "BRST_Destination_SetFitB" 
      STATUS 
  ((dst Destination)))

(func Destination-SetFitBH 
     "BRST_Destination_SetFitBH" 
      STATUS 
  ((dst Destination)
   (top REAL)))

(func Destination-SetFitBV 
     "BRST_Destination_SetFitBV" 
      STATUS 
  ((dst Destination)
   (left REAL)))
