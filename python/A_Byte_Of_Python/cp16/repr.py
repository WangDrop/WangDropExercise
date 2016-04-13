#!/usr/bin/env python
# coding=utf-8
#repr用来取得对象规范字符串的表示，在大多数时候都与eval(repr(object)) == object
i = []
i.append('item')
print(i)
print(repr(i))
print(eval(repr(i)))

