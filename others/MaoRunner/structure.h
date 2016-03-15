#ifndef STRUCTURE_H
#define STRUCTURE_H
#include "define.h"

/**
**下面主要是程序使用过程中需要使用的堆栈（因为使用了逆波兰表示法）
**/

struct Varible{
	char varName[NAME_MAX_LEN];	//变量的名称
	enum varType type; //变量的类型（0：int， 1：double）
	int32_t val0;
	double val1;
};


struct subExp{ //这里是按照等号分开的子表达式
	char * p;	//表达式的起始位置
	int expLen; //表达式的长度
};


struct tokenStack{
	char token[MAX_TOKEN];
	int top;
};
void push(struct tokenStack * s, char c);
char pop(struct tokenStack * s);
int isEmpty(struct tokenStack * s);
char top(struct tokenStack * s);


struct tokenStackExp{ // 字符串形式的堆栈
	char exp[MAX_TOKEN][NAME_MAX_LEN]; // 最多存放100个变脸或者数字在堆栈里面
	int top;
};
void pushExp(struct tokenStackExp * s, const char * exp);
const char * popExp(struct tokenStackExp * s);
int isEmptyExp(struct tokenStackExp * s);
const char * topExp(struct tokenStackExp * s);

#endif
