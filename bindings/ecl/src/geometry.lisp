;; 
;; libBeresta
;; 
;; Заголовочные файлы для Embeddable Common Lisp (ecl)
;; Дмитрий Соломенников, (с) 2025-2026
;;

(in-package #:cl-beresta)

(include-header)

(func Page-GSave 
     "BRST_Page_GSave" 
      STATUS 
  ((page Page)))

(func Page-GRestore 
     "BRST_Page_GRestore" 
      STATUS 
  ((page Page)))

(func Page-Concat 
     "BRST_Page_Concat" 
      STATUS 
  ((page Page)
   (a REAL)
   (b REAL)
   (c REAL)
   (d REAL)
   (x REAL)
   (y REAL)))

(func Page-Translate 
     "BRST_Page_Translate" 
      STATUS 
  ((page Page)
   (dx REAL)
   (dy REAL)))

(func Page-Scale 
     "BRST_Page_Scale" 
      STATUS 
  ((page Page)
   (sx REAL)
   (sy REAL)))

(func Page-RotateDeg 
     "BRST_Page_RotateDeg" 
      STATUS 
  ((page Page)
   (degrees REAL)))

(func Page-Rotate 
     "BRST_Page_Rotate" 
      STATUS 
  ((page Page)
   (radians REAL)))

(func Page-Skew 
     "BRST_Page_Skew" 
      STATUS 
  ((page Page)
   (a REAL)
   (b REAL)))

(func Page-Circle 
     "BRST_Page_Circle" 
      STATUS 
  ((page Page)
   (x REAL)
   (y REAL)
   (radius REAL)))

(func Page-Ellipse 
     "BRST_Page_Ellipse" 
      STATUS 
  ((page Page)
   (x REAL)
   (y REAL)
   (a REAL)
   (b REAL)))

(func Page-Arc 
     "BRST_Page_Arc" 
      STATUS 
  ((page Page)
   (x REAL)
   (y REAL)
   (radius REAL)
   (angle1 REAL)
   (angle2 REAL)))

(func Page-SetGrayFill 
     "BRST_Page_SetGrayFill" 
      STATUS 
  ((page Page)
   (value REAL)))

(func Page-SetGrayStroke 
     "BRST_Page_SetGrayStroke" 
      STATUS 
  ((page Page)
   (value REAL)))

(func Page-SetRGBFill 
     "BRST_Page_SetRGBFill" 
      STATUS 
  ((page Page)
   (r REAL)
   (g REAL)
   (b REAL)))

(func Page-SetRGBFillUint 
     "BRST_Page_SetRGBFillUint" 
      STATUS 
  ((page Page)
   (r UINT8)
   (g UINT8)
   (b UINT8)))

(func Page-SetRGBFillHex 
     "BRST_Page_SetRGBFillHex" 
      STATUS 
  ((page Page)
   (rgb UINT32)))

(func Page-SetRGBStroke 
     "BRST_Page_SetRGBStroke" 
      STATUS 
  ((page Page)
   (r REAL)
   (g REAL)
   (b REAL)))

(func Page-SetRGBStrokeUint 
     "BRST_Page_SetRGBStrokeUint" 
      STATUS 
  ((page Page)
   (r UINT8)
   (g UINT8)
   (b UINT8)))

(func Page-SetRGBStrokeHex 
     "BRST_Page_SetRGBStrokeHex" 
      STATUS 
  ((page Page)
   (rgb UINT32)))

(func Page-SetCMYKFill 
     "BRST_Page_SetCMYKFill" 
      STATUS 
  ((page Page)
   (c REAL)
   (m REAL)
   (y REAL)
   (k REAL)))

(func Page-SetCMYKStroke 
     "BRST_Page_SetCMYKStroke" 
      STATUS 
  ((page Page)
   (c REAL)
   (m REAL)
   (y REAL)
   (k REAL)))

(func Page-Clip 
     "BRST_Page_Clip" 
      STATUS 
  ((page Page)))

(func Page-Eoclip 
     "BRST_Page_Eoclip" 
      STATUS 
  ((page Page)))

(func Page-Stroke 
     "BRST_Page_Stroke" 
      STATUS 
  ((page Page)))

(func Page-ClosePathStroke 
     "BRST_Page_ClosePathStroke" 
      STATUS 
  ((page Page)))

(func Page-Fill 
     "BRST_Page_Fill" 
      STATUS 
  ((page Page)))

(func Page-Eofill 
     "BRST_Page_Eofill" 
      STATUS 
  ((page Page)))

(func Page-FillStroke 
     "BRST_Page_FillStroke" 
      STATUS 
  ((page Page)))

(func Page-EofillStroke 
     "BRST_Page_EofillStroke" 
      STATUS 
  ((page Page)))

(func Page-ClosePathFillStroke 
     "BRST_Page_ClosePathFillStroke" 
      STATUS 
  ((page Page)))

(func Page-ClosePathEofillStroke 
     "BRST_Page_ClosePathEofillStroke" 
      STATUS 
  ((page Page)))

(func Page-EndPath 
     "BRST_Page_EndPath" 
      STATUS 
  ((page Page)))

(func Page-MoveTo 
     "BRST_Page_MoveTo" 
      STATUS 
  ((page Page)
   (x REAL)
   (y REAL)))

(func Page-LineTo 
     "BRST_Page_LineTo" 
      STATUS 
  ((page Page)
   (x REAL)
   (y REAL)))

(func Page-CurveTo 
     "BRST_Page_CurveTo" 
      STATUS 
  ((page Page)
   (x1 REAL)
   (y1 REAL)
   (x2 REAL)
   (y2 REAL)
   (x3 REAL)
   (y3 REAL)))

(func Page-CurveTo2 
     "BRST_Page_CurveTo2" 
      STATUS 
  ((page Page)
   (x2 REAL)
   (y2 REAL)
   (x3 REAL)
   (y3 REAL)))

(func Page-CurveTo3 
     "BRST_Page_CurveTo3" 
      STATUS 
  ((page Page)
   (x1 REAL)
   (y1 REAL)
   (x3 REAL)
   (y3 REAL)))

(func Page-ClosePath 
     "BRST_Page_ClosePath" 
      STATUS 
  ((page Page)))

(func Page-Rectangle 
     "BRST_Page_Rectangle" 
      STATUS 
  ((page Page)
   (x REAL)
   (y REAL)
   (width REAL)
   (height REAL)))

(func Page-SetLineWidth 
     "BRST_Page_SetLineWidth" 
      STATUS 
  ((page Page)
   (line-width REAL)))

(func Page-SetLineCap 
     "BRST_Page_SetLineCap" 
      STATUS 
  ((page Page)
   (line-cap LineCap)))

(func Page-SetLineJoin 
     "BRST_Page_SetLineJoin" 
      STATUS 
  ((page Page)
   (line-join LineJoin)))

(func Page-SetMiterLimit 
     "BRST_Page_SetMiterLimit" 
      STATUS 
  ((page Page)
   (miter-limit REAL)))

(func Page-SetDash 
     "BRST_Page_SetDash" 
      STATUS 
  ((page Page)
   (dash-pattern DASH-PATTERN)
   (num-elem UINT)
   (phase REAL)))

(func Page-SetFlat 
     "BRST_Page_SetFlat" 
      STATUS 
  ((page Page)
   (flatness REAL)))

(func Page-GrayFill 
     "BRST_Page_GrayFill" 
      REAL 
  ((page Page)))

(func Page-GrayStroke 
     "BRST_Page_GrayStroke" 
      REAL 
  ((page Page)))

(func Page-StrokeColorSpace 
     "BRST_Page_StrokeColorSpace" 
      ColorSpace 
  ((page Page)))

(func Page-FillColorSpace 
     "BRST_Page_FillColorSpace" 
      ColorSpace 
  ((page Page)))

(func Page-LineWidth 
     "BRST_Page_LineWidth" 
      REAL 
  ((page Page)))

(func Page-LineCap 
     "BRST_Page_LineCap" 
      LineCap 
  ((page Page)))

(func Page-LineJoin 
     "BRST_Page_LineJoin" 
      LineJoin 
  ((page Page)))

(func Page-MiterLimit 
     "BRST_Page_MiterLimit" 
      REAL 
  ((page Page)))

(func Page-Flat 
     "BRST_Page_Flat" 
      REAL 
  ((page Page)))

(func Page-Matrix 
     "BRST_Page_Matrix" 
      Matrix 
  ((page Page)))
