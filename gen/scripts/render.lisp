;;; Copyright © 2025-2026 Dmitry Solomennikov
;;;
;;; Набор функций для генерации привязок
;;;
;;; Лицензия в файле LICENSE в корне проекта
;;;

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
