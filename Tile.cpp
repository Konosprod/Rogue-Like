#include "Tile.h"

Tile::Tile(bool animated) : m_animated(animated)
{
    m_blocking = false;
    m_isTP = false;
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
    return m_blocking;
}

bool Tile::isTP()
{
    return m_isTP;
}

bool Tile::isAnimated()
{
    return m_animated;
}

void Tile::setBlocking(bool b)
{
    m_blocking = b;
}

void Tile::setIsTP(bool b)
{
    m_isTP = b;
}


void Tile::setAnimated(bool val)
{
    m_animated = val;
}

