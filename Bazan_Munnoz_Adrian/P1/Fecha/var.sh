    export CPLUS_INCLUDE_PATH=$(echo | clang -E -v -x c++ - |&
     sed -n -e '/^#include </,/^End of search list/p'|
     sed -e '1d' -e '$d' -e 's/^ //' -e 's/$/:/' | paste -s |   
     sed -e 's/\t//g' -e's/:$//')
