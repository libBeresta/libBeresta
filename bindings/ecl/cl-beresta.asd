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
             (:file "consts" :depends-on ("package"))
             (:file "types" :depends-on ("package" "macro"))
             (:file "doc" :depends-on ("package" "types" "macro"))
             (:file "mmgr" :depends-on ("package" "types" "macro"))
             (:file "matrix" :depends-on ("package" "types" "macro"))
             (:file "pattern" :depends-on ("package" "types" "macro"))
             (:file "base" :depends-on ("package" "types" "mmgr" "doc" "macro"))
             (:file "doc_page" :depends-on ("package" "types" "mmgr" "doc" "base" "macro"))
             (:file "doc_save" :depends-on ("package" "types" "mmgr" "doc" "base" "macro"))
             (:file "doc_info" :depends-on ("package" "types" "mmgr" "doc" "base" "macro"))
             (:file "doc_font" :depends-on ("package" "types" "mmgr" "doc" "base" "macro" "font"))
             (:file "date" :depends-on ("package" "types" "mmgr" "doc" "base" "macro"))
             (:file "doc_encoder" :depends-on ("package" "types" "mmgr" "doc" "base" "macro"))
             (:file "doc_matrix" :depends-on ("package" "types" "mmgr" "doc" "base" "macro" "matrix"))
             (:file "doc_encoding_utf" :depends-on ("package" "types" "mmgr" "doc" "base" "macro"))
             (:file "doc_xobject" :depends-on ("package" "types" "mmgr" "doc" "base" "macro" "xobject"))
             (:file "doc_ext_gstate" :depends-on ("package" "types" "mmgr" "doc" "base" "macro"))
             (:file "doc_page_pattern" :depends-on ("package" "types" "mmgr" "doc" "base" "macro" "pattern" "matrix"))
             (:file "page_xobject" :depends-on ("package" "types" "mmgr" "doc" "base" "macro" "xobject"))
             (:file "xobject" :depends-on ("package" "types" "mmgr" "doc" "base" "macro"))
             (:file "error")
             (:file "array" :depends-on ("package"))
             (:file "destination" :depends-on ("package" "array"))
             (:file "geometry_defines" :depends-on ("package" "types" "page"))
             (:file "geometry" :depends-on ("package" "types" "geometry_defines" "page"))
             (:file "stream_geometry" :depends-on ("package" "types" "geometry_defines" "stream"))
             (:file "stream_text" :depends-on ("package" "types" "geometry_defines" "stream"))
             (:file "page" :depends-on ("package" "types" "dict"))
             (:file "stream" :depends-on ("package" "types" "dict"))
             (:file "dict" :depends-on ("package" "types"))
             (:file "font" :depends-on ("package" "dict"))
             (:file "ext_gstate" :depends-on ("package" "types" "geometry_defines"))
             (:file "page_routines" :depends-on ("package" "types" #-iso-216-only "page_sizes" #+iso-216-only "page_sizes_216" "structs" "ext_gstate" "destination"))
             (:file "structs" :depends-on ("package" "types"))
             (:file #-iso-216-only "page_sizes" #+iso-216-only "page_sizes_216")
             (:file "text_defines" :depends-on ("package" "types"))
             (:file "text")
             ))))
