#!/usr/bin/env python
# coding=utf-8
try:
    text = input("Enter SomeThing: ")
except EOFError:
    print("Why did you do an eof on me?")
except KeyboardInterrupt:
    print("You cancelled the operation!")
else:
    print("You entered {0}".format(text))
