#include "parser.h"
#include "renderer.h"

#define WIDTH 140
#define HEIGHT 45
#define SIZE (WIDTH * HEIGHT)

// Size of object
const float cWidth = 40;

// EQUATION
char* str = "x^4 - 5*x^2 + y^4 - 5*y^2 + z^4 - 5*z^2 + 11.8 < 0";

// Buffers for output points
char buffer[SIZE];
// Coordinates of projection z-buffering
float zbuffer[SIZE];
// Buffer for color
RGB colorbuffer[SIZE];
// Prev buffer
char PrevBuffer[SIZE];

float A, B, C;  // Angles
int background = ' ';
float deltaA, deltaB, deltaC;  // delta of Angle

int main()
{
    float i, j, g;

    CLEAR_SCREEN();

    // delta of Angles for rotation
    deltaA = 0.09;
    deltaB = 0.05;
    deltaC = -0.05;

    tokenQueue queue = init(str);

    // Start
    printf("The program will start in 5sec, open console on FULL SCREEN");
    SLEEP(5000);

    while (1)
    {
        memset(buffer, background, sizeof(buffer));
        memset(zbuffer, 0, sizeof(zbuffer));

        Angles ang = {sin(A), sin(B), sin(C), cos(A), cos(B), cos(C)};

        for (i = -cWidth / 2; i < cWidth / 2; i += 1)
        {
            for (j = -cWidth / 2; j < cWidth / 2; j += 1)
            {
                for (g = -cWidth / 2; g <= cWidth / 2; g += 1)
                {
                    point p = {i, j, g};
                    if (evalPolish(&queue, p))
                    {
                        calculatePoint(i, j, g, WIDTH, HEIGHT, zbuffer, buffer,
                                       colorbuffer, &ang);
                    }
                }
            }
        }

        // Move cursor to home position
        printf("%c[%d;%df", 0x1B, 0, 0);

        // Coordinates of X Y Z (Debug)
        printf("%0.2f %0.2f %0.2f\n", A, B, C);

        // Print all points
        renderObject(WIDTH, HEIGHT, buffer, colorbuffer, PrevBuffer);

        // Change angles
        if (abs(C) >= 100)
        {
            deltaC *= -1;
        }
        if (abs(B) >= 100) deltaB *= -1;
        if (abs(A) >= 100) deltaA *= -1;

        C += deltaC;  // X rotation (roll)
        B += deltaB;  // Y rotation (pitch)
        A += deltaA;  // Z rotation (yaw)

        SLEEP(10);
    }
}
