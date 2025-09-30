#!/bin/bash

#set -e

SCRIPT_DIR=$( cd "$( dirname "$0" )" && pwd -P )

RENDER_DIR=$SCRIPT_DIR/../../gen/
PREFIX=../bindings/ecl

mkdir $SCRIPT_DIR/src > /dev/null

pushd $RENDER_DIR > /dev/null

./render.sh $PREFIX/ecl-page-sizes.dj     page_sizes.lsp ru $PREFIX/src/page_sizes.lisp
./render.sh $PREFIX/ecl-page-sizes-216.dj page_sizes.lsp ru $PREFIX/src/page_sizes_216.lisp

./render.sh $PREFIX/ecl-types.dj types.lsp      ru $PREFIX/src/types.lisp
./render.sh $PREFIX/ecl.dj base.lsp             ru $PREFIX/src/base.lisp
./render.sh $PREFIX/ecl.dj error.lsp            ru $PREFIX/src/error.lisp
./render.sh $PREFIX/ecl.dj destination.lsp      ru $PREFIX/src/destination.lisp
./render.sh $PREFIX/ecl.dj array.lsp            ru $PREFIX/src/array.lisp
./render.sh $PREFIX/ecl.dj mmgr.lsp             ru $PREFIX/src/mmgr.lisp
./render.sh $PREFIX/ecl.dj dict.lsp             ru $PREFIX/src/dict.lisp
./render.sh $PREFIX/ecl.dj font.lsp             ru $PREFIX/src/font.lisp
./render.sh $PREFIX/ecl.dj page.lsp             ru $PREFIX/src/page.lisp
./render.sh $PREFIX/ecl.dj page_routines.lsp    ru $PREFIX/src/page_routines.lisp
./render.sh $PREFIX/ecl.dj text.lsp             ru $PREFIX/src/text.lisp
./render.sh $PREFIX/ecl.dj geometry.lsp         ru $PREFIX/src/geometry.lisp
./render.sh $PREFIX/ecl.dj doc.lsp              ru $PREFIX/src/doc.lisp
./render.sh $PREFIX/ecl.dj doc_page.lsp         ru $PREFIX/src/doc_page.lisp
./render.sh $PREFIX/ecl.dj doc_save.lsp         ru $PREFIX/src/doc_save.lisp
./render.sh $PREFIX/ecl.dj mmgr.lsp             ru $PREFIX/src/mmgr.lisp
./render.sh $PREFIX/ecl.dj geometry_defines.lsp ru $PREFIX/src/geometry_defines.lisp
./render.sh $PREFIX/ecl.dj structs.lsp          ru $PREFIX/src/structs.lisp
./render.sh $PREFIX/ecl.dj ext_gstate.lsp       ru $PREFIX/src/ext_gstate.lisp
./render.sh $PREFIX/ecl.dj text_defines.lsp     ru $PREFIX/src/text_defines.lisp
./render.sh $PREFIX/ecl.dj doc_info.lsp         ru $PREFIX/src/doc_info.lisp
./render.sh $PREFIX/ecl.dj date.lsp             ru $PREFIX/src/date.lisp
./render.sh $PREFIX/ecl.dj doc_encoding_utf.lsp ru $PREFIX/src/doc_encoding_utf.lisp
./render.sh $PREFIX/ecl.dj doc_encoder.lsp      ru $PREFIX/src/doc_encoder.lisp
./render.sh $PREFIX/ecl.dj doc_xobject.lsp      ru $PREFIX/src/doc_xobject.lisp
./render.sh $PREFIX/ecl.dj page_xobject.lsp     ru $PREFIX/src/page_xobject.lisp
./render.sh $PREFIX/ecl.dj xobject.lsp          ru $PREFIX/src/xobject.lisp
./render.sh $PREFIX/ecl.dj stream_geometry.lsp  ru $PREFIX/src/stream_geometry.lisp
./render.sh $PREFIX/ecl.dj stream.lsp           ru $PREFIX/src/stream.lisp
./render.sh $PREFIX/ecl.dj pattern.lsp          ru $PREFIX/src/pattern.lisp
./render.sh $PREFIX/ecl.dj matrix.lsp           ru $PREFIX/src/matrix.lisp
./render.sh $PREFIX/ecl.dj doc_matrix.lsp       ru $PREFIX/src/doc_matrix.lisp
./render.sh $PREFIX/ecl.dj doc_page_pattern.lsp ru $PREFIX/src/doc_page_pattern.lisp
./render.sh $PREFIX/ecl.dj consts.lsp           ru $PREFIX/src/consts.lisp
./render.sh $PREFIX/ecl.dj stream_text.lsp      ru $PREFIX/src/stream_text.lisp
./render.sh $PREFIX/ecl.dj doc_font.lsp         ru $PREFIX/src/doc_font.lisp

./render.sh $PREFIX/exp-ecl-page-sizes.dj     page_sizes.lsp ru $PREFIX/src/exp-page_sizes.lisp
./render.sh $PREFIX/exp-ecl-page-sizes-216.dj page_sizes.lsp ru $PREFIX/src/exp-page_sizes-216.lisp

./render.sh $PREFIX/exp-ecl-types.dj types.lsp      ru $PREFIX/src/exp-types.lisp
./render.sh $PREFIX/exp-ecl.dj base.lsp             ru $PREFIX/src/exp-base.lisp
./render.sh $PREFIX/exp-ecl.dj error.lsp            ru $PREFIX/src/exp-error.lisp
./render.sh $PREFIX/exp-ecl.dj destination.lsp      ru $PREFIX/src/exp-destination.lisp
./render.sh $PREFIX/exp-ecl.dj array.lsp            ru $PREFIX/src/exp-array.lisp
./render.sh $PREFIX/exp-ecl.dj mmgr.lsp             ru $PREFIX/src/exp-mmgr.lisp
./render.sh $PREFIX/exp-ecl.dj page.lsp             ru $PREFIX/src/exp-page.lisp
./render.sh $PREFIX/exp-ecl.dj dict.lsp             ru $PREFIX/src/exp-dict.lisp
./render.sh $PREFIX/exp-ecl.dj font.lsp             ru $PREFIX/src/exp-font.lisp
./render.sh $PREFIX/exp-ecl.dj page_routines.lsp    ru $PREFIX/src/exp-page_routines.lisp
./render.sh $PREFIX/exp-ecl.dj text.lsp             ru $PREFIX/src/exp-text.lisp
./render.sh $PREFIX/exp-ecl.dj geometry.lsp         ru $PREFIX/src/exp-geometry.lisp
./render.sh $PREFIX/exp-ecl.dj doc.lsp              ru $PREFIX/src/exp-doc.lisp
./render.sh $PREFIX/exp-ecl.dj doc_page.lsp         ru $PREFIX/src/exp-doc_page.lisp
./render.sh $PREFIX/exp-ecl.dj doc_save.lsp         ru $PREFIX/src/exp-doc_save.lisp
./render.sh $PREFIX/exp-ecl.dj mmgr.lsp             ru $PREFIX/src/exp-mmgr.lisp
./render.sh $PREFIX/exp-ecl.dj geometry_defines.lsp ru $PREFIX/src/exp-geometry_defines.lisp
./render.sh $PREFIX/exp-ecl.dj structs.lsp          ru $PREFIX/src/exp-structs.lisp
./render.sh $PREFIX/exp-ecl.dj ext_gstate.lsp       ru $PREFIX/src/exp-ext_gstate.lisp
./render.sh $PREFIX/exp-ecl.dj text_defines.lsp     ru $PREFIX/src/exp-text_defines.lisp
./render.sh $PREFIX/exp-ecl.dj doc_info.lsp         ru $PREFIX/src/exp-doc_info.lisp
./render.sh $PREFIX/exp-ecl.dj date.lsp             ru $PREFIX/src/exp-date.lisp
./render.sh $PREFIX/exp-ecl.dj doc_encoding_utf.lsp ru $PREFIX/src/exp-doc_encoding_utf.lisp
./render.sh $PREFIX/exp-ecl.dj doc_encoder.lsp      ru $PREFIX/src/exp-doc_encoder.lisp
./render.sh $PREFIX/exp-ecl.dj doc_page_xobject.lsp ru $PREFIX/src/exp-doc_page_xobject.lisp
./render.sh $PREFIX/exp-ecl.dj page_xobject.lsp     ru $PREFIX/src/exp-page_xobject.lisp
./render.sh $PREFIX/exp-ecl.dj xobject.lsp          ru $PREFIX/src/exp-xobject.lisp
./render.sh $PREFIX/exp-ecl.dj stream_geometry.lsp  ru $PREFIX/src/exp-stream_geometry.lisp
./render.sh $PREFIX/exp-ecl.dj stream.lsp           ru $PREFIX/src/exp-stream.lisp
./render.sh $PREFIX/exp-ecl.dj pattern.lsp          ru $PREFIX/src/exp-pattern.lisp
./render.sh $PREFIX/exp-ecl.dj matrix.lsp           ru $PREFIX/src/exp-matrix.lisp
./render.sh $PREFIX/exp-ecl.dj doc_matrix.lsp       ru $PREFIX/src/exp-doc_matrix.lisp
./render.sh $PREFIX/exp-ecl.dj doc_page_pattern.lsp ru $PREFIX/src/exp-doc_page_pattern.lisp
./render.sh $PREFIX/exp-ecl.dj consts.lsp           ru $PREFIX/src/exp-consts.lisp
./render.sh $PREFIX/exp-ecl.dj stream_text.lsp      ru $PREFIX/src/exp-stream_text.lisp
./render.sh $PREFIX/exp-ecl.dj doc_font.lsp         ru $PREFIX/src/exp-doc_font.lisp

cp $PREFIX/macro.lisp  $PREFIX/src/

cat $PREFIX/ЛИЦЕНЗИЯ.txt    > $PREFIX/src/package.lisp
cat $PREFIX/package.head   >> $PREFIX/src/package.lisp
cat $PREFIX/src/exp-*.lisp >> $PREFIX/src/package.lisp
rm  $PREFIX/src/exp-*.lisp
cat $PREFIX/package.tail   >> $PREFIX/src/package.lisp


popd > /dev/null
