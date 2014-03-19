#ifndef CHARACTER_H
#define CHARACTER_H

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include "Room.h"

enum State{
    Walk = 4,
    Run = 8
};

class Character : public sf::Drawable, public sf::Transformable
{
    public:
        Character(std::string tileset);
        virtual ~Character();

        void setTexture(std::string filename);
        void moveCharacter();

        sf::Vector2f getPosition();
        sf::Vector2i getBounds();
        State getState() {return m_state;};
        Dir getDirection() {return m_dir;};

        void setPosition(int x, int y);
        void setWindow(sf::RenderWindow* t) {m_window = t;};
        void setState(State s){m_state = s;};
        void setDirection(Dir d) {if(m_dir == Default){m_olddir = m_dir;}m_dir=d;};

        void healParty();

    protected:

    private:
        int m_frame;
        int m_alternate;
        sf::Time m_delay;
        sf::Clock m_clock;
        sf::Texture m_texture;
        sf::Sprite m_sprite;
        sf::IntRect m_rect;
        sf::RenderWindow* m_window;
        Dir m_dir;
        Dir m_olddir;
        State m_state;

        virtual void draw(sf::RenderTarget& t, sf::RenderStates s) const;
};

#endif // CHARACTER_H
