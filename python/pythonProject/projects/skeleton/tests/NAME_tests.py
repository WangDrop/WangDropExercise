#!/usr/bin/env python
# coding=utf-8
from nose.tools import *
import NAME

def setup():
    print('setup!')
def teardown():
    print('tear down!')
def test_basic():
    print('I RAN')
