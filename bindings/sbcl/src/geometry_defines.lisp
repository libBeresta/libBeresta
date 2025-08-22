;; 
;; libBeresta
;; 
;; Заголовочные файлы для Embeddable Common Lisp (ecl)
;; Дмитрий Соломенников, (с) 2025
;;

(in-package #:cl-beresta)

(defcenum LineCap 
  :BUTT-CAP
  :ROUND-CAP
  :PROJECTING-SQUARE-CAP
)

(defcenum LineJoin 
  :MITER-JOIN
  :ROUND-JOIN
  :BEVEL-JOIN
)

(defcenum BorderStyle 
  :BORDERSTYLE-SOLID
  :BORDERSTYLE-DASHED
  :BORDERSTYLE-BEVELED
  :BORDERSTYLE-INSET
  :BORDERSTYLE-UNDERLINED
)

(defcenum BlendMode 
  :BLENDMODE-NORMAL
  :BLENDMODE-COMPATIBLE
  :BLENDMODE-MULTIPLY
  :BLENDMODE-SCREEN
  :BLENDMODE-OVERLAY
  :BLENDMODE-DARKEN
  :BLENDMODE-LIGHTEN
  :BLENDMODE-COLOR-DODGE
  :BLENDMODE-COLOR-BURN
  :BLENDMODE-HARD-LIGHT
  :BLENDMODE-SOFT-LIGHT
  :BLENDMODE-DIFFERENCE
  :BLENDMODE-EXCLUSION
)

(defcenum ColorSpace 
  :COLORSPACE-DEVICE-GRAY
  :COLORSPACE-DEVICERGB
  :COLORSPACE-DEVICECMYK
  :COLORSPACE-CALGRAY
  :COLORSPACE-CALRGB
  :COLORSPACE-LAB
  :COLORSPACE-ICCBASED
  :COLORSPACE-SEPARATION
  :COLORSPACE-DEVICEN
  :COLORSPACE-INDEXED
  :COLORSPACE-PATTERN
)

(defcstruct RGBColor
  "Структура для хранения информации о цвете (RGB)"
  (r REAL)
  (g REAL)
  (b REAL)
)

(defcstruct CMYKColor
  "Структура для хранения информации о цвете (CMYK)"
  (c REAL)
  (m REAL)
  (y REAL)
  (k REAL)
)

(defcstruct TransMatrix
  "Структура для хранения матрицы преобразований"
  (a REAL)
  (b REAL)
  (c REAL)
  (d REAL)
  (x REAL)
  (y REAL)
)

(defcstruct DashMode
  "Структура описания пунктира"
  (ptn REAL :count 8)
  (num_ptn UINT)
  (phase REAL)
)
