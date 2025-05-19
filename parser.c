#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include "stack.h"

#define T_NUMBER 0
#define T_OPERATOR 1
#define T_BRACKET 2
#define T_VARIABLE 3
#define T_EQUALITY 4

/*typedef struct token
{
    int value;
    int type; // 0 - number , 1 - opertaion, 2 - brackets
}token;*/ //Defined in stack.h

typedef struct point
{
    float x;
    float y;
    float z;
}point;

void printScreen(char screen[][100], int length, int width);
void chooseChar(char* p, float dist);
int parseRule(char* rule, token** tokens);
void printTokens(token* tokens, int size);

int main()
{
    char* str = "x^2 + y^2 >= 16";
    token* tokens;
    int size = parseRule(str, &tokens);
    printTokens(tokens, size);
}

void printTokens(token* tokens, int size)
{
    int i = 0;
    for(; i< size; i++)
    {
        printf("Type: %d , val: %d\n", tokens[i].type, tokens[i].value);
    }
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

int convertToPolish(token* tokens, int size, point p)
{//Takes coords of point p and evaluates using the tokens calculated, if true ret 1 else 0
    //Impelemts Shunting yard algo with reverse polish notation
    tokenStack opstack;
    initialize_stack(&opstack);
    tokenNode queue;
    token temp;
    int i;
    for(i = 0; i < size; i++)
    {
        switch(tokens[i].type)
        {
            case T_NUMBER:
                enqueue(&queue, tokens[i]);
                break;
            case T_OPERATOR:
                if(peek(&opstack, &temp) == NOT_OK)
                {
                    push(&opstack, tokens[i]);
                    break;
                }
                else
                {
                    
                }
            
        }
        
    }
    
}

int parseRule(char* rule, token** res)
{//Takes equation in str and tokenizes to numbers, operators, brackets, order signs, variables
    token* tokens = (token*)malloc(sizeof(token));
    token* temp;
    int i = 0, index_t = 0;
    while(rule[i] != '\0')
    {
        while(rule[i] == ' ') i++;
        if(isdigit(rule[i]))
        {
            tokens[index_t].type = T_NUMBER;
            tokens[index_t].value = 0;
            do
            {
                tokens[index_t].value = tokens[index_t].value * 10 + (rule[i] - '0');
                i++;
            } while (isdigit(rule[i]));
        }
        else if(strchr("+\\-*^",rule[i]) != NULL)
        {
            tokens[index_t].type = T_OPERATOR;
            tokens[index_t].value = rule[i];
            i++;
        }
        else if(strchr("()",rule[i]) != NULL)
        {
            tokens[index_t].type = T_BRACKET;
            tokens[index_t].value = rule[i];
            i++;
        }
        else if(strchr("xyz",rule[i]) != NULL)
        {
            tokens[index_t].type = T_VARIABLE;
            tokens[index_t].value = rule[i];
            i++;
        }
        else if(strchr("=><",rule[i]) != NULL)
        {
            tokens[index_t].type = T_EQUALITY;
            tokens[index_t].value = rule[i];
            i++;
        }
        temp = (token*)realloc(tokens, (index_t + 2)*sizeof(token));
        tokens = temp;
        index_t++;
    }
    *res = tokens;
    return (index_t + 1);
}