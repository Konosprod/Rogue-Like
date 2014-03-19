#include "Room.h"

Room::Room(bool* connexions, bool hasChest, bool isHeal) :
    m_connexions(connexions), m_hasChest(hasChest), m_isHeal(isHeal)
{

}

Room::~Room()
{
    deleteTab();
    delete [] m_connexions;
}

void Room::createGround()
{
    for(unsigned int i = 0; i < m_y; i++)
    {
        for(unsigned int j = 0; j < m_x; j++)
        {
            m_tab[0][i][j] = FLOOR_T;
        }
    }
}

bool Room::setTileset(std::string filename)
{
    if(!m_tileset.loadFromFile(filename))
    {
        std::cerr << "Erreur : impossible de charger : " << filename << std::endl;
        return false;
    }

    return true;
}

void Room::drawRoomDebug()
{
    for (unsigned int y = 0; y < m_y; y++)
    {
        for (unsigned int x = 0; x < m_x; x++)
        {
            std::cout << (int)m_tab[1][y][x];
        }
        std::cout << std::endl;
    }
}


void Room::createEvent()
{
    bool isPlaced = false;

    while(!isPlaced)
    {
        int x = rand()%(m_x-4) + 2;
        int y = rand()%(m_y-4) + 2;

        if(m_tab[1][y][x] == 0)
        {
            m_tab[1][y][x] = STAIRS_T;
            isPlaced = true;
        }
    }
}

void Room::generateEventRoom()
{
    m_x = rand()%5+12;
    m_y = rand()%5+12;

    m_tab = new char**[LAYER];

    for(int i = 0; i < LAYER; i++)
    {
        m_tab[i] = new char*[m_y];

        for(unsigned int j = 0; j < m_y; j++)
        {
            m_tab[i][j] = new char[m_x];
        }
    }

    initTab();

    createGround();
    createWall();
    createTP();
    createEvent();

    loadTileset();
}

void Room::generateHealRoom()
{
    m_x = rand()%5+12;
    m_y = rand()%5+12;

    m_tab = new char**[LAYER];

    for(int i = 0; i < LAYER; i++)
    {
        m_tab[i] = new char*[m_y];

        for(unsigned int j = 0; j < m_y; j++)
        {
            m_tab[i][j] = new char[m_x];
        }
    }

    initTab();

    createGround();
    createWall();
    createTP();
    createHealer();

    loadTileset();
}

void Room::createHealer()
{
    bool isPlaced = false;

    while(!isPlaced)
    {
        int x = rand()%(m_x-4) + 2;
        int y = rand()%(m_y-4) + 2;

        if(m_tab[1][y][x] == 0)
        {
            m_tab[1][y][x] = HEALER_T;
            isPlaced = true;
        }
    }
}

void Room::createWall()
{
    for(unsigned int i = 0; i < m_x; i++)
    {
        m_tab[1][0][i] = WALL_T;
        m_tab[1][m_y-1][i] = WALL_T;
    }

    for(unsigned int i = 0; i < m_y; i++)
    {
        m_tab[1][i][0] = WALL_T;
        m_tab[1][i][m_x-1] = WALL_T;
    }
}

void Room::createTP()
{
    int pos = 0;
    for(int i = 0; i < 4; i++)
    {
        bool done = false;
        if(m_connexions[i])
        {
            while(!done)
            {
                if(i%2 == 0 )
                {
                    pos = ((m_x/4) + rand()%(m_x/2));

                    if(i == 0 && isTPSetable(i, pos))
                    {
                        m_tab[1][0][pos] = N_TP_T;
                        done = true;
                    }
                    else if(isTPSetable(i, pos))
                    {
                        m_tab[1][m_y-1][pos] = S_TP_T;
                        done = true;
                    }
                }
                else
                {
                    pos = ((m_y/4) + rand()%(m_y/2));

                    if(i == 3 && isTPSetable(i, pos))
                    {
                        m_tab[1][pos][0] = O_TP_T;
                        done = true;
                    }
                    else if(isTPSetable(i, pos))
                    {
                        m_tab[1][pos][m_x-1] = E_TP_T;
                        done = true;
                    }
                }
            }
        }
        done = false;
    }
}



bool Room::isTPSetable(int i, int pos)
{
    bool res = false;

    switch(i)
    {
        case 0:
        {
            if(m_tab[1][0][pos] == 2 && m_tab[1][1][pos] != 2)
                res = true;

            break;
        }

        case 1:
        {
            if(m_tab[1][pos][m_x-1] == 2 && m_tab[1][pos][m_x-2] != 2)
                res = true;

            break;
        }

        case 2:
        {
            if(m_tab[1][m_y-1][pos] == 2 && m_tab[1][m_y-2][pos] != 2)
                res = true;

            break;
        }

        case 3:
        {
            if(m_tab[1][pos][0] == 2 && m_tab[1][pos][1] != 2)
                res = true;

            break;
        }
    }

    return res;
}

void Room::initTab()
{
    for(int i = 0; i < LAYER; i++)
    {
        for(unsigned int j = 0; j < m_y; j++)
        {
            for(unsigned int k = 0; k < m_x; k++)
            {
                m_tab[i][j][k] = 0;
            }
        }
    }
}

void Room::deleteTab()
{
    for(int i = 0; i < LAYER; i++)
    {
        for(unsigned int j = 0; j < m_y; j++)
        {
            delete[] m_tab[i][j];
            delete[] m_tiles[i][j];
        }

        delete[] m_tab[i];
        delete[] m_tiles[i];
    }

    delete[] m_tiles;
    delete[] m_tab;
}

void Room::createChest()
{
    bool isPlaced = false;

    while(!isPlaced)
    {
        int x = rand()%(m_x-4) + 2;
        int y = rand()%(m_y-4) + 2;

        if(m_tab[1][y][x] == 0)
        {
            m_tab[1][y][x] = CHEST_T;
            isPlaced = true;
        }
    }
}

void Room::createMob()
{
    int nbMob = rand()%6;

    int i = 0;

    while(i < nbMob)
    {
        int y = rand()%(m_y-4) + 2;
        int x = rand()%(m_x-4) + 2;

        if (m_tab[1][y][x] == 0 && m_tab[0][y][x] != 0)
        {
            m_tab[1][y][x] = ZOMBIE_T;
            i++;
        }
    }
}

void Room::generateStartRoom()
{
    m_x = rand()%5+12;
    m_y = rand()%5+12;

    m_tab = new char**[LAYER];

    for(int i = 0; i < LAYER; i++)
    {
        m_tab[i] = new char*[m_y];

        for(unsigned int j = 0; j < m_y; j++)
        {
            m_tab[i][j] = new char[m_x];
        }
    }

    initTab();

    createGround();
    createWall();
    createTP();

    loadTileset();
}

void Room::generateEndRoom()
{
    generateRoom();
}

void Room::alterRoom()
{
    int choice = rand()%4;
    int alterX = rand()%3 + 4;
    int alterY = rand()%3 + 4;
    int borderX = m_x-1;
    int borderY = m_y-1;

    switch(choice)
    {
        case 0:
            for(int k = 0; k < LAYER; k++)
            {
                for(int i = 0; i < alterX; i++)
                {
                    for(int j = 0; j < alterY; j++)
                    {
                        m_tab[k][j][i] = 0;
                    }
                }
            }
            for(int i = 0; i < alterY; i++)
            {
                m_tab[1][i][alterX] = 2;
            }
            for(int i = 0; i < alterX; i++)
            {
                m_tab[1][alterY][i] = 2;
            }

            m_tab[1][alterY][alterX] = 2;
        break;

        case 1:
            for(int i = borderX; i > borderX - alterX; i--)
            {
                m_tab[1][alterY][i] = 2;
            }
            for(int j=0; j<alterY; j++)
            {
                m_tab[1][j][borderX-alterX] = 2;
            }

            for(int k = 0; k < LAYER; k++)
            {
                for(int i=borderX; i>borderX-alterX; i--)
                {
                    for(int j=0; j<alterY; j++)
                    {
                        m_tab[k][j][i] = 0;
                    }
                }
            }

            m_tab[1][alterY][borderX-alterX] = 2;
        break;

        case 2:
             for(int i=0; i<alterX; i++)
             {
                 m_tab[1][borderY-alterY][i] = 2;
             }

             for(int j=borderY; j>borderY-alterY; j--)
             {
                 m_tab[1][j][alterX] = 2;
             }

             for(int k = 0; k < LAYER; k++)
             {
                for(int i=0; i<alterX; i++)
                {
                    for(int j=borderY; j>borderY-alterY; j--)
                    {
                        m_tab[k][j][i] = 0;
                    }
                }
             }

             m_tab[1][borderY-alterY][alterX] = 2;
        break;

        case 3:
            for(int i=borderX; i>borderX-alterX; i--)
            {
                m_tab[1][borderY-alterY][i] = 2;
            }
            for(int j=borderY; j>borderY-alterY; j--)
            {
                m_tab[1][j][borderX-alterX] = 2;
            }

            for(int k = 0; k < LAYER; k++)
            {
                for(int i=borderX; i>borderX-alterX; i--)
                {
                    for(int j=borderY; j>borderY-alterY; j--)
                    {
                        m_tab[k][j][i] = 0;
                    }
                }
            }

            m_tab[1][borderY-alterY][borderX-alterX] = 2;

        break;

        default:
        break;
    }
}

void Room::generateRoom()
{
    m_x = rand()%5+12;
    m_y = rand()%5+12;

    m_tab = new char**[LAYER];

    for(int i = 0; i < LAYER; i++)
    {
        m_tab[i] = new char*[m_y];

        for(unsigned int j = 0; j < m_y; j++)
        {
            m_tab[i][j] = new char[m_x];
        }
    }

    initTab();

    createGround();
    createWall();
    alterRoom();
    createTP();
    createMob();


    if(m_hasChest)
    {
        createChest();
    }

    loadTileset();
}

Tile Room::getTile(int x, int y)
{
    return m_tiles[1][y][x];
}

sf::Vector2i Room::getTP(Dir d)
{
    sf::Vector2i v;
    int  i = 0;
    if(d == Up)
    {
        while(m_tab[1][0][i] != N_TP_T)
        {
            i++;
        }
        v.y = 0;
        v.x = i;
    }

    if(d == Right)
    {
        while(m_tab[1][i][m_x - 1] != E_TP_T)
        {
            i++;
        }

        v.y = i;
        v.x = m_x-1;
    }

    if(d == Down)
    {
        while(m_tab[1][m_y-1][i] != S_TP_T)
        {
            i++;
        }
        //std::cout << (int)m_tab[1][m_y-1][i] << std::endl;
        v.y = m_y-1;
        v.x = i;
    }

    if(d == Left)
    {
        while(m_tab[1][i][0] != O_TP_T)
        {
            i++;
        }

        v.y = i;
        v.x = 0;
    }

    //std::cout << v.x << " " << v.y << std::endl;

    return v;
}

void Room::draw(sf::RenderTarget& t, sf::RenderStates s) const
{
    for(int i = 0; i < LAYER; i++)
    {
        for(unsigned int j = 0; j < m_y; j++)
        {
            for(unsigned int k = 0; k < m_x; k++)
            {
                t.draw(m_tiles[i][j][k].getSprite());
            }
        }
    }

    (void)s;
}

void Room::loadTileset()
{
    m_tiles = new Tile**[LAYER];

    for(int i = 0; i < LAYER; i++)
    {
        m_tiles[i] = new Tile*[m_y];

        for(unsigned int j = 0; j < m_y; j++)
        {
            m_tiles[i][j] = new Tile[m_x];
        }
    }

    for(int i = 0; i < LAYER; i++)
    {
        for(unsigned int j = 0; j < m_y; j++)
        {
            for(unsigned int k = 0; k < m_x; k++)
            {
                Tile tile;
                sf::Sprite r;
                sf::IntRect rect;
                int tileValue = m_tab[i][j][k];


                r.setTexture(m_tileset);

                rect.height = 32;
                rect.width = 32;

                rect.top = (tileValue / (m_tileset.getSize().y / 32))*32;
                rect.left = (tileValue % (m_tileset.getSize().x / 32))*32;

                r.setTextureRect(rect);
                r.setPosition(k*TILE_HEIGHT, j*TILE_WIDTH);

                tile.setSprite(r);

                switch(tileValue)
                {
                    case N_TP_T:
                    case E_TP_T:
                    case S_TP_T:
                    case O_TP_T:
                        tile.setIsTP(true);
                    break;

                    case STAIRS_T:
                        tile.setIsStairs(true);
                        tile.setIsTP(true);
                    break;

                    case WALL_T:
                    case ZOMBIE_T:
                        tile.setBlocking(true);
                    break;

                    case HEALER_T:
                        tile.setBlocking(true);
                        tile.setHealer(true);
                    break;

                    case CHEST_T:
                        tile.setBlocking(true);
                        tile.setAnimated(true);
                        tile.setChest(true);
                    break;

                    default:
                        tile.setBlocking(false);
                    break;

                }

                m_tiles[i][j][k] = tile;
            }
        }
    }
}


