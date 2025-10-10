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

(func Doc-Font 
     "BRST_Doc_Font" 
      Font 
  ((pdf Doc)
   (font-name CSTR)
   (encoding-name CSTR)))

(func Doc-TTFont-LoadFromFile 
     "BRST_Doc_TTFont_LoadFromFile" 
      Font 
  ((pdf Doc)
   (filename CSTR)
   (embedding BOOL)))
