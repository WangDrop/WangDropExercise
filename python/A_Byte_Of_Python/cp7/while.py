#!/usr/bin/env python
# coding=utf-8
number=23
running=True
while running:
    guess=int(input('Enter a integer'))
    if(guess == number):
        print('Congradulations! you guessed it.')
        running=False
    elif(guess < number):
        print('it is too small')
    elif(guess > number):
        print('it is too large')
else:
    print('the loop is over!')
print('done')
