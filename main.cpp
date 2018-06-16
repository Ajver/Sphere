#include <iostream>
#include <windows.h>
#include <conio.h>
#include <math.h>
#include <vector>

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

class Particle : public slVec2D
{
public:
    vector<Particle> neighbors;

    void addNeighbor(Particle p)
    {
        neighbors.push_back(p);
    }

    void render()
    {
        for(int i=0; i<neighbors.size(); i++)
            drawLine('o', neighbors[i].x, neighbors[i].y-4, neighbors[i].x, neighbors[i].y, 14);
    }
};

class Sphere
{
public:
    Sphere(float nr, int ntotal)
    {
        r = nr;
        total = ntotal;

        grid = new Particle[total*total];

        create();
        setNeighbors();
    }

    void create()
    {
        for(int i=0; i<total; i++)
        {
            for(int j=0; j<total; j++)
            {
                float alpha = map(total-i-1, 0, total-1, 0, PI);
                float beta = map(total-j-1, 0, total-1, 0, TWO_PI);

                int x = (int)(r * sin(alpha) * cos(beta));
                int y = (int)(r * sin(alpha) * sin(beta));

                Particle *p = &grid[total * i + j];

                p->x = x;
                p->y = y;
            }
        }
    }

    void setNeighbors()
    {
        for(int i=0; i<total-1; i++)
        {
            for(int j=0; j<total; j++)
            {
                Particle *p = &grid[total * i + j];

                p->addNeighbor(grid[total * i + j + 1]);
                p->addNeighbor(grid[total * (i+1) + j]);
            }
        }
    }

    void render()
    {
        for(int i=0; i<total; i++)
        {
            for(int j=0; j<total; j++)
            {
                float alpha = map(total-i-1, 0, total-1, 0, PI);
                float beta = map(total-j-1, 0, total-1, 0, TWO_PI);

                int x = (int)(r * sin(alpha) * cos(beta));
                int y = (int)(r * sin(alpha) * sin(beta));
                int z = (int)(r * cos(alpha));

                translate(getWindowWidth()/4-15, 0);
                draw(getCharFromZ(z), x, y, getColorFromZ(z));

                //grid[10].render();

                translate(getWindowWidth()/4+15, 0);
                draw(getCharFromZ(z), z, y, getColorFromZ(z));

                translate(getWindowWidth()/4+15, 0);
                draw(getCharFromZ(z), y, -z, getColorFromZ(z));


                translate(-getWindowWidth()/4*3-15, 0);
            }
        }
    }

private:
    Particle *grid;

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

    slVec2D get(int x, int y)
    {
        return grid[total * y + x];
    }
};

void stering()
{
    int x = 3;
    int y = 20;

    while(true)
    {
        clearScreen();
        drawLine('#', 0, 0, x, y, 14);

        draw(toString(x)+", "+toString(y), x+1, y, 15);

        switch(getch())
        {
        case 'w': y--; break;
        case 's': y++; break;
        case 'a': x--; break;
        case 'd': x++; break;
        case 27: return;
        }
    }
}

int main()
{
    setWindowSize(180, 70);



    translate(0, getWindowHeight()/2);

    Sphere sp(25,20);
    sp.render();

    translateTo(getWindowWidth()/2,getWindowHeight()/2);



    getch();


    stering();


    float r = 30;

    for(int i=0; true; i=(i+1)%60)
    {
        clearScreen();
        drawCircle('@', 0, 0, (int)r, 12);

        drawLine('#', 0, 0, (int)(r * cos(i*TWO_PI/60)), (int)(r * sin(i*TWO_PI/60)), 14);

        Sleep(100);
    }

    translateTo(24,40);
    drawCircle('x', 00, 00, 20, 12);

    drawLine('x', 0, 0, 0, 20, 10);

    // For pause the program
    getch();

    return 0;
}
