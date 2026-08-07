#!/bin/bash -x

#set -e

SCRIPT_DIR=$( cd "$( dirname "$0" )" && pwd -P )

RENDER_DIR=$SCRIPT_DIR/../../gen/
PREFIX=../bindings/C
mkdir $SCRIPT_DIR/src > /dev/null

pushd $RENDER_DIR > /dev/null

#./render.sh $PREFIX/ecl-page-sizes.dj     page_sizes.lsp ru $PREFIX/src/page_sizes.lisp
#./render.sh $PREFIX/ecl-page-sizes-216.dj page_sizes.lsp ru $PREFIX/src/page_sizes_216.lisp

#./render.sh $PREFIX/ecl-types.dj types.lsp      ru $PREFIX/src/types.lisp
echo "$PREFIX/genc.dj"
./render.sh $PREFIX/genc.dj base.lsp             ru $PREFIX/src/base.h
./render.sh $PREFIX/genc.dj error.lsp            ru $PREFIX/src/error.h
./render.sh $PREFIX/genc.dj destination.lsp      ru $PREFIX/src/destination.h
./render.sh $PREFIX/genc.dj array.lsp            ru $PREFIX/src/array.h
./render.sh $PREFIX/genc.dj mmgr.lsp             ru $PREFIX/src/mmgr.h
./render.sh $PREFIX/genc.dj dict.lsp             ru $PREFIX/src/dict.h
./render.sh $PREFIX/genc.dj font.lsp             ru $PREFIX/src/font.h
./render.sh $PREFIX/genc.dj page.lsp             ru $PREFIX/src/page.h
./render.sh $PREFIX/genc.dj page_routines.lsp    ru $PREFIX/src/page_routines.h
./render.sh $PREFIX/genc.dj text.lsp             ru $PREFIX/src/text.h
./render.sh $PREFIX/genc.dj geometry.lsp         ru $PREFIX/src/geometry.h
./render.sh $PREFIX/genc.dj doc.lsp              ru $PREFIX/src/doc.h
./render.sh $PREFIX/genc.dj doc_ext_gstate.lsp   ru $PREFIX/src/doc_ext_gstate.h
./render.sh $PREFIX/genc.dj doc_page.lsp         ru $PREFIX/src/doc_page.h
./render.sh $PREFIX/genc.dj doc_save.lsp         ru $PREFIX/src/doc_save.h
./render.sh $PREFIX/genc.dj mmgr.lsp             ru $PREFIX/src/mmgr.h
./render.sh $PREFIX/genc.dj geometry_defines.lsp ru $PREFIX/src/geometry_defines.h
./render.sh $PREFIX/genc.dj structs.lsp          ru $PREFIX/src/structs.h
./render.sh $PREFIX/genc.dj ext_gstate.lsp       ru $PREFIX/src/ext_gstate.h
./render.sh $PREFIX/genc.dj text_defines.lsp     ru $PREFIX/src/text_defines.h
./render.sh $PREFIX/genc.dj doc_info.lsp         ru $PREFIX/src/doc_info.h
./render.sh $PREFIX/genc.dj date.lsp             ru $PREFIX/src/date.h
./render.sh $PREFIX/genc.dj doc_encoding_utf.lsp ru $PREFIX/src/doc_encoding_utf.h
./render.sh $PREFIX/genc.dj doc_encoder.lsp      ru $PREFIX/src/doc_encoder.h
./render.sh $PREFIX/genc.dj doc_xobject.lsp      ru $PREFIX/src/doc_xobject.h
./render.sh $PREFIX/genc.dj page_xobject.lsp     ru $PREFIX/src/page_xobject.h
./render.sh $PREFIX/genc.dj xobject.lsp          ru $PREFIX/src/xobject.h
./render.sh $PREFIX/genc.dj stream_geometry.lsp  ru $PREFIX/src/stream_geometry.h
./render.sh $PREFIX/genc.dj stream.lsp           ru $PREFIX/src/stream.h
./render.sh $PREFIX/genc.dj pattern.lsp          ru $PREFIX/src/pattern.h
./render.sh $PREFIX/genc.dj matrix.lsp           ru $PREFIX/src/matrix.h
./render.sh $PREFIX/genc.dj doc_matrix.lsp       ru $PREFIX/src/doc_matrix.h
./render.sh $PREFIX/genc.dj doc_page_pattern.lsp ru $PREFIX/src/doc_page_pattern.h
./render.sh $PREFIX/genc.dj consts.lsp           ru $PREFIX/src/consts.h
./render.sh $PREFIX/genc.dj stream_text.lsp      ru $PREFIX/src/stream_text.h
./render.sh $PREFIX/genc.dj doc_font.lsp         ru $PREFIX/src/doc_font.h
./render.sh $PREFIX/genc.dj doc_compression.lsp  ru $PREFIX/src/doc_compression.h

popd > /dev/null
