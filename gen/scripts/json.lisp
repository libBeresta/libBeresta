(defun do-json-many (args)
  (let ((dir (first args))
        (files (cdr args)))
    (dolist (f files)
      (let ((output (change-ext f dir "json")))
        (process-to-json f output)))))

(let ((rs-json:*encode-symbol-hook* :downcase))
  (multiple-value-bind (args found--)
      (rem-args (ext:command-args) (ext:command-args))

    (if found--
        (if (< (length args) 2)
            (princ "There must be parameters:
  <target folder> <file(s)>
  set after '--'.
")
            (progn
              (do-json-many args)
              (si:exit 0)))
        (princ "Please call with '--' command line argument.
"))
    (si:exit 1)))
