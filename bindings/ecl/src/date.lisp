;; 
;; libBeresta
;; 
;; Заголовочные файлы для Embeddable Common Lisp (ecl)
;; Дмитрий Соломенников, (с) 2025-2026
;;

(in-package #:cl-beresta)

(include-header)

(pointer Date)

(enum Date-Parts (
  
  DATE-PART-YEAR
  DATE-PART-MONTH
  DATE-PART-DAY
  DATE-PART-HOUR
  DATE-PART-MINUTE
  DATE-PART-SECOND
  DATE-PART-HOUR-OFFSET
  DATE-PART-MINUTE-OFFSET
  DATE-PART-UT-RELATIONSHIP))

(enum UT-Relationship (
  
  UT-RELATIONSHIP-NONE
  UT-RELATIONSHIP-PLUS
  UT-RELATIONSHIP-MINUS
  UT-RELATIONSHIP-ZERO))

(func Date-Now 
     "BRST_Date_Now" 
      Date 
  ((pdf Doc)))

(func Date-Part 
     "BRST_Date_Part" 
      INT 
  ((date Date)
   (part Date-Parts)))

(func Date-Validate 
     "BRST_Date_Validate" 
      STATUS 
  ((date Date)))

(func Date-Free 
     "BRST_Date_Free" 
      void 
  ((date Date)))
