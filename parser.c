#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<windows.h>
#include "stack.h"
#include "eval.h"

/*typedef struct token
{
    int value;
    int type; // 0 - number , 1 - opertaion, 2 - brackets
}token;*/ //Defined in stack.h

typedef struct point
{
    double x;
    double y;
    double z;
}point;

void printScreen(char screen[][100], int length, int width);
void chooseChar(char* p, float dist);
int parseRule(char* rule, token** tokens);
void printTokens(token* tokens, int size);
void convertToPolish(tokenQueue* queue, token* tokens, int size);
double evalPolish(tokenQueue* queue, point p);

int main()
{
    char* str = " x^2 + y^2 + z^2";
    token* tokens;
    int size = parseRule(str, &tokens);
    printTokens(tokens, size);
    tokenQueue queue;
    initialize_queue(&queue);
    convertToPolish(&queue, tokens, size);
    printf("\n\n");
    print_queue(&queue);

    printf("\n\n");
    free(tokens);
    point p = {1.3 , -2.4 , 0};//TODO BUG
    int res = evalPolish(&queue, p);
    printf("%g", res);
    
    Sleep(100000);
    return 0;
}

void printTokens(token* tokens, int size)
{
    int i = 0;
    for(; i< size; i++)
    {
        switch(tokens[i].type)
        {
            case T_NUMBER:
                printf("Type: 1, Value: %g\n" , tokens[i].value.num);
                break;
            case T_OPERATOR:
                printf("Type: %d, Value: %c\n" , tokens[i].type, tokens[i].value.op->symbol);
                break;
            case T_VARIABLE:
                printf("Type: %d, Value: %c\n" , tokens[i].type, tokens[i].value.var);
                break;
        }
    }
}

/*void chooseChar(char* p, float dist)
{
    int num = 0;
    char* map = "@$()!&*l>";
    if(2*dist > 1)
    {
        *p = ' ';
        return;
    }
    *p = map[abs((int)dist*20)];
}*/

/*void printScreen(char screen[][100], int length, int width)
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
}*/

//Impelemts Shunting yard algo with reverse polish notation
void convertToPolish(tokenQueue* queue, token* tokens, int size)
{

    tokenStack opstack;
    initialize_stack(&opstack);
    token temp;
    int i;
    for(i = 0; i < size; i++)
    {
        switch(tokens[i].type)
        {
            case T_NUMBER: case T_VARIABLE:
                enqueue(queue, tokens[i]);
                break;
            case T_OPERATOR:
                if(tokens[i].value.op->symbol == '(')
                {
                    push(&opstack,tokens[i]);
                    break;
                }
                if(tokens[i].value.op->symbol == ')')
                {
                    while(peek(&opstack,&temp) == OK && temp.value.op->symbol != '(')
                    {
                        pop(&opstack,&temp);
                        enqueue(queue,temp);
                    }
                    pop(&opstack,&temp);//Throw "Open bracket" token
                    break;
                }
                else if(peek(&opstack, &temp) == NOT_OK)
                {
                    push(&opstack, tokens[i]);
                    break;
                }
                else
                {
                    while(peek(&opstack,&temp) == OK && temp.value.op->precedence > tokens[i].value.op->precedence && temp.value.op->symbol != '(')
                    {
                        pop(&opstack,&temp);
                        enqueue(queue, temp);
                    }
                    push(&opstack,tokens[i]);
                    break;
                } 
        }
        
    }
    while(pop(&opstack, &temp) != NOT_OK)
    {
        enqueue(queue, temp);
    }
    free_stack(&opstack);
}


int parseRule(char* rule, token** res)
{//Takes equation in str and tokenizes to numbers, operators, brackets, order signs, variables
    token* tokens = (token*)malloc(sizeof(token));
    token* temp;
    int index_t = 0;
    while(*rule != '\0')
    {
        while(*rule == ' ' || *rule == ',') rule++;
        if(isdigit(*rule))
        {//TODO PARSE DECIMALS instead
            tokens[index_t].type = T_NUMBER;
            tokens[index_t].value.num = 0;
            do
            {
                tokens[index_t].value.num = tokens[index_t].value.num * 10 + (*rule - '0');
                rule++;
            } while (isdigit(*rule));
        }
        else if(strchr("+\\-*^()=",*rule) != NULL)
        {
            tokens[index_t].type = T_OPERATOR;
            tokens[index_t].value.op = getop(*rule);
            rule++;
        }
        else if(strchr("xyz",*rule) != NULL)
        {
            tokens[index_t].type = T_VARIABLE;
            tokens[index_t].value.var = *rule;
            rule++;
        }
        else if(strchr("><",*rule) != NULL)
        {
            if(*rule + 1 == '=')
            {
                tokens[index_t].type = T_OPERATOR;
                tokens[index_t].value.op = getop('.');
                rule += 2;
            }
            else
            {
                tokens[index_t].type = T_OPERATOR;
                tokens[index_t].value.op = getop(*rule);
                rule++;
            }
            
        }
        else if(strstr(rule, "max") == &(*rule))
        {//TODO THINK OF SOMETHING BETTER
            tokens[index_t].type = T_OPERATOR;
            tokens[index_t].value.op = getop('M');
            rule = rule + 3;
        }
        else if(strstr(rule, "abs") == &(*rule))
        {
            tokens[index_t].type = T_OPERATOR;
            tokens[index_t].value.op = getop('a');
            rule = rule + 3;
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

double evalPolish(tokenQueue* queue, point p)
{
    tokenStack numstack;
    initialize_stack(&numstack);
    tokenNode *head = queue->head, *tail = queue->tail;
    int size = queue->size;
    while(head != NULL)
    {
        switch(head->_token.type)
        {
            case(T_NUMBER):
                push(&numstack, head->_token);
                break;
            case(T_VARIABLE):
                switch(head->_token.value.var)
                {
                    case 'x':
                        token x = {(int)p.x , T_NUMBER};
                        push(&numstack, x);
                        break;
                    case 'y':
                        token y = {(int)p.y , T_NUMBER};
                        push(&numstack, y);
                        break;
                    case 'z':
                        token z = {(int)p.z , T_NUMBER};
                        push(&numstack, z);
                        break;    
                }
                break;
            case(T_OPERATOR):
                token L,R,result;
                if(!(head->_token.value.op->isUnary))//NOT UNARY
                {
                    pop(&numstack, &L);
                    pop(&numstack, &R);
                    result.value.num = head->_token.value.op->evalfunc(L.value.num, R.value.num);
                    result.type = T_NUMBER;
                    push(&numstack,result);
                }
                else //YES UNARY
                {
                    pop(&numstack, &L);
                    result.value.num = head->_token.value.op->evalfunc(L.value.num, 0);
                    result.type = T_NUMBER;
                    push(&numstack,result);
                }
                break;
                
                
        }
        head = head->next;
    }
    return numstack.tokenTop->_token.value.num;

}