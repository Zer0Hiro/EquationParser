#include "stack.h"
#include "eval.h"

/*
defined operators:
+, *, /, ^, -(not unary), abs, max(M), min(m) - arithmetic operations
== , >, >=, <, <= : evaluation operators
&, | : logic operators
() : parentheses
*/
operator ops[] =
{  //sym, precedence, assoc, unary, evalfunc
    {'+',       2,      LEFT, 0, evalplus},
    {'*',       3,      LEFT, 0, evalmult},
    {'/',       3,      LEFT, 0, evaldiv},
    {'^',       4,      RIGHT, 0, evalpow},
    {'-',       2,      LEFT, 0, evalminus},
    {'a',       4,      RIGHT, 1, evalabs},
    {'M',       4,      RIGHT, 0, evalmax},//MAX
    {'m',       4,      RIGHT, 0, evalmin},//MIN
    {'<',       0,      LEFT, 0, evalls},
    {'>',       0,      LEFT, 0, evalgr},
    {'.',       0,      LEFT, 0, evalleq}, // less than equal
    {',',       0,      LEFT, 0, evalgeq}, // greater than equal
    {'=',       0,      LEFT, 0, evaleq},
    {'&',       -1,     LEFT, 0, evaland}, //LOGIC and
    {'|',       -1,     LEFT, 0, evalor}, //LOGIC or
    {'(',       0,      NONE, 0, NULL},
    {')',       0,      NONE, 0, NULL},
};


double evalplus(double a, double b)
{
    return a + b;
}
double evalminus(double a, double b)
{
    return a - b;
}
double evalmult(double a, double b)
{
    return a * b;
}
double evalpow(double a, double b)
{
    return pow(a , b);
}
double evaldiv(double a, double b)
{//TODO handle divbyzero
    return a/b;
}
double evaleq(double a, double b)
{
    return a == b;
}
double evalls(double a, double b)
{
    return a < b;
}
double evalgr(double a, double b)
{
    return a > b;
}
double evalleq(double a, double b)
{
    return a <= b;
}
double evalgeq(double a, double b)
{
    return a >= b;
}
double evalabs(double a, double b)
{
    return fabs(a);
}
double evalmax(double a, double b)
{
    return a > b ? a : b;
}
double evalmin(double a, double b)
{
    return a < b ? a : b;
}
double evaland(double a, double b)
{
    return a && b;
}
double evalor(double a, double b)
{
    return a || b;
}

//Gets char and returns pointer to operator with more info (Associativity direction, is unary, pointer to eval function)
operator* getop(char c)
{
    int i;
    for(i = 0; i < (sizeof(ops) / sizeof(operator)); i++)
    {
        if(ops[i].symbol == c)
        {
            return &(ops[i]);
        }
    }
    return NULL;
}
