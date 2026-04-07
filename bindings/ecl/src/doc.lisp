;; 
;; libBeresta
;; 
;; Заголовочные файлы для Embeddable Common Lisp (ecl)
;; Дмитрий Соломенников, (с) 2025-2026
;;

(in-package #:cl-beresta)

(include-header)

(pointer Doc)

(enum PdfVer (
  
  VER-10
  VER-11
  VER-12
  VER-13
  VER-14
  VER-15
  VER-16
  VER-17
  VER-20))
