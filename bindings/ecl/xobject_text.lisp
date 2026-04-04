(in-package #:cl-beresta)

(with-pdf-document (pdf "xobject_text.pdf")
  (let ((page (doc-page-add pdf)))
    (page-setsize page
                  page-size-a4
                  page-orientation-landscape)

    (doc-useutfencodings pdf)
    (doc-encoder-setcurrent pdf "UTF-8")

    (with-ttf-font (font pdf "../../data/fonts/PT/PT/PT-Astra-Serif/pt-astra-serif_regular.ttf")
      (let* ((xobj (doc-xobject-create pdf
                                            100 100
                                            1 1))
             (stream (xobject-stream xobj))
             (width (page-width page))
             (height (page-height page)))

	(dict-setfontandsize xobj font 24)
	(stream-rectangle stream 0 0 100 100)
	(stream-stroke stream)

	(stream-begintext stream)
	(stream-movetextpos stream 0 0)
	(stream-showtext stream font (string-to-cstring "Ю"))
	(stream-endtext stream)

	(page-translate page (- (/ width 2) 50) (- (/ height 2) 50))
	(page-xobject-execute page xobj)

	(setf page (doc-page-add pdf))
	(page-setsize page
                      page-size-a4
                      page-orientation-landscape)
	(page-translate page (/ width 2) (/ height 2))
	(page-rotatedeg page -45)
	(page-translate page -50 -50)
	(page-xobject-execute page xobj)))))
