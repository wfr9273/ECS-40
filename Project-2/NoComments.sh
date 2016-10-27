#! /bin/bash

#scan for every C file in current directory
for file in `ls *.c`; do
  #test whether file exists
  if [ -r $file ]
  then
    while read line
    do
      echo $line
    done < $file
  #  done  #end while
  fi  #end if
done  #end for
