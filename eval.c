#include "stack.h"
#include "eval.h"


int evalplus(int a, int b)
{
    return a + b;
}
int evalminus(int a, int b)
{
    return a - b;
}
int evalmult(int a, int b)
{
    return a * b;
}
int evalpow(int a, int b)
{
    return (double)pow(a , b);
}
int evaldiv(int a, int b)
{//TODO handle divbyzero
    return a/b;
}
int evaleq(int a, int b)
{
    return a == b;
}
int evalls(int a, int b)
{
    return a < b;
}
int evalleq(int a, int b)
{
    return a <= b;
}
int evalabs(int a, int b)
{
    return fabs(a);
}
int evalmax(int a, int b)
{
    return a > b ? a : b;
}

int operate(int a, int b, char c)
{
    switch(c)
    {
        case '+':
            return evalplus(a,b);
        case '*':
            return evalmult(a,b);
        case '\\':
            return evaldiv(a,b);
        case '-':
            return evalminus(a,b);
        case '^':
            return evalpow(a,b);
        case '=':
            return evaleq(a,b);
        case '<':
            return evalls(a,b);
        case 'a':
            return evalabs(a,0);
        case 'M':
            return evalmax(a,b);
        case '.':
            return evalleq(a,b);
    }
}
