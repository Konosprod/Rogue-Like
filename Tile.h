#ifndef TILE_H
#define TILE_H

#include <SFML/Graphics.hpp>


class Tile
{
    public:
        Tile(bool animated = false);
        virtual ~Tile();
        sf::Sprite getSprite() const { return m_sprite; }
        void setSprite(sf::Sprite val);

    protected:

    private:
        sf::Sprite m_sprite;
        bool m_animated;
};

#endif // TILE_H
