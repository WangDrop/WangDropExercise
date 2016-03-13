#ifndef FUNCTION_H
#define FUNCTION_H
#include "define.h"
#include "structure.h"
#include <stdlib.h>
#include <ctype.h>

int getContent(const char *); //该函数得到文件中的内容，存入字符数组中
int getVarVaule(const char *);	//这个函数根据情况的不同调用下面两个函数
int getVarDeclare(const char *); // 得到某一行声明的变量
int getVarCalculate(const char *);//得到莫一行计算生成的变量的值
struct Varible * getVarible(const char *); //从变量结构体数组里面得到变量的名字和值

void processTheInput(const char * line); //对输入进行处理，将*-这种形式换成类似*(0-sth)这种情况，便于后面的理解
char * skipSpace(const char *);//跳过空格
char * floatToStr(float val, char *buf);//浮点数转换成字符串
char * intToStr(int val, char * buf);//int型转换成字符串打印

#endif
