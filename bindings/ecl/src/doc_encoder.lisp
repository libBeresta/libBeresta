;; 
;; libBeresta
;; 
;; Заголовочные файлы для Embeddable Common Lisp (ecl)
;; Дмитрий Соломенников, (с) 2025-2026
;;

(in-package #:cl-beresta)

(include-header)

(func Doc-Encoder-SetCurrent 
     "BRST_Doc_Encoder_SetCurrent" 
      STATUS 
  ((pdf Doc)
   (encoding-name CSTR)))

(func Doc-Encoder-Prepare 
     "BRST_Doc_Encoder_Prepare" 
      Encoder 
  ((pdf Doc)
   (encoding-name CSTR)))

(func Doc-Encoder-Current 
     "BRST_Doc_Encoder_Current" 
      Encoder 
  ((pdf Doc)))
