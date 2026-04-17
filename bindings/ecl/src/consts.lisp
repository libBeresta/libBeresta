;; 
;; libBeresta
;; 
;; Заголовочные файлы для Embeddable Common Lisp (ecl)
;; Дмитрий Соломенников, (с) 2025-2026
;;

(in-package #:cl-beresta)

(include-header)

(constant TRUE 1)

(constant FALSE 0)

(constant OK 0)

(constant PI 3.14159265358979323846)

(constant MM 2.834646)

(constant IN 72.00000)

(enum GMode (
   
  (GMODE-PAGE-DESCRIPTION #x0001) 
  (GMODE-PATH-OBJECT #x0002) 
  (GMODE-TEXT-OBJECT #x0004) 
  (GMODE-CLIPPING-PATH #x0008) 
  (GMODE-SHADING #x0010) 
  (GMODE-INLINE-IMAGE #x0020) 
  (GMODE-EXTERNAL-OBJECT #x0040)))

(enum CompressionMode (
   
  (COMP-MODE-NONE #x00) 
  (COMP-MODE-TEXT #x01) 
  (COMP-MODE-IMAGE #x02) 
  (COMP-MODE-METADATA #x04) 
  (COMP-MODE-ALL #x0F)))

(enum Permission (
   
  (ENABLE-READ 0) 
  (ENABLE-PRINT 4) 
  (ENABLE-EDIT-ALL 8) 
  (ENABLE-COPY 16) 
  (ENABLE-EDIT 32)))

(enum ViewerPreference (
   
  (HIDE-TOOLBAR 1) 
  (HIDE-MENUBAR 2) 
  (HIDE-WINDOW-UI 4) 
  (FIT-WINDOW 8) 
  (CENTER-WINDOW 16) 
  (PRINT-SCALING-NONE 32) 
  (DISPLAY-DOC-TITLE 64)))
