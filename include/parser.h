#ifndef PARSER
#define PARSER

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<time.h>

// Cross-platform sleep and clear screen
#ifdef _WIN32
    #include<windows.h>
    #define SLEEP(ms) Sleep(ms)
    #define CLEAR_SCREEN() system("cls")
#else
    #include<unistd.h>
    #define SLEEP(ms) usleep((ms) * 1000)
    #define CLEAR_SCREEN() system("clear")
#endif

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
tokenQueue init(char* str);

#endif