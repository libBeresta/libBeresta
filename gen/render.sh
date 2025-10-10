#!/bin/bash

if [ "x$1" == "x" ]; then
  echo "Утилита генерации заголовков libBeresto"
  echo "render.sh <файл шаблона> <файл данных> [[язык] <файл выхода>] "
  echo ""
  echo "Язык задается кодом (ru, en)"
  exit
fi

# Должна быть задана переменная ECL, указывающая на исполняемый файл ecl.
if [ "x$ECL" == "x" ]; then
  ECL=ecl
fi

if [ ! -f $1 ]; then
    echo "Не найден файл шаблона $1"
fi

if [ ! -f $2 ]; then
    echo "Не найден файл данных $1"
fi

OUT=""
if [ "x$4" != "x" ]; then
OUT=":output #p\"$4\""
fi

LNG=""
if [ "x$3" != "x" ]; then
  LNG=":lang :$3"
fi

P1=`realpath $1`
P2=`realpath $2`

$ECL --eval "(asdf:load-system 'djula)"     \
     --eval "(load \"render.lsp\")"         \
     --eval "(do-render #p\"$P1\" #p\"$P2\" $OUT $LNG)" \
     --eval "(si:exit)"                     \
     -q