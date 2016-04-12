#!/usr/bin/env python
# coding=utf-8
poem = '''
Prog is fun,
when the wroking is done
if you wanna make your work also fun 
use python!
'''

f = open('poem.txt', 'w')
f.write(poem);
f.close()

f = open('poem.txt')
while(True):
    line = f.readline()
    if(len(line) == 0):
        break # get the end
    print(line, end='\n\n') #可以看下这个end代表的具体的含义
f.close()
