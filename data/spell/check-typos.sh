#!/bin/bash

# Скрипт проверки орфографии исходных текстов библиотеки.
# Для его работы необходимо установить typos (https://github.com/crate-ci/typos),
# ripgrep (https://github.com/BurntSushi/ripgrep) и hunspell (https://hunspell.github.io/),
# а также дополнительно словарь русского языка для hunspell.
#
# Скрипт не должен ничего напечатать, это является признаком успеха.
#
# TODO Обработать вывод и напечатать, что все в порядке.

~/.cargo/bin/typos -c ./typos.toml ../../src
~/.cargo/bin/typos -c ./typos.toml ../../include
~/.cargo/bin/typos -c ./typos.toml ../../demo
rg -I "//" ../../src | rg -v http | hunspell -d ru_RU,en_US -p hunspell.dict -l
rg -I "//" ../../include | rg -v http | hunspell -d ru_RU,en_US -p hunspell.dict -l
rg -I "//" ../../demo | hunspell -d ru_RU,en_US -p hunspell.dict -l
