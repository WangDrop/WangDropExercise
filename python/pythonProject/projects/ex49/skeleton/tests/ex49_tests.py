#!/usr/bin/env python
# coding=utf-8
from nose.tools import *
from ex49 import lexicon
from ex49 import parser
def test_directions():
    assert_equal(lexicon.scan('north'), [('direction', 'north')])
    result = lexicon.scan("north south east")
    assert_equal(result, [('direction', 'north'), ('direction', 'south'), ('direction', 'east')])

def test_verbs():
    assert_equal(lexicon.scan("go"), [('verb', 'go')])
    result = lexicon.scan("go kill eat")
    assert_equal(result, [("verb", "go"), ("verb", "kill"), ("verb", "eat")])

def test_stops():
    assert_equal(lexicon.scan("the"), [('stop', 'the')])
    result = lexicon.scan("the in of")
    assert_equal(result, [("stop", "the"), ("stop", "in"), ("stop", "of")])

def test_nouns():
    assert_equal(lexicon.scan("1234"), [('number', '1234')])
    result = lexicon.scan("3 91234")
    assert_equal(result, [("number", '3'), ('number', '91234')])

def test_errors():
    assert_equal(lexicon.scan("ASDFADFASDF"), [('error', 'ASDFADFASDF')])
    result = lexicon.scan("bear IAS princess")
    assert_equal(result, [('noun', 'bear'), ('error', 'IAS'), ('noun', 'princess')])

def test_peek():
    assert_equal(parser.peek([('verb', 'kill')]), 'verb')
    assert_equal(None, None)

def test_match():
    assert_equal(parser.match([('verb', 'kill')], 'verb'), ('verb', 'kill'))
    assert_equal(parser.match([('noun', 'carrbinet')], 'noun'), ('noun', 'carrbinet'))
    assert_equal(parser.match(None, 'verb'), None)
    assert_equal(parser.match([('verb', 'like')], 'noun'), None)

#def test_skip(word_list, word_type):

