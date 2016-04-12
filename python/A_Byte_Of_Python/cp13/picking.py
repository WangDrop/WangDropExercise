#!/usr/bin/env python
# coding=utf-8
#pickle在这里的作用相当于是序列化以及解序列化的作用
import pickle

shoplistfile = 'shoplist.data'
shoplist = ['apple', 'mango', 'banana']

f = open(shoplistfile, 'wb')
pickle.dump(shoplist, f)
f.close()

del shoplist

f = open(shoplistfile, 'rb')
storedlist = pickle.load(f)
print(storedlist)

