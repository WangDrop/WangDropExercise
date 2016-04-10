#!/usr/bin/env python
# coding=utf-8
name = 'Swaroop'
if name.startswith('Swa'):
    print('Yes, the string start with Swa')
if('a' in name):
    print('Yes, the string contains string "a"')
if(name.find('war') != -1):
    print ('Yes, the string contains "war"')

delimiter = '_*_'
mylist=['Brazil', 'Russia', 'India', 'China']
print(delimiter.join(mylist))

