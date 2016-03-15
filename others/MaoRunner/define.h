#ifndef DEFINE_H
#define DEFINE_H
#include "stdio.h"
#include "string.h"
#include "stdint.h"
#include "limits.h"
#define NAME_MAX_LEN 21 //定义变量名最长不可以超过20，左后一个用来存放字符串结尾的0
#define MAX_LINE_LEN 1024
#define MAX_LINE 1024
#define MAX_TOKEN 100 //堆栈中可以包含的最多的符号的数目
#define MAX_CONST_LEN 32 //常量的最长长度（十进制）
typedef int BOOL;
#define True 1
#define False 0
#define DEVIDE_ERROR -2147483647//除出错
enum varType{
	 INT, DOUBLE }; //定义一个枚举类型，表明数据的


#endif
	
