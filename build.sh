#!/bin/sh

set -xe

CLFAGS="-Wall -Wextra -ggdb"
FILES="-I./src src/*.c"

mkdir -p ./build/
clang $CFLAGS -o ./build/cider $FILES
