#!/bin/bash

#ecl \
/home/dmitrys/devel/lisp/ecl-pkg/bin/ecl \
    --eval "(ext:install-c-compiler)" \
    --eval "(setf c:*user-cc-flags* \"-I../../include -L../../build/src/ -lbrst -fPIC -lz\")" \
    --eval "(setf c:*user-linker-libs* \"-L../../build/src/ -lbrst -fPIC -lz\")" \
    --eval "(pushnew  #P\"$(realpath .)/\" asdf:*central-registry*)" \
    --eval "(asdf:load-system 'cl-beresta :verbose t :force t)"

	#--eval "(princ (format nil \"~A\" compiler::*default-machine*))" \



# (pushnew  #P"/home/dmitrys/devel/libberesta/bindings/ecl/" asdf:*central-registry*)
# (asdf:load-system 'cl-beresta :verbose t)