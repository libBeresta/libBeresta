(defun do-create-stats (args)
  (let* ((header-dir (first args))
         (data-dir (second args))
	 (target (third args))
	 (headers (directory
		   (merge-pathnames (pathname header-dir)
				    (pathname "*.h"))))
	 (data (directory (merge-pathnames (pathname data-dir)
					   (pathname "*.lsp"))))
	 (target-path (pathname target)))
    (fill-stats headers data target-path)))

(multiple-value-bind (args found--)
    (rem-args (ext:command-args) (ext:command-args))

  (if found--
      (if (< (length args) 3)
          (princ "There must be parameters:
  <headers folder> <generator data folder> <target filename>
  set after '--'.
")
          (progn
            (do-create-stats args)
            (si:exit 0)))
      (princ "Please call with '--' command line argument.
"))
  (si:exit 1))
