#!/usr/bin/env python
# coding=utf-8
import os
import time
target_dir = "/root/BackUp"
source = ["/root/Codes/", "/root/huaweiGA/"]
today = target_dir + os.sep + time.strftime("%Y%m%d")
now = time.strftime("%H%M%S")

if(not os.path.exists(today)):
    os.mkdir(today)
    print("Successful create directory !\n")

target = today + os.sep + now + ".zip"
zip_command = "zip -qr {0} {1}".format(target, ' '.join(source))
if(os.system(zip_command) == 0):
    print("Successful backup to ", target)
else:
    print("Backup FAILED")
