;; 
;; libBeresta
;; 
;; Заголовочные файлы для Embeddable Common Lisp (ecl)
;; Дмитрий Соломенников, (с) 2025
;;

(in-package #:cl-beresta)

(defctype Doc :pointer)

(defcenum PdfVer 
  :VER-10
  :VER-11
  :VER-12
  :VER-13
  :VER-14
  :VER-15
  :VER-16
  :VER-17
  :VER-20
)
