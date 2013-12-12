#include "Map.h"

Map::Map()
{

}

Map::~Map()
{
    freeTab(m_tab);
}

int absValue (int n)
{
    if (n > 0)
        return n;
    else
        return -n;
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

bool Map::isEmpty (int** t)
{
    bool empty = true;

    for (int i=0; i<SIZE_MAX; i++)
    {
        for (int j=0; j<SIZE_MAX; j++)
        {
            if (t[j][i] == 1)
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

int Map::numberRoomCo (int x, int y, int** grille)
{
    int res = 0;
    if (isCorner(x,y))
    {
        if (y == 0)
        {
            if(x == 0)
            {
                if (grille[y+1][x] == 1)
                    res++;
                if (grille[y][x+1] == 1)
                    res++;
            }
            else if(x == SIZE_MAX - 1)
            {
                if (grille[y+1][x] == 1)
                    res++;
                if (grille[y][x-1] == 1)
                    res++;
            }
        }
        else if (y == SIZE_MAX)
        {
            if(x == 0)
            {
                if (grille[y-1][x] == 1)
                    res++;
                if (grille[y][x+1] == 1)
                    res++;
            }
            else if(x == SIZE_MAX -1)
            {
                if (grille[y-1][x] == 1)
                    res++;
                if (grille[y][x-1] == 1)
                    res++;
            }
        }
    }
    else if (isOnEdge(x,y))
    {
        if (y == 0)
        {
            if (grille[y][x-1] == 1)
                res++;
            if (grille[y][x+1] == 1)
                res++;
            if (grille[y+1][x] == 1)
                res++;
        }
        else if (y == SIZE_MAX - 1)
        {
            if (grille[y][x-1] == 1)
                res++;
            if (grille[y][x+1] == 1)
                res++;
            if (grille[y-1][x] == 1)
                res++;
        }
        else if (x == 0)
        {
            if (grille[y-1][x] == 1)
                res++;
            if (grille[y+1][x] == 1)
                res++;
            if (grille[y][x+1] == 1)
                res++;
        }
        else
        {
            if (grille[y-1][x] == 1)
                res++;
            if (grille[y+1][x] == 1)
                res++;
            if (grille[y][x-1] == 1)
                res++;
        }
    }
    else
    {
        if (grille[y-1][x] == 1)
            res++;
        if (grille[y+1][x] == 1)
            res++;
        if (grille[y][x-1] == 1)
            res++;
        if (grille[y][x+1] == 1)
            res++;
    }
    return res;
} // numberRoomCo

std::vector<Point> Map::coordRoomCo (int x, int y, int** grille)
{
    std::vector<Point> res;
    Point p = {0,0};

    if (isCorner(x,y))
    {
        if (y == 0 && x == 0)
        {
            if (grille[y][x+1] == 1)
            {
                p.x = x+1;
                p.y = y;
                res.push_back(p);
            }
            if (grille[y+1][x] == 1)
            {
                p.x = x;
                p.y = y+1;
                res.push_back(p);
            }
        }
        else if (y == 0 && x == SIZE_MAX - 1)
        {
            if (grille[y][x-1] == 1)
            {
                p.x = x-1;
                p.y = y;
                res.push_back(p);
            }
            if (grille[y+1][x] == 1)
            {
                p.x = x;
                p.y = y+1;
                res.push_back(p);
            }
        }
        else if (y == SIZE_MAX - 1 && x == 0)
        {
            if (grille[y-1][x] == 1)
            {
                p.y = y-1;
                p.x = x;
                res.push_back(p);
            }
            if (grille[y][x+1] == 1)
            {
                p.y = y;
                p.x = x+1;
                res.push_back(p);
            }
        }
        else if (y == SIZE_MAX - 1 && x == SIZE_MAX - 1)
        {
            if (grille[y-1][x] == 1)
            {
                p.y = y-1;
                p.x = x;
                res.push_back(p);
            }
            if (grille[y][x-1] == 1)
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
            if (grille[y][x-1] == 1)
            {
                p.x = x-1;
                p.y = y;
                res.push_back(p);
            }
            if (grille[y][x+1] == 1)
            {
                p.x = x+1;
                p.y = y;
                res.push_back(p);
            }
            if (grille[y+1][x] == 1)
            {
                p.x = x;
                p.y = y+1;
                res.push_back(p);
            }
        }
        else if (y == SIZE_MAX - 1)
        {
            if (grille[y][x-1] == 1)
            {
                p.x = x-1;
                p.y = y;
                res.push_back(p);
            }
            if (grille[y][x+1] == 1)
            {
                p.x = x+1;
                p.y = y;
                res.push_back(p);
            }
            if (grille[y-1][x] == 1)
            {
                p.x = x;
                p.y = y-1;
                res.push_back(p);
            }
        }
        else if (x == 0)
        {
            if (grille[y-1][x] == 1)
            {
                p.x = x;
                p.y = y-1;
                res.push_back(p);
            }
            if (grille[y+1][x] == 1)
            {
                p.x = x;
                p.y = y+1;
                res.push_back(p);
            }
            if (grille[y][x+1] == 1)
            {
                p.x = x+1;
                p.y = y;
                res.push_back(p);
            }
        }
        else // x == SIZE_MAX - 1
        {
            if (grille[y-1][x] == 1)
            {
                p.x = x;
                p.y = y-1;
                res.push_back(p);
            }
            if (grille[y+1][x] == 1)
            {
                p.x = x;
                p.y = y+1;
                res.push_back(p);
            }
            if (grille[y][x-1] == 1)
            {
                p.x = x-1;
                p.y = y;
                res.push_back(p);
            }
        }
    }
    else
    {
        if (grille[y-1][x] == 1)
        {
            p.x = x;
            p.y = y-1;
            res.push_back(p);
        }
        if (grille[y+1][x] == 1)
        {
            p.x = x;
            p.y = y+1;
            res.push_back(p);
        }
        if (grille[y][x-1] == 1)
        {
            p.x = x-1;
            p.y = y;
            res.push_back(p);
        }
        if (grille[y][x+1] == 1)
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
}

void Map::initTab(int** t)
{
    for (int i=0; i<SIZE_MAX; i++)
    {
        for (int j=0; j<SIZE_MAX; j++)
        {
            t[j][i] = 0;
        }
    }
}

bool Map::setEvent()
{
    int y = 0;
    int x = 0;
    bool trouve = false;

    for (int i=0; i<SIZE_MAX && !trouve; i++)
    {
        for (int j=0; j<SIZE_MAX && !trouve; j++)
        {
            if((m_tab[j][i] == 1) && (numberRoomCo(i, j, m_tab) == 1))
            {
                m_tab[j][i] = 2;
                y = j;
                x = i;
                trouve = true;
            }
        }
    }

    trouve = false;

    for (int k=7; k>0 && !trouve; k++)
    {
        for (int i=0; i<SIZE_MAX && !trouve; i++)
        {
            for (int j=0; j<SIZE_MAX && !trouve; j++)
            {
                if(((m_tab[j][i] == 1) && (numberRoomCo(i, j, m_tab) == 1)) &&
                    ((absValue(j-y) + absValue(i-x)) > k))
                {
                    m_tab[j][i] = 2;
                    trouve = true;
                }
            }
        }

        if (!trouve)
        {
            for (int i=0; i<SIZE_MAX && !trouve; i++)
            {
                for (int j=0; j<SIZE_MAX && !trouve; j++)
                {
                    if(((m_tab[j][i] == 1) && (numberRoomCo(i, j, m_tab) == 2)) &&
                        ((absValue(j-y) + absValue(i-x)) > k))
                    {
                        m_tab[j][i] = 2;
                        trouve = true;
                    }
                }
            }
        }
    }
    return trouve;
}

int Map::packNumber (int** t)
{
    int** check = new int*[SIZE_MAX];
    int res = 0;
    int x = 0;
    int y = 0;
    bool trouve = false;
    std::vector<Point> aCheck;
    std::vector<Point> temp;
    Point p = {0,0};

    for(int i=0; i<SIZE_MAX; i++)
    {
        check[i] = new int[SIZE_MAX];
    }

    initTab(check);

    copyTab(t, check);

    while(!isEmpty(check))
    {
        for (int i=0; i<SIZE_MAX && !trouve; i++)
        {
            for (int j=0; j<SIZE_MAX && !trouve; j++)
            {
                if (check[j][i] == 1)
                {
                    p.x = i;
                    p.y = j;
                    trouve = true;
                }
            }
        }

        aCheck = coordRoomCo(p.x,p.y,check);
        aCheck.push_back(p);

        while(!aCheck.empty())
        {
            y = aCheck[0].y;
            x = aCheck[0].x;
            temp = coordRoomCo(x,y,check);
            check[y][x] = 0;
            aCheck.erase(aCheck.begin(), aCheck.begin()+1);

            while(!temp.empty())
            {
                p.y = temp.back().y;
                p.x = temp.back().x;
                aCheck.push_back(p);
                check[temp.back().y][temp.back().x] = 0;
                temp.pop_back();
            }
        }
        trouve = false;
        res++;
    }

    freeTab(check);

    return res;
}

int Map::distanceRoom(Point a, Point b)
{
    return ((absValue(a.x-b.x))+(absValue(a.y-b.y)));
}

int** Map::extractPack()
{
    int** check = new int*[SIZE_MAX];
    std::vector<Point> aCheck;
    std::vector<Point> temp;
    int x = 0;
    int y = 0;
    bool trouve = false;
    Point p = {0,0};

    for(int i=0; i<SIZE_MAX; i++)
    {
        check[i] = new int[SIZE_MAX];
    }

    initTab(check);

    for(int i = 0; i < SIZE_MAX && !trouve; i++)
    {
        for(int j = 0; j < SIZE_MAX && !trouve; j++)
        {
            if(m_tab[j][i] == 1)
            {
                p.x = i;
                p.y = j;
                trouve =  false;
            }
        }
    }

    aCheck = coordRoomCo(p.x, p.y, m_tab);
    aCheck.push_back(p);

    while(!aCheck.empty())
    {
        x = aCheck[0].x;
        y = aCheck[0].y;

        temp = coordRoomCo(x, y, m_tab);
        check[y][x] = 1;

        aCheck.erase(aCheck.begin(), aCheck.begin()+1);

        while(!temp.empty())
        {
            p.y = temp.back().y;
            p.x = temp.back().x;

            aCheck.push_back(p);
            check[p.y][p.x] = 1;
            m_tab[p.y][p.x] = 0;
            temp.pop_back();
        }
    }

    return check;
}

void Map::insertTab(int** src, int** dst)
{
    for(int i = 0; i < SIZE_MAX; i++)
    {
        for(int j = 0; j < SIZE_MAX; j++)
        {
            if(src[j][i] != 0)
            {
                dst[j][i] = 1;
            }
        }
    }
}

void Map::linkPacks()
{
    int** check = new int*[SIZE_MAX];
    bool trouve = false;
    int x = 0;
    int y = 0;
    int mini = 1337;
    int x1 = 0;
    int y1 = 0;
    int x2 = 0;
    int y2 = 0;
    std::vector<Point> pack[2];
    std::vector<Point> aCheck;
    std::vector<Point> temp;
    Point p = {0,0};

    for(int i=0; i<SIZE_MAX; i++)
    {
        check[i] = new int[SIZE_MAX];
    }

    initTab(check);
    copyTab(m_tab, check);

    while(packNumber(check) == 2)
    {
        for (int i=0; i<SIZE_MAX && !trouve; i++)
        {
            for (int j=0; j<SIZE_MAX && !trouve; j++)
            {
                if (check[j][i] == 1)
                {
                    p.x = i;
                    p.y = j;
                    trouve = true;
                }
            }
        }

        aCheck = coordRoomCo(p.x,p.y,check);
        aCheck.push_back(p);

        while(!aCheck.empty())
        {
            y = aCheck[0].y;
            x = aCheck[0].x
            ;

            if (numberRoomCo(x,y,check) < 4)
            {
                p.x = x;
                p.y = y;

                pack[0].push_back(p);
            }

            temp = coordRoomCo(x,y,check);
            check[y][x] = 0;
            aCheck.erase(aCheck.begin(),aCheck.begin()+1);

            while(!temp.empty())
            {
                p.y = temp.back().y;
                p.x = temp.back().x;

                aCheck.push_back(p);
                check[temp.back().y][temp.back().x] = 0;
                temp.pop_back();
            }
        }

        trouve = false;
    }

    aCheck.clear();
    temp.clear();

    while (!isEmpty(check))
    {
        for (int i=0; i<SIZE_MAX && !trouve; i++)
        {
            for (int j=0; j<SIZE_MAX && !trouve; j++)
            {
                if (check[j][i] == 1)
                {
                    p.x = i;
                    p.y = j;
                    trouve = true;
                }
            }
        }

        aCheck = coordRoomCo(p.x,p.y,check);
        aCheck.push_back(p);

        while(!aCheck.empty())
        {
            y = aCheck[0].y;
            x = aCheck[0].x;

            if (numberRoomCo(x,y,check) < 4)
            {
                p.x = x;
                p.y = y;
                pack[1].push_back(p);
            }

            temp = coordRoomCo(x,y,check);
            check[y][x] = 0;
            aCheck.erase(aCheck.begin(),aCheck.begin()+1);

            while(!temp.empty())
            {
                p.y = temp.back().y;
                p.x = temp.back().x;

                aCheck.push_back(p);
                check[temp.back().y][temp.back().x] = 0;
                temp.pop_back();
            }
        }

        trouve = false;
    }

    for (unsigned int i = 0; i < pack[0].size(); i++)
    {
        for (unsigned int j = 0; j < pack[1].size(); j++)
        {
            if (distanceRoom(pack[0].at(i), pack[1].at(j)) < mini)
            {
                mini = distanceRoom(pack[0].at(i), pack[1].at(j));
                x1 = pack[0].at(i).x;
                y1 = pack[0].at(i).y;
                x2 = pack[1].at(j).x;
                y2 = pack[1].at(j).y;
            }
        }
    }
    if (x1 < x2)
    {
        for (int i=1; i<x2-x1+1; i++)
        {
            m_tab[y1][x1+i] = 1;
        }
    }
    else
    {
        for (int i=1; i<x1-x2+1; i++)
        {
            m_tab[y1][x1-i] = 1;
        }
    }
    if (y1 < y2)
    {
        for (int i=1; i<y2-y1+1; i++)
        {
            m_tab[y1+i][x2] = 1;
        }
    }
    else
    {
        for (int i=1; i<y1-y2+1; i++)
        {
            m_tab[y1-i][x2] = 1;
        }
    }

    freeTab(check);
}

bool Map::joinPack ()
{
    bool res = false;
    int** aInsert = NULL;

    if (packNumber(m_tab) == 1)
    {
        res = true;
    }
    else if (packNumber(m_tab) == 2)// 2 packs, il faut les relier
    {
        linkPacks();
        res = true;
    }

    else if (packNumber(m_tab) == 3) // 3 packs, on relie tout
    {
        aInsert = extractPack();
        linkPacks();
        insertTab(aInsert, m_tab);
        linkPacks();
    }

    freeTab(aInsert);

    return res;
}

void Map::generateMap()
{
    m_tab = new int*[SIZE_MAX];
    int x = 0;
    int y = 0;

    for(int i = 0; i < SIZE_MAX; i++)
    {
        m_tab[i] = new int[SIZE_MAX];
    }

    while(!(packNumber(m_tab) == 3))
    {
        initTab(m_tab);
        m_tab[y][x] = 1;
        createRoomCo(x, y);

        for (int i = 0; i < 8; i++)
        {
            x = rand()%(SIZE_MAX-10) + 5;
            y = rand()%(SIZE_MAX-10) + 5;
            m_tab[y][x] = 1;
            createRoomCo(x, y);
        }
    }

    joinPack();
    setEvent();
}



Point Map::findStart ()
{
    Point res = {0,0};
    for(int i=0; i < SIZE_MAX; i++)
    {
        for(int j=0; j< SIZE_MAX; j++)
        {
            if(m_tab[j][i] == 2)
            {
                res.x = j;
                res.y = i;
            }
        }
    }

    return res;
}

void Map::draw(sf::RenderTarget& t, sf::RenderStates s) const
{

}
