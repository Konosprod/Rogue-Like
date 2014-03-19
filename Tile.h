#ifndef TILE_H
#define TILE_H

#include <SFML/Graphics.hpp>

#define EMPTY_T 0
#define FLOOR_T 1
#define WALL_T 2
#define O_TP_T 3
#define N_TP_T 4
#define E_TP_T 5
#define S_TP_T 6
#define ZOMBIE_T 7
#define CHEST_T 8
#define HEALER_T 9
#define STAIRS_T 10
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
    Healer = 5
};

        sf::Sprite getSprite() const;

        bool isBlocking();
        bool isTP();
        bool isAnimated();
        bool isStairs();
        bool isHealer();
        bool isChest();

        void setBlocking(bool b);
        void setIsTP(bool val);
        void setAnimated(bool val);
        void setIsStairs(bool val);
        void setSprite(sf::Sprite val);
        void setHealer(bool b);
        void setChest(bool b);

    protected:

    private:
        sf::Sprite m_sprite;
        bool m_properties[Healer+1];
};

#endif // TILE_H
