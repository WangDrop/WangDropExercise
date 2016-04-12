#!/usr/bin/env python
# coding=utf-8
class SchoolMember:
    '''rep any sch mem'''
    def __init__(self, name, age):
        self.name = name
        self.age = age
        print('Init SchoolMember:{0}'.format(self.name))

    def tell(self):
        '''Tell my details '''
        print('Name:{0}, Age:{1}'.format(self.name, self.age))

class Teacher(SchoolMember):
    def __init__(self, name, age, salary):
        SchoolMember.__init__(self, name, age)
        self.salary = salary
        print('Init Teacher:{0}'.format(self.name))

    def tell(self):
        SchoolMember.tell(self)
        print('Salary ', self.salary)

class Student(SchoolMember):
    def __init__(self, name, age, grades):
        SchoolMember.__init__(self, name, age)
        self.grades = grades

    def tell(self):
        SchoolMember.tell(self) #注意调用基类的方法是参数列表中需要有self
        print('Grades ', self.grades)

tom = Teacher("Tom", 33, 10000)
amy = Student("Amy", 16, 88)

tom.tell()
amy.tell()
