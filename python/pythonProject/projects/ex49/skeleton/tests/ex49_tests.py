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

def test_skip(): #该函数会跳过和制定的词语类型相同的所有的tuple
    assert_equal(parser.skip([('verb', 'kill'), ('noun', 'princess')], 'verb'), None)
    assert_equal(parser.skip([('noun', 'princess'), ('verb', 'kill')], 'verb'), None)

def test_parse_verb():
    assert_equal(parser.parse_verb([('stop', 'the'), ('verb', 'kill')]), ('verb', 'kill'))

def test_parse_object():
    assert_raises(parser.ParseError,parser.parse_object,([('stop', 'the'), ('stop', 'of')], None))
    assert_equal(parser.parse_object([('stop', 'the'), ('stop', 'of'), ('noun', 'princess')]),('noun', 'princess'))
    assert_equal(parser.parse_object([('stop', 'the'), ('direction', 'east')]), ('direction', 'east'))

#def test_parse_subject():
#    assert_equal(parser.parse_subject([('verb', 'kill'), ('noun', 'tom')], ('subj', 'I')), parser.Sentence(('subj', 'I'), ('verb', 'kill'), ('noun', 'tom')))



