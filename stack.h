#ifndef _STACK_H
#define _STACK_H
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include <ctype.h>

#define T_NUMBER 0
#define T_OPERATOR 1
#define T_BRACKET 2
#define T_VARIABLE 3
#define T_EQUALITY 4

typedef struct token
{
    int value;
    int type; // 0 - number , 1 - opertaion, 2 - brackets
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