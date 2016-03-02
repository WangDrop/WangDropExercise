#!/bin/bash
#check the disk use on sda1 
if [ $# -ne 1 ]
then
	echo Usage : ./disk.sh a#a represent the limit
else
	perc=`df | grep sda1 | awk '{print $5}'| cut -d '%' -f 1`
	
fi

if [ $perc -gt $1 ]
then
	echo the use of disk exceed the target!
else
	echo "the use of disk doesn't exceed the target!"
fi	

 
