#include "Tile.h"

Tile::Tile(bool animated) : m_animated(animated)
{

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
