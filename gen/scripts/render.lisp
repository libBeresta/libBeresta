
(defun do-render (template-file
                  data-file
                  &optional &key
                              (lang *language*)
                              (output :no))
  (when (not (eql output :no))
    (princ (format nil "Processing ~A...~%" data-file)))

  (mapcar #'(lambda (x)
              (let* ((str (string x))
                     (key (intern str :keyword))
                     (val (string-downcase (concatenate 'string ":" str)))
                     (substitute (gethash (cons val *language*) *substitutes*)))
                (setf (getf djula:*default-template-arguments* key) substitute)))
          +given-substitutes+)

  (let* ((*language* lang)
         (template (djula:compile-template* template-file))
         (data (with-open-file (s data-file) (read s))))
    (let ((res (apply #'djula:render-template*
                      (cons template
                            (cons nil
                                  data)))))

      ;;(princ djula:*default-template-arguments*)
      (if (eq output :no)
          (princ res)
          (alexandria:write-string-into-file
           res
           output
           :if-exists :overwrite
           :if-does-not-exist :create)))))

(defun do-render-many (args)
  (let ((template (first args))
        (lang (intern (second args) :keyword))
        (ext (third args))
        (dir (fourth args))
        (files (cddddr args)))
    (dolist (f files)
      (let ((output (change-ext f dir ext)))
        
        (do-render template f :lang lang :output output)))))

(multiple-value-bind (args found--)
    (rem-args (ext:command-args) (ext:command-args))

  (if found--
      (if (< (length args) 5)
          (princ "There must be parameters:
<template file> <language> <extension> <target folder> <file(s)>
set after '--'.
")
          (progn
            (do-render-many args)
            (si:exit 0)))
      (princ "Please call with '--' command line argument.
"))
  (si:exit 1))
