;; 
;; libBeresta
;; 
;; Заголовочные файлы для Embeddable Common Lisp (ecl)
;; Дмитрий Соломенников, (с) 2025-2026
;;

(in-package #:cl-beresta)

(include-header)

(struct Point
  ":ru is not set"
  (x REAL)
  (y REAL)
)

(struct Rect
  ":ru is not set"
  (left REAL)
  (bottom REAL)
  (right REAL)
  (top REAL)
)

(struct TextWidth
  ":ru is not set"
  (numchars UINT)
  (numwords UINT)
  (width UINT)
  (numspace UINT)
)
