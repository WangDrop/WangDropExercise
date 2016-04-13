#!/usr/bin/env python
# coding=utf-8
#with语句可以得到去后面语句的文件的控制权
with open("poem.txt") as f:
    for line in f:
        print(line, end='')
#起一般会自动的打开以及关闭文件，这起到了和前面的finally语句相同的结果


