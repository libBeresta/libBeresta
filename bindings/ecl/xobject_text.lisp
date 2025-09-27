(in-package #:cl-beresta)

(with-pdf-document (pdf "xobject_text.pdf")
  (let ((page (doc-page-add pdf)))
    (page-setsize page
                  page-size-a4
                  page-orientation-landscape)

    (Doc-UseUTFEncodings pdf)
    (Doc-Encoder-SetCurrent pdf "UTF-8")

    (let* ((xobj (doc-page-xobject-create pdf
					  page
					  100 100
					  1 1))
	   (stream (xobject-stream xobj))
	   (width (page-width page))
	   (height (page-height page))
	   (font-name (doc-ttfont-loadfromfile
		       pdf
		       (string-to-cstring
			"../../data/fonts/PT/PT/PT-Astra-Serif/pt-astra-serif_regular.ttf")
		       1))) ;; BRST_TRUE

      (setf font
	    (doc-font pdf
		      (ffi:convert-from-foreign-string font-name)
		      "UTF-8"))

      (dict-setfontandsize xobj font 24)
      (stream-rectangle stream 0 0 100 100)
      (stream-stroke stream)

      (stream-begintext stream)
      (stream-movetextpos stream 0 0)
      (stream-showtext stream font (string-to-cstring "Ю"))
      (stream-endtext stream)

      (page-translate page
		      (- (/ width 2) 50)
		      (- (/ height 2) 50))
      (page-xobject-execute page xobj)
      (setf page (doc-page-add pdf))
      (page-setsize page
                    page-size-a4
                    page-orientation-landscape)
      (page-translate page
		      (/ width 2)
		      (/ height 2))
      (page-rotatedeg page
		      -45)
      (page-translate page
		      -50
		      -50)
      (page-xobject-execute page xobj))))
