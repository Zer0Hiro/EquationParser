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

void calculatePoint(int i, int j, int k, char sym, int width, int height, float* zbuffer, char* buffer, RGB* colorbuffer, float A, float B, float C);
char map(float a);
RGB ColorMap(float a);
void renderObject(int width, int height, char *buffer, RGB *colorbuffer, char* PrevBuffer);

#endif