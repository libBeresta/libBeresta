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

(func Doc-Pattern-Tiling-Create 
     "BRST_Doc_Pattern_Tiling_Create" 
      Pattern 
  ((pdf Doc)
   (left REAL)
   (bottom REAL)
   (right REAL)
   (top REAL)
   (xstep REAL)
   (ystep REAL)
   (m Matrix)))

(func Doc-Pattern-Stream 
     "BRST_Doc_Pattern_Stream" 
      Stream 
  ((pattern Pattern)))

(func Doc-Dict-RGBPatternFill-Select 
     "BRST_Doc_Dict_RGBPatternFill_Select" 
      STATUS 
  ((pdf Doc)
   (dict Dict)
   (r REAL)
   (g REAL)
   (b REAL)
   (pattern Pattern)))

(func Doc-Dict-RGBPatternFillUint-Select 
     "BRST_Doc_Dict_RGBPatternFillUint_Select" 
      STATUS 
  ((pdf Doc)
   (dict Dict)
   (r UINT8)
   (g UINT8)
   (b UINT8)
   (pattern Pattern)))

(func Doc-Dict-RGBPatternFillHex-Select 
     "BRST_Doc_Dict_RGBPatternFillHex_Select" 
      STATUS 
  ((pdf Doc)
   (dict Dict)
   (rgb UINT8)
   (pattern Pattern)))

(func Doc-Page-RGBPatternFill-Select 
     "BRST_Doc_Page_RGBPatternFill_Select" 
      STATUS 
  ((pdf Doc)
   (page Page)
   (r REAL)
   (g REAL)
   (b REAL)
   (pattern Pattern)))

(func Doc-Page-RGBPatternFillUint-Select 
     "BRST_Doc_Page_RGBPatternFillUint_Select" 
      STATUS 
  ((pdf Doc)
   (page Page)
   (r UINT8)
   (g UINT8)
   (b UINT8)
   (pattern Pattern)))

(func Doc-Page-RGBPatternFillHex-Select 
     "BRST_Doc_Page_RGBPatternFillHex_Select" 
      STATUS 
  ((pdf Doc)
   (page Page)
   (rgb UINT8)
   (pattern Pattern)))
