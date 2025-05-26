#include "stack.h"

void initialize_stack (tokenStack *Pstack)
{
    Pstack->tokenTop = NULL;
    Pstack->top = -1;
}

void push (tokenStack *Pstack, token item)
{
    tokenNode *node = (tokenNode*)malloc(sizeof(tokenNode));
    node->next = Pstack->tokenTop;
    node->_token = item;
    (Pstack->top)++;
    Pstack->tokenTop = node;
}

Tboolean pop (tokenStack *Pstack, token *Pitem)
{
    if(Pstack->top == -1) return NOT_OK;
    else
    {
        tokenNode *temp = Pstack->tokenTop;
        *Pitem = Pstack->tokenTop->_token;
        Pstack->tokenTop = Pstack->tokenTop->next;
        free(temp);
        (Pstack->top)--;
        return OK;
    }
}

Tboolean peek(tokenStack *PStack, token* token)
{
    if(PStack->top == -1) return NOT_OK;
    else
    {
        *token = PStack->tokenTop->_token;
        return OK;
    }
}


void free_stack (tokenStack *Pstack)
{
    while(Pstack->top != -1)
    {
        tokenNode *temp = Pstack->tokenTop;
        Pstack->tokenTop = Pstack->tokenTop->next;
        free(temp);
        (Pstack->top)--;
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
        temp->_token = token;
        queue->tail = queue->head = temp;
        queue->size++;
    }
    else
    {
        tokenNode* temp = (tokenNode*)malloc(sizeof(tokenNode));
        temp->next = NULL;
        temp->_token = token;
        queue->tail->next = temp;
        queue->tail = temp;
        queue->size++;
    }
    
}

Tboolean dequeue(tokenQueue* queue,token *token)
{  
    if(queue->head == NULL) return NOT_OK;
    *token = queue->head->_token;
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
        switch(temp->_token.type)
        {
            case T_NUMBER:
                printf("Type: 1, Value: %d\n" , temp->_token.value);
                break;
            case T_EQUALITY: case T_OPERATOR: case T_VARIABLE:
                printf("Type: %d, Value: %c\n" , temp->_token.type, temp->_token.value);
                break;

        }
        temp = temp->next;
        size--;
    }
}

int convert_to_array(token* tokens,tokenQueue* queue)
{
    tokens = (token*)malloc(sizeof(token) * (queue->size));
    tokenNode* temp = queue->head;
    int size = queue->size, i;
    for(i = 0; i < size; i++)
    {
        tokens[i] = temp->_token;
        temp = temp->next;
    }
    return size;
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