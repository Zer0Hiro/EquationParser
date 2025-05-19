#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#define T_NUMBER 0
#define T_OPERATOR 1
#define T_BRACKET 2

typedef struct Shape
{
    char Rule[100];
}Shape;

typedef struct token
{
    int value;
    int type; // 0 - number , 1 - opertaion, 2 - brackets
}token;
typedef struct point
{
    float x;
    float y;
}point;

float parseShape(Shape*, point*);
float atoi_Conversion(const char* strg);
void evaluate(float* Result, char operator);
void printScreen(char screen[][100], int length, int width);
void chooseChar(char* p, float dist);


int main()
{
    Shape s = {"x^2 + y <= 10"};
    char screen[100][100] = {0};

    int i, j;
    for(int i = 0; i < 100; i++)
    {
        for(int j = 0; j < 100; j++)
        {
           /* point p = {i-50,0.5*j-25};
            if(parseShape(&s, &p) > 0)
            {
                screen[i][j] = '@';
            }
            else screen[i][j] = ' ';
            //chooseChar(&screen[i][j], parseShape(&s, &p));*/
        }
    }
    printScreen(screen, 100, 100);
}

void chooseChar(char* p, float dist)
{
    int num = 0;
    char* map = "@$()!&*l>";
    if(2*dist > 1)
    {
        *p = ' ';
        return;
    }
    *p = map[abs((int)dist*20)];
}


void printScreen(char screen[][100], int length, int width)
{
    printf("\e[1;1H\e[2J");
    int i, j;
    for(i = 0; i < length; i++)
    {
        for(j = 0; j < width; j++)
        {
            printf("%c", screen[i][j]);
        }
        printf("\n");
    }
}







/*float parseShape(Shape *s, point *p)
{//takes ruleset from s and parses the symbols to get if point p is on the shape
    int i;
    char str[100];
    strcpy(str,s->Rule);
    char operator;
    float result[4] , size = 4;
    for(i = 0; i < strlen(s->Rule); i++)
    {
        switch(str[i])
        {
            case 'x':
                result[0] = p->x;
                break;
            case 'y':
                result[1] = p->y;
                break;
            case '^':
                if(str[i-1] == 'x')
                {
                    result[0] = (int)pow(result[0],atoi_Conversion(&str[i+1]));
                    i++;
                }
                if(str[i-1] == 'y')
                {
                    result[1] = (int)pow(result[1],atoi_Conversion(&str[i+1]));
                    i++;
                }
                break;
            case '+':
                operator = '+';
                break;
            case '=':
                evaluate(result, operator);
                return result[2] == atoi_Conversion(&str[i+2]);
            case '<':
                evaluate(result, operator);
                if(str[i+1] == '=')
                {
                    return result[2] <= atoi_Conversion(&str[i+3]);
                }
                return result[2] < atoi_Conversion(&str[i+2]);
            case '>':
                evaluate(result, operator);
                if(str[i+1] == '=')
                {
                    return result[2] >= atoi_Conversion(&str[i+3]);
                }  
                return result[2] < atoi_Conversion(&str[i+2]);
        }
    }

}

void evaluate(float* Result, char operator)
{
    switch(operator)
    {
        case '+':
            Result[2] = Result[0] + Result[1];
            break;
    }
}

float atoi_Conversion(const char* strg)
{

    // Initialize res to 0
    int res = 0;
    int i = 0;

    // Iterate through the string strg and compute res
    while (strg[i] != ' ' && strg[i] != '\0' ) {
        res = res * 10 + (strg[i] - '0');
        i++;
    }
    return res;
}*/