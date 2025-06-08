#include "parser.h"
#define WIDTH 100
#define HEIGHT 40

typedef struct rgb
{
    int r;
    int g;
    int b;
} RGB;

// Size of cube
const float cWidth = 40;

// EQUATION
char *str = "x^2 + y^2 <= z^2";

// Buffers for output points
char buffer[WIDTH * HEIGHT];
// Coordinates of projection z-buffering
float zbuffer[WIDTH * HEIGHT];
// Buffer for color
RGB colorbuffer[WIDTH * HEIGHT];

int background = ' ';
int xproj, yproj; // projection position
int cam = 110;    // distance from camera to object
float zdist = 40; // distance from camera to screen
int screenpos;    // position of a point on the screen
float ooz;        // z-buffer 1/z

float x, y, z; // Point coords
float A, B, C; // Angle

void calculatePoint(int i, int j, int k, int sym, char *color);
char map(float a);
RGB ColorMap(float ooz);

int main()
{
    float i, j, g;
    int k;
    int lastcolor, newcolor;
    int maxR = 0;

    system("cls");

    token *tokens;
    int size = parseRule(str, &tokens);
    tokenQueue queue;
    initialize_queue(&queue);
    convertToPolish(&queue, tokens, size);

    free(tokens);

    while (1)
    {
        memset(buffer, background, sizeof(buffer));
        memset(zbuffer, 0, sizeof(zbuffer));

        for (i = -cWidth / 2; i < cWidth / 2; i += 1)
        {
            for (j = -cWidth / 2; j < cWidth / 2; j += 1)
            {
                for (g = -cWidth / 2; g <= cWidth / 2; g += 1)
                {
                    point p = {i, j, g};
                    if (evalPolish(&queue, p))
                    {
                        calculatePoint(i, j, g, '@', "\033[33m"); // Z fixed
                    }
                    // calculatePoint(i, j, -g, '#', "\033[32m"); // -Z fixed
                    // calculatePoint(g, i, j, '%', "\033[33m");  // X fixed
                    // calculatePoint(-g, i, j, '&', "\033[0m");  // -X fixed
                    // calculatePoint(i, -g, j, 'O', "\033[34m");  // Y fixed
                    // calculatePoint(i, g, j, 'H', "\033[35m"); // -Y fixed
                }
            }
        }

        // Move cursor to home position
        printf("%c[%d;%df", 0x1B, 0, 0);

        // Coordinates of X Y Z (Debug)
        // printf("%0.2f %0.2f %0.2f\n", x, y, z);

        // Print all points
        for (k = 0; k < WIDTH * HEIGHT; k++)
        {
            // Color swap
            newcolor = (buffer[k] != ' ') ? 1 : 0;
            if (newcolor != lastcolor)
            {
                lastcolor = newcolor;
                printf("\033[38;2;%d;%d;%dm", colorbuffer[k].r, colorbuffer[k].g, colorbuffer[k].b);
            }

            // Print Char
            putchar(k % WIDTH ? buffer[k] : '\n');
        }

        if (C == 1)
            C = 0;
        if (B == 1)
            B = 0;
        if (A == 1)
            A = 0;
        C += 0.05; // X rotation (roll)
        B += 0.05; // Y rotation (pitch)
        A += 0.05; // Z rotation (yaw)

        Sleep(10);
    }
}

// Calculate position of the point
void calculatePoint(int i, int j, int k, int sym, char *color)
{

    // Sines and Cosines
    float sinA = sin(A), cosA = cos(A); // X-axis rotation
    float sinB = sin(B), cosB = cos(B); // Y-axis rotation
    float sinC = sin(C), cosC = cos(C); // Z-axis rotation

    // Rotate around Z
    float x1 = i;
    float y1 = j * cosA - k * sinA;
    float z1 = j * sinA + k * cosA;

    // Rotate around Y
    float x2 = x1 * cosB + z1 * sinB;
    float y2 = y1;
    float z2 = -x1 * sinB + z1 * cosB;

    // Rotate around X
    float x3 = x2 * cosC - y2 * sinC;
    float y3 = x2 * sinC + y2 * cosC;
    float z3 = z2;

    x = x3;
    y = y3;
    z = z3 + cam;
    ooz = 1 / z;

    xproj = (int)(WIDTH / 2 + x * zdist * ooz * 2);
    yproj = (int)(HEIGHT / 2 + y * zdist * ooz);
    screenpos = xproj + yproj * WIDTH;

    if (screenpos >= 0 && screenpos < WIDTH * HEIGHT)
    {
        if (ooz > zbuffer[screenpos])
        {
            zbuffer[screenpos] = ooz;
            buffer[screenpos] = map(ooz);
            colorbuffer[screenpos] = ColorMap(ooz);
        }
    }
}

char map(float a)
{
    return (char)(a * 1000 + 66);
}

RGB ColorMap(float a)
{

    float shade = a * 1000;
    int r, g = 0, b = 0;

    // Color swap
    r = (int)shade * 10;
    if (r > 255)
        r = 255;
    else if (r < 0)
        r = 0;

    return (RGB){r, g, b};
}