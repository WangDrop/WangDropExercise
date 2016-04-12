#!/usr/bin/env python
# coding=utf-8
class Person:
    def __init__(self, name):
        self.name = name
    def sayHi(self):
        print('My name is ', self.name)

p = Person("wangcheng ")
p.sayHi()
