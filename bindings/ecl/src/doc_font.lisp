;; 
;; libBeresta
;; 
;; Заголовочные файлы для Embeddable Common Lisp (ecl)
;; Дмитрий Соломенников, (с) 2025-2026
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

(func Doc-Type1Font-LoadFromFile 
     "BRST_Doc_Type1Font_LoadFromFile" 
      CSTR 
  ((pdf Doc)
   (afm-filename CSTR)
   (data-filename CSTR)))

(func Doc-TTFont-LoadFromFile2 
     "BRST_Doc_TTFont_LoadFromFile2" 
      CSTR 
  ((pdf Doc)
   (filename CSTR)
   (index UINT)
   (embedding BOOL)))

(func Doc-TTFont-LoadFromMemory 
     "BRST_Doc_TTFont_LoadFromMemory" 
      CSTR 
  ((pdf Doc)
   (buffer BYTE*)
   (size UINT)
   (embedding BOOL)))
