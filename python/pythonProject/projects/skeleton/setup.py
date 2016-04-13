#!/usr/bin/env python
# coding=utf-8
try:
    from setuptools import setup
except ImportError:
    from distutils.core import setup
config = {
    'description' : 'MyProject',
    'author' : 'WangCheng',
    'url': 'Url to get it at.',
    'download url': 'url to download it',
    'author email' : '1208374893@qq.com', 
    'version' : '0.1', 
    'install requires ' : ['nose'],
    'packages' : ['NAME'],
    'scripts' : [],
    'name' : 'projectName'
}
setup(**config)
