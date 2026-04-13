;;; Copyright © 2025-2026 Dmitry Solomennikov
;;;
;;; Набор функций для генерации привязок
;;;
;;; Лицензия в файле LICENSE в корне проекта
;;;

;; Генерация языковой привязки из файла-шаблона
;; template-file, файла данных data-file (*.lsp),
;; с учетом языка lang.
;; Параметр output указывает, что результат выводится
;; на консоль (:no), либо в файл (путь указывается в output).
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

      (if (eq output :no)
          (princ res)
          (alexandria:write-string-into-file
           res
           output
           :if-exists :overwrite
           :if-does-not-exist :create)))))

;; Обработка списка файлов,
;; передаваемых через командную строку
(defun do-render-many (args)
  (let ((template (first args))
        (lang (intern (second args) :keyword))
        (ext (third args))
        (dir (fourth args))
        (files (cddddr args)))
    (dolist (f files)
      (let ((output (change-ext f dir ext)))
        (do-render template f :lang lang :output output)))))

;; Непосредственно генерация файлов
;; Проверяется наличие "--" в командной строке.
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
