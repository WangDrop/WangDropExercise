#!/usr/bin/env python
# coding=utf-8
class Robot:
    ''' represent a robot with a name '''
    population = 0
    
    def __init__(self, name):
        '''Init the data '''
        self.name = name
        print('Initialze the {0}'.format(self.name))
        Robot.population += 1

    def __del__(self):
        ''' I am dying '''
        print('{0} is now being destroyed !'.format(self.name))
        Robot.population -= 1;
        if(Robot.population == 0):
            print('The ', self.name, ' is just the last one ')
        else:
            print('There also ',Robot.population , ' robots now working !')

    def sayHi(self):
        '''Greeting by the robots '''
        print('Hello, my master call me {0}'.format(self.name))

    def howMany(): #without self mean it is a static method
        '''show the current population'''
        print('we still have {0:d} robots '.format(Robot.population))
    howMany = staticmethod(howMany)

droid1 = Robot('wang');
droid1.sayHi()
Robot.howMany()

droid2 = Robot('cheng')
droid2.sayHi()
Robot.howMany()

del droid1
del droid2

#注意，这里的population实际上属于Robot类，但是name是属于对象的。前者相当于static变量
#howMany由于没有加上self进行限制，所以而且使用staticmethod修饰表示了其是一个静态方法
#当然，除了staticmethod修饰之外，也可以使用@staticmethod进行修饰，如下所示：
#@staticmethod
#def howMany():


#还有一点应该注意的是，python类中所有的成员，无论是数据还是方法都是共有的，有一个例外是
#双下划线前缀的数据成员例如：__privatevar,python会将其当做私有变量来看待
