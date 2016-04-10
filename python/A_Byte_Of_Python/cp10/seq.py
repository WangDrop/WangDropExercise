#!/usr/bin/env python
# coding=utf-8
shoplist = ['carrort', 'apple', 'mango', 'banana'];
name = 'swaroop';

print('Item o is ', shoplist[0])
print('Item 1 is ', shoplist[1])
print('Item 2 is ', shoplist[2])
print('Item 3 is ', shoplist[3])
print('Item -1 is ', shoplist[-1])
print('Item -2 is ', shoplist[-2])
print('Item -3 is ', shoplist[-3])
print('Character 0 is ', name[0])

#slicing
print('Item 1 to 3 is ', shoplist[1:3])
print('Item 2 to end is ', shoplist[2:])
print('Item 1 to -1 is ', shoplist[1:-1])
print('Item start to end is: ', shoplist[:])


#adjust the length os slice 
print('Set step to 1, ', shoplist[::1])
print('Set step to 2, ', shoplist[::2])
print('set step to 3, ', shoplist[::3])
print('set step to -1 ', shoplist[::-1])
