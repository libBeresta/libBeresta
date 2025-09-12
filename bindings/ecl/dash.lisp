(in-package #:cl-beresta)

(with-pdf-document (pdf "dash.pdf")
  (let ((page (doc-page-add pdf)))
    (page-setsize page
                  page-size-a4
                  page-orientation-landscape)

    (page-set-dash-pattern page #(8 7 2 7) 4 0)

    (let ((width (page-width page))
	  (height (page-height page))
	  (margin (* 15 2.834646)))
      (page-rectangle page
		      margin margin
		      (- width (* 2 margin))
		      (- height (* 2 margin))))
    (page-stroke page)))
