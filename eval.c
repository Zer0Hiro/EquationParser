#include "stack.h"
#include "eval.h"

operator ops[] =
{  //sym, pre, assoc, unary, evalfunc
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
    {'(', 0, NONE, 0, NULL},
    {')', 0, NONE, 0, NULL},
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
    return (double)pow(a , b);
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
double evalleq(double a, double b)
{
    return a <= b;
}
double evalabs(double a, double b)
{
    return fabs(a);
}
double evalmax(double a, double b)
{
    return a > b ? a : b;
}

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
