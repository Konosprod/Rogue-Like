#include "Character.h"

Character::Character(std::string tileset)
{
    setTexture(tileset);
    m_rect.width = 32;
	m_rect.height = 32;
	m_rect.left = 0;
	m_rect.top = 0;

	m_sprite.setTextureRect(m_rect);
	m_sprite.setPosition(64, 64);

	m_delay = sf::seconds(0.025f);
	m_alternate = 0;
	m_frame = 0;
	m_dir = Down;
	m_olddir = Down;
	m_state = Walk;
}

Character::~Character()
{
    //dtor
}

void Character::setTexture(std::string filename)
{
    if(!m_texture.loadFromFile(filename))
        std::cout<<"Error! Incorrect input"<<std::endl;

    m_sprite.setTexture(m_texture);
}

sf::Vector2f Character::getPosition()
{
    return m_sprite.getPosition();
}

sf::Vector2i Character::getBounds()
{
    sf::Vector2i v;
    v.x = m_rect.width;
    v.y = m_rect.height;
    return v;
}

void Character::healParty()
{
    std::cout << "Heal party" << std::endl;
}

bool Character::moveTo(int xWanted, int yWanted)
{
    int x = m_sprite.getPosition().x;
    int y = m_sprite.getPosition().y;

    if (x < xWanted)
    {
        m_dir = Right;
        moveCharacter();
    }
    else if (x > xWanted)
    {
        m_dir = Left;
        moveCharacter();
    }
    else
    {
        if (y < yWanted)
        {
            m_dir = Down;
            moveCharacter();
        }
        else if (y > yWanted)
        {
            m_dir = Up;
            moveCharacter();
        }
    }

    return (x == xWanted && y == yWanted);
}

void Character::moveCharacter()
{
    switch(m_dir)
    {
        case Down:
            if (m_alternate == 0)
            {
                m_frame = 1;
            }
            if(m_frame == 2 && m_alternate == 3)
            {
            m_frame = 1;
                m_alternate = 0;
            }
            else if(m_frame == 1 && m_alternate == 3)
            {
                m_frame = 2;
                m_alternate = 0;
            }

            m_rect.width = 32;
            m_rect.height = 32;
            m_rect.left = m_frame * 32;
            m_rect.top = m_dir * 32;

            m_sprite.setTextureRect(m_rect);
            m_clock.restart();
            while(m_clock.getElapsedTime() < m_delay);
            m_sprite.move(0,m_state);
            m_clock.restart();
            m_alternate++;
        break;

        case Left:
            if (m_alternate == 0)
            {
                m_frame = 1;
            }
            if(m_frame == 2 && m_alternate == 3)
            {
            m_frame = 1;
                m_alternate = 0;
            }
            else if(m_frame == 1 && m_alternate == 3)
            {
                m_frame = 2;
                m_alternate = 0;
            }

            m_rect.width = 32;
            m_rect.height = 32;
            m_rect.left = m_frame * 32;
            m_rect.top = m_dir * 32;

            m_sprite.setTextureRect(m_rect);
            m_clock.restart();
            while(m_clock.getElapsedTime() < m_delay);
            m_sprite.move(-m_state,0);
            m_clock.restart();
            m_alternate++;
        break;

        case Up:
            if (m_alternate == 0)
            {
                m_frame = 1;
            }
            if(m_frame == 2 && m_alternate == 3)
            {
            m_frame = 1;
                m_alternate = 0;
            }
            else if(m_frame == 1 && m_alternate == 3)
            {
                m_frame = 2;
                m_alternate = 0;
            }

            m_rect.width = 32;
            m_rect.height = 32;
            m_rect.left = m_frame * 32;
            m_rect.top = m_dir * 32;

            m_sprite.setTextureRect(m_rect);
            m_clock.restart();
            while(m_clock.getElapsedTime() < m_delay);
            m_sprite.move(0,-m_state);
            m_clock.restart();
            m_alternate++;
        break;

        case Right:
            if (m_alternate == 0)
            {
                m_frame = 1;
            }
            if(m_frame == 2 && m_alternate == 3)
            {
            m_frame = 1;
                m_alternate = 0;
            }
            else if(m_frame == 1 && m_alternate == 3)
            {
                m_frame = 2;
                m_alternate = 0;
            }

            m_rect.width = 32;
            m_rect.height = 32;
            m_rect.left = m_frame * 32;
            m_rect.top = m_dir * 32;

            m_sprite.setTextureRect(m_rect);
            m_clock.restart();
            while(m_clock.getElapsedTime() < m_delay);
            m_sprite.move(m_state,0);
            m_clock.restart();
            m_alternate++;
        break;

        case Default:
            m_rect.left = 0;
            m_rect.width = 32;
            m_rect.height = 32;
            m_rect.top = m_olddir * 32;
            m_sprite.setTextureRect(m_rect);
        break;
    }
}

void Character::setPosition(int x, int y)
{
    m_sprite.setPosition(x, y);
}

void Character::setDirection(Dir d)
{
    if(d != Default)
    {
        if(m_dir != Default)
        {
            m_olddir = m_dir;
        }
        m_dir = d;
    }
    else
    {
        if(m_dir != Default)
        {
            m_olddir = m_dir;
        }
        m_dir = d;
    }
}

void Character::draw(sf::RenderTarget& t, sf::RenderStates s) const
{
    t.draw(m_sprite);
    (void)s;
}

