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
            m_tab[0][i][j] = 1;
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
            m_tab[1][y][x] = 9;
            isPlaced = true;
        }
    }
}

void Room::createWall()
{
    for(unsigned int i = 0; i < m_x; i++)
    {
        m_tab[1][0][i] = 2;
        m_tab[1][m_y-1][i] = 2;
    }

    for(unsigned int i = 0; i < m_y; i++)
    {
        m_tab[1][i][0] = 2;
        m_tab[1][i][m_x-1] = 2;
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
                    m_tab[1][0][pos] = 3;
                }
                else
                {
                    m_tab[1][m_y-1][pos] = 5;
                }
            }
            else
            {
                pos = ((m_y/4) + rand()%(m_y/2));

                if(i == 3)
                {
                    m_tab[1][pos][0] = 4;
                }
                else
                {
                    m_tab[1][pos][m_x-1] = 6;
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
        }

        delete[] m_tab[i];
    }

    delete m_tab;
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
            m_tab[1][y][x] = 8;
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
            m_tab[1][y][x] = 7;
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

void Room::draw(sf::RenderTarget& t, sf::RenderStates s) const
{
    for(unsigned int i = 0; i < m_rect.size(); i++)
    {
        t.draw(m_rect[i]);
    }
}

void Room::loadTileset()
{
    if(!m_tileset.loadFromFile("rc/test.png"))
    {
        std::cerr << "Erreur : impossible de charger test.png" << std::endl;
    }

    for(int i = 0; i < LAYER; i++)
    {
        for(unsigned int j = 0; j < m_x; j++)
        {
            for(unsigned int k = 0; k < m_y; k++)
            {
                sf::Sprite r;
                r.setTexture(m_tileset);
                sf::IntRect rect;

                rect.height = 32;
                rect.width = 32;

                rect.top = (m_tab[i][k][j] / (m_tileset.getSize().x / 32))*32;
                rect.left = (m_tab[i][k][j] % (m_tileset.getSize().x / 32))*32;

                r.setTextureRect(rect);
                r.setPosition(k*TILE_HEIGHT, j*TILE_WIDTH);
                m_rect.push_back(r);
            }
        }
    }
}


