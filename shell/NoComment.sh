#!/bin/bash
# This sh can delete the comment
find . -name  '*.c' | while read i
do 
	sed '/^\/\*/,/^\*\//d' $i
done 

