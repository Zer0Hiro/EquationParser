#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<windows.h>
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
void convertToPolish(tokenQueue* queue, token* tokens, int size, point p);
int Precedence(token *t);

int main()
{
    char* str = "x^2 + y^2 >= 16";
    token* tokens;
    int size = parseRule(str, &tokens);
    printTokens(tokens, size);
    point p = {0,0};
    tokenNode polish = {{10,20},NULL};
    tokenQueue queue;
    initialize_queue(&queue);
    convertToPolish(&queue, tokens, size, p);
    printf("\n\n");
    print_queue(&queue);
    free_queue(&queue);
    Sleep(100000);
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

//Impelemts Shunting yard algo with reverse polish notation
void convertToPolish(tokenQueue* queue, token* tokens, int size, point p)
{//Takes coords of point p and evaluates using the tokens calculated, if true ret 1 else 0

    tokenStack opstack;
    initialize_stack(&opstack);
    token temp;
    int i;
    for(i = 0; i < size; i++)
    {
        switch(tokens[i].type)
        {
            case T_NUMBER:
                enqueue(queue, tokens[i]);
                printf("1");
                break;
            case T_VARIABLE:
                enqueue(queue, tokens[i]);
                printf("4");
                break;
            case T_OPERATOR: case T_EQUALITY:
                if(peek(&opstack, &temp) == NOT_OK)
                {
                    push(&opstack, tokens[i]);
                    printf("2");
                    break;
                }
                else
                {
                    while(peek(&opstack,&temp) == OK && Precedence(&temp) > Precedence(&(tokens[i])))
                    {
                        printf("3");
                        pop(&opstack,&temp);
                        enqueue(queue, temp);
                    }
                    push(&opstack,tokens[i]);
                }
            
        }
        
    }
    while(pop(&opstack, &temp) != NOT_OK)
    {
        printf("5");
        enqueue(queue, temp);
    }
}

int Precedence(token *t)
{
    switch(t->value)
    {
        case '>': case '=': case '<':
            return 0;
        case '+':
            return 2;
        case '-':
            return 2;
        case '*':
            return 3;
        case '^':
            return 4;
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
    temp = (token*)realloc(tokens, (index_t + 1)*sizeof(token));
    tokens = temp;
    return (index_t);
}