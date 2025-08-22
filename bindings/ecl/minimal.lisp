(in-package #:cl-beresta)

(with-pdf-document (pdf "minimal.pdf")
  (let ((page (doc-page-add pdf)))
    (page-setsize page
                  page-size-a4
                  page-orientation-landscape)))
