#!/usr/bin/env python
# coding=utf-8
def get_error_details():
    return (2, 'second error details')
errnum, errstr = get_error_details()
print(errnum, " ", errstr)

#注意，这里的b的前面加上一个*号之后赋值得到的才是一个元组
a, *b = [1,2,3,4]
print(a)
print(b)
