#!/usr/bin/env python
# coding=utf-8
class ShortInputException(Exception):
    """A user defined exception"""
    def __init__(self, length, atleast):
        Exception.__init__(self)
        self.length = length
        self.atleast = atleast
try:
    text = input('Enter somthing-->')
    if(len(text) < 3):
        raise ShortInputException(len(text), 3)
except EOFError:
    print("Why do you did a EoF on me ?")
except ShortInputException as ex:
    print("Short Input exception: the input length is {0}, excepted at least {0}".format(ex.length, ex.atleast))
else:
    print("No Exception was raised.")
