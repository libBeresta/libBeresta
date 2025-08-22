;; 
;; libBeresta
;; 
;; Заголовочные файлы для Embeddable Common Lisp (ecl)
;; Дмитрий Соломенников, (с) 2025
;;

(in-package #:cl-beresta)

(defcfun ("BRST_Page_SetWidth" Page-SetWidth) STATUS
  (page Page)
  (value REAL))

(defcfun ("BRST_Page_SetHeight" Page-SetHeight) STATUS
  (page Page)
  (value REAL))

(defcfun ("BRST_Page_SetBoundary" Page-SetBoundary) STATUS
  (page Page)
  (boundary PageBoundary)
  (left REAL)
  (bottom REAL)
  (right REAL)
  (top REAL))

(defcfun ("BRST_Page_SetSize" Page-SetSize) STATUS
  (page Page)
  (size PageSizes)
  (orientation PageOrientation))

(defcfun ("BRST_Page_SetRotate" Page-SetRotate) STATUS
  (page Page)
  (angle UINT16))

(defcfun ("BRST_Page_SetSlideShow" Page-SetSlideShow) STATUS
  (page Page)
  (type PageTransition)
  (disp-time REAL)
  (trans-time REAL))

(defcfun ("BRST_Page_SetHorizontalScaling" Page-SetHorizontalScaling) STATUS
  (page Page)
  (value REAL))

(defcfun ("BRST_Page_GStateDepth" Page-GStateDepth) UINT
  (page Page))

(defcfun ("BRST_Page_HorizontalScaling" Page-HorizontalScaling) REAL
  (page Page))

(defcfun ("BRST_Page_SetZoom" Page-SetZoom) STATUS
  (page Page)
  (zoom REAL))

(defcfun ("BRST_Page_Width" Page-Width) REAL
  (page Page))

(defcfun ("BRST_Page_Height" Page-Height) REAL
  (page Page))

(defcfun ("BRST_Page_GMode" Page-GMode) UINT16
  (page Page))

(defcfun ("BRST_Page_MMgr" Page-MMgr) MMgr
  (page Page))

(defcfun ("BRST_Page_Insert_Shared_Content_Stream" Page-Insert-Shared-Content-Stream) STATUS
  (page Page)
  (shared-stream Dict))

(defcfun ("BRST_Page_RawWrite" Page-RawWrite) STATUS
  (page Page)
  (data CSTR))

(defcfun ("BRST_Page_SetExtGState" Page-SetExtGState) STATUS
  (page Page)
  (ext-gstate ExtGState))

(defcfun ("BRST_Page_CreateDestination" Page-CreateDestination) Destination
  (page Page))
