#!/usr/bin/env python
# coding=utf-8
def func_outter():
    x = 2
    print('x is ',x)
    def func_inner():
        nonlocal x
        x = 5
    func_inner()
    print('change local x to ', x)
func_outter()
