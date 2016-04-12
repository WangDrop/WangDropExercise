#!/usr/bin/env python
# coding=utf-8
import os
import time
source = ['/root/Codes', '/root/huaweiGA']
target_dir = '/root/BackUp'

today = target_dir + os.sep + time.strftime('%Y%m%d')
now = time.strftime('%H%M%S')

comment = input('Please input a note of the backup: ')
if(len(comment) == 0):
    target = today + os.sep + now + '.zip'
else:
    target = today + os.sep + now + '_' + comment.replace(' ', '_') + '.zip'

if(not os.path.exists(today)):
    os.mkdir(today)
    print("Successful create directory !")
zip_command = "zip -qr {0} {1}".format(target, ' '.join(source))

if(os.system(zip_command) == 0):
    print("Successfully backup to ", target)
else:
    print('backup FAILED')
