#!/bin/bash

if [ "x$1" == "x" ]; then
  echo "Утилита генерации json файлов языковых привязок libBeresta"
  echo "json.sh <целевой каталог> <файл данных> [<файл данных> ...] "
  echo ""
  exit
fi

# Должна быть задана переменная ECL, указывающая на исполняемый файл ecl.
if [ "x$ECL" == "x" ]; then
  ECL=ecl
fi

$ECL --load "json.lisp" -- $*