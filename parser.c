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
    float x;
    float y;
    float z;
}point;

void printScreen(char screen[][100], int length, int width);
void chooseChar(char* p, float dist);
int parseRule(char* rule, token** tokens);
void printTokens(token* tokens, int size);
void convertToPolish(tokenQueue* queue, token* tokens, int size);
int Precedence(token *t);
int evalPolish(tokenQueue* queue, point p);

int main()
{
    char* str = " x^2 + y^2 + z^2 <= 10";
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
    point p = {1 , -2 , 0};
    int res = evalPolish(&queue, p);
    printf("%d", res);
    
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
                printf("Type: 1, Value: %d\n" , tokens[i].value);
                break;
            case T_EQUALITY: case T_OPERATOR: case T_VARIABLE: case T_BRACKET:
                printf("Type: %d, Value: %c\n" , tokens[i].type, tokens[i].value);
                break;

        }
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
            case T_NUMBER:
                enqueue(queue, tokens[i]);
                break;
            case T_VARIABLE:
                enqueue(queue, tokens[i]);
                break;
            case T_OPERATOR: case T_EQUALITY:
                if(peek(&opstack, &temp) == NOT_OK && temp.value != '(')
                {
                    push(&opstack, tokens[i]);
                    break;
                }
                else
                {
                    while(peek(&opstack,&temp) == OK && Precedence(&temp) > Precedence(&(tokens[i])) && temp.value != '(')
                    {
                        pop(&opstack,&temp);
                        enqueue(queue, temp);
                    }
                    push(&opstack,tokens[i]);
                    break;
                }
            case T_BRACKET:
                if(tokens[i].value == '(')
                {
                    push(&opstack,tokens[i]);
                    break;
                }
                if(tokens[i].value == ')')
                {
                    while(peek(&opstack,&temp) == OK && temp.value != '(')
                    {
                        pop(&opstack,&temp);
                        enqueue(queue,temp);
                    }
                    pop(&opstack,&temp);//Throw "Open bracket" token
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

int Precedence(token *t)
{
    switch(t->value)
    {
        case '>': case '=': case '<': case '.':
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
    int index_t = 0;
    while(*rule != '\0')
    {
        while(*rule == ' ' || *rule == ',') rule++;
        if(isdigit(*rule))
        {
            tokens[index_t].type = T_NUMBER;
            tokens[index_t].value = 0;
            do
            {
                tokens[index_t].value = tokens[index_t].value * 10 + (*rule - '0');
                rule++;
            } while (isdigit(*rule));
        }
        else if(strchr("+\\-*^",*rule) != NULL)
        {
            tokens[index_t].type = T_OPERATOR;
            tokens[index_t].value = *rule;
            rule++;
        }
        else if(strchr("()",*rule) != NULL)
        {
            tokens[index_t].type = T_BRACKET;
            tokens[index_t].value = *rule;
            rule++;
        }
        else if(strchr("xyz",*rule) != NULL)
        {
            tokens[index_t].type = T_VARIABLE;
            tokens[index_t].value = *rule;
            rule++;
        }
        else if(strchr("=",*rule) != NULL)
        {
            tokens[index_t].type = T_EQUALITY;
            tokens[index_t].value = *rule;
            rule++;
        }
        else if(strchr("><",*rule) != NULL)
        {
            if(*rule + 1 == '=')
            {
                tokens[index_t].type = T_EQUALITY;
                tokens[index_t].value = '.';
                rule += 2;
            }
            else
            {
                tokens[index_t].type = T_EQUALITY;
                tokens[index_t].value = *rule;
                rule++;
            }
            
        }
        else if(strstr(rule, "max") == &(*rule))
        {
            tokens[index_t].type = T_OPERATOR;
            tokens[index_t].value = 'M';
            rule = rule + 3;
        }
        else if(strstr(rule, "abs") == &(*rule))
        {
            tokens[index_t].type = T_OPERATOR;
            tokens[index_t].value = 'a';
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

int evalPolish(tokenQueue* queue, point p)
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
                switch(head->_token.value)
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
            case(T_OPERATOR): case(T_EQUALITY):
                token L,R,result;
                if(head->_token.value != 'a')//NOT UNARY
                {
                    pop(&numstack, &L);
                    pop(&numstack, &R);
                    result.value = operate(R.value , L.value, (char)head->_token.value);
                    result.type = T_NUMBER;
                    push(&numstack,result);
                }
                else //YES UNARY
                {
                    pop(&numstack, &L);
                    result.value = operate(L.value , 0, (char)head->_token.value);
                    result.type = T_NUMBER;
                    push(&numstack,result);
                }
                break;
                
                
        }
        head = head->next;
    }
    return numstack.tokenTop->_token.value;

}