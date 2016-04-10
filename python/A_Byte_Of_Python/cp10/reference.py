#!/usr/bin/env python
# coding=utf-8
print('Sample Assignment')
shoplist=['apple', 'mango', 'carrot', 'banana']
mylist = shoplist # just a point pointing to shoplist
del shoplist[0]
print('shoplist is ', shoplist)
print('mylist is ', mylist)

#now is deap copy
mylist = shoplist[:]
del mylist[0]
print('shoplist is ', shoplist)
print('mylist is ', mylist)
