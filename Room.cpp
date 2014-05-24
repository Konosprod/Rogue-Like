#include "Room.h"
#include "Enemy.h"

Room::Room(bool* connexions, bool hasChest, bool isHeal) :
    m_connexions(connexions), m_hasChest(hasChest), m_isHeal(isHeal), m_count(0)
{
    m_found = false;
}

Room::~Room()
{
    deleteTab();
    freeTileset();
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
    if(m_gameEnvironment->textureManager->getTexture(filename) != NULL)
    {
        m_filename = filename;
        return true;
    }

    return false;
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
        }

        delete[] m_tab[i];
    }
    delete[] m_tab;
}

void Room::createChest()
{
    bool isPlaced = false;

    while(!isPlaced)
    {
        int x = rand()%(m_x-4) + 2;
        int y = rand()%(m_y-4) + 2;

        if(m_tab[1][y][x] == EMPTY_T && m_tab[0][y][x] == FLOOR_T)
        {
            m_tab[1][y][x] = CHEST_T;
            isPlaced = true;
        }
    }
}

void Room::createMob()
{
    int nbMob = rand()%5 + 1;
    int i = 0;

    while(i < nbMob)
    {
        int x = (rand()%(getX() - 4) + 2);
        int y = (rand()%(getY() - 4) + 2);

        if(m_tab[1][y][x] == EMPTY_T)
        {
            x = x*32;
            y = y*32;
            m_enemies[m_count] = new Enemy(m_gameEnvironment, "rc/images/tileset1.png", m_count);
            m_enemies[m_count]->setPosition(x, y);
            m_count++;
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
    m_found = true;
}

void Room::generateEndRoom()
{
    generateRoom();
}

void Room::alterRoom()
{
    int choice = rand()%5;
    int alterX = rand()%3 + 4;
    int alterY = rand()%3 + 4;

    int borderX = m_x-1;
    int borderY = m_y-1;

    switch(choice)
    {
        case 0:
            for(int i=0; i<alterX; i++)
            {
                m_tab[1][alterY][i] = WALL_T;
            }
            for(int j=0; j<alterY; j++)
            {
                m_tab[1][j][alterX] = WALL_T;
            }
            m_tab[1][alterY][alterX] = WALL_T;

            for(int k=0; k<LAYER; k++)
            {
                for(int i=0; i<alterX; i++)
                {
                    for(int j=0; j<alterY; j++)
                    {
                        m_tab[k][j][i] = NON_DRAW_T;
                    }
                }
            }
        break;

        case 1:
            for(int i=borderX; i>borderX-alterX; i--)
            {
                m_tab[1][alterY][i] = WALL_T;
            }
            for(int j=0; j<alterY; j++)
            {
                m_tab[1][j][borderX-alterX] = WALL_T;
            }
            m_tab[1][alterY][borderX-alterX] = WALL_T;


            for(int k=0; k<LAYER; k++)
            {
                for(int i=borderX; i>borderX-alterX; i--)
                {
                    for(int j=0; j<alterY; j++)
                    {
                        m_tab[k][j][i] = NON_DRAW_T;
                    }
                }
            }
        break;

        case 2:
            for(int i=0; i<alterX; i++)
            {
                m_tab[1][borderY-alterY][i] = WALL_T;
            }
            for(int j=borderY; j>borderY-alterY; j--)
            {
                m_tab[1][j][alterX] = WALL_T;
            }
            m_tab[1][borderY-alterY][alterX] = WALL_T;

            for(int k=0; k<LAYER; k++)
            {
                for(int i=0; i<alterX; i++)
                {
                    for(int j=borderY; j>borderY-alterY; j--)
                    {
                        m_tab[k][j][i] = NON_DRAW_T;
                    }
                }
            }
        break;

        case 3:
            for(int i=borderX; i>borderX-alterX; i--)
            {
                m_tab[1][borderY-alterY][i] = WALL_T;
            }
            for(int j=borderY; j>borderY-alterY; j--)
            {
                m_tab[1][j][borderX-alterX] = WALL_T;
            }
            m_tab[1][borderY-alterY][borderX-alterX] = WALL_T;

            for(int k=0; k<LAYER; k++)
            {
                for(int i=borderX; i>borderX-alterX; i--)
                {
                    for(int j=borderY; j>borderY-alterY; j--)
                    {
                    m_tab[k][j][i] = NON_DRAW_T;
                    }
                }
            }
        break;

        case 4:
        {
            int scaleX = rand()%3 + 2;
            int scaleY = rand()%3 + 2;
            int x = borderX/2 - 1;
            int y = borderY/2 - 1;

            for(int i = x; i <= x+scaleX; i++)
            {
                m_tab[1][y][i] = WALL_T;
                m_tab[1][y+scaleY][i] = WALL_T;
            }

            for(int j = y; j <= y+scaleY; j++)
            {
                m_tab[1][j][x] = WALL_T;
                m_tab[1][j][x+scaleX] = WALL_T;
            }

            for(int k = 0; k < LAYER; k++)
            {
                for(int i = x+1; i < x+scaleX; i++)
                {
                    for(int j = y+1; j < y+scaleY; j++)
                    {
                        m_tab[k][j][i] = NON_DRAW_T;
                    }
                }

            }
        }
        break;

        default:
        break;
    }
}

void Room::setEnvironment(GameEnvironment* gameEnvironment)
{
    m_gameEnvironment = gameEnvironment;
}

void Room::freeTileset()
{
    for(int i = 0; i < LAYER; i++)
    {
        for(unsigned int j = 0; j < m_y; j++)
        {
            delete[] m_tiles[i][j];
        }

        delete[] m_tiles[i];
    }

    delete[] m_tiles;
}

void Room::updateTileset()
{
    freeTileset();
    loadTileset();
}

void Room::deleteZombie(sf::FloatRect r)
{
    std::map<int, Enemy*>::iterator itr(m_enemies.begin());

    while(itr != m_enemies.end() && !itr->second->collision(r))
    {
        itr++;
    }

    if(itr->second->collision(r))
    {
        m_enemies.erase(itr->first);
    }
}

void Room::clearMob()
{
    for(unsigned int i = 0; i < m_x; i++)
    {
        for(unsigned int j = 0; j < m_y; j++)
        {
            if(m_tab[1][j][i] == ZOMBIE_T)
            {
                m_tab[1][j][i] = EMPTY_T;
            }
        }
    }
}

void Room::update()
{
    createMob();
    updateTileset();
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

    std::map<int, Enemy*>::const_iterator itr(m_enemies.begin());
    for(; itr != m_enemies.end(); itr++)
    {
        t.draw(*m_enemies.at(itr->first));
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


                r.setTexture(*m_gameEnvironment->textureManager->getTexture(m_filename));

                rect.height = 32;
                rect.width = 32;

                rect.top = (tileValue / (m_gameEnvironment->textureManager->getTexture(m_filename)->getSize().y / 32))*32;
                rect.left = (tileValue % (m_gameEnvironment->textureManager->getTexture(m_filename)->getSize().x / 32))*32;

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
                        tile.setBlocking(true);
                    break;

                    case ZOMBIE_T:
                        tile.setBlocking(true);
                        tile.setZombie(true);
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

bool Room::isZombie(sf::FloatRect r)
{
    bool res = false;
    std::map<int, Enemy*>::const_iterator itr(m_enemies.begin());

    for(; itr != m_enemies.end() && !res; itr++)
    {
        res = itr->second->collision(r);
    }
    return res;
}


Enemy* Room::getRandomZombie()
{
    int total = 0;
    std::vector<int> listKey;
    std::map<int, Enemy*>::const_iterator itr(m_enemies.begin());

    for(; itr != m_enemies.end(); itr++)
    {
        listKey.push_back(itr->first);
        total++;
    }

    int i = Random::Get(0, total-1);
    return m_enemies.at(listKey.at(i));
}

