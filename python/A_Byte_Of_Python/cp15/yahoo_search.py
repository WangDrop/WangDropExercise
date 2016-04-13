#!/usr/bin/env python
# coding=utf-8
import sys

if sys.version_info[0] != 3:
    sys.exit('This program needs pyhton 3.0')
import json
import urllib, urllib.parse, urllib.request, urllib.response

YAHOO_APP_ID = 'jl22psvV34HELWhdfUJbfDQzlJ2B57KFS_qs4I8D0Wz5U5_yCI1Awv8.lBSfPhwr'
SEARCH_BASE = 'http://search.yahooapis.com/WebSearchService/V1/webSearch'

class YahooSearchError(Exception):
    pass

def search(query, results=20, start=1, **kwargs):
    kwargs.update({
        'appid':YAHOO_APP_ID,
        'query':query,
        'results':results,
        'start':start,
        'output':json,
    })
    url = SEARCH_BASE + '?' + urllib.parse.urlencode(kwargs)
    result = json.load(urllib.request.urlopen(url))
    if 'Error' in result:
        raise YahooSearchError(result['Errorr'])
    return result['ResultSet']

query=input('what do you want to search for?')
for result in search(query)['Result']:
    print('{0}:{1}'.format(result['Title'], result['Url']))
