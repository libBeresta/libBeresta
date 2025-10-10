;; 
;; libBeresta
;; 
;; Заголовочные файлы для Embeddable Common Lisp (ecl)
;; Дмитрий Соломенников, (с) 2025
;;
;; Текст лицензии см. в файле ЛИЦЕНЗИЯ в корне проекта
;;
(in-package #:cl-beresta)

(include-header)

(constant TRUE 1)

(constant FALSE 0)

(constant OK 0)

(constant PI 3.14159265358979323846)

(constant MM 2.834646)

(constant IN 72.00000)

(enum CompressionMode (
   
  (COMP-MODE-NONE #x00) 
  (COMP-MODE-TEXT #x01) 
  (COMP-MODE-IMAGE #x02) 
  (COMP-MODE-METADATA #x04) 
  (COMP-MODE-ALL #x0F)))
