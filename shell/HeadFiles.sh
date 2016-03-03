#!/bin/bash
# list the 3 line of a file and choose to delete it
if [ $# -ne 0 ]
then 
	while [ -n "$1" ]
	do
		head -n 3 ./$1
		read -p "Delete file $1? (y/n) " chioce1
		if [ "$chioce1"x = "y"x ]
		then
			rm $1	 
		fi
	shift
	done
else# para not exist, handle all text file in curr dir
    for file in `find ./ -name "*.txt"`
	do
		head -n 3 $file
		read -p  "Delete file $i? (y/n) " chioce2
		if [ "$chioce2"x = "y"x ]
		then 
			rm $file
		fi
	done
fi

