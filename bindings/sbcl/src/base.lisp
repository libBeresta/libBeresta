;; 
;; libBeresta
;; 
;; Заголовочные файлы для Embeddable Common Lisp (ecl)
;; Дмитрий Соломенников, (с) 2025
;;

(in-package #:cl-beresta)

(defcfun ("BRST_Doc_New_Ex" Doc-New-Ex) Doc
  (user-error-fn Error-Handler)
  (user-alloc-fn Alloc-Func)
  (user-free-fn Free-Func)
  (mem-pool-buf-size UINT)
  (user-data RAW-POINTER))

(defcfun ("BRST_Version" Version) CSTR)

(defcfun ("BRST_Doc_New" Doc-New) Doc
  (user-error-fn Error-Handler)
  (user-data RAW-POINTER))

(defcfun ("BRST_Doc_New_Empty" Doc-New-Empty) Doc)

(defcfun ("BRST_BRST_Doc_Initialize" BRST-Doc-Initialize) STATUS
  (pdf Doc))

(defcfun ("BRST_Doc_Destroy" Doc-Destroy) void
  (pdf Doc))

(defcfun ("BRST_Doc_Initialized" Doc-Initialized) BOOL
  (pdf Doc))

(defcfun ("BRST_Doc_Destroy_All" Doc-Destroy-All) void
  (pdf Doc))

(defcfun ("BRST_Doc_MMgr" Doc-MMgr) MMgr
  (pdf Doc))
