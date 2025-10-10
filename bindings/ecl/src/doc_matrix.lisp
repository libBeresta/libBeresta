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

(func Doc-Matrix-Identity 
     "BRST_Doc_Matrix_Identity" 
      Matrix 
  ((pdf Doc)))

(func Doc-Matrix-Free 
     "BRST_Doc_Matrix_Free" 
      void 
  ((m Matrix)))

(func Doc-Matrix-Multiply 
     "BRST_Doc_Matrix_Multiply" 
      Matrix 
  ((pdf Doc)
   (m Matrix)
   (n Matrix)))

(func Doc-Matrix-Translate 
     "BRST_Doc_Matrix_Translate" 
      Matrix 
  ((pdf Doc)
   (m Matrix)
   (dx REAL)
   (dy REAL)))

(func Doc-Matrix-Scale 
     "BRST_Doc_Matrix_Scale" 
      Matrix 
  ((pdf Doc)
   (m Matrix)
   (sx REAL)
   (sy REAL)))

(func Doc-Matrix-Rotate 
     "BRST_Doc_Matrix_Rotate" 
      Matrix 
  ((pdf Doc)
   (m Matrix)
   (angle REAL)))

(func Doc-Matrix-RotateDeg 
     "BRST_Doc_Matrix_RotateDeg" 
      Matrix 
  ((pdf Doc)
   (m Matrix)
   (degrees REAL)))

(func Doc-Matrix-Skew 
     "BRST_Doc_Matrix_Skew" 
      Matrix 
  ((pdf Doc)
   (m Matrix)
   (a REAL)
   (b REAL)))
