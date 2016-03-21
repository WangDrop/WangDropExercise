#include "stdio.h"
#include "stdlib.h"
#include "stdarg.h"
#define MAXLINE 32
char buf[MAXLINE];

void itoa(int integer, char * s)
{
    int i = 0, j = 0;
    int intArray[32];
    do{
        intArray[i++]= integer % 10;
        integer /= 10;
    }while(integer != 0);
    for(; i > 0; --i){
        s[j++] = intArray[i - 1] + '0';
    }
    s[j] = '\0';
}

void MyPrint(char * fmt, ...);


int main()
{
    MyPrint("wawawaw, %s, %d, %f", "wangcheng", 111, 1.1);
    printf("\n");
    return 0;
}

void printChar(const char * s);
void printFloat(double f);
void printInt(int i);

void MyPrint(char * fmt, ...)
{
    va_list vp;
    char *vaChar;
    int vaInt;
    float vaFloat; 
    char * pfmt = NULL;

    va_start(vp, fmt);
    pfmt = fmt;
    while(*pfmt){
        if(*pfmt == '%'){
            switch(*++pfmt){
                case 's':
                    vaChar = va_arg(vp, char*);
                    printChar(vaChar);
                    break;
                case 'f':
                    vaFloat = va_arg(vp, double);
                    printFloat(vaFloat);
                    break;
                case 'd':
                    vaInt = va_arg(vp, int);
                    printInt(vaInt);
                    break;
                default:
                    break;
            }
            
        }else{
            write(fileno(stdout), pfmt, 1);
        }
        ++pfmt;
    }
    va_end(vp);
}

void printChar(const char * s)
{
    write(fileno(stdout), s, strlen(s));
}

void printFloat(double f)
{
    int fInt;
    fInt = (int)f;
    f = (f - fInt) * 1000000;
    
    printInt(fInt);
    write(fileno(stdout), ".", 1);
    printInt((int)f);
    return ;
}

void printInt(int i)
{
    itoa(i, buf);
    printChar(buf); 
    return ;
}
