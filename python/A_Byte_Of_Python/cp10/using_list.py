#!/usr/bin/env python
# coding=utf-8
shoplist = ['apple', 'mango', 'carrot', 'banana']
print('I have ', len(shoplist), 'things to buy')
print('These items are:', end = ' ')
for item in shoplist:
    print(item, end = ' ')
print('\nI also have to buy rice.')
shoplist.append('rice')
print('My shoplist now is ', shoplist)
print('I will sort my list now ')
shoplist.sort()
print('Sorted shoplist now is ', shoplist)
print('The first item i have to buy is ', shoplist[0])
olditem = shoplist[0]
del shoplist[0]
print('I have bought item ', olditem)
print('now my shoplist is ', shoplist)
