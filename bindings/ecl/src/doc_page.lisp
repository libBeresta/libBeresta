;; 
;; libBeresta
;; 
;; Заголовочные файлы для Embeddable Common Lisp (ecl)
;; Дмитрий Соломенников, (с) 2025
;;

(in-package #:cl-beresta)

(include-header)

(func Doc-Pages-SetConfiguration 
     "BRST_Doc_Pages_SetConfiguration" 
      STATUS 
  ((pdf Doc)
   (page-per-pages UINT)))

(func Doc-Page-ByIndex 
     "BRST_Doc_Page_ByIndex" 
      Page 
  ((pdf Doc)
   (index UINT)))

(func Doc-Page-Layout 
     "BRST_Doc_Page_Layout" 
      PageLayout 
  ((pdf Doc)))

(func Doc-Page-SetLayout 
     "BRST_Doc_Page_SetLayout" 
      STATUS 
  ((pdf Doc)
   (layout PageLayout)))

(func Doc-Page-Mode 
     "BRST_Doc_Page_Mode" 
      PageMode 
  ((pdf Doc)))

(func Doc-Page-SetMode 
     "BRST_Doc_Page_SetMode" 
      STATUS 
  ((pdf Doc)
   (mode PageMode)))

(func Doc-Page-Current 
     "BRST_Doc_Page_Current" 
      Page 
  ((pdf Doc)))

(func Doc-Page-Add 
     "BRST_Doc_Page_Add" 
      Page 
  ((pdf Doc)))

(func Doc-Page-Insert 
     "BRST_Doc_Page_Insert" 
      Page 
  ((pdf Doc)
   (page Page)))

(func Doc-Page-AddLabel 
     "BRST_Doc_Page_AddLabel" 
      STATUS 
  ((pdf Doc)
   (page-num UINT)
   (style PageNumStyle)
   (first-page UINT)
   (prefix CSTR)))
