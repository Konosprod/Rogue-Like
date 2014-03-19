#include "Map.h"

/**TODO:

**/

Map::Map(std::string tilesetFilename, std::string soundFilename, int floorMax) : m_tileset(tilesetFilename), m_floorMax(floorMax)
{
    m_floor = 0;
    //m_music.openFromFile(soundFilename);
    //m_music.setLoop(true);
    //m_music.play();
    m_done = false;
    generateMap();
    (void)soundFilename;
}

Map::~Map()
{
    freeRooms();
    freeTab(m_tab);
}

void Map::freeRooms()
{
    for(int i = 0; i < SIZE_MAX_TAB; i++)
    {
        for(int j = 0; j < SIZE_MAX_TAB; j++)
        {
            delete[] m_rooms[i];
        }
    }
    delete[] m_rooms;
}

bool Map::update(Character& c)
{
    bool fade = false;

    switch(c.getDirection())
    {
        case Down:
            if(isChangingTile(c.getPosition().x, c.getPosition().y+32))
            {
                if(!isChangingFloor(c.getPosition().x, c.getPosition().y+32))
                {
                    sf::Vector2i v;
                    moveRoom(Down);
                    v = getTP(Up);
                    c.setPosition((v.x*32), 32);
                }
                else
                {
                    nextFloor();
                    c.setPosition(64, 64);
                }
                fade = true;
            }
        break;

        case Right:
            if(isChangingTile(c.getPosition().x+32, c.getPosition().y))
            {
                if(!isChangingFloor(c.getPosition().x+32, c.getPosition().y))
                {
                    sf::Vector2i v;
                    moveRoom(Right);
                    v = getTP(Left);
                    c.setPosition((v.x+1)*32, v.y*32);
                }
                else
                {
                    nextFloor();
                    c.setPosition(64, 64);
                }
                fade = true;
            }
        break;

        case Up:
            if(isChangingTile(c.getPosition().x, c.getPosition().y-32))
            {
                if(!isChangingFloor(c.getPosition().x, c.getPosition().y-32))
                {
                    sf::Vector2i v;
                    moveRoom(Up);
                    v = getTP(Down);
                    c.setPosition(v.x*32, (v.y-1)*32);
                }
                else
                {
                    nextFloor();
                    c.setPosition(64, 64);
                }
                fade = true;
            }
        break;

        case Left:
            if(isChangingTile(c.getPosition().x-32, c.getPosition().y))
            {
                if(!isChangingFloor(c.getPosition().x-32, c.getPosition().y))
                {
                    sf::Vector2i v;
                    moveRoom(Left);
                    v = getTP(Right);
                    c.setPosition((v.x-1)*32, v.y*32);
                }
                else
                {
                    nextFloor();
                    c.setPosition(64, 64);
                }
                fade = true;

            }
        break;

        default:
        break;
    }

    return fade;
}

void Map::freeTab(int** t)
{
    for(unsigned int i = 0; i < SIZE_MAX_TAB; i++)
    {
        delete[] t[i];
    }
    delete[] t;
}

void Map::generateMap()
{
    if(m_done == true)
    {
        freeTab(m_tab);
        freeRooms();
        m_done = false;
    }
    m_tab = new int*[SIZE_MAX_TAB];

    for(unsigned int i = 0; i < SIZE_MAX_TAB; i++)
    {
        m_tab[i] = new int[SIZE_MAX_TAB];
    }

    m_randomizer.setTab(m_tab);
    m_randomizer.setFloor(m_floor);
    m_randomizer.setFloorMax(m_floorMax);
    m_randomizer.generateMap();

    createRooms();

    m_done = true;
}

void Map::moveRoom(Dir d)
{
    if(d == Up)
    {
        m_currentPos.y--;
    }
    else if(d == Right)
    {
        m_currentPos.x++;
    }
    else if(d == Down)
    {
        m_currentPos.y++;
    }
    else
    {
        m_currentPos.x--;
    }
}

void Map::getNbRoom()
{
    for(unsigned int i = 0; i < SIZE_MAX_TAB; i++)
    {
        for(unsigned int j = 0; j < SIZE_MAX_TAB; j++)
        {
            if(m_tab[i][j] != 0)
            {
                m_nbRoom++;
            }
        }
    }
}

void Map::createRooms()
{
    m_rooms = new Room**[SIZE_MAX_TAB];

    for(unsigned int i = 0; i < SIZE_MAX_TAB; i++)
    {
        m_rooms[i] = new Room*[SIZE_MAX_TAB];
    }

    for(unsigned int i = 0; i < SIZE_MAX_TAB; i++)
    {
        for(unsigned int j = 0; j < SIZE_MAX_TAB; j++)
        {
            if(m_tab[j][i] != 0)
            {
                m_rooms[j][i] = new Room(m_randomizer.dirRoomCo(i, j), (m_tab[j][i] == CHEST_ROOM) ? true : false, (m_tab[j][i] == HEAL_ROOM) ? true : false);

                m_rooms[j][i]->setTileset(m_tileset);

                if(m_tab[j][i] == HEAL_ROOM)
                {
                    m_rooms[j][i]->generateHealRoom();
                }
                else if(m_tab[j][i] == START_ROOM)
                {
                    m_rooms[j][i]->generateStartRoom();
                }
                else if(m_tab[j][i] == EVENT_ROOM)
                {
                    m_rooms[j][i]->generateEventRoom();
                }
                else if(m_tab[j][i] == CHEST_ROOM)
                {
                    m_rooms[j][i]->generateRoom();
                }
                else if(m_tab[j][i] == END_ROOM)
                {
                    m_rooms[j][i]->generateEndRoom();
                }
                else
                {
                    m_rooms[j][i]->generateRoom();
                }
            }
        }
    }

    m_currentPos = m_randomizer.findStart();
}

void Map::currentRoom()
{
    std::cout << "currentRoom : y : " << m_currentPos.y << " x : " << m_currentPos.x << std::endl;
}

bool Map::isValidMove(Character& c)
{
    int ymin = 0;
    int xmin = 0;
    int xmax = 0;
    int ymax = 0;

    switch(c.getDirection())
    {
        case Up:
        xmin = ((int)c.getPosition().x)/32;
        ymin = ((int)c.getPosition().y-1)/32;
        xmax = ((int)c.getPosition().x + c.getBounds().x)/32;
        ymax = ((int)c.getPosition().y-1)/32;
        break;

        case Right:
        xmin = ((int)c.getPosition().x + c.getBounds().x+1)/32;
        ymin = ((int)c.getPosition().y)/32;
        xmax = ((int)c.getPosition().x + c.getBounds().x+1)/32;
        ymax = ((int)c.getPosition().y + c.getBounds().y)/32;
        break;

        case Down:
        xmin = ((int)c.getPosition().x)/32;
        ymin = ((int)c.getPosition().y + c.getBounds().y+1)/32;
        xmax = ((int)c.getPosition().x + c.getBounds().x)/32;
        ymax = ((int)c.getPosition().y + c.getBounds().y+1)/32;
        break;

        case Left:
        xmin = ((int)c.getPosition().x-1)/32;
        ymin = ((int)c.getPosition().y)/32;
        xmax = ((int)c.getPosition().x-1)/32;
        ymax = ((int)c.getPosition().y + c.getBounds().y)/32;
        break;

        default:
        break;
    }

    if((((c.getDirection() == Up) || (c.getDirection() == Down)) && ((int)c.getPosition().x%32 == 0)) ||
       (((c.getDirection() == Left) || (c.getDirection() == Right)) && ((int)c.getPosition().y%32 == 0)))
    {
        return !(m_rooms[m_currentPos.y][m_currentPos.x]->getTile(xmin, ymin).isBlocking());
    }

    return !((m_rooms[m_currentPos.y][m_currentPos.x]->getTile(xmin, ymin).isBlocking()) ||
             (m_rooms[m_currentPos.y][m_currentPos.x]->getTile(xmax, ymax).isBlocking()));
}

bool Map::isChangingTile(int x, int y)
{
    return (m_rooms[m_currentPos.y][m_currentPos.x]->getTile(x/32, y/32).isTP());
}

bool Map::isChangingFloor(int x, int y)
{
    return (m_rooms[m_currentPos.y][m_currentPos.x]->getTile(x/32, y/32).isStairs());
}

void Map::nextFloor()
{
    m_floor++;
    generateMap();
}


sf::Vector2i Map::getTP(Dir d)
{
    return m_rooms[m_currentPos.y][m_currentPos.x]->getTP(d);
}

void Map::drawMapDebug()
{
   for (unsigned int i=0; i<SIZE_MAX_TAB; i++)
    {
        for (unsigned int j=0; j<SIZE_MAX_TAB; j++)
        {
            if(m_tab[i][j] == 1)
            {
                std::cout << "*";
            }
            else if (m_tab[i][j] == START_ROOM)
            {
                std::cout << "O";
            }
            else if (m_tab[i][j] == EVENT_ROOM)
            {
                std::cout << "X";
            }
            else if (m_tab[i][j] == CHEST_ROOM)
            {
                std::cout << "C";
            }
            else if (m_tab[i][j] == HEAL_ROOM)
            {
                std::cout << "H";
            }
            else if(m_tab[i][j] == END_ROOM)
            {
                std::cout << "E";
            }
            else
            {
                std::cout << " ";
            }
        }
        std::cout << std::endl;
    }
}

Event Map::checkEvent(Character& c)
{
    Event e = None;
    int xmin = 0;
    int ymin = 0;

    switch(c.getDirection())
    {
        case Up:
        xmin = ((int)c.getPosition().x)/32;
        ymin = ((int)c.getPosition().y-1)/32;
        break;

        case Right:
        xmin = ((int)c.getPosition().x + c.getBounds().x+1)/32;
        ymin = ((int)c.getPosition().y)/32;
        break;

        case Down:
        xmin = ((int)c.getPosition().x)/32;
        ymin = ((int)c.getPosition().y + c.getBounds().y+1)/32;
        break;

        case Left:
        xmin = ((int)c.getPosition().x-1)/32;
        ymin = ((int)c.getPosition().y)/32;
        break;

        default:
        break;
    }

    if(m_rooms[m_currentPos.y][m_currentPos.x]->getTile(xmin, ymin).isChest())
    {
        e = Chest;
    }
    if(m_rooms[m_currentPos.y][m_currentPos.x]->getTile(xmin, ymin).isHealer())
    {
        e = Healer;
    }

    return e;
}

void Map::openChest()
{
    std::cout << "Open chest" << std::endl;
}

void Map::draw(sf::RenderTarget& t, sf::RenderStates s) const
{
    t.draw(*m_rooms[m_currentPos.y][m_currentPos.x]);
    (void)s;
}


