#include "parser.h"

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
                // IF operator stack is empty, just push the operator OR IF token is '(', just push it
                if(peek(&opstack, &temp) == NOT_OK || tokens[i].value.op->symbol == '(')
                {
                    push(&opstack, tokens[i]);
                }
                // IF token is ')', pop all operators to the output queue and throw the '('
                //
                else if(tokens[i].value.op->symbol == ')')
                {
                    while(peek(&opstack,&temp) == OK && temp.value.op->symbol != '(')
                    {
                        pop(&opstack,&temp);
                        enqueue(queue,temp);
                    }
                    pop(&opstack,&temp);//Throw "Open bracket" token
                    //IF first operator after brackets is unary, push it to the queue
                    if(peek(&opstack, &temp) == OK && temp.value.op->isUnary)
                    {
                        pop(&opstack,&temp);
                        enqueue(queue,temp);
                    }
                }
                // for all other operators w\o any special case
                else
                {
                    // WHILE the next operator is of lower precedence, pop all non '(' operators to output queue
                    while(peek(&opstack,&temp) == OK && temp.value.op->precedence > tokens[i].value.op->precedence && temp.value.op->symbol != '(')
                    {
                        pop(&opstack,&temp);
                        enqueue(queue, temp);
                    }
                    push(&opstack,tokens[i]);
                } 
                break;
        }
        
    }
    // after going through the whole token array; just pop all operators to the output queue
    while(pop(&opstack, &temp) != NOT_OK)
    {
        enqueue(queue, temp);
    }
    free_stack(&opstack);
}

//Takes equation in str and tokenizes to numbers, operators, brackets, order signs, variables
int parseRule(char* rule, token** res)
{
    token* tokens = (token*)malloc(sizeof(token)), *temp;
    int index_t = 0, index_num = 0;
    char temp_num[30];

    while(*rule != '\0')
    {
        temp = (token*)realloc(tokens, (index_t + 1)*sizeof(token));
        if(temp == NULL)
        {
            free(tokens);
            printf("ERROR allocating memory");
            exit(1);
        }
        tokens = temp;
        while(*rule == ' ' || *rule == ',') rule++; //Ignores whitespace and commas

        //If the char is a digit- must be part of a num so evaluates the decimal number
        if(isdigit(*rule))
        {
            char* start_num = rule; //save start of num
            do
            {
                index_num++;
                rule++;
            } while(isdigit(*rule) || *rule == '.'); //continue going through the string while chars represent a number
            strncpy(temp_num, start_num, index_num); // copies only part of the string: the number
            temp_num[index_num] = '\0'; // Null terminate the end
            index_num = 0; //Reset for next num
            tokens[index_t].type = T_NUMBER;
            tokens[index_t].value.num = atof(temp_num);
        }
        //if the char is a single-char operator
        else if(strchr("+/-*^()=&|",*rule) != NULL)
        {
            tokens[index_t].type = T_OPERATOR;
            tokens[index_t].value.op = getop(*rule);
            rule++;
        }
        //if the char is a variable
        else if(strchr("xyz",*rule) != NULL)
        {
            tokens[index_t].type = T_VARIABLE;
            tokens[index_t].value.var = *rule;
            rule++;
        }
        //if the char is < , >
        else if(strchr("><",*rule) != NULL)
        {
            if(*rule + 1 == '=')
            {//if the operator is <= or >=
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
        //if the char is a multi-char operator (CURRENTLY ONLY: abs, max, min)
        else if(strstr(rule, "max") == &(*rule))
        {//TODO THINK OF SOMETHING BETTER
            tokens[index_t].type = T_OPERATOR;
            tokens[index_t].value.op = getop('M');
            rule = rule + 3;
        }
        else if(strstr(rule, "min") == &(*rule))
        {
            tokens[index_t].type = T_OPERATOR;
            tokens[index_t].value.op = getop('m');
            rule = rule + 3;
        }
        else if(strstr(rule, "abs") == &(*rule))
        {
            tokens[index_t].type = T_OPERATOR;
            tokens[index_t].value.op = getop('a');
            rule = rule + 3;
        }
        else
        {//Edge case
            printf("illegal char %c" , *rule);
            exit(1);
        }
        index_t++;
    }
    *res = tokens;
    return index_t;
}

//Takes Reverse polish equation and point p and evaluates the equation with respect to p's coords
double evalPolish(tokenQueue* queue, point p)
{//Does not overwrite tokenQueue* queue; so can be reused
    tokenStack numstack;
    initialize_stack(&numstack);
    tokenNode *head = queue->head;
    int size = queue->size ,res;
    while(head != NULL)
    {
        switch(head->_token.type)
        {
            //If the token is just a number; push it to the numstack
            case(T_NUMBER):
                push(&numstack, head->_token);
                break;
            //If the token is a variable; convert it to num and push it to the numstack
            case(T_VARIABLE):
                switch(head->_token.value.var)
                {
                    case 'x':
                        token x;
                        x.value.num = p.x;
                        x.type = T_NUMBER;
                        push(&numstack, x);
                        break;
                    case 'y':
                        token y;
                        y.value.num = p.y;
                        y.type = T_NUMBER;
                        push(&numstack, y);
                        break;
                    case 'z':
                        token z;
                        z.value.num = p.z;
                        z.type = T_NUMBER;
                        push(&numstack, z);
                        break;    
                }
                break;
            case(T_OPERATOR):
                token L,R,result;
                if(!(head->_token.value.op->isUnary))//NOT UNARY
                {
                    pop(&numstack, &R);
                    pop(&numstack, &L);
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
    res = numstack.tokenTop->_token.value.num;
    free_stack(&numstack);
    return res;

}

// Initialize parser
tokenQueue init(char* str)
{
    token *tokens;
    int size = parseRule(str, &tokens);
    tokenQueue queue;
    initialize_queue(&queue);
    convertToPolish(&queue, tokens, size);

    free(tokens);
    return queue;
}
