#! /bin/bash

for file in `ls *.c`; do
  cat $file | grep "printf" | grep -v "sprintf"
  match1=$?
  cat $file | grep "fprintf"
  match2=$?
  if [ $match1 -eq 0 ] ; then
    cat $file | grep -x "#include <stdio.h>"
    a=$?
    if [ $a -eq 1 ]; then
      sed -n "1i\'#include <stdio.h>'" $file
    fi
  fi
  if [ $match2 -eq 0 ] ; then
    cat $file | grep -x "#include <stdio.h>"
    a=$?
    if [ $a -eq 1 ]; then
      sed -n "1i\'#include <stdio.h>'" $file
    fi
  fi
done
