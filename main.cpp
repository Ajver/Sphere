#include <iostream>
#include <windows.h>
#include <conio.h>
#include <math.h>

#include "slGraphics.h"

using namespace std;

const float PI = 3.14159f;
const float TWO_PI = 3.14159f * 2.0f;
const float HALF_PI = PI / 2.0f;

float map(float a, float minA, float maxA, float minB, float maxB)
{
    float Arange = maxA - minA;
    float Brange = maxB - minB;

    float proportion = (a-minA)/Arange;

    return Brange*proportion + minB;
}

class Sphere
{
public:
    Sphere(float nr, int ntotal)
    {
        r = nr;
        total = ntotal;
    }

    void render()
    {
        for(int i=0; i<total; i++) {
            for(int j=0; j<total; j++) {
                float alpha = map(total-i-1, 0, total-1, 0, PI);
                float beta = map(total-j-1, 0, total-1, 0, TWO_PI);

                int x = (int)(r * sin(alpha) * cos(beta));
                int y = (int)(r * sin(alpha) * sin(beta));
                int z = (int)(r * cos(alpha));

                translate(getWindowWidth()/4-15, 0);
                draw(getCharFromZ(z), x, y, getColorFromZ(z));

                translate(getWindowWidth()/4+15, 0);
                draw(getCharFromZ(z), z, y, getColorFromZ(z));

                translate(getWindowWidth()/4+15, 0);
                draw(getCharFromZ(z), y, -z, getColorFromZ(z));


                translate(-getWindowWidth()/4*3-15, 0);
            }
        }
    }

private:
    float r;

    // Number of all particles
    int total;

    int getColorFromZ(int z)
    {
        if(z == -r)
            return 14;

        if(z <= -r/2)
            return 1;

        if(z <= 0)
            return 2;

        if(z <= r/2)
            return 8;

        return 15;
    }

    char getCharFromZ(int z)
    {
        if(z == -r)
            return 'o';

        if(z <= -r/2)
            return 176;

        if(z <= 0)
            return 177;

        if(z <= r/2)
            return 178;

        return 219;
    }

};

int main()
{
    setWindowSize(180, 70);

    translate(0, getWindowHeight()/2);

    Sphere sp(25, 10);
    //sp.render();

    translateTo(getWindowWidth()/2,getWindowHeight()/2);

    int x = 3;
    int y = 20;

    /*
    while(true)
    {
        clearScreen();
        drawLine('#', 0, 0, x, y, 14);


        switch(getch())
        {
        case 'w': y--; break;
        case 's': y++; break;
        case 'a': x--; break;
        case 'd': x++; break;
        }
    }
    */

    float r = 30;

    for(int i=0; false; i=(i+1)%60)
    {
        clearScreen();
        drawCircle('@', 0, 0, (int)r+1, 12);

        drawLine('#', 0, 0, (int)(r * cos(i*TWO_PI/60)), (int)(r * sin(i*TWO_PI/60)), 14);

        Sleep(100);
    }

    drawCircle('x', 0, 0, 5, 10);

    // For pause the program
    getch();

    return 0;
}
