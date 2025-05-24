#include "stack.h"

void initialize_stack (tokenStack *Pstack)
{
    Pstack->top = -1;
}

Tboolean push (tokenStack *Pstack, token item)
{
    if(Pstack->top >= MAXSTACK - 1)
    {
        return NOT_OK;
    }
    else
    {
        (Pstack->top)++;
        Pstack->array[Pstack->top] = item;
        return OK;
    }
}
Tboolean pop (tokenStack *Pstack, token *Pitem)
{
    if(Pstack->top == -1) return NOT_OK;
    else
    {
        *Pitem = Pstack->array[Pstack->top];
        (Pstack->top)--;
        return OK;
    }
}
Tboolean peek(tokenStack *PStack, token* token)
{
    if(PStack->top == -1) return NOT_OK;
    else
    {
        *token = PStack->array[PStack->top];
        return OK;
    }
}

void initialize_queue(tokenQueue* queue)
{
    queue->head = queue->tail = NULL;
    queue->size = 0;
}

void enqueue(tokenQueue* queue,token token)
{
    if(queue->head == NULL)
    {
        tokenNode* temp = (tokenNode*)malloc(sizeof(tokenNode));
        temp->next = NULL;
        temp->token = token;
        queue->tail = queue->head = temp;
        queue->size++;
    }
    else
    {
        tokenNode* temp = (tokenNode*)malloc(sizeof(tokenNode));
        temp->next = NULL;
        temp->token = token;
        queue->tail->next = temp;
        queue->tail = temp;
        queue->size++;
    }
    
}

Tboolean dequeue(tokenQueue* queue,token *token)
{  
    if(queue->head == NULL) return NOT_OK;
    *token = queue->head->token;
    queue->head = queue->head->next;
    queue->size--;
    return OK;
}

void print_queue(tokenQueue* queue)
{
    tokenNode* temp = queue->head;
    int size = queue->size;
    while(size > 0)
    {
        printf("Type: %d, Value: %d\n" , temp->token.type, temp->token.value);
        temp = temp->next;
        size--;
    }
}


void free_queue(tokenQueue* queue)
{
    tokenNode* temp;
    while(queue->head != NULL)
    {
        temp = queue->head;
        queue->head = queue->head->next;
        free(temp);
    }
}