;; 
;; libBeresta
;; 
;; Заголовочные файлы для Embeddable Common Lisp (ecl)
;; Дмитрий Соломенников, (с) 2025
;;

(in-package #:cl-beresta)

(defcfun ("BRST_Page_GSave" Page-GSave) STATUS
  (page Page))

(defcfun ("BRST_Page_GRestore" Page-GRestore) STATUS
  (page Page))

(defcfun ("BRST_Page_Concat" Page-Concat) STATUS)

(defcfun ("BRST_Page_Translate" Page-Translate) STATUS
  (page Page)
  (dx REAL)
  (dy REAL))

(defcfun ("BRST_Page_Scale" Page-Scale) STATUS
  (page Page)
  (sx REAL)
  (sy REAL))

(defcfun ("BRST_Page_RotateDeg" Page-RotateDeg) STATUS
  (page Page)
  (degrees REAL))

(defcfun ("BRST_Page_Rotate" Page-Rotate) STATUS
  (page Page)
  (radians REAL))

(defcfun ("BRST_Page_Skew" Page-Skew) STATUS
  (page Page)
  (a REAL)
  (b REAL))

(defcfun ("BRST_Page_Circle" Page-Circle) STATUS
  (page Page)
  (x REAL)
  (y REAL)
  (radius REAL))

(defcfun ("BRST_Page_Ellipse" Page-Ellipse) STATUS
  (page Page)
  (x REAL)
  (y REAL)
  (a REAL)
  (b REAL))

(defcfun ("BRST_Page_Arc" Page-Arc) STATUS
  (page Page)
  (x REAL)
  (y REAL)
  (radius REAL)
  (angle1 REAL)
  (angle2 REAL))

(defcfun ("BRST_Page_SetGrayFill" Page-SetGrayFill) STATUS
  (page Page)
  (value REAL))

(defcfun ("BRST_Page_SetGrayStroke" Page-SetGrayStroke) STATUS
  (page Page)
  (value REAL))

(defcfun ("BRST_Page_SetRGBFill" Page-SetRGBFill) STATUS
  (page Page)
  (r REAL)
  (g REAL)
  (b REAL))

(defcfun ("BRST_Page_SetRGBFillUint" Page-SetRGBFillUint) STATUS
  (page Page)
  (r UINT8)
  (g UINT8)
  (b UINT8))

(defcfun ("BRST_Page_SetRGBFillHex" Page-SetRGBFillHex) STATUS
  (page Page)
  (rgb UINT32))

(defcfun ("BRST_Page_SetRGBStroke" Page-SetRGBStroke) STATUS
  (page Page)
  (r REAL)
  (g REAL)
  (b REAL))

(defcfun ("BRST_Page_SetRGBStrokeUint" Page-SetRGBStrokeUint) STATUS
  (page Page)
  (r UINT8)
  (g UINT8)
  (b UINT8))

(defcfun ("BRST_Page_SetRGBStrokeHex" Page-SetRGBStrokeHex) STATUS
  (page Page)
  (rgb UINT32))

(defcfun ("BRST_Page_SetCMYKFill" Page-SetCMYKFill) STATUS
  (page Page)
  (c REAL)
  (m REAL)
  (y REAL)
  (k REAL))

(defcfun ("BRST_Page_SetCMYKStroke" Page-SetCMYKStroke) STATUS
  (page Page)
  (c REAL)
  (m REAL)
  (y REAL)
  (k REAL))

(defcfun ("BRST_Page_Clip" Page-Clip) STATUS
  (page Page))

(defcfun ("BRST_Page_Eoclip" Page-Eoclip) STATUS
  (page Page))

(defcfun ("BRST_Page_Stroke" Page-Stroke) STATUS
  (page Page))

(defcfun ("BRST_Page_ClosePathStroke" Page-ClosePathStroke) STATUS
  (page Page))

(defcfun ("BRST_Page_Fill" Page-Fill) STATUS
  (page Page))

(defcfun ("BRST_Page_Eofill" Page-Eofill) STATUS
  (page Page))

(defcfun ("BRST_Page_FillStroke" Page-FillStroke) STATUS
  (page Page))

(defcfun ("BRST_Page_EofillStroke" Page-EofillStroke) STATUS
  (page Page))

(defcfun ("BRST_Page_ClosePathFillStroke" Page-ClosePathFillStroke) STATUS
  (page Page))

(defcfun ("BRST_Page_ClosePathEofillStroke" Page-ClosePathEofillStroke) STATUS
  (page Page))

(defcfun ("BRST_Page_EndPath" Page-EndPath) STATUS
  (page Page))

(defcfun ("BRST_Page_MoveTo" Page-MoveTo) STATUS
  (page Page)
  (x REAL)
  (y REAL))

(defcfun ("BRST_Page_LineTo" Page-LineTo) STATUS
  (page Page)
  (x REAL)
  (y REAL))

(defcfun ("BRST_Page_CurveTo" Page-CurveTo) STATUS
  (page Page)
  (x1 REAL)
  (y1 REAL)
  (x2 REAL)
  (y2 REAL)
  (x3 REAL)
  (y3 REAL))

(defcfun ("BRST_Page_CurveTo2" Page-CurveTo2) STATUS
  (page Page)
  (x2 REAL)
  (y2 REAL)
  (x3 REAL)
  (y3 REAL))

(defcfun ("BRST_Page_CurveTo3" Page-CurveTo3) STATUS
  (page Page)
  (x1 REAL)
  (y1 REAL)
  (x3 REAL)
  (y3 REAL))

(defcfun ("BRST_Page_ClosePath" Page-ClosePath) STATUS
  (page Page))

(defcfun ("BRST_Page_Rectangle" Page-Rectangle) STATUS
  (page Page)
  (x REAL)
  (y REAL)
  (width REAL)
  (height REAL))

(defcfun ("BRST_Page_SetLineWidth" Page-SetLineWidth) STATUS
  (page Page)
  (line-width REAL))

(defcfun ("BRST_Page_SetLineCap" Page-SetLineCap) STATUS
  (page Page)
  (line-cap LineCap))

(defcfun ("BRST_Page_SetLineJoin" Page-SetLineJoin) STATUS
  (page Page)
  (line-join LineJoin))

(defcfun ("BRST_Page_SetMiterLimit" Page-SetMiterLimit) STATUS
  (page Page)
  (miter-limit REAL))

(defcfun ("BRST_Page_SetDash" Page-SetDash) STATUS
  (page Page)
  (dash-pattern DASH-PATTERN)
  (num-elem UINT)
  (phase REAL))

(defcfun ("BRST_Page_SetFlat" Page-SetFlat) STATUS
  (page Page)
  (flatness REAL))

(defcfun ("BRST_Page_GrayFill" Page-GrayFill) REAL
  (page Page))

(defcfun ("BRST_Page_GrayStroke" Page-GrayStroke) REAL
  (page Page))

(defcfun ("BRST_Page_StrokeColorSpace" Page-StrokeColorSpace) ColorSpace
  (page Page))

(defcfun ("BRST_Page_FillColorSpace" Page-FillColorSpace) ColorSpace
  (page Page))

(defcfun ("BRST_Page_LineWidth" Page-LineWidth) REAL
  (page Page))

(defcfun ("BRST_Page_LineCap" Page-LineCap) LineCap
  (page Page))

(defcfun ("BRST_Page_LineJoin" Page-LineJoin) LineJoin
  (page Page))

(defcfun ("BRST_Page_MiterLimit" Page-MiterLimit) REAL
  (page Page))

(defcfun ("BRST_Page_Flat" Page-Flat) REAL
  (page Page))
