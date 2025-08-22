;;; -*- Mode: Lisp indent-tabs-mode: nil -*-
;;;
;;; cl-beresta.asd --- Определение системы ASDF для cl-beresta.
;;
;; libBeresta
;;
;; Заголовочные файлы для Embeddable Common Lisp (ecl)
;; Дмитрий Соломенников, (с) 2025
;;

(asdf:defsystem :cl-beresta
  :description "Заголовочные файлы Lisp для библиотеки libBeresta"
  :author "Дмитрий Соломенников <dmitrys99@mail.ru>"
  :version "1.0.0"
  :components
  ((:module "src"
    :components
            ((:file "package")
             (:file "macro" :depends-on ("package"))
             (:file "types" :depends-on ("package" "macro"))
             (:file "doc" :depends-on ("package" "types" "macro"))
             (:file "mmgr" :depends-on ("package" "types" "macro"))
             (:file "base" :depends-on ("package" "types" "mmgr" "doc" "macro"))
             (:file "doc_page" :depends-on ("package" "types" "mmgr" "doc" "base" "macro"))
             (:file "doc_save" :depends-on ("package" "types" "mmgr" "doc" "base" "macro"))
             (:file "error")
             (:file "array" :depends-on ("package"))
             (:file "destination" :depends-on ("package" "array"))
             (:file "geometry_defines" :depends-on ("package" "types" "page"))
             (:file "geometry" :depends-on ("package" "types" "geometry_defines" "page"))
             (:file "page" :depends-on ("package" "types" "dict"))
             (:file "dict" :depends-on ("package" "types"))
             (:file "font" :depends-on ("package" "dict"))
             (:file "ext_gstate" :depends-on ("package" "types" "geometry_defines"))
             (:file "page_routines" :depends-on ("package" "types" "page_sizes" "structs" "ext_gstate" "destination"))
             (:file "structs" :depends-on ("package" "types"))
             (:file "page_sizes")
             (:file "text_defines" :depends-on ("package" "types"))
             (:file "text")
             ))))
