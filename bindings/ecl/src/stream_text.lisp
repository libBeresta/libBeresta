;; 
;; libBeresta
;; 
;; Заголовочные файлы для Embeddable Common Lisp (ecl)
;; Дмитрий Соломенников, (с) 2025
;;
;; Текст лицензии см. в файле ЛИЦЕНЗИЯ в корне проекта
;;
(in-package #:cl-beresta)

(include-header)

(func Stream-BeginText 
     "BRST_Stream_BeginText" 
      STATUS 
  ((stream Stream)))

(func Stream-EndText 
     "BRST_Stream_EndText" 
      STATUS 
  ((stream Stream)))

(func Stream-SetTextLeading 
     "BRST_Stream_SetTextLeading" 
      STATUS 
  ((stream Stream)
   (value REAL)))

(func Stream-SetTextRenderingMode 
     "BRST_Stream_SetTextRenderingMode" 
      STATUS 
  ((stream Stream)
   (mode TextRenderingMode)))

(func Stream-MoveTextPos 
     "BRST_Stream_MoveTextPos" 
      STATUS 
  ((stream Stream)
   (x REAL)
   (y REAL)))

(func Stream-MoveTextPos2 
     "BRST_Stream_MoveTextPos2" 
      STATUS 
  ((stream Stream)
   (x REAL)
   (y REAL)))

(func Stream-SetTextMatrix 
     "BRST_Stream_SetTextMatrix" 
      STATUS 
  ((stream Stream)
   (a REAL)
   (b REAL)
   (c REAL)
   (d REAL)
   (x REAL)
   (y REAL)))

(func Stream-ShowText 
     "BRST_Stream_ShowText" 
      STATUS 
  ((stream Stream)
   (font Font)
   (text CSTR)))

(func Stream-TextOut 
     "BRST_Stream_TextOut" 
      STATUS 
  ((stream Stream)
   (font Font)
   (xpos REAL)
   (ypos REAL)
   (text CSTR)))

(func Stream-MoveToNextLine 
     "BRST_Stream_MoveToNextLine" 
      STATUS 
  ((stream Stream)))
