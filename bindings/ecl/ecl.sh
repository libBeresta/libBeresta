#!/bin/bash

#set -e

SCRIPT_DIR=$( cd "$( dirname "$0" )" && pwd -P )

RENDER_DIR=$SCRIPT_DIR/../../gen/
PREFIX=../bindings/ecl

mkdir $SCRIPT_DIR/src 2> /dev/null

pushd $RENDER_DIR > /dev/null

cp $PREFIX/macro.exp $PREFIX/src/

./render.sh `realpath $PREFIX/ecl-page-sizes.dj`     ru lisp     `realpath $PREFIX/src/` page_sizes.lsp       
./render.sh `realpath $PREFIX/ecl-page-sizes-216.dj` ru lisp_216 `realpath $PREFIX/src/` page_sizes.lsp

./render.sh `realpath $PREFIX/ecl-types.dj` ru lisp `realpath $PREFIX/src/` types.lsp

./render.sh `realpath $PREFIX/ecl.dj` ru lisp `realpath $PREFIX/src/` \
            base.lsp             \
            error.lsp            \
            destination.lsp      \
            array.lsp            \
            mmgr.lsp             \
            dict.lsp             \
            font.lsp             \
            page.lsp             \
            page_routines.lsp    \
            text.lsp             \
            geometry.lsp         \
            doc.lsp              \
            doc_ext_gstate.lsp   \
            doc_page.lsp         \
            doc_save.lsp         \
            mmgr.lsp             \
            geometry_defines.lsp \
            structs.lsp          \
            ext_gstate.lsp       \
            text_defines.lsp     \
            doc_info.lsp         \
            date.lsp             \
            doc_encoding_utf.lsp \
            doc_encoder.lsp      \
            doc_xobject.lsp      \
            page_xobject.lsp     \
            xobject.lsp          \
            stream_geometry.lsp  \
            stream.lsp           \
            pattern.lsp          \
            matrix.lsp           \
            doc_matrix.lsp       \
            doc_page_pattern.lsp \
            consts.lsp           \
            stream_text.lsp      \
            doc_font.lsp         \
            doc_compression.lsp

./render.sh `realpath $PREFIX/exp-ecl.dj` ru exp `realpath $PREFIX/src/` \
            base.lsp             \
            error.lsp            \
            destination.lsp      \
            array.lsp            \
            mmgr.lsp             \
            page.lsp             \
            dict.lsp             \
            font.lsp             \
            page_routines.lsp    \
            text.lsp             \
            geometry.lsp         \
            doc.lsp              \
            doc_ext_gstate.lsp   \
            doc_page.lsp         \
            doc_save.lsp         \
            mmgr.lsp             \
            geometry_defines.lsp \
            structs.lsp          \
            ext_gstate.lsp       \
            text_defines.lsp     \
            doc_info.lsp         \
            date.lsp             \
            doc_encoding_utf.lsp \
            doc_encoder.lsp      \
            doc_xobject.lsp      \
            page_xobject.lsp     \
            xobject.lsp          \
            stream_geometry.lsp  \
            stream.lsp           \
            pattern.lsp          \
            matrix.lsp           \
            doc_matrix.lsp       \
            doc_page_pattern.lsp \
            consts.lsp           \
            stream_text.lsp      \
            doc_font.lsp         \
            doc_compression.lsp  

cp $PREFIX/macro.lisp  $PREFIX/src/

cat $PREFIX/ЛИЦЕНЗИЯ.txt    > $PREFIX/src/package.lisp
cat $PREFIX/package.head   >> $PREFIX/src/package.lisp
cat $PREFIX/src/*.exp      >> $PREFIX/src/package.lisp
rm  $PREFIX/src/*.exp
cat $PREFIX/package.tail   >> $PREFIX/src/package.lisp

mv $PREFIX/src/page_sizes.lisp_216 $PREFIX/src/page_sizes_216.lisp

popd > /dev/null
