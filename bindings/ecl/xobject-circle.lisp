(in-package #:cl-beresta)

(with-pdf-document (pdf "xobject-circle.pdf")
  (let ((page (doc-page-add pdf)))
    (page-setsize page
                  page-size-a4
                  page-orientation-landscape)

    (let* ((xobj (doc-xobject-create pdf
					  100 100
					  1 1))
	   (stream (xobject-stream xobj)))
      (stream-circle stream 50 50 49.5)
      (stream-stroke stream)

      (page-translate page 50 50)
      (page-xobject-execute page xobj)

      (setf page (doc-page-add pdf))
      (page-setsize page
                    page-size-a4
                    page-orientation-landscape)
      (page-translate page 200 110)
      (page-xobject-execute page xobj))))
