#ifndef _EVAL
#define _EVAL
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<math.h>
#include <ctype.h>
#include "stack.h"


typedef enum {LEFT, RIGHT, NONE} ASSOC;


typedef struct op
{
    char symbol;
    char precedence;
    ASSOC assoc;
    char isUnary;
    float (*evalfunc)(float, float);
}operator;

int evalplus(int a, int b);
int evalminus(int a, int b);
int evalmult(int a, int b);
int evalpow(int a, int b);
int evaldiv(int a, int b);
int evaleq(int a, int b);
int evalls(int a, int b);
int evalleq(int a, int b);
int evalabs(int a, int b);
int evalmax(int a, int b);


/*operator ops[] =
{  //sym, pre, assoc, unary, evanfunc
    {'+', 2, LEFT, 0, evalplus},
    {'*', 3, LEFT, 0, evalmult},
    {'\\', 3, LEFT, 0, evaldiv},
    {'^', 4, RIGHT, 0, evalpow},
    {'-', 2, LEFT, 0, evalminus},
    {'a', 1, RIGHT, 1, evalabs},
    {'M', 1, RIGHT, 0, evalmax},
    {'>', 0, LEFT, 0, evalls},
    {'=', 0, LEFT, 0, evaleq},
    {'.', 0, LEFT, 0, evalleq}, // less than equal
};*/


int operate(int a, int b, char c);

#endif