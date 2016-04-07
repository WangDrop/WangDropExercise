#!/usr/bin/env python
# coding=utf-8
def printMax(x,y):
    '''Print the maxmium of the two numbers
    The two numbers must be integers'''
    x=int(x)
    y=int(y)
    if(x > y):
        print(x, 'is maximum')
    else:
        print(y, 'is maximum')
printMax(3,5)
print(printMax.__doc__)
