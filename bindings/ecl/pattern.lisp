(in-package #:cl-beresta)

(with-pdf-document (pdf "pattern.pdf")
  (let ((page (doc-page-add pdf))
	(matrix (doc-matrix-scale pdf
				  (doc-matrix-identity pdf)
				  0.5
				  0.5)))
    (page-setsize page
                  page-size-a4
                  page-orientation-landscape)
    (let* ((pattern (doc-page-pattern-tiling-create pdf
						    page
						    0 0
						    10 10
						    10 10
						    matrix))
	   (stream (doc-page-pattern-stream pattern))
	   (width (page-width page))
	   (height (page-height page))
	   (margin (* 15 2.834646)))
      (stream-setlinewidth stream 0.49814)
      (stream-moveto stream -1  4)
      (stream-lineto stream  6 11)
      (stream-moveto stream  4 -1)
      (stream-lineto stream 11  6)
      (stream-stroke stream)

      (doc-page-rgbpatternfill-select pdf page 1 0 1 pattern)

      (page-rectangle page
		      margin margin
		      (- width  (* margin 2))
		      (- height (* margin 2)))

      (page-fill page)
      (doc-matrix-free matrix))))
