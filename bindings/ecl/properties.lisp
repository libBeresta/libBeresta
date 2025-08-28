(in-package #:cl-beresta)

(with-pdf-document (pdf "properties.pdf")
  (let ((page (doc-page-add pdf)))
    (page-setsize page
                  page-size-a4
                  page-orientation-landscape)

    (Doc-UseUTFEncodings pdf)
    (Doc-Encoder-SetCurrent pdf "UTF-8")

    (Doc-SetInfoAttr pdf INFO-AUTHOR "Author")
    (Doc-SetInfoAttr pdf INFO-CREATOR "Creator")
    (Doc-SetInfoAttr pdf INFO-PRODUCER "Producer")
    (Doc-SetInfoAttr pdf INFO-TITLE "Title")
    (Doc-SetInfoAttr pdf INFO-SUBJECT "Subject")
    (Doc-SetInfoAttr pdf INFO-KEYWORDS "Keywords")

    (let ((date (Date-Now pdf)))
      (Doc-SetInfoDateAttr pdf INFO-CREATION-DATE date)
      (Doc-SetInfoDateAttr pdf INFO-MOD-DATE date))))
