;; 
;; libBeresta
;; 
;; Заголовочные файлы для Embeddable Common Lisp (ecl)
;; Дмитрий Соломенников, (с) 2025
;;

(in-package #:cl-beresta)

(defcstruct Point
  "Положение точки на странице"
  (x REAL)
  (y REAL)
)

(defcstruct Rect
  ""
  (left REAL)
  (bottom REAL)
  (right REAL)
  (top REAL)
)

(defcstruct TextWidth
  ""
  (numchars UINT)
  (numwords UINT)
  (width UINT)
  (numspace UINT)
)
