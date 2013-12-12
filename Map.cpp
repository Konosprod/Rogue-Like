#include "Map.h"

Map::Map()
{
    //ctor
}

Map::~Map()
{
    //dtor
}

void Map::copyTab(int** src, int** dest)
{
    for (int i=0; i<SIZE_MAX; i++)
    {
        for (int j=0; j<SIZE_MAX; j++)
        {
            if (src[j][i] != 0)
            {
                dest[j][i] = 1;
            }
        }
    }
}

void Map::freeTab(int** t)
{
    for(int i = 0; i < SIZE_MAX; i++)
    {
        delete[] t[i];
    }
    delete[] t;
}

bool Map::isCorner (int y, int x)
{
    bool res = false;
    if (y == 0 && x == 0)
        res = true;
    else if (y == 0 && x == SIZE_MAX - 1)
        res = true;
    else if (y == SIZE_MAX - 1 && x == 0)
        res = true;
    else if (y == SIZE_MAX - 1 && x == SIZE_MAX -1)
        res = true;

    return res;
}

bool Map::isEmpty ()
{
    bool empty = true;

    for (int i=0; i<SIZE_MAX; i++)
    {
        for (int j=0; j<SIZE_MAX; j++)
        {
            if (m_tab[j][i] == 1)
            {
                empty = false;
            }
        }
    }
    return empty;
}

bool Map::isOnEdge (int y, int x)
{
    bool res = false;
    if (y == 0)
        res = true;
    else if (x == 0)
        res = true;
    else if (y == SIZE_MAX - 1)
        res = true;
    else if (x == SIZE_MAX - 1)
        res = true;
    return res;
}

int Map::numberRoomCo (int x, int y)
{
    int res = 0;
    if (isCorner(x,y))
    {
        if (y == 0)
        {
            if(x == 0)
            {
                if (m_tab[y+1][x] == 1)
                    res++;
                if (m_tab[y][x+1] == 1)
                    res++;
            }
            else if(x == SIZE_MAX - 1)
            {
                if (m_tab[y+1][x] == 1)
                    res++;
                if (m_tab[y][x-1] == 1)
                    res++;
            }
        }
        else if (y == SIZE_MAX)
        {
            if(x == 0)
            {
                if (m_tab[y-1][x] == 1)
                    res++;
                if (m_tab[y][x+1] == 1)
                    res++;
            }
            else if(x == SIZE_MAX -1)
            {
                if (m_tab[y-1][x] == 1)
                    res++;
                if (m_tab[y][x-1] == 1)
                    res++;
            }
        }
    }
    else if (isOnEdge(x,y))
    {
        if (y == 0)
        {
            if (m_tab[y][x-1] == 1)
                res++;
            if (m_tab[y][x+1] == 1)
                res++;
            if (m_tab[y+1][x] == 1)
                res++;
        }
        else if (y == SIZE_MAX - 1)
        {
            if (m_tab[y][x-1] == 1)
                res++;
            if (m_tab[y][x+1] == 1)
                res++;
            if (m_tab[y-1][x] == 1)
                res++;
        }
        else if (x == 0)
        {
            if (m_tab[y-1][x] == 1)
                res++;
            if (m_tab[y+1][x] == 1)
                res++;
            if (m_tab[y][x+1] == 1)
                res++;
        }
        else
        {
            if (m_tab[y-1][x] == 1)
                res++;
            if (m_tab[y+1][x] == 1)
                res++;
            if (m_tab[y][x-1] == 1)
                res++;
        }
    }
    else
    {
        if (m_tab[y-1][x] == 1)
            res++;
        if (m_tab[y+1][x] == 1)
            res++;
        if (m_tab[y][x-1] == 1)
            res++;
        if (m_tab[y][x+1] == 1)
            res++;
    }
    return res;
}

void Map::draw(sf::RenderTarget& t, sf::RenderStates s) const
{

}
