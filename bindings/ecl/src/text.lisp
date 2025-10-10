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

(func Page-BeginText 
     "BRST_Page_BeginText" 
      STATUS 
  ((page Page)))

(func Page-EndText 
     "BRST_Page_EndText" 
      STATUS 
  ((page Page)))

(func Page-SetTextLeading 
     "BRST_Page_SetTextLeading" 
      STATUS 
  ((page Page)
   (value REAL)))

(func Page-SetFontAndSize 
     "BRST_Page_SetFontAndSize" 
      STATUS 
  ((page Page)
   (font Font)
   (size REAL)))

(func Dict-SetFontAndSize 
     "BRST_Dict_SetFontAndSize" 
      STATUS 
  ((dict Dict)
   (font Font)
   (size REAL)))

(func Page-SetTextRenderingMode 
     "BRST_Page_SetTextRenderingMode" 
      STATUS 
  ((page Page)
   (mode TextRenderingMode)))

(func Page-SetTextRise 
     "BRST_Page_SetTextRise" 
      STATUS 
  ((page Page)
   (value REAL)))

(func Page-MoveTextPos 
     "BRST_Page_MoveTextPos" 
      STATUS 
  ((page Page)
   (x REAL)
   (y REAL)))

(func Page-MoveTextPos2 
     "BRST_Page_MoveTextPos2" 
      STATUS 
  ((page Page)
   (x REAL)
   (y REAL)))

(func Page-SetTextMatrix 
     "BRST_Page_SetTextMatrix" 
      STATUS 
  ((page Page)
   (a REAL)
   (b REAL)
   (c REAL)
   (d REAL)
   (x REAL)
   (y REAL)))

(func Page-MoveToNextLine 
     "BRST_Page_MoveToNextLine" 
      STATUS 
  ((page Page)))

(func Page-ShowText 
     "BRST_Page_ShowText" 
      STATUS 
  ((page Page)
   (text CSTR)))

(func Page-ShowTextNextLine 
     "BRST_Page_ShowTextNextLine" 
      STATUS 
  ((page Page)
   (text CSTR)))

(func Page-ShowTextNextLineEx 
     "BRST_Page_ShowTextNextLineEx" 
      STATUS 
  ((page Page)
   (word-space REAL)
   (char-space REAL)
   (text CSTR)))

(func Page-TextOut 
     "BRST_Page_TextOut" 
      STATUS 
  ((page Page)
   (xpos REAL)
   (ypos REAL)
   (text CSTR)))

(func Page-TextRect 
     "BRST_Page_TextRect" 
      STATUS 
  ((page Page)
   (left REAL)
   (top REAL)
   (right REAL)
   (bottom REAL)
   (text CSTR)
   (align TextAlignment)
   (len UINT*)))

(func Page-SetCharSpace 
     "BRST_Page_SetCharSpace" 
      STATUS 
  ((page Page)
   (value REAL)))

(func Page-SetWordSpace 
     "BRST_Page_SetWordSpace" 
      STATUS 
  ((page Page)
   (value REAL)))

(func Page-TextMatrix 
     "BRST_Page_TextMatrix" 
      Matrix 
  ((page Page)))

(func Page-TextLeading 
     "BRST_Page_TextLeading" 
      REAL 
  ((page Page)))

(func Page-TextRenderingMode 
     "BRST_Page_TextRenderingMode" 
      TextRenderingMode 
  ((page Page)))

(func Page-TextRise 
     "BRST_Page_TextRise" 
      REAL 
  ((page Page)))

(func Page-CharSpace 
     "BRST_Page_CharSpace" 
      REAL 
  ((page Page)))

(func Page-WordSpace 
     "BRST_Page_WordSpace" 
      REAL 
  ((page Page)))

(func Page-CurrentTextPos2 
     "BRST_Page_CurrentTextPos2" 
      STATUS 
  ((page Page)
   (pos Point*)))

(func Page-CurrentFont 
     "BRST_Page_CurrentFont" 
      Font 
  ((page Page)))

(func Page-CurrentFontSize 
     "BRST_Page_CurrentFontSize" 
      REAL 
  ((page Page)))

(func Page-TextWidth 
     "BRST_Page_TextWidth" 
      REAL 
  ((page Page)
   (text CSTR)))

(func Page-MeasureText 
     "BRST_Page_MeasureText" 
      UINT 
  ((page Page)
   (text CSTR)
   (width REAL)
   (wordwrap BOOL)
   (real-width REAL*)))
