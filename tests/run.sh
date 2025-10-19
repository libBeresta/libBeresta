#!/bin/sh

echo run $1 [[$2]]

PATH=$PATH:$1
cd $1

PATH=$PATH clitest $2/*.test
