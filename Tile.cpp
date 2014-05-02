#include "Tile.h"

Tile::Tile(bool animated)
{
    for(int i = 0; i < StateMax; i++)
    {
        m_properties[i] = false;
    }

    m_properties[Animated] = animated;
}

Tile::~Tile()
{

}

void Tile::setSprite(sf::Sprite val)
{
    m_sprite.setColor(val.getColor());
    m_sprite.setOrigin(val.getOrigin());
    m_sprite.setPosition(val.getPosition());
    m_sprite.setRotation(val.getRotation());
    m_sprite.setTexture(*(val.getTexture()));
    m_sprite.setTextureRect(val.getTextureRect());
}

sf::Sprite Tile::getSprite() const
{
    return m_sprite;
}

bool Tile::isBlocking()
{
    return m_properties[Blocking];
}

bool Tile::isTP()
{
    return m_properties[TP];
}

bool Tile::isAnimated()
{
    return m_properties[Animated];
}

bool Tile::isStairs()
{
    return m_properties[Stairs];
}

bool Tile::isHealer()
{
    return m_properties[Healer];
}

bool Tile::isChest()
{
    return m_properties[Chest];
}

bool Tile::isZombie()
{
    return m_properties[Zombie];
}

void Tile::setBlocking(bool b)
{
    m_properties[Blocking] = b;
}

void Tile::setIsTP(bool b)
{
    m_properties[TP] = b;
}

void Tile::setIsStairs(bool b)
{
    m_properties[Stairs] = b;
}

void Tile::setAnimated(bool val)
{
    m_properties[Animated] = val;
}

void Tile::setChest(bool b)
{
    m_properties[Chest] = b;
}

void Tile::setHealer(bool b)
{
    m_properties[Healer] = b;
}

void Tile::setZombie(bool b)
{
    m_properties[Zombie] = b;
}

