#ifndef PARSER
#define PARSER

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<windows.h>
#include<time.h>
#include "stack.h"
#include "eval.h"

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

#endif