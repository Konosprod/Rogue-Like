#ifndef ROOM_H
#define ROOM_H

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include "Tile.h"
#include "GameEnvironment.h"
#include "Random.h"

#define LAYER 3
#define TILE_WIDTH 32
#define TILE_HEIGHT 32

class Enemy;

enum Dir{Up = 0, Right = 1, Down = 2, Left = 3, Default = 4};

class Room : public sf::Drawable, public sf::Transformable
{
    public:
        Room(bool connexions[], bool hasChest = false, bool isHeal = false);
        virtual ~Room();

        bool setTileset(std::string filename);

        void generateRoom();
        void generateStartRoom();
        void generateHealRoom();
        void generateEventRoom();
        void generateEndRoom();
        void update();
        void deleteZombie(sf::FloatRect r);

        bool wasFound() {return m_found;};
        void setWasFound(bool b){m_found = b;};

        int getX() {return m_x;};
        int getY() {return m_y;};

        void setEnvironment(GameEnvironment* gameEnvironment);

        void drawRoomDebug();

        Tile getTile(int x, int y);
        sf::Vector2i getTP(Dir d);

        bool isZombie(sf::FloatRect r);
        Enemy* getRandomZombie();
        bool isEmpty(){return m_enemies.empty();};

        int getNbZombie(){return ((m_enemies.size() > 0) ? m_enemies.size() : 1);};

    protected:
        void createGround();
        void createWall();
        void createTP();
        void initTab();
        void deleteTab();
        void createMob();
        void createChest();
        void createHealer();
        void createEvent();
        void alterRoom();
        void clearMob();
        void updateTileset();
        void freeTileset();
        bool isTPSetable(int i, int pos);

    private:
        bool* m_connexions;
        unsigned int m_x;
        unsigned int m_y;
        bool m_hasChest;
        bool m_isHeal;
        char*** m_tab;
        int m_count;
        bool m_found;

        GameEnvironment* m_gameEnvironment;
        std::string m_filename;
        sf::VertexArray m_vertices;
        std::map<int, Enemy*> m_enemies;
        Tile*** m_tiles;

        void loadTileset();
        virtual void draw(sf::RenderTarget& t, sf::RenderStates s) const;
};

#endif // ROOM_H
