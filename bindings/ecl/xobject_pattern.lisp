(in-package #:cl-beresta)

(with-pdf-document (pdf "xobject_pattern.pdf")
  (let ((page (doc-page-add pdf)))
    (page-setsize page
                  page-size-a4
                  page-orientation-landscape)

    (let* ((xobj (doc-page-xobject-create pdf
					  page
					  100 100
					  1 1))
	   (stream (xobject-stream xobj))
	   (matrix (doc-matrix-scale pdf
				  (doc-matrix-identity pdf)
				  0.5
				  0.5))
	   (pattern (doc-page-pattern-tiling-create pdf
						    page
						    0 0
						    10 10
						    10 10
						    matrix))
	   (pattern-stream (doc-page-pattern-stream pattern)))
      (stream-setlinewidth pattern-stream 0.49814)


      (stream-moveto pattern-stream -1  4)
      (stream-lineto pattern-stream  6 11)
      (stream-moveto pattern-stream  4 -1)
      (stream-lineto pattern-stream 11  6)
      (stream-stroke pattern-stream)


      (doc-dict-rgbpatternfill-select pdf xobj 1 0 0 pattern)
      (stream-rectangle stream 20 20 80 80)
      (stream-fill stream)
      
      (page-translate page 50 50)
      (page-xobject-execute page xobj)

      (setf page (doc-page-add pdf))
      (page-setsize page
                    page-size-a4
                    page-orientation-landscape)
      (page-translate page 200 110)
      (page-xobject-execute page xobj))))
