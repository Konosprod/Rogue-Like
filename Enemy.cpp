#include "Enemy.h"
#include "Room.h"


Enemy::Enemy(GameEnvironment* gameEnvironment, std::string tileset, int id) : Character(gameEnvironment, tileset), m_id (id)
{
    m_percentage = 91;
}

Enemy::~Enemy()
{
    //dtor
}


bool Enemy::collision(sf::FloatRect r)
{
    return m_sprite.getGlobalBounds().intersects(r);
}

