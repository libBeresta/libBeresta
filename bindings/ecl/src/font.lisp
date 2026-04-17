;; 
;; libBeresta
;; 
;; Заголовочные файлы для Embeddable Common Lisp (ecl)
;; Дмитрий Соломенников, (с) 2025-2026
;;

(in-package #:cl-beresta)

(include-header)

(synonym Font Dict)

(func Font-Descent 
     "BRST_Font_Descent" 
      REAL 
  ((font Font)
   (font-size REAL)))

(func Font-TextWidth2 
     "BRST_Font_TextWidth2" 
      REAL 
  ((font Font)
   (font-size REAL)
   (word-space REAL)
   (char-space REAL)
   (text CSTR)))
