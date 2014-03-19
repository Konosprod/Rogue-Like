#ifndef ROOM_H
#define ROOM_H

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include "Tile.h"

#define LAYER 3
#define TILE_WIDTH 32
#define TILE_HEIGHT 32

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

        int getX() {return m_x;};
        int getY() {return m_y;};

        void drawRoomDebug();

        Tile getTile(int x, int y);
        sf::Vector2i getTP(Dir d);

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
        bool isTPSetable(int i, int pos);

    private:
        bool* m_connexions;
        unsigned int m_x;
        unsigned int m_y;
        bool m_hasChest;
        bool m_isHeal;
        char*** m_tab;

        sf::Texture m_tileset;
        sf::VertexArray m_vertices;
        Tile*** m_tiles;

        void loadTileset();
        virtual void draw(sf::RenderTarget& t, sf::RenderStates s) const;
};

#endif // ROOM_H
