#!/bin/zsh

if [ -e out.txt ]; then
    rm out.txt
    echo "out.txt successfully deleted"
else
    ./listfiles xxx listfiles.c listfiles-example-dir /dev/tty > out.txt 2>&1
    echo "out.txt successfully created"
    diff -Z out.txt listfiles-out.txt
    LC_ALL=C sort out.txt | diff -Z - listfiles-out-sorted.txt
fi
