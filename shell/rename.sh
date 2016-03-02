#!/bin/bash
# This sh is aimed for change the name of the file 
if [ $# -ne 2 ]
then
	echo Usage : .sh a b#a and b represent different file types
	exit 1
else
	find ./ -name *.$1 | while read i
	do 
		name=`echo $i|sed 's/'$1'$/'$2'/g'`
		echo $name
		echo "$i change to $name"
		mv $i $name
	done
fi	
