#!/usr/bin/env python
# coding=utf-8
def reverse_text(text):
    return text[::-1]

def is_palindrome(text):
    return text == reverse_text(text)

str = input('Please enter a string, we will check if it is a palindrome: ')
if(is_palindrome(str)):
    print('Yes , this str is a palindrome!')
else:
    print('sorry, the str is not a palindrome!')
