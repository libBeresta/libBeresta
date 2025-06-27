#!/bin/sh
#
# Этот скрипт пересоздает файлы brst_page_sizes.h 
# и brst_page_sizes_minimal.h
# 
# Для запуска генерации используется Jinja2, 
# ставится с помощью
# `pip3 install jinja2-cli`
#
# TODO переделать генерацию, включить минимальное
# 
J=~/.local/bin/jinja2
RES=../include/brst_page_sizes.h
RES216=../include/brst_page_sizes_iso_216.h

cat brst_page_sizes.json | $J brst_page_sizes.template > $RES
cat brst_page_sizes_iso_216.json | $J brst_page_sizes.template > $RES216
