;; 
;; libBeresta
;; 
;; Заголовочные файлы для Embeddable Common Lisp (ecl)
;; Дмитрий Соломенников, (с) 2025
;;

(in-package #:cl-beresta)

(include-header)

(struct Point
  "Положение точки на странице"
  (x REAL)
  (y REAL)
)

(struct Rect
  ""
  (left REAL)
  (bottom REAL)
  (right REAL)
  (top REAL)
)

(struct TextWidth
  ""
  (numchars UINT)
  (numwords UINT)
  (width UINT)
  (numspace UINT)
)
