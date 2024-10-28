#!/bin/bash
#
# CMS communication task testing script (Linux)
# usage: bash runtest.sh input.txt solution [args for solution]

CFLAGS="-g -Wall -DDEBUG" make check/manager
test=$1
shift

rm -f to_prg
rm -f from_prg
mknod to_prg p
mknod from_prg p
timeout 10 $* < to_prg > from_prg &
cat $test | ./check/manager from_prg to_prg
rm -f to_prg
rm -f from_prg
