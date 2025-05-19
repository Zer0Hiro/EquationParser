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




void enqueue(tokenNode *PNode, token token)
{
    tokenNode temp = {token, PNode};
    PNode = &temp;
}

Tboolean dequeue(tokenNode *PNode, token* token)
{
    if(PNode == NULL) return NOT_OK;
    while(PNode->next != NULL) PNode = PNode->next;
    *token = PNode->token;
}