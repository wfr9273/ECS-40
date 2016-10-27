#! /bin/bash

#if there is no argument
if [ $# -eq 0 ]; then
  #scan each file in current directory
  for file in `ls *.txt`; do
    #display the first 3 lines of the file
    echo Displaying first 3 lines of $file:
    sed -n '1,3p' $file
    echo ''
    #interact with user
    echo -e "Delete file $file? (y/n) \c"
    read choice
    #if choice is yes, remove file
    if [ $choice = 'y' ]; then
      rm -f $file
    fi  #if end
  done  #for end
#if there is argument
else
  #scan each file in arguments
  while [ $# -gt 0 ]; do
    #display the first 3 lines of the file
    echo Displaying first 3 lines of $1:
    sed -n '1,3p' $1
    echo ''
    #interact with user
    echo -e "Delete file $1? (y/n) \c"
    read choice
    #if choice is yes, remove file
    if [ $choice = 'y' ]; then
      rm -f $1
    fi  #if end
    shift #get the next argument
  done  #while end
fi  #if end
