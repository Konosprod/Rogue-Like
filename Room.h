#ifndef ROOM_H
#define ROOM_H

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <SFML/Graphics.hpp>

#define LAYER 3
#define TILE_WIDTH 32
#define TILE_HEIGHT 32

class Room : public sf::Drawable, public sf::Transformable
{
    public:
        Room(bool connexions[], bool hasChest = false, bool isHeal = false);
        virtual ~Room();

        void generateRoom();
        void generateStartRoom();
        void generateHealRoom();
        void generateEventRoom();

        int getX() {return m_x;};
        int getY() {return m_y;};

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

    private:
        bool* m_connexions;
        unsigned int m_x;
        unsigned int m_y;
        bool m_hasChest;
        bool m_isHeal;
        char*** m_tab;

        sf::Texture m_tileset;
        sf::VertexArray m_vertices;
        std::vector<sf::Sprite> m_rect;

        void loadTileset();
        virtual void draw(sf::RenderTarget& t, sf::RenderStates s) const;
};

#endif // ROOM_H
