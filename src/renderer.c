#include "renderer.h"
#define N 

// Calculate position of the point
void calculatePoint(int i, int j, int k, int width, int height, float *zbuffer, char *buffer, RGB *colorbuffer, Angles* angle)
{
    float x, y, z;    // Point coords
    int xproj, yproj; // projection position
    int cam = 70;    // distance from camera to object
    float zdist = 40; // distance from camera to screen
    int screenpos;    // position of a point on the screen
    float ooz;        // z-buffer 1/z

    // // Sines and Cosines
    // float sinA = sin(A), cosA = cos(A); // X-axis rotation
    // float sinB = sin(B), cosB = cos(B); // Y-axis rotation
    // float sinC = sin(C), cosC = cos(C); // Z-axis rotation

    // Rotate around Z
    float x1 = i;
    float y1 = j * angle->cosA - k * angle->sinA;
    float z1 = j * angle->sinA + k * angle->cosA;

    // Rotate around Y
    float x2 = x1 * angle->cosB + z1 * angle->sinB;
    float y2 = y1;
    float z2 = -x1 * angle->sinB + z1 * angle->cosB;

    // Rotate around X
    float x3 = x2 * angle->cosC - y2 * angle->sinC;
    float y3 = x2 * angle->sinC + y2 * angle->cosC;
    float z3 = z2;

    x = x3;
    y = y3;
    z = z3 + cam;
    ooz = 1 / z;

    xproj = (int)(width / 2 + x * zdist * ooz * 2);
    yproj = (int)(height / 2 + y * zdist * ooz);
    screenpos = xproj + yproj * width;

    if (screenpos >= 0 && screenpos < width * height)
    {
        if (ooz > zbuffer[screenpos])
        {
            zbuffer[screenpos] = ooz;
            buffer[screenpos] = map(ooz);
            colorbuffer[screenpos] = ColorMap(ooz);
        }
    }
}

// Will change symbols depending on distance
char map(float a)
{
    return (char)(a * 1000 + 66);
}

// Will shade colors on object
RGB ColorMap(float a)
{

    float shade = a * 10000;
    int r = 0, g = 0, b = 0, mod;

    mod = (int)shade %10;
    // Color swap
    r = ((int)shade + mod*10);
    g = b = r;
    if (r > 255)
    {
        r = 255;
        g = 255;
        b = 255;
    }
    else if (r < 0)
    {
       r = 0;
       g = 0;
       b = 0;
    }

    return (RGB){r, g, b};
}

// Will print one frame of object
void renderObject(int width, int height, char *buffer, RGB *colorbuffer, char* PrevBuffer)
{
    int k;
    int lastcolor, newcolor;
    int row;
    int col;

    for (k = 0; k < width * height; k++)
    {
        if (buffer[k] != PrevBuffer[k])
        {
            // Save symbols
            PrevBuffer[k] = buffer[k];

            // Position check for jump
            row = k / width;
            col = k % width;
            // Jump to specific point on the screen
            printf("\033[%d;%dH", row + 1, col + 1);

            // Color swap
            newcolor = (buffer[k] != ' ') ? 1 : 0;
            if (newcolor != lastcolor)
            {
                lastcolor = newcolor;
                printf("\033[38;2;%d;%d;%dm", colorbuffer[k].r, colorbuffer[k].g, colorbuffer[k].b);
            }

            // Print Char
            putchar(buffer[k]);
        }
    }
    fflush(stdout);
}
