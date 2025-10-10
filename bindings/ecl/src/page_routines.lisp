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

(func Page-SetWidth 
     "BRST_Page_SetWidth" 
      STATUS 
  ((page Page)
   (value REAL)))

(func Page-SetHeight 
     "BRST_Page_SetHeight" 
      STATUS 
  ((page Page)
   (value REAL)))

(func Page-SetBoundary 
     "BRST_Page_SetBoundary" 
      STATUS 
  ((page Page)
   (boundary PageBoundary)
   (left REAL)
   (bottom REAL)
   (right REAL)
   (top REAL)))

(func Page-SetSize 
     "BRST_Page_SetSize" 
      STATUS 
  ((page Page)
   (size PageSizes)
   (orientation PageOrientation)))

(func Page-SetRotate 
     "BRST_Page_SetRotate" 
      STATUS 
  ((page Page)
   (angle UINT16)))

(func Page-SetSlideShow 
     "BRST_Page_SetSlideShow" 
      STATUS 
  ((page Page)
   (type PageTransition)
   (disp-time REAL)
   (trans-time REAL)))

(func Page-SetHorizontalScaling 
     "BRST_Page_SetHorizontalScaling" 
      STATUS 
  ((page Page)
   (value REAL)))

(func Page-GStateDepth 
     "BRST_Page_GStateDepth" 
      UINT 
  ((page Page)))

(func Page-HorizontalScaling 
     "BRST_Page_HorizontalScaling" 
      REAL 
  ((page Page)))

(func Page-SetZoom 
     "BRST_Page_SetZoom" 
      STATUS 
  ((page Page)
   (zoom REAL)))

(func Page-Width 
     "BRST_Page_Width" 
      REAL 
  ((page Page)))

(func Page-Height 
     "BRST_Page_Height" 
      REAL 
  ((page Page)))

(func Page-GMode 
     "BRST_Page_GMode" 
      UINT16 
  ((page Page)))

(func Page-MMgr 
     "BRST_Page_MMgr" 
      MMgr 
  ((page Page)))

(func Page-Insert-Shared-Content-Stream 
     "BRST_Page_Insert_Shared_Content_Stream" 
      STATUS 
  ((page Page)
   (shared-stream Dict)))

(func Page-RawWrite 
     "BRST_Page_RawWrite" 
      STATUS 
  ((page Page)
   (data CSTR)))

(func Page-SetExtGState 
     "BRST_Page_SetExtGState" 
      STATUS 
  ((page Page)
   (ext-gstate ExtGState)))

(func Page-CreateDestination 
     "BRST_Page_CreateDestination" 
      Destination 
  ((page Page)))
