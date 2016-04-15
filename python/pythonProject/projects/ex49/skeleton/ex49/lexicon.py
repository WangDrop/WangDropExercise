#!/usr/bin/env python
# coding=utf-8
direction = [('direction', 'north'), ('direction','south'), ('direction', 'east'), ('direction', 'west'), ('direction', 'down'), ('direction', 'up'), ('direction', 'left'), ('direction', 'right'), ('direction', 'back')]
verb = [('verb', 'go'), ('verb', 'stop'), ('verb','kill'), ('verb','eat')]
nouns = [('noun', 'door'), ('noun', 'bear'), ('noun', 'princess'), ('noun', 'cabinet')]
modifer = [('stop', 'the'),('stop', 'in'),('stop', 'of'),('stop', 'from'),('stop', 'at'),('stop', 'it')]
allwords = (direction, verb, nouns, modifer)
def scan(stuff):
    words = stuff.split()
    findOne = False
    ret = []
    for word in words:
        if(word.isdigit()):
            ret.append(('number', str(word)))
            continue
        for i in allwords:
            for j in i:
                if word == j[1]:
                    ret.append(j)
                    findOne = True
        if(findOne == False):
            ret.append(('error', word))
        else:
            findOne = False

    return ret

print(scan('go'))
