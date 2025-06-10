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
    double (*evalfunc)(double, double);
}operator;

double evalplus(double a, double b);
double evalminus(double a, double b);
double evalmult(double a, double b);
double evalpow(double a, double b);
double evaldiv(double a, double b);
double evaleq(double a, double b);
double evalls(double a, double b);
double evalgr(double a, double b);
double evalleq(double a, double b);
double evalgeq(double a, double b);
double evalabs(double a, double b);
double evalmax(double a, double b);
double evalmin(double a, double b);
double evaland(double a, double b);
double evalor(double a, double b);





operator* getop(char c);

#endif