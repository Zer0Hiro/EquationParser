#ifndef RENDER
#define RENDER

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

typedef struct rgb
{
    int r;
    int g;
    int b;
} RGB;

typedef struct angles
{
    float sinA, sinB, sinC;
    float cosA, cosB, cosC;
} Angles;

void calculatePoint(int i, int j, int k, int width, int height, float *zbuffer, char *buffer, RGB *colorbuffer, Angles* angle);
char map(float a);
RGB ColorMap(float a);
void renderObject(int width, int height, char *buffer, RGB *colorbuffer, char *PrevBuffer);

#endif