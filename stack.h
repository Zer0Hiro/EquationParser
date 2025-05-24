
#ifndef _STACK_H
#define _STACK_H
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include <ctype.h>
#define MAXSTACK 10

typedef struct token
{
    int value;
    int type; // 0 - number , 1 - opertaion, 2 - brackets
}token;

typedef enum {NOT_OK, OK} Tboolean;

typedef struct 
{
    token array[MAXSTACK];
    int top;
}tokenStack;

typedef struct tokenNode
{
    token token;
    struct tokenNode* next;
}tokenNode;

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

void initialize_stack (tokenStack *Pstack);
Tboolean push (tokenStack *Pstack, token item);
Tboolean pop (tokenStack *Pstack, token *Pitem);
Tboolean peek(tokenStack *PStack, token* token);
void free_stack (tokenStack *Pstack, void(*FrElm)(token));


#endif