#!/bin/bash

if [ "x$1" == "x" ]; then
  echo "Утилита генерации заголовков libBeresta"
  echo "render.sh <файл шаблона> <язык> <расширение> <целевой каталог> <файл данных> [<файл данных> ...] "
  echo ""
  echo "Язык задается кодом (ru, en)"
  exit
fi

# Должна быть задана переменная ECL, указывающая на исполняемый файл ecl.
if [ "x$ECL" == "x" ]; then
  ECL=ecl
fi

$ECL --load "utils.lisp" --load "render.lisp" -- $*
