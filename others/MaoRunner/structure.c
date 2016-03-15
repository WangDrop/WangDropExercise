#include "structure.h"
void push(struct tokenStack * s, char c)
{
	if (MAX_TOKEN == s->top){
		return;
	}
	s->token[s->top++] = c;
}

char pop(struct tokenStack * s)
{
	if (0 == s->top){
		return 0;
	}
	return s->token[--s->top];
}

char top(struct tokenStack * s)
{
	if (0 == s->top){
		return;
	}
	return s->token[s->top - 1];
}


int isEmpty(struct tokenStack * s)
{
	if (s->top == 0)
		return 1;
	else
		return 0;
}


void pushExp(struct tokenStackExp * s, const char * exp)
{
	if (s->top == MAX_TOKEN){
		return;
	}
	strcpy(s->exp[s->top], exp);
	s->top++;
}


const char * popExp(struct tokenStackExp * s)
{
	if (s->top == 0){
		return;
	}
	return s->exp[--s->top];
}

const char * topExp(struct tokenStackExp * s)
{
	if (0 == s->top){
		return;
	}
	return s->exp[s->top - 1];

}

int isEmptyExp(struct tokenStackExp * s)
{
	if (s->top == 0)
		return 1;
	else
		return 0;
}