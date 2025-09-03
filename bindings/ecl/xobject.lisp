(in-package #:cl-beresta)

(with-pdf-document (pdf "xobject.pdf")
  (let ((page (doc-page-add pdf)))
    (page-setsize page
                  page-size-a4
                  page-orientation-landscape)

    (let* ((xobj (doc-page-xobject-create pdf
					  page
					  100 100
					  1 1))
	   (stream (xobject-stream xobj)))
      (stream-moveto stream 0 0)
      (stream-lineto stream 100 100)
      (stream-stroke stream)

      (page-translate page 50 50)
      (page-xobject-execute page xobj)

      (setf page (doc-page-add pdf))
      (page-setsize page
                    page-size-a4
                    page-orientation-landscape)
      (page-translate page 200 110)
      (page-xobject-execute page xobj))))
