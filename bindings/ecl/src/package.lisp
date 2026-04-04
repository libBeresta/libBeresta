;; 
;; libBeresta
;; 
;; Заголовочные файлы для Embeddable Common Lisp (ecl)
;; Дмитрий Соломенников, (с) 2025
;;
(in-package #:cl-user)

(defpackage #:cl-beresta
  (:use #:cl)
  (:nicknames :brst)
  (:export
  #:string-to-cstring
  #:with-pdf-document
  #:with-ttf-font
  #:page-set-dash-pattern
  #:stream-set-dash-pattern
  #:with-page-gsave
  #:with-stream-gsave

)
(:shadow :REAL :BYTE :Error :Array :PI))
