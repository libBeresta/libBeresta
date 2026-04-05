#!/bin/bash

# Скрипт проверки орфографии исходных текстов библиотеки.
# Для его работы необходимо установить typos (https://github.com/crate-ci/typos),
# ripgrep (https://github.com/BurntSushi/ripgrep) и hunspell (https://hunspell.github.io/),
# а также дополнительно словарь русского языка для hunspell.
#
# Скрипт не должен ничего напечатать, это является признаком успеха.

# Определяем корень репозитория относительно расположения скрипта
SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
ROOT_DIR="$(cd "$SCRIPT_DIR/../.." && pwd)"

errors=0

typos -c "$SCRIPT_DIR/typos.toml" "$ROOT_DIR/src"       || errors=$((errors + 1))
typos -c "$SCRIPT_DIR/typos.toml" "$ROOT_DIR/include"    || errors=$((errors + 1))
typos -c "$SCRIPT_DIR/typos.toml" "$ROOT_DIR/demo"       || errors=$((errors + 1))
typos -c "$SCRIPT_DIR/typos.toml" "$ROOT_DIR/gen"        || errors=$((errors + 1))

result=""
result+=$(rg -I "//" "$ROOT_DIR/src" | rg -v http | hunspell -d ru_RU,en_US -p "$SCRIPT_DIR/hunspell.dict" -l 2>/dev/null)
result+=$(rg -I "//" "$ROOT_DIR/include" | rg -v http | hunspell -d ru_RU,en_US -p "$SCRIPT_DIR/hunspell.dict" -l 2>/dev/null)
result+=$(rg -I "//" "$ROOT_DIR/demo" | hunspell -d ru_RU,en_US -p "$SCRIPT_DIR/hunspell.dict" -l 2>/dev/null)
result+=$(cat "$ROOT_DIR"/gen/*.lsp 2>/dev/null | hunspell -d ru_RU,en_US -p "$SCRIPT_DIR/hunspell.dict" -l 2>/dev/null)

if [ -n "$result" ]; then
  echo "Spelling issues found in comments:"
  echo "$result"
  errors=$((errors + 1))
fi

exit $errors
