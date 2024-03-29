#! /bin/sh
     
exec 3>&1
export GLIBCPP_FORCE_NEW=1
export GLIBCXX_FORCE_NEW=1
exec valgrind --num-callers=20 \
    --leak-check=yes \
    --leak-resolution=high \
    --show-reachable=yes \
    "$@" 2>&1 1>&3 3>&- |
sed 's/^==[0-9]*==/==/' >&2 1>&2 3>&-
