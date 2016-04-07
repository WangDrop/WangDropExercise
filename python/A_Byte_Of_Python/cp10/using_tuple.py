#!/usr/bin/env python
# coding=utf-8
zoo=('pythonon', 'elephant', 'penguin')
print('numbers of animals in the zoo is ', len(zoo))

new_zoo = ('monkey', 'camel', zoo)
print('number of cages in the new zoo is ', len(new_zoo))
print('all animal in new zoo is ', new_zoo)
print('animal bought of the old zoo are ', new_zoo[2])
print('number of animals in the new zoo is ', len(new_zoo) - 1 + len(zoo))
