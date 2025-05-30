#ifndef _STACK_H
#define _STACK_H
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include <ctype.h>
#include "eval.h"




typedef enum {
    T_NUMBER,
    T_OPERATOR,
    T_VARIABLE,
} T_TYPE;

typedef struct token
{
    T_TYPE type;
    union value
    {
        double num;
        operator* op;
        char var;
    }value;

}token;

typedef struct tokenNode
{
    token _token;
    struct tokenNode* next;
}tokenNode;

typedef enum {NOT_OK, OK} Tboolean;

typedef struct 
{   
    tokenNode *tokenTop;
    int top;
}tokenStack;

typedef struct tokenQueue
{
    tokenNode *head, *tail;
    int size;
}tokenQueue;


void initialize_queue(tokenQueue*);
void enqueue(tokenQueue*,token token);
Tboolean dequeue(tokenQueue* queue,token *token);
void print_queue(tokenQueue* queue);
void free_queue(tokenQueue* queue);
int convert_to_array(token* tokens,tokenQueue* queue);

void initialize_stack (tokenStack *Pstack);
void push (tokenStack *Pstack, token item);
Tboolean pop (tokenStack *Pstack, token *Pitem);
Tboolean peek(tokenStack *PStack, token* token);
void free_stack (tokenStack *Pstack);


#endif