#!/usr/bin/env python
# coding=utf-8
ad = {
    'Swaroop': 'Swaroop&2221122@212.com',
    'wangcheng': '1208374893@qq.com',
    'swarm':'asdasdasdasd'
}

print('wangcheng \'s address is ', ad['wangcheng'] )
del ad['wangcheng']
print('now there are {0} contain in the address-book'.format(len(ad)))

for name, item in ad.items():
    print('Concat {0} and {1}'.format(name, item))
ad['Guido'] = 'hahah'
if 'Guido' in ad:
    print('Find Guide in ', ad['Guido'] );
