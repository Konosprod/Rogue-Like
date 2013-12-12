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

vector<Point> Map::coordRoomCo (int x, int y)
{
    vector<Point> res;
    Point p = {0,0};

    if (isCorner(x,y))
    {
        if (y == 0 && x == 0)
        {
            if (m_tab[y][x+1] == 1)
            {
                p.x = x+1;
                p.y = y;
                res.push_back(p);
            }
            if (m_tab[y+1][x] == 1)
            {
                p.x = x;
                p.y = y+1;
                res.push_back(p);
            }
        }
        else if (y == 0 && x == SIZE_MAX - 1)
        {
            if (m_tab[y][x-1] == 1)
            {
                p.x = x-1;
                p.y = y;
                res.push_back(p);
            }
            if (m_tab[y+1][x] == 1)
            {
                p.x = x;
                p.y = y+1;
                res.push_back(p);
            }
        }
        else if (y == SIZE_MAX - 1 && x == 0)
        {
            if (m_tab[y-1][x] == 1)
            {
                p.y = y-1;
                p.x = x;
                res.push_back(p);
            }
            if (m_tab[y][x+1] == 1)
            {
                p.y = y;
                p.x = x+1;
                res.push_back(p);
            }
        }
        else if (y == SIZE_MAX - 1 && x == SIZE_MAX - 1)
        {
            if (m_tab[y-1][x] == 1)
            {
                p.y = y-1;
                p.x = x;
                res.push_back(p);
            }
            if (m_tab[y][x-1] == 1)
            {
                p.x = x-1;
                p.y = y;
                res.push_back(p);
            }
        }
    }
    else if (isOnEdge(x,y))
    {
        if (y == 0)
        {
            if (m_tab[y][x-1] == 1)
            {
                p.x = x-1;
                p.y = y;
                res.push_back(p);
            }
            if (m_tab[y][x+1] == 1)
            {
                p.x = x+1;
                p.y = y;
                res.push_back(p);
            }
            if (m_tab[y+1][x] == 1)
            {
                p.x = x;
                p.y = y+1;
                res.push_back(p);
            }
        }
        else if (y == SIZE_MAX - 1)
        {
            if (m_tab[y][x-1] == 1)
            {
                p.x = x-1;
                p.y = y;
                res.push_back(p);
            }
            if (m_tab[y][x+1] == 1)
            {
                p.x = x+1;
                p.y = y;
                res.push_back(p);
            }
            if (m_tab[y-1][x] == 1)
            {
                p.x = x;
                p.y = y-1;
                res.push_back(p);
            }
        }
        else if (x == 0)
        {
            if (m_tab[y-1][x] == 1)
            {
                p.x = x;
                p.y = y-1;
                res.push_back(p);
            }
            if (m_tab[y+1][x] == 1)
            {
                p.x = x;
                p.y = y+1;
                res.push_back(p);
            }
            if (m_tab[y][x+1] == 1)
            {
                p.x = x+1;
                p.y = y;
                res.push_back(p);
            }
        }
        else // x == SIZE_MAX - 1
        {
            if (m_tab[y-1][x] == 1)
            {
                p.x = x;
                p.y = y-1;
                res.push_back(p);
            }
            if (m_tab[y+1][x] == 1)
            {
                p.x = x;
                p.y = y+1;
                res.push_back(p);
            }
            if (m_tab[y][x-1] == 1)
            {
                p.x = x-1;
                p.y = y;
                res.push_back(p);
            }
        }
    }
    else
    {
        if (m_tab[y-1][x] == 1)
        {
            p.x = x;
            p.y = y-1;
            res.push_back(p);
        }
        if (m_tab[y+1][x] == 1)
        {
            p.x = x;
            p.y = y+1;
            res.push_back(p);
        }
        if (m_tab[y][x-1] == 1)
        {
            p.x = x-1;
            p.y = y;
            res.push_back(p);
        }
        if (m_tab[y][x+1] == 1)
        {
            p.x = x+1;
            p.y = y;
            res.push_back(p);
        }
    }
    return res;
}

void Map::createRoomCo (int x, int y)
{
    int random = rand()%4 + 1;
    int signe = 0; //0 pour - et 1 pour +
    int coord = 0; //0 pour y et 1 pour x

    if (isCorner(x,y))
    {
        coord = rand()%2; // 0 pour y et 1 pour x

        if (random >= 2)
        {
            if (y == 0 && x == 0)
            {
                m_tab[y+1][x] = 1;
                m_tab[y][x+1] = 1;
            }
            else if (y == 0 && x == SIZE_MAX - 1)
            {
                m_tab[y+1][x] = 1;
                m_tab[y][x-1] = 1;
            }
            else if (y == SIZE_MAX - 1 && x == 0)
            {
                m_tab[y-1][x] = 1;
                m_tab[y][x+1] = 1;
            }
            else if (y == SIZE_MAX - 1 && x == SIZE_MAX -1)
            {
                m_tab[y-1][x] = 1;
                m_tab[y][x-1] = 1;
            }
        }
        else
        {
            if (y == 0 && x == 0)
            {
                if (coord == 0)
                    m_tab[y+1][x] = 1;
                else
                    m_tab[y][x+1] = 1;
            }
            else if (y == 0 && x == SIZE_MAX - 1)
            {
                if (coord == 0)
                    m_tab[y+1][x] = 1;
                else
                    m_tab[y][x-1] = 1;
            }
            else if (y == SIZE_MAX - 1 && x == 0)
            {
                if (coord == 0)
                    m_tab[y-1][x] = 1;
                else
                    m_tab[y][x+1] = 1;
            }
            else if (y == SIZE_MAX - 1 && x == SIZE_MAX -1)
            {
                if (coord == 0)
                    m_tab[y-1][x] = 1;
                else
                    m_tab[y][x-1] = 1;
            }
        }
    }
    else if (isOnEdge(x,y))
    {
        if (random >= 3)
        {
            if (y == 0)
            {
                m_tab[y][x-1] = 1;
                m_tab[y][x+1] = 1;
                m_tab[y+1][x] = 1;
            }
            else if (x == 0)
            {
                m_tab[y-1][x] = 1;
                m_tab[y+1][x] = 1;
                m_tab[y][x+1] = 1;
            }
            else if (y == SIZE_MAX - 1)
            {
                m_tab[y][x-1] = 1;
                m_tab[y][x+1] = 1;
                m_tab[y-1][x] = 1;
            }
            else if (x == SIZE_MAX - 1)
            {
                m_tab[y-1][x] = 1;
                m_tab[y+1][x] = 1;
                m_tab[y][x-1] = 1;
            }
        }
        else
        {
            if (y == 0)
            {
                while (random != 0)
                {
                    signe = rand()%2;
                    coord = rand()%2;

                    if (coord == 0)
                    {
                        m_tab[y+1][x] = 1;
                    }
                    else if (signe == 0 && coord == 1)
                    {
                        m_tab[y][x-1] = 1;
                    }
                    else
                    {
                        m_tab[y][x+1] = 1;
                    }
                    random--;
                }
            }
            else if (y == SIZE_MAX - 1)
            {
                while (random != 0)
                {
                    signe = rand()%2;
                    coord = rand()%2;

                    if (coord == 0)
                    {
                        m_tab[y-1][x] = 1;
                    }
                    else if (signe == 0 && coord == 1)
                    {
                        m_tab[y][x-1] = 1;
                    }
                    else
                    {
                        m_tab[y][x+1] = 1;
                    }
                    random--;
                }
            }
            else if (x == SIZE_MAX - 1)
            {
                while (random != 0)
                {
                    signe = rand()%2;
                    coord = rand()%2;

                    if (coord == 1)
                    {
                        m_tab[y][x-1] = 1;
                    }
                    else if (signe == 0 && coord == 0)
                    {
                        m_tab[y-1][x] = 1;
                    }
                    else
                    {
                        m_tab[y+1][x] = 1;
                    }
                    random--;
                }
            }
            else
            {
                while (random != 0)
                {
                    signe = rand()%2;
                    coord = rand()%2;

                    if (coord == 1)
                    {
                        m_tab[y][x+1] = 1;
                    }
                    else if (signe == 0 && coord == 0)
                    {
                        m_tab[y-1][x] = 1;
                    }
                    else
                    {
                        m_tab[y+1][x] = 1;
                    }
                    random--;
                }
            }
        }
    }
    else
    {
        while (random != 0)
        {
            signe = rand()%2;
            coord = rand()%2;

            if (coord == 0)
            {
                if (signe == 0)
                    m_tab[y-1][x] = 1;
                else
                    m_tab[y+1][x] = 1;
            }
            else
            {
                if (signe == 0)
                    m_tab[y][x-1] = 1;
                else
                    m_tab[y][x+1] = 1;
            }
            random--;
        }
    }
} // createSalleCo


void Map::draw(sf::RenderTarget& t, sf::RenderStates s) const
{

}
