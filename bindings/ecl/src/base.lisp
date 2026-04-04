;; 
;; libBeresta
;; 
;; Заголовочные файлы для Embeddable Common Lisp (ecl)
;; Дмитрий Соломенников, (с) 2025
;;

(in-package #:cl-beresta)

(include-header)

(func Doc-New-Ex 
     "BRST_Doc_New_Ex" 
      Doc 
  ((user-error-fn Error-Handler)
   (user-alloc-fn Alloc-Func)
   (user-free-fn Free-Func)
   (mem-pool-buf-size UINT)
   (user-data RAW-POINTER)))

(func Version 
     "BRST_Version" 
      CSTR 
  ())

(func Doc-New 
     "BRST_Doc_New" 
      Doc 
  ((user-error-fn Error-Handler)
   (user-data RAW-POINTER)))

(func Doc-New-Empty 
     "BRST_Doc_New_Empty" 
      Doc 
  ())

(func Doc-Initialize 
     "BRST_Doc_Initialize" 
      STATUS 
  ((pdf Doc)))

(func Doc-Destroy 
     "BRST_Doc_Destroy" 
      void 
  ((pdf Doc)))

(func Doc-Initialized 
     "BRST_Doc_Initialized" 
      BOOL 
  ((pdf Doc)))

(func Doc-Destroy-All 
     "BRST_Doc_Destroy_All" 
      void 
  ((pdf Doc)))

(func Doc-MMgr 
     "BRST_Doc_MMgr" 
      MMgr 
  ((pdf Doc)))

(func Doc-Free 
     "BRST_Doc_Free" 
      void 
  ((pdf Doc)))

(func PageSize-Width 
     "BRST_PageSize_Width" 
      REAL 
  ((size PageSizes)
   (orientation PageOrientation)))

(func PageSize-Height 
     "BRST_PageSize_Height" 
      REAL 
  ((size PageSizes)
   (orientation PageOrientation)))
