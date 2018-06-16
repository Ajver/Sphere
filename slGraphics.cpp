#include "slGraphics.h"

int cx = 0,
    cy = 0;

int tx = 0,
    ty = 0;

int WW = 30,
    WH = 30;

//==============================================================================
void setCursorPosition(int x, int y)
{
    x += tx;
    y += ty;

    /*
    if(x < 0) return;
    if(x > WW-1) return;
    if(y < 0) return;
    if(y > WH-1) return;
    */

    COORD c;
    c.X = cx = x;
    c.Y = cy = y;
    SetConsoleCursorPosition (GetStdHandle (STD_OUTPUT_HANDLE), c);
}
void setColor(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
void clearScreen()
{
    system("cls");
}

//==============================================================================
void draw(char c)
{
    if(!inScreen(cx, cy)) return;
    cout << c;
}
void draw(char c, int x, int y)
{
    setCursorPosition(x, y);
    draw(c);
}
void draw(int i , int x , int y , int color)
{
    setColor(color);
    setCursorPosition(x,y);
    draw(toString(i), x, y);
}
void draw(int i , string x , int y , int color)
{
    draw(toString(i), x, y, color);
}
void draw(char c, int x, int y, int color)
{
    setColor(color);
    setCursorPosition(x, y);
    draw(c);
}
void draw(string s, int x, int y)
{
    setCursorPosition(x, y);
    for(int i=0; i<s.length(); i++)
        draw(s[i], x+i, y);
}
void draw(string s, int x, int y, int color)
{
    setColor(color);
    draw(s, x, y);
}
void draw(string s , string a, int y, int color)
{
    if(a == "center")
    {
        draw(s,WW/2 - s.length()/2,y,color);
    }
    else if(a == "left")
    {
        draw(s, 0, y, color);
    }
    else if(a == "right")
    {
        draw(s, WW - s.length(), y, color);
    }
}

//==============================================================================
void write(string s, int x, int y, int color, int delay)
{
    for(int i = 0; i < s.length(); i++)
    {
        //draw(char(219),x+i,y,15);
        Sleep(delay);
        draw(s[i], x+i ,y ,color);
    }
}
void write(string s , string a, int y, int color, int delay)
{
    if(a == "center")
    {
        write(s,WW/2 - s.length()/2,y, color, delay);
    }
    else if(a == "left")
    {
        write(s, 0, y, color, delay);
    }
    else if(a == "right")
    {
        write(s, WW - s.length(), y, color, delay);
    }
}
void write(char c, int x, int y, int color, int delay)
{
    setColor(color);
    draw(char(219),x,y,color);
    Sleep(delay);
    draw(c, x, y);
}

//==============================================================================
void translate(int ntx, int nty)
{
    tx += ntx;
    ty += nty;
}
void translateTo(int ntx, int nty)
{
    tx = ntx;
    ty = nty;
}

//==============================================================================
void fillRectangle(char c, int x, int y, int w, int h, int color)
{
    string s = "";
    for(int i=0; i<w; i++) s += c;

    setColor(color);

    for(int i=0; i<h; i++)
    {
        setCursorPosition(x, y+i);
        draw(s, x, y);
    }
}
void drawCircle(char c, int x, int y, int r, int color)
{
    setColor(color);

    int margin = 12;

    for(int i=-r; i<r; i++)
    {
        for(int j=-r; j<r; j++)
        {
            if(r*r > i*i + j*j - margin && r*r < i*i + j*j + margin)
                draw(c, x+j, y+i);
        }
    }
}

//==============================================================================
void drawLine(char c, int x1, int y1, int x2, int y2, int color)
{
    setColor(color);


    int w = x2 - x1;
    int h = y2 - y1;

    if(w == h && h == 0) return;

    if(abs(w) > abs(h)) {
        if(w < 0)
        {
            swap(y1, y2);
            swap(x1, x2);
            w = x2 - x1;
            h = y2 - y1;
        }

        for(int x=x1; x<w+x1; x++)
        {
            int y = (int)(x*h/w);
            draw(c, x, y);
        }
    }
    else
    {
        if(h < 0)
        {
            swap(y1, y2);
            swap(x1, x2);
            w = x2 - x1;
            h = y2 - y1;
        }
        for(int y=y1; y<h+y1; y++)
        {
            int x = (int)(y*w/h);
            draw(c, x, y);
        }
    }
}

void setWindowSize(int nw, int nh) {
    WW = nw;
    WH = nh;

    system(toCharArr("mode "+toString(WW)+','+toString(WH)));
}
int getWindowWidth() { return WW; }
int getWindowHeight() { return WH; }

bool inScreen(int x, int y)
{
    return
        x >= 0   &&
        x < WW   &&
        y >= 0   &&
        y < WH;
}
