;; 
;; libBeresta
;; 
;; Заголовочные файлы для Embeddable Common Lisp (ecl)
;; Дмитрий Соломенников, (с) 2025-2026
;;
(in-package #:cl-user)

(defpackage #:cl-beresta
  (:use #:cl)
  (:nicknames :brst)
  (:export
  ;; array: pointers
  #:Array



  ;; base: functions
  #:Doc-New-Ex
  #:Version
  #:Doc-New
  #:Doc-New-Empty
  #:Doc-Initialize
  #:Doc-Destroy
  #:Doc-Initialized
  #:Doc-Destroy-All
  #:Doc-MMgr
  #:Doc-Free
  #:PageSize-Width
  #:PageSize-Height
  ;; consts: constants
  #:TRUE
  #:FALSE
  #:OK
  #:PI
  #:MM
  #:IN

  ;;; consts: enums
  ;; CompressionMode
  #:COMP-MODE-NONE
  #:COMP-MODE-TEXT
  #:COMP-MODE-IMAGE
  #:COMP-MODE-METADATA
  #:COMP-MODE-ALL
  ;; Permission
  #:ENABLE-READ
  #:ENABLE-PRINT
  #:ENABLE-EDIT-ALL
  #:ENABLE-COPY
  #:ENABLE-EDIT
  ;; ViewerPreference
  #:HIDE-TOOLBAR
  #:HIDE-MENUBAR
  #:HIDE-WINDOW-UI
  #:FIT-WINDOW
  #:CENTER-WINDOW
  #:PRINT-SCALING-NONE
  #:DISPLAY-DOC-TITLE
  ;; date: pointers
  #:Date

  ;;; date: enums
  ;; Date_Parts
  #:DATE-PART-YEAR
  #:DATE-PART-MONTH
  #:DATE-PART-DAY
  #:DATE-PART-HOUR
  #:DATE-PART-MINUTE
  #:DATE-PART-SECOND
  #:DATE-PART-HOUR-OFFSET
  #:DATE-PART-MINUTE-OFFSET
  #:DATE-PART-UT-RELATIONSHIP
  ;; UT_Relationship
  #:UT-RELATIONSHIP-NONE
  #:UT-RELATIONSHIP-PLUS
  #:UT-RELATIONSHIP-MINUS
  #:UT-RELATIONSHIP-ZERO
  ;; date: functions
  #:Date-Now
  #:Date-Part
  #:Date-Validate
  #:Date-Free
  ;; destination: definitions
  #:Destination

  ;; destination: functions
  #:Destination-SetXYZ
  #:Destination-SetFit
  #:Destination-SetFitH
  #:Destination-SetFitV
  #:Destination-SetFitR
  #:Destination-SetFitB
  #:Destination-SetFitBH
  #:Destination-SetFitBV
  ;; dict: pointers
  #:Dict



  ;; doc_compression: functions
  #:Doc-SetCompressionMode


  ;; doc_encoder: functions
  #:Doc-Encoder-SetCurrent
  #:Doc-Encoder-Prepare
  #:Doc-Encoder-Current


  ;; doc_encoding_utf: functions
  #:Doc-UseUTFEncodings
  ;; doc: pointers
  #:Doc

  ;;; doc: enums
  ;; PdfVer
  #:VER-10
  #:VER-11
  #:VER-12
  #:VER-13
  #:VER-14
  #:VER-15
  #:VER-16
  #:VER-17
  #:VER-20


  ;; doc_ext_gstate: functions
  #:Doc-Create-ExtGState


  ;; doc_font: functions
  #:Doc-Font
  #:Doc-TTFont-LoadFromFile
  #:Doc-Type1Font-LoadFromFile
  #:Doc-TTFont-LoadFromFile2
  #:Doc-TTFont-LoadFromMemory


  ;;; doc_info: enums
  ;; InfoType
  #:INFO-CREATION-DATE
  #:INFO-MOD-DATE
  #:INFO-AUTHOR
  #:INFO-CREATOR
  #:INFO-PRODUCER
  #:INFO-TITLE
  #:INFO-SUBJECT
  #:INFO-KEYWORDS
  #:INFO-TRAPPED
  #:INFO-GTS-PDFX
  ;; doc_info: functions
  #:Doc-SetInfoAttr
  #:Doc-SetInfoDateAttr


  ;; doc_matrix: functions
  #:Doc-Matrix-Identity
  #:Doc-Matrix-Free
  #:Doc-Matrix-Multiply
  #:Doc-Matrix-Translate
  #:Doc-Matrix-Scale
  #:Doc-Matrix-Rotate
  #:Doc-Matrix-RotateDeg
  #:Doc-Matrix-Skew


  ;; doc_page: functions
  #:Doc-Pages-SetConfiguration
  #:Doc-Page-ByIndex
  #:Doc-Page-Layout
  #:Doc-Page-SetLayout
  #:Doc-Page-Mode
  #:Doc-Page-SetMode
  #:Doc-Page-Current
  #:Doc-Page-Add
  #:Doc-Page-Insert
  #:Doc-Page-AddLabel


  ;; doc_page_pattern: functions
  #:Doc-Pattern-Tiling-Create
  #:Doc-Pattern-Stream
  #:Doc-Dict-RGBPatternFill-Select
  #:Doc-Dict-RGBPatternFillUint-Select
  #:Doc-Dict-RGBPatternFillHex-Select
  #:Doc-Page-RGBPatternFill-Select
  #:Doc-Page-RGBPatternFillUint-Select
  #:Doc-Page-RGBPatternFillHex-Select


  ;; doc_save: functions
  #:Doc-SaveToStream
  #:Doc-SaveToFile


  ;; doc_xobject: functions
  #:Doc-XObject-CreateFromImage
  #:Doc-XObject-CreateAsWhiteRect
  #:Doc-XObject-Create
  ;; error: pointers
  #:Error

  ;;; error: enums
  ;; ErrorKind
  #:ARRAY-COUNT-ERR
  #:ARRAY-ITEM-NOT-FOUND
  #:ARRAY-ITEM-UNEXPECTED-TYPE
  #:BINARY-LENGTH-ERR
  #:CANNOT-GET-PALETTE
  #:DICT-COUNT-ERR
  #:DICT-ITEM-NOT-FOUND
  #:DICT-ITEM-UNEXPECTED-TYPE
  #:DICT-STREAM-LENGTH-NOT-FOUND
  #:DOC-ENCRYPTDICT-NOT-FOUND
  #:DOC-INVALID-OBJECT
  #:DUPLICATE-REGISTRATION
  #:EXCEED-JWW-CODE-NUM-LIMIT
  #:ENCRYPT-INVALID-PASSWORD
  #:ERR-UNKNOWN-CLASS
  #:EXCEED-GSTATE-LIMIT
  #:FAILED-TO-ALLOC-MEM
  #:FILE-IO-ERROR
  #:FILE-OPEN-ERROR
  #:FONT-EXISTS
  #:FONT-INVALID-WIDTH-TABLE
  #:INVALID-AFM-HEADER
  #:INVALID-ANNOTATION
  #:INVALID-BIT-PER-COMPONENT
  #:INVALID-CHAR-MATRIX-DATA
  #:INVALID-COLOR-SPACE
  #:INVALID-COMPRESSION-MODE
  #:INVALID-DATE-TIME
  #:INVALID-DESTINATION
  #:INVALID-DOCUMENT
  #:INVALID-DOCUMENT-STATE
  #:INVALID-ENCODER
  #:INVALID-ENCODER-TYPE
  #:INVALID-ENCODING-NAME
  #:INVALID-ENCRYPT-KEY-LEN
  #:INVALID-FONTDEF-DATA
  #:INVALID-FONTDEF-TYPE
  #:INVALID-FONT-NAME
  #:INVALID-IMAGE
  #:INVALID-JPEG-DATA
  #:INVALID-N-DATA
  #:INVALID-OBJECT
  #:INVALID-OBJ-ID
  #:INVALID-OPERATION
  #:INVALID-OUTLINE
  #:INVALID-PAGE
  #:INVALID-PAGES
  #:INVALID-PARAMETER
  #:INVALID-PNG-IMAGE
  #:INVALID-STREAM
  #:MISSING-FILE-NAME-ENTRY
  #:INVALID-TTC-FILE
  #:INVALID-TTC-INDEX
  #:INVALID-WX-DATA
  #:ITEM-NOT-FOUND
  #:LIBPNG-ERROR
  #:NAME-INVALID-VALUE
  #:NAME-OUT-OF-RANGE
  #:PAGES-MISSING-KIDS-ENTRY
  #:PAGE-CANNOT-FIND-OBJECT
  #:PAGE-CANNOT-GET-ROOT-PAGES
  #:PAGE-CANNOT-RESTORE-GSTATE
  #:PAGE-CANNOT-SET-PARENT
  #:PAGE-FONT-NOT-FOUND
  #:PAGE-INVALID-FONT
  #:PAGE-INVALID-FONT-SIZE
  #:PAGE-INVALID-GMODE
  #:PAGE-INVALID-INDEX
  #:PAGE-INVALID-ROTATE-VALUE
  #:PAGE-INVALID-SIZE
  #:PAGE-INVALID-XOBJECT
  #:PAGE-OUT-OF-RANGE
  #:REAL-OUT-OF-RANGE
  #:STREAM-EOF
  #:STREAM-READLN-CONTINUE
  #:STRING-OUT-OF-RANGE
  #:THIS-FUNC-WAS-SKIPPED
  #:TTF-CANNOT-EMBED-FONT
  #:TTF-INVALID-CMAP
  #:TTF-INVALID-FORMAT
  #:TTF-MISSING-TABLE
  #:UNSUPPORTED-FONT-TYPE
  #:UNSUPPORTED-JPEG-FORMAT
  #:UNSUPPORTED-TYPE1-FONT
  #:XREF-COUNT-ERR
  #:ZLIB-ERROR
  #:INVALID-PAGE-INDEX
  #:INVALID-URI
  #:PAGE-LAYOUT-OUT-OF-RANGE
  #:PAGE-MODE-OUT-OF-RANGE
  #:PAGE-NUM-STYLE-OUT-OF-RANGE
  #:ANNOT-INVALID-ICON
  #:ANNOT-INVALID-BORDER-STYLE
  #:PAGE-INVALID-DIRECTION
  #:PAGE-INSUFFICIENT-SPACE
  #:PAGE-INVALID-DISPLAY-TIME
  #:PAGE-INVALID-TRANSITION-TIME
  #:INVALID-PAGE-SLIDESHOW-TYPE
  #:EXT-GSTATE-OUT-OF-RANGE
  #:INVALID-EXT-GSTATE
  #:EXT-GSTATE-READ-ONLY
  #:INVALID-ICC-COMPONENT-NUM
  #:PAGE-INVALID-BOUNDARY
  #:INVALID-SHADING-TYPE
  ;; error: functions
  #:Error-Check
  #:Doc-Error-Code
  #:Doc-Error-DetailCode
  #:Doc-Error-Reset
  #:Doc-Error-SetHandler
  ;; ext_gstate: definitions
  #:ExtGState

  ;; ext_gstate: functions
  #:ExtGState-SetAlphaStroke
  #:ExtGState-SetAlphaFill
  #:ExtGState-SetBlendMode
  ;; font: definitions
  #:Font

  ;; font: functions
  #:Font-Descent
  #:Font-TextWidth2


  ;;; geometry_defines: enums
  ;; LineCap
  #:BUTT-CAP
  #:ROUND-CAP
  #:PROJECTING-SQUARE-CAP
  ;; LineJoin
  #:MITER-JOIN
  #:ROUND-JOIN
  #:BEVEL-JOIN
  ;; BorderStyle
  #:BORDERSTYLE-SOLID
  #:BORDERSTYLE-DASHED
  #:BORDERSTYLE-BEVELED
  #:BORDERSTYLE-INSET
  #:BORDERSTYLE-UNDERLINED
  ;; BlendMode
  #:BLENDMODE-NORMAL
  #:BLENDMODE-COMPATIBLE
  #:BLENDMODE-MULTIPLY
  #:BLENDMODE-SCREEN
  #:BLENDMODE-OVERLAY
  #:BLENDMODE-DARKEN
  #:BLENDMODE-LIGHTEN
  #:BLENDMODE-COLOR-DODGE
  #:BLENDMODE-COLOR-BURN
  #:BLENDMODE-HARD-LIGHT
  #:BLENDMODE-SOFT-LIGHT
  #:BLENDMODE-DIFFERENCE
  #:BLENDMODE-EXCLUSION
  ;; ColorSpace
  #:COLORSPACE-DEVICEGRAY
  #:COLORSPACE-DEVICERGB
  #:COLORSPACE-DEVICECMYK
  #:COLORSPACE-CALGRAY
  #:COLORSPACE-CALRGB
  #:COLORSPACE-LAB
  #:COLORSPACE-ICCBASED
  #:COLORSPACE-SEPARATION
  #:COLORSPACE-DEVICEN
  #:COLORSPACE-INDEXED
  #:COLORSPACE-PATTERN


  ;; geometry: functions
  #:Page-GSave
  #:Page-GRestore
  #:Page-Concat
  #:Page-Translate
  #:Page-Scale
  #:Page-RotateDeg
  #:Page-Rotate
  #:Page-Skew
  #:Page-Circle
  #:Page-Ellipse
  #:Page-Arc
  #:Page-SetGrayFill
  #:Page-SetGrayStroke
  #:Page-SetRGBFill
  #:Page-SetRGBFillUint
  #:Page-SetRGBFillHex
  #:Page-SetRGBStroke
  #:Page-SetRGBStrokeUint
  #:Page-SetRGBStrokeHex
  #:Page-SetCMYKFill
  #:Page-SetCMYKStroke
  #:Page-Clip
  #:Page-Eoclip
  #:Page-Stroke
  #:Page-ClosePathStroke
  #:Page-Fill
  #:Page-Eofill
  #:Page-FillStroke
  #:Page-EofillStroke
  #:Page-ClosePathFillStroke
  #:Page-ClosePathEofillStroke
  #:Page-EndPath
  #:Page-MoveTo
  #:Page-LineTo
  #:Page-CurveTo
  #:Page-CurveTo2
  #:Page-CurveTo3
  #:Page-ClosePath
  #:Page-Rectangle
  #:Page-SetLineWidth
  #:Page-SetLineCap
  #:Page-SetLineJoin
  #:Page-SetMiterLimit
  #:Page-SetDash
  #:Page-SetFlat
  #:Page-GrayFill
  #:Page-GrayStroke
  #:Page-StrokeColorSpace
  #:Page-FillColorSpace
  #:Page-LineWidth
  #:Page-LineCap
  #:Page-LineJoin
  #:Page-MiterLimit
  #:Page-Flat
  #:Page-Matrix
  #:string-to-cstring
  #:with-pdf-document
  #:with-ttf-font
  #:page-set-dash-pattern
  #:stream-set-dash-pattern
  #:with-page-gsave
  #:with-stream-gsave
  ;; matrix: pointers
  #:Matrix

  ;; mmgr: pointers
  #:MMgr

  ;; page: definitions
  #:Page

  ;;; page: enums
  ;; PageLayout
  #:PAGE-LAYOUT-SINGLE
  #:PAGE-LAYOUT-ONE-COLUMN
  #:PAGE-LAYOUT-TWO-COLUMN-LEFT
  #:PAGE-LAYOUT-TWO-COLUMN-RIGHT
  #:PAGE-LAYOUT-TWO-PAGE-LEFT
  #:PAGE-LAYOUT-TWO-PAGE-RIGHT
  ;; PageMode
  #:PAGE-MODE-USE-NONE
  #:PAGE-MODE-USE-OUTLINE
  #:PAGE-MODE-USE-THUMBS
  #:PAGE-MODE-FULL-SCREEN
  #:PAGE-MODE-USE-OC
  #:PAGE-MODE-USE-ATTACHMENTS
  ;; PageNum
  #:PAGE-NUM-DECIMAL
  #:PAGE-NUM-UPPER-ROMAN
  #:PAGE-NUM-LOWER-ROMAN
  #:PAGE-NUM-UPPER-LETTERS
  #:PAGE-NUM-LOWER-LETTERS
  ;; PageBoundary
  #:PAGE-MEDIABOX
  #:PAGE-CROPBOX
  #:PAGE-BLEEDBOX
  #:PAGE-TRIMBOX
  #:PAGE-ARTBOX
  ;; PageTransition
  #:PAGE-TRANSITION-WIPE-RIGHT
  #:PAGE-TRANSITION-WIPE-UP
  #:PAGE-TRANSITION-WIPE-LEFT
  #:PAGE-TRANSITION-WIPE-DOWN
  #:PAGE-TRANSITION-BARN-DOORS-HORIZONTAL-OUT
  #:PAGE-TRANSITION-BARN-DOORS-HORIZONTAL-IN
  #:PAGE-TRANSITION-BARN-DOORS-VERTICAL-OUT
  #:PAGE-TRANSITION-BARN-DOORS-VERTICAL-IN
  #:PAGE-TRANSITION-BOX-OUT
  #:PAGE-TRANSITION-BOX-IN
  #:PAGE-TRANSITION-BLINDS-HORIZONTAL
  #:PAGE-TRANSITION-BLINDS-VERTICAL
  #:PAGE-TRANSITION-DISSOLVE
  #:PAGE-TRANSITION-GLITTER-RIGHT
  #:PAGE-TRANSITION-GLITTER-DOWN
  #:PAGE-TRANSITION-GLITTER-TOP-LEFT-TO-BOTTOM-RIGHT
  #:PAGE-TRANSITION-REPLACE
  ;; PageOrientation
  #:PAGE-ORIENTATION-PORTRAIT
  #:PAGE-ORIENTATION-LANDSCAPE


  ;; page_routines: functions
  #:Page-SetWidth
  #:Page-SetHeight
  #:Page-SetBoundary
  #:Page-SetSize
  #:Page-SetRotate
  #:Page-SetSlideShow
  #:Page-SetHorizontalScaling
  #:Page-GStateDepth
  #:Page-HorizontalScaling
  #:Page-SetZoom
  #:Page-Width
  #:Page-Height
  #:Page-GMode
  #:Page-MMgr
  #:Page-Insert-Shared-Content-Stream
  #:Page-RawWrite
  #:Page-SetExtGState
  #:Page-CreateDestination


  ;; page_xobject: functions
  #:Page-XObject-Execute
  #:Dict-XObject-Execute
  ;; pattern: definitions
  #:Pattern

  ;; stream: pointers
  #:Stream



  ;; stream_geometry: functions
  #:Stream-GSave
  #:Stream-GRestore
  #:Stream-Concat
  #:Stream-Translate
  #:Stream-Scale
  #:Stream-RotateDeg
  #:Stream-Rotate
  #:Stream-Skew
  #:Stream-Circle
  #:Stream-SetGrayFill
  #:Stream-SetGrayStroke
  #:Stream-SetRGBFill
  #:Stream-SetRGBFillUint
  #:Stream-SetRGBFillHex
  #:Stream-SetRGBStroke
  #:Stream-SetRGBStrokeUint
  #:Stream-SetRGBStrokeHex
  #:Stream-SetCMYKFill
  #:Stream-SetCMYKStroke
  #:Stream-Clip
  #:Stream-Eoclip
  #:Stream-Stroke
  #:Stream-ClosePathStroke
  #:Stream-Fill
  #:Stream-Eofill
  #:Stream-FillStroke
  #:Stream-EofillStroke
  #:Stream-ClosePathFillStroke
  #:Stream-ClosePathEofillStroke
  #:Stream-EndPath
  #:Stream-MoveTo
  #:Stream-LineTo
  #:Stream-CurveTo
  #:Stream-CurveTo2
  #:Stream-CurveTo3
  #:Stream-ClosePath
  #:Stream-Rectangle
  #:Stream-SetLineWidth
  #:Stream-SetLineCap
  #:Stream-SetLineJoin
  #:Stream-SetMiterLimit
  #:Stream-SetDash
  #:Stream-SetFlat


  ;; stream_text: functions
  #:Stream-BeginText
  #:Stream-EndText
  #:Stream-SetTextLeading
  #:Stream-SetTextRenderingMode
  #:Stream-MoveTextPos
  #:Stream-MoveTextPos2
  #:Stream-SetTextMatrix
  #:Stream-ShowText
  #:Stream-TextOut
  #:Stream-MoveToNextLine




  ;;; text_defines: enums
  ;; TextRenderingMode
  #:TEXT-RENDERING-MODE-FILL
  #:TEXT-RENDERING-MODE-STROKE
  #:TEXT-RENDERING-MODE-FILL-THEN-STROKE
  #:TEXT-RENDERING-MODE-INVISIBLE
  #:TEXT-RENDERING-MODE-FILL-CLIPPING
  #:TEXT-RENDERING-MODE-STROKE-CLIPPING
  #:TEXT-RENDERING-MODE-FILL-STROKE-CLIPPING
  #:TEXT-RENDERING-MODE-CLIPPING
  ;; TextAlignment
  #:TEXT-ALIGN-LEFT
  #:TEXT-ALIGN-RIGHT
  #:TEXT-ALIGN-CENTER
  #:TEXT-ALIGN-JUSTIFY
  ;; WritingMode
  #:WRITING-MODE-HORIZONTAL
  #:WRITING-MODE-VERTICAL


  ;; text: functions
  #:Page-BeginText
  #:Page-EndText
  #:Page-SetTextLeading
  #:Page-SetFontAndSize
  #:Dict-SetFontAndSize
  #:Page-SetTextRenderingMode
  #:Page-SetTextRise
  #:Page-MoveTextPos
  #:Page-MoveTextPos2
  #:Page-SetTextMatrix
  #:Page-MoveToNextLine
  #:Page-ShowText
  #:Page-ShowTextNextLine
  #:Page-ShowTextNextLineEx
  #:Page-TextOut
  #:Page-TextRect
  #:Page-SetCharSpace
  #:Page-SetWordSpace
  #:Page-TextMatrix
  #:Page-TextLeading
  #:Page-TextRenderingMode
  #:Page-TextRise
  #:Page-CharSpace
  #:Page-WordSpace
  #:Page-CurrentTextPos2
  #:Page-CurrentFont
  #:Page-CurrentFontSize
  #:Page-TextWidth
  #:Page-MeasureText
  ;; xobject: definitions
  #:XObject

  ;; xobject: functions
  #:XObject-Stream

)
(:shadow :REAL :BYTE :Error :Array :PI))
