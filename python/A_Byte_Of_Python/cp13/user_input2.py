#!/usr/bin/env python
# coding=utf-8
import string
def reverse_str(text):
    return text[::-1]

def is_palindrome(text):
    return text == reverse_str(text)

def main():
    str = input("Input a string to check if it's a palindrome: ")
    str = str.lower()
    str = str.replace(' ','')
    for char in string.punctuation:
        str = str.replace(char, '')
    if(is_palindrome(str)):
        print('The sting is a palindrome ')
    else:
        print('The string is not a Palindrome ')

if (__name__ == '__main__'):
    main()
else:
    print("user_input2.py was imported!")
