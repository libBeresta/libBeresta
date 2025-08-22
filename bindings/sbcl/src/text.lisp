;; 
;; libBeresta
;; 
;; Заголовочные файлы для Embeddable Common Lisp (ecl)
;; Дмитрий Соломенников, (с) 2025
;;

(in-package #:cl-beresta)

(defcfun ("BRST_Page_BeginText" Page-BeginText) STATUS
  (page Page))

(defcfun ("BRST_Page_EndText" Page-EndText) STATUS
  (page Page))

(defcfun ("BRST_Page_SetTextLeading" Page-SetTextLeading) STATUS
  (page Page)
  (value REAL))

(defcfun ("BRST_Page_SetFontAndSize" Page-SetFontAndSize) STATUS
  (page Page)
  (font Font)
  (size REAL))

(defcfun ("BRST_Page_SetTextRenderingMode" Page-SetTextRenderingMode) STATUS
  (page Page)
  (mode TextRenderingMode))

(defcfun ("BRST_Page_SetTextRise" Page-SetTextRise) STATUS
  (page Page)
  (value REAL))

(defcfun ("BRST_Page_MoveTextPos" Page-MoveTextPos) STATUS
  (page Page)
  (x REAL)
  (y REAL))

(defcfun ("BRST_Page_MoveTextPos2" Page-MoveTextPos2) STATUS
  (page Page)
  (x REAL)
  (y REAL))

(defcfun ("BRST_Page_SetTextMatrix" Page-SetTextMatrix) STATUS
  (page Page)
  (a REAL)
  (b REAL)
  (c REAL)
  (d REAL)
  (x REAL)
  (y REAL))

(defcfun ("BRST_Page_MoveToNextLine" Page-MoveToNextLine) STATUS
  (page Page))

(defcfun ("BRST_Page_ShowText" Page-ShowText) STATUS
  (page Page)
  (text CSTR))

(defcfun ("BRST_Page_ShowTextNextLine" Page-ShowTextNextLine) STATUS
  (page Page)
  (text CSTR))

(defcfun ("BRST_Page_ShowTextNextLineEx" Page-ShowTextNextLineEx) STATUS
  (page Page)
  (word-space REAL)
  (char-space REAL)
  (text CSTR))

(defcfun ("BRST_Page_TextOut" Page-TextOut) STATUS
  (page Page)
  (xpos REAL)
  (ypos REAL)
  (text CSTR))

(defcfun ("BRST_Page_TextRect" Page-TextRect) STATUS
  (page Page)
  (left REAL)
  (top REAL)
  (right REAL)
  (bottom REAL)
  (text CSTR)
  (align TextAlignment)
  (len UINT*))

(defcfun ("BRST_Page_SetCharSpace" Page-SetCharSpace) STATUS
  (page Page)
  (value REAL))

(defcfun ("BRST_Page_SetWordSpace" Page-SetWordSpace) STATUS
  (page Page)
  (value REAL))

(defcfun ("BRST_Page_TextLeading" Page-TextLeading) REAL
  (page Page))

(defcfun ("BRST_Page_TextRenderingMode" Page-TextRenderingMode) TextRenderingMode
  (page Page))

(defcfun ("BRST_Page_TextRise" Page-TextRise) REAL
  (page Page))

(defcfun ("BRST_Page_CharSpace" Page-CharSpace) REAL
  (page Page))

(defcfun ("BRST_Page_WordSpace" Page-WordSpace) REAL
  (page Page))

(defcfun ("BRST_Page_CurrentTextPos2" Page-CurrentTextPos2) STATUS
  (page Page)
  (pos Point*))

(defcfun ("BRST_Page_CurrentFont" Page-CurrentFont) Font
  (page Page))

(defcfun ("BRST_Page_CurrentFontSize" Page-CurrentFontSize) REAL
  (page Page))

(defcfun ("BRST_Page_TextWidth" Page-TextWidth) REAL
  (page Page)
  (text CSTR))

(defcfun ("BRST_Page_MeasureText" Page-MeasureText) UINT
  (page Page)
  (text CSTR)
  (width REAL)
  (wordwrap BOOL)
  (real-width REAL*))
