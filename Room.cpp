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

void Room::drawRoomDebug()
{
    for (int y = 0; y < m_y; y++)
    {
        for (int x = 0; x < m_x; x++)
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
        if(m_connexions[i])
        {
            if(i%2 == 0)
            {
                pos = ((m_x/4) + rand()%(m_x/2));

                if(i == 0)
                {
                    m_tab[1][0][pos] = N_TP_T;
                }
                else
                {
                    m_tab[1][m_y-1][pos] = S_TP_T;
                }
            }
            else
            {
                pos = ((m_y/4) + rand()%(m_y/2));

                if(i == 3)
                {
                    m_tab[1][pos][0] = O_TP_T;
                }
                else
                {
                    m_tab[1][pos][m_x-1] = E_TP_T;
                }
            }
        }
    }
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

    for(int i = 0; i < nbMob; i++)
    {
        int y = rand()%(m_y-4) + 2;
        int x = rand()%(m_x-4) + 2;

        if (m_tab[1][y][x] == 0)
        {
            m_tab[1][y][x] = ZOMBIE_T;
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
}

void Room::loadTileset()
{
    if(!m_tileset.loadFromFile("rc/test.png"))
        std::cerr << "Erreur : impossible de charger test.png" << std::endl;


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

                if((tileValue == N_TP_T) || (tileValue == E_TP_T) || (tileValue == S_TP_T) || (tileValue == O_TP_T))
                    tile.setIsTP(true);
                if(tileValue == WALL_T)
                    tile.setBlocking(true);
                else
                    tile.setBlocking(false);

                if(tileValue == CHEST_T)
                    tile.setAnimated(true);

                m_tiles[i][j][k] = tile;
            }
        }
    }
}


