;; 
;; libBeresta
;; 
;; Заголовочные файлы для Embeddable Common Lisp (ecl)
;; Дмитрий Соломенников, (с) 2025-2026
;;

(in-package #:cl-beresta)

(include-header)

(func Stream-GSave 
     "BRST_Stream_GSave" 
      STATUS 
  ((page Stream)))

(func Stream-GRestore 
     "BRST_Stream_GRestore" 
      STATUS 
  ((page Stream)))

(func Stream-Concat 
     "BRST_Stream_Concat" 
      STATUS 
  ((page Stream)
   (a REAL)
   (b REAL)
   (c REAL)
   (d REAL)
   (x REAL)
   (y REAL)))

(func Stream-Translate 
     "BRST_Stream_Translate" 
      STATUS 
  ((page Stream)
   (dx REAL)
   (dy REAL)))

(func Stream-Scale 
     "BRST_Stream_Scale" 
      STATUS 
  ((page Stream)
   (sx REAL)
   (sy REAL)))

(func Stream-RotateDeg 
     "BRST_Stream_RotateDeg" 
      STATUS 
  ((page Stream)
   (degrees REAL)))

(func Stream-Rotate 
     "BRST_Stream_Rotate" 
      STATUS 
  ((page Stream)
   (radians REAL)))

(func Stream-Skew 
     "BRST_Stream_Skew" 
      STATUS 
  ((page Stream)
   (a REAL)
   (b REAL)))

(func Stream-Circle 
     "BRST_Stream_Circle" 
      STATUS 
  ((page Stream)
   (x REAL)
   (y REAL)
   (radius REAL)))

(func Stream-SetGrayFill 
     "BRST_Stream_SetGrayFill" 
      STATUS 
  ((page Stream)
   (value REAL)))

(func Stream-SetGrayStroke 
     "BRST_Stream_SetGrayStroke" 
      STATUS 
  ((page Stream)
   (value REAL)))

(func Stream-SetRGBFill 
     "BRST_Stream_SetRGBFill" 
      STATUS 
  ((page Stream)
   (r REAL)
   (g REAL)
   (b REAL)))

(func Stream-SetRGBFillUint 
     "BRST_Stream_SetRGBFillUint" 
      STATUS 
  ((page Stream)
   (r UINT8)
   (g UINT8)
   (b UINT8)))

(func Stream-SetRGBFillHex 
     "BRST_Stream_SetRGBFillHex" 
      STATUS 
  ((page Stream)
   (rgb UINT32)))

(func Stream-SetRGBStroke 
     "BRST_Stream_SetRGBStroke" 
      STATUS 
  ((page Stream)
   (r REAL)
   (g REAL)
   (b REAL)))

(func Stream-SetRGBStrokeUint 
     "BRST_Stream_SetRGBStrokeUint" 
      STATUS 
  ((page Stream)
   (r UINT8)
   (g UINT8)
   (b UINT8)))

(func Stream-SetRGBStrokeHex 
     "BRST_Stream_SetRGBStrokeHex" 
      STATUS 
  ((page Stream)
   (rgb UINT32)))

(func Stream-SetCMYKFill 
     "BRST_Stream_SetCMYKFill" 
      STATUS 
  ((page Stream)
   (c REAL)
   (m REAL)
   (y REAL)
   (k REAL)))

(func Stream-SetCMYKStroke 
     "BRST_Stream_SetCMYKStroke" 
      STATUS 
  ((page Stream)
   (c REAL)
   (m REAL)
   (y REAL)
   (k REAL)))

(func Stream-Clip 
     "BRST_Stream_Clip" 
      STATUS 
  ((page Stream)))

(func Stream-Eoclip 
     "BRST_Stream_Eoclip" 
      STATUS 
  ((page Stream)))

(func Stream-Stroke 
     "BRST_Stream_Stroke" 
      STATUS 
  ((page Stream)))

(func Stream-ClosePathStroke 
     "BRST_Stream_ClosePathStroke" 
      STATUS 
  ((page Stream)))

(func Stream-Fill 
     "BRST_Stream_Fill" 
      STATUS 
  ((page Stream)))

(func Stream-Eofill 
     "BRST_Stream_Eofill" 
      STATUS 
  ((page Stream)))

(func Stream-FillStroke 
     "BRST_Stream_FillStroke" 
      STATUS 
  ((page Stream)))

(func Stream-EofillStroke 
     "BRST_Stream_EofillStroke" 
      STATUS 
  ((page Stream)))

(func Stream-ClosePathFillStroke 
     "BRST_Stream_ClosePathFillStroke" 
      STATUS 
  ((page Stream)))

(func Stream-ClosePathEofillStroke 
     "BRST_Stream_ClosePathEofillStroke" 
      STATUS 
  ((page Stream)))

(func Stream-EndPath 
     "BRST_Stream_EndPath" 
      STATUS 
  ((page Stream)))

(func Stream-MoveTo 
     "BRST_Stream_MoveTo" 
      STATUS 
  ((page Stream)
   (x REAL)
   (y REAL)))

(func Stream-LineTo 
     "BRST_Stream_LineTo" 
      STATUS 
  ((page Stream)
   (x REAL)
   (y REAL)))

(func Stream-CurveTo 
     "BRST_Stream_CurveTo" 
      STATUS 
  ((page Stream)
   (x1 REAL)
   (y1 REAL)
   (x2 REAL)
   (y2 REAL)
   (x3 REAL)
   (y3 REAL)))

(func Stream-CurveTo2 
     "BRST_Stream_CurveTo2" 
      STATUS 
  ((page Stream)
   (x2 REAL)
   (y2 REAL)
   (x3 REAL)
   (y3 REAL)))

(func Stream-CurveTo3 
     "BRST_Stream_CurveTo3" 
      STATUS 
  ((page Stream)
   (x1 REAL)
   (y1 REAL)
   (x3 REAL)
   (y3 REAL)))

(func Stream-ClosePath 
     "BRST_Stream_ClosePath" 
      STATUS 
  ((page Stream)))

(func Stream-Rectangle 
     "BRST_Stream_Rectangle" 
      STATUS 
  ((page Stream)
   (x REAL)
   (y REAL)
   (width REAL)
   (height REAL)))

(func Stream-SetLineWidth 
     "BRST_Stream_SetLineWidth" 
      STATUS 
  ((page Stream)
   (line-width REAL)))

(func Stream-SetLineCap 
     "BRST_Stream_SetLineCap" 
      STATUS 
  ((page Stream)
   (line-cap LineCap)))

(func Stream-SetLineJoin 
     "BRST_Stream_SetLineJoin" 
      STATUS 
  ((page Stream)
   (line-join LineJoin)))

(func Stream-SetMiterLimit 
     "BRST_Stream_SetMiterLimit" 
      STATUS 
  ((page Stream)
   (miter-limit REAL)))

(func Stream-SetDash 
     "BRST_Stream_SetDash" 
      STATUS 
  ((page Stream)
   (dash-pattern DASH-PATTERN)
   (num-elem UINT)
   (phase REAL)))

(func Stream-SetFlat 
     "BRST_Stream_SetFlat" 
      STATUS 
  ((page Stream)
   (flatness REAL)))
