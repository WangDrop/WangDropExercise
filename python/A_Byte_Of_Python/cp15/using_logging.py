#!/usr/bin/env python
# coding=utf-8
import os, platform, logging
if platform.platform().startswith('Windows'):
    logging_file = os.path.join(os.getenv('HOMEDRIVE'), 'test.log')
else:
    logging_file = os.path.join(os.getenv('HOME'), 'test.log')

logging.basicConfig(
                    level = logging.DEBUG,
                    format = '%(asctime)s : % (levelname)s : %(message)s',
                    filename = logging_file, 
                    filemode = 'w',
                    )

logging.debug('Start of the programm')
logging.info('Doing sth')
logging.warning('Dying Now')

#platform模块用来从系统中得到系统信息
#os提供join的api
#logging用于将信息记录到文件中
