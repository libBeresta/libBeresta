;; 
;; libBeresta
;; 
;; Заголовочные файлы для Embeddable Common Lisp (ecl)
;; Дмитрий Соломенников, (с) 2025
;;

(in-package #:cl-beresta)

(include-header)

;;(func Doc-XObject-CreateFromImage 
;;     "BRST_Doc_XObject_CreateFromImage" 
;;      XObject 
;;  ((pdf Doc)
;;   (rect Rect)
;;   (image Image)
;;   (zoom BOOL)))

;;(func Doc-XObject-CreateAsWhiteRect 
;;     "BRST_Doc_XObject_CreateAsWhiteRect" 
;;      XObject 
;;  ((pdf Doc)
;;   (rect Rect)))

(func Doc-XObject-Create 
     "BRST_Doc_XObject_Create" 
      XObject 
  ((pdf Doc)
   (width REAL)
   (height REAL)
   (scalex REAL)
   (scaley REAL)))
