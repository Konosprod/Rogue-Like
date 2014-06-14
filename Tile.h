#ifndef TILE_H
#define TILE_H

#include <SFML/Graphics.hpp>

#define EMPTY_T 0
#define FLOOR_T 1
#define WALL_TOP_T 2
#define WALL_RIGHT_T 3
#define WALL_BOT_T 4
#define WALL_LEFT_T 5
#define DOOR_TOP_C_T 6
#define DOOR_TOP_O_T 7
#define DOOR_RIGHT_C_T 8
#define DOOR_RIGHT_O_T 9
#define DOOR_BOT_C_T 10
#define DOOR_BOT_O_T 11
#define DOOR_LEFT_C_T 12
#define DOOR_LEFT_O_T 13
#define CHEST_C_T 14
#define CHEST_O_T 15
#define LAMP_T 16
#define HEALER_T 253
#define STAIRS_T 254
#define NON_DRAW_T 255

class Tile
{
    public:
        Tile(bool animated = false);
        virtual ~Tile();

        enum TileState{
            Blocking = 0,
            TP = 1,
            Stairs = 2,
            Animated = 3,
            Chest = 4,
            Healer = 5,
            Zombie = 6,
            StateMax = 7
        };

        sf::Sprite getSprite() const;

        bool isBlocking();
        bool isTP();
        bool isAnimated();
        bool isStairs();
        bool isHealer();
        bool isChest();
        bool isZombie();

        void setBlocking(bool b);
        void setIsTP(bool val);
        void setAnimated(bool val);
        void setIsStairs(bool val);
        void setSprite(sf::Sprite val);
        void setHealer(bool b);
        void setChest(bool b);
        void setZombie(bool b);

    protected:

    private:
        sf::Sprite m_sprite;
        bool m_properties[StateMax];
};

#endif // TILE_H
