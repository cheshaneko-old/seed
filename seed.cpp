#include "seed.h"
#include <algorithm>

Seed::Seed()
{
    area[0]=NULL;
    area[1]=NULL;
}

Seed::Seed(int w, int h, const bool* p)
{
    width = w;
    height = h;
    gen = 0;
    cells = 0;
    area[0] = new bool[width*height];
    area[1] = new bool[width*height];

    points[0] = new int[width*height];
    points[1] = new int[width*height];
    duplicatesCheck = new bool[width*height];
    pointsSize = width*height;
    changeGen = 0;
    for(int i=0; i<width*height; ++i)
    {
        points[0][i]=i;
    }


    if(p!=NULL){
        for(int i=0; i<width*height; ++i)
            area[0][i]=p[i];
    }
    else
    {
        for(int i=0; i<width*height; ++i)
            area[0][i]=false;
    }
}

Seed::~Seed()
{
    if((area[0]) && (area[1]))
    {
        delete[] (area[0]);
        delete[] (area[1]);
        delete[] (points[0]);
        delete[] (points[1]);
        delete[] duplicatesCheck;
    }
}

const bool* Seed::get()
{
    return area[0];
}

const int* Seed::getCangedCells()
{
    return points[0];
}

int Seed::getChangedSize()
{
    return pointsSize;
}

inline bool Seed::alive(int c)
{
    int x = c % width;
    int y = c / width;

    if(area[0][width*y+x]==true)
        return false;

    int k = 0;
    int xt;
    int yt;

    for(int i=-1; i<=1; ++i)
        for(int j=-1; j<=1; ++j)
        {
            if(!(i==0 && j==0))
            {
                xt = (x + i + width)%width;
                yt = (y + j + height)%height;
                if(area[0][width*yt+xt]==true)
                    ++k;
            }
        }
    return k==2;
}

void Seed::next_generation()
{
    cells = 0;
    int s = pointsSize;
    pointsSize = 0;
    for(int i=0; i<width*height; ++i)
    {
        duplicatesCheck[i] = false;
        area[1][i] = false;
    }


    for(int i=0; i<s; ++i)
    {
        if(alive(points[0][i]))
        {
            area[1][(points[0][i])]=true;
            cellChanged(points[0][i]);
            ++cells;
        }
    }
    std::swap(area[0], area[1]);
    std::swap(points[0], points[1]);

    ++gen;
    ++changeGen;
}

long int Seed::getGen()
{
    return gen;
}

long int Seed::getCells()
{
    return cells;
}

void Seed::cellChanged(int c)
{
    int x = c % width;
    int y = c / width;
    int xt;
    int yt;
    for(int i=-1; i<=1; ++i)
        for(int j=-1; j<=1; ++j)
        {
            xt = (x + i + width)%width;
            yt = (y + j + height)%height;
            if(!duplicatesCheck[yt*width+xt])
            {
                duplicatesCheck[yt*width+xt] = true;
                points[1][pointsSize] = yt*width+xt;
                ++pointsSize;
            }
        }
}
