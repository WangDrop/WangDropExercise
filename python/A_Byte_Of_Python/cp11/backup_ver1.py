#!/usr/bin/env python
# coding=utf-8
import os
import time
source=['/root/Codes/', '/root/huawei/']

#first have to create a dir called BackUp in '/'
target_dir = '/BackUp'

target = target_dir + os.sep + time.strftime('%Y%m%d%H%M%S') + '.zip'
zip_command = 'zip -qr {0} {1}'.format(target, ' '.join(source))

if os.system(zip_command) == 0:
    print('Success BackUp to ', target)
else:
    print('BackUp FAILED')

