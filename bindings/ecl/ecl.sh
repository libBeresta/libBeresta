#!/bin/bash

#set -e

SCRIPT_DIR=$( cd "$( dirname "$0" )" && pwd -P )

RENDER_DIR=$SCRIPT_DIR/../../gen/scripts/
PREFIX=../../bindings/ecl

mkdir $SCRIPT_DIR/src 2> /dev/null

pushd $RENDER_DIR > /dev/null

cp $PREFIX/macro.exp $PREFIX/src/

./render.sh `realpath $PREFIX/ecl-page-sizes.dj`     ru lisp     `realpath $PREFIX/src/` ../data/page_sizes.lsp
./render.sh `realpath $PREFIX/ecl-page-sizes-216.dj` ru lisp_216 `realpath $PREFIX/src/` ../data/page_sizes.lsp

./render.sh `realpath $PREFIX/ecl-types.dj` ru lisp `realpath $PREFIX/src/` ../data/types.lsp

./render.sh `realpath $PREFIX/exp-ecl-page-sizes-216.dj` ru exp `realpath $PREFIX/src/` ../data/page_sizes.lsp

./render.sh `realpath $PREFIX/ecl.dj` ru lisp `realpath $PREFIX/src/` \
            ../data/base.lsp             \
            ../data/error.lsp            \
            ../data/destination.lsp      \
            ../data/array.lsp            \
            ../data/mmgr.lsp             \
            ../data/dict.lsp             \
            ../data/font.lsp             \
            ../data/page.lsp             \
            ../data/page_routines.lsp    \
            ../data/text.lsp             \
            ../data/geometry.lsp         \
            ../data/doc.lsp              \
            ../data/doc_ext_gstate.lsp   \
            ../data/doc_page.lsp         \
            ../data/doc_save.lsp         \
            ../data/mmgr.lsp             \
            ../data/geometry_defines.lsp \
            ../data/structs.lsp          \
            ../data/ext_gstate.lsp       \
            ../data/text_defines.lsp     \
            ../data/doc_info.lsp         \
            ../data/date.lsp             \
            ../data/doc_encoding_utf.lsp \
            ../data/doc_encoder.lsp      \
            ../data/doc_xobject.lsp      \
            ../data/page_xobject.lsp     \
            ../data/xobject.lsp          \
            ../data/stream_geometry.lsp  \
            ../data/stream.lsp           \
            ../data/pattern.lsp          \
            ../data/matrix.lsp           \
            ../data/doc_matrix.lsp       \
            ../data/doc_page_pattern.lsp \
            ../data/consts.lsp           \
            ../data/stream_text.lsp      \
            ../data/doc_font.lsp         \
            ../data/doc_compression.lsp

./render.sh `realpath $PREFIX/exp-ecl.dj` ru exp `realpath $PREFIX/src/` \
            ../data/base.lsp             \
            ../data/error.lsp            \
            ../data/destination.lsp      \
            ../data/array.lsp            \
            ../data/mmgr.lsp             \
            ../data/page.lsp             \
            ../data/dict.lsp             \
            ../data/font.lsp             \
            ../data/page_routines.lsp    \
            ../data/text.lsp             \
            ../data/geometry.lsp         \
            ../data/doc.lsp              \
            ../data/doc_ext_gstate.lsp   \
            ../data/doc_page.lsp         \
            ../data/doc_save.lsp         \
            ../data/mmgr.lsp             \
            ../data/geometry_defines.lsp \
            ../data/structs.lsp          \
            ../data/ext_gstate.lsp       \
            ../data/text_defines.lsp     \
            ../data/doc_info.lsp         \
            ../data/date.lsp             \
            ../data/doc_encoding_utf.lsp \
            ../data/doc_encoder.lsp      \
            ../data/doc_xobject.lsp      \
            ../data/page_xobject.lsp     \
            ../data/xobject.lsp          \
            ../data/stream_geometry.lsp  \
            ../data/stream.lsp           \
            ../data/pattern.lsp          \
            ../data/matrix.lsp           \
            ../data/doc_matrix.lsp       \
            ../data/doc_page_pattern.lsp \
            ../data/consts.lsp           \
            ../data/stream_text.lsp      \
            ../data/doc_font.lsp         \
            ../data/doc_compression.lsp  

cp $PREFIX/macro.lisp  $PREFIX/src/

cat $PREFIX/ЛИЦЕНЗИЯ.txt    > $PREFIX/src/package.lisp
cat $PREFIX/package.head   >> $PREFIX/src/package.lisp
cat $PREFIX/src/*.exp      >> $PREFIX/src/package.lisp
rm  $PREFIX/src/*.exp
cat $PREFIX/package.tail   >> $PREFIX/src/package.lisp

mv $PREFIX/src/page_sizes.lisp_216 $PREFIX/src/page_sizes_216.lisp

popd > /dev/null
