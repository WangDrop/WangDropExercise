#!/bin/bash
#This sh can change the direction
awk '
{
    for(i = 1; i <= NF; ++i){
        if(NR == 1)
            s[i] = $i
        else
            s[i] = s[i] " " $i;
    }
}END #start to print the answer
{
    for(i = 1; s[i] != ""; ++i){
        print s[i];
    }
} file.txt
