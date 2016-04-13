#!/usr/bin/env python
# coding=utf-8
def make_repeter(n):
    return lambda s: s*n#注意这里的s代表的是lambda表达式中传入的值，分别是
twice = make_repeter(2)

print(twice('word'))
print(twice(5))

#lambda表达式需要一个参数，后面跟着单个表达式作为函数体，而表达式的值被这个新建的函数返回，
#注意，即使是print语句也不能使用在lambda表达式中，其中只可以存在表达式

points = [{'x' : 2, 'y' : 3}, {'x' : 4, 'y' : 1}]
points.sort(lambda a,b : cmp(a['x'], b['x']))
