#!/usr/bin/env python
# coding=utf-8
x = 50
def func_global():
    global x
    print('The global x is ', x)
    x = 2
    print('now the x is ', x)

func_global()
print('after fuction, the x is : ', x)
