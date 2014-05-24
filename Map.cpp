#include "Map.h"

/**TODO:

**/

Map::Map(GameEnvironment* gameEnvironment, std::string tilesetFilename, int floorMax) : m_tileset(tilesetFilename),
                                                                                        m_floorMax(floorMax),
                                                                                        m_gameEnvironment(gameEnvironment)
{
    m_floor = 0;
    m_done = false;
    generateMap();
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

void Map::drawMiniMap()
{
    std::cout << "-------------------------" << std::endl;

    for(int i = 0; i < SIZE_MAX_TAB; i++)
    {
        for(int j = 0; j < SIZE_MAX_TAB; j++)
        {
            if(m_tab[i][j] != 0)
            {
                if(m_rooms[i][j]->wasFound())
                {
                    std::cout << "*";
                }
            }
            else
            {
                std::cout << " ";
            }
        }

        std::cout << std::endl;
    }

    std::cout << "-------------------------" << std::endl;
}

bool Map::update(Character& c)
{
    bool fade = false;

    switch(c.getDirection())
    {
        case Down:
            if(isChangingTile(c))
            {
                if(!isChangingFloor(c))
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
            if(isChangingTile(c))
            {
                if(!isChangingFloor(c))
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
            if(isChangingTile(c))
            {
                if(!isChangingFloor(c))
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
            if(isChangingTile(c))
            {
                if(!isChangingFloor(c))
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

void Map::updateZombie(Character& c)
{
    m_rooms[m_currentPos.y][m_currentPos.x]->deleteZombie(c.getGlobalBounds());
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

    m_rooms[m_currentPos.y][m_currentPos.x]->setWasFound(true);

    if(m_tab[m_currentPos.y][m_currentPos.x] == MOB_ROOM)
    {
        m_rooms[m_currentPos.y][m_currentPos.x]->update();
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

                m_rooms[j][i]->setEnvironment(m_gameEnvironment);
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
                else if(m_tab[j][i] == MOB_ROOM)
                {
                    m_rooms[j][i]->generateRoom();
                }
            }
        }
    }

    m_currentPos = m_randomizer.findStart();
}

Point Map::currentRoom()
{
    return m_currentPos;
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
            return false;
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

bool Map::isEngagingFight(Character& c)
{
    return m_rooms[m_currentPos.y][m_currentPos.x]->isZombie(c.getGlobalBounds());
}

bool Map::isChangingTile(Character& c)
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
        return m_rooms[m_currentPos.y][m_currentPos.x]->getTile(xmin, ymin).isTP();
    }

    return (m_rooms[m_currentPos.y][m_currentPos.x]->getTile(xmin, ymin).isTP()) ||
             (m_rooms[m_currentPos.y][m_currentPos.x]->getTile(xmax, ymax).isTP());
}

bool Map::isChangingFloor(Character& c)
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
        return m_rooms[m_currentPos.y][m_currentPos.x]->getTile(xmin, ymin).isStairs();
    }

    return (m_rooms[m_currentPos.y][m_currentPos.x]->getTile(xmin, ymin).isStairs()) ||
             (m_rooms[m_currentPos.y][m_currentPos.x]->getTile(xmax, ymax).isStairs());
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
            if(m_tab[i][j] == MOB_ROOM)
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

Room* Map::getCurrentRoom()
{
    return m_rooms[currentRoom().y][currentRoom().x];
}



bool Map::isValidMoveZombie(Enemy& c)
{
    int chance = Random::Get(0,100);
    int newDir = Random::Get(0,3);
    switch (c.getPercentage())
    {
        case 91:
            if(chance < 91)
            {
                c.setDirection(c.getOldDirection());
            }
            else
            {
                while(newDir == c.getOldDirection())
                {
                    newDir = Random::Get(0, 3);
                }

                c.setDirection(static_cast<Dir>(newDir));
            }
        break;
        case 73:
            if(chance < 73)
            {
                c.setDirection(c.getOldDirection());
            }
            else
            {
                while(newDir == c.getOldDirection())
                {
                    newDir = Random::Get(0, 3);
                }

                c.setDirection(static_cast<Dir>(newDir));
            }
        break;
        case 46:
            if(chance < 46)
            {
                c.setDirection(c.getOldDirection());
            }
            else
            {
                while(newDir == c.getOldDirection())
                {
                    newDir = Random::Get(0, 3);
                }

                c.setDirection(static_cast<Dir>(newDir));
            }
        break;
        case 25:
            c.setDirection(static_cast<Dir>(Random::Get(0,3)));
        break;
    }

    c.setPercentage(91);


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
            return false;
        break;
    }

    if((((c.getDirection() == Up) || (c.getDirection() == Down)) && ((int)c.getPosition().x%32 == 0)) ||
       (((c.getDirection() == Left) || (c.getDirection() == Right)) && ((int)c.getPosition().y%32 == 0)))
    {
        return (!(m_rooms[m_currentPos.y][m_currentPos.x]->getTile(xmin, ymin).isBlocking()) &&
                (!isChangingTile(c)));
    }

    return (!((m_rooms[m_currentPos.y][m_currentPos.x]->getTile(xmin, ymin).isBlocking()) ||
             (m_rooms[m_currentPos.y][m_currentPos.x]->getTile(xmax, ymax).isBlocking()))) &&
             (!isChangingTile(c));
}



