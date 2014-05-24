#ifndef CHARACTER_H
#define CHARACTER_H

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include "Room.h"
#include "GameEnvironment.h"

enum State{
    Walk = 4,
    Run = 8
};

class Character : public sf::Drawable, public sf::Transformable
{
    public:
        Character(std::string tileset);
        Character(GameEnvironment* gameEnvironment, std::string tileset);
        virtual ~Character();


        void moveCharacter();
        bool moveTo(int, int);
        void healParty();

        sf::Vector2f getPosition();
        sf::Vector2i getBounds();
        sf::FloatRect getGlobalBounds() {return m_sprite.getGlobalBounds();};
        State getState() {return m_state;};
        Dir getDirection() {return m_dir;};
        Dir getOldDirection(){return m_olddir;};

        void setPosition(int x, int y);
        void setTexture(std::string filename);
        void setEnvironment(GameEnvironment* gameEnvironment);
        void setState(State s){m_state = s;};
        void setDirection(Dir d);

    protected:
        sf::Sprite m_sprite;
        Dir m_olddir;

    private:
        int m_frame;
        int m_alternate;
        sf::Time m_delay;
        sf::Clock m_clock;
        GameEnvironment* m_gameEnvironment;
        sf::IntRect m_rect;
        Dir m_dir;
        State m_state;

        virtual void draw(sf::RenderTarget& t, sf::RenderStates s) const;
};

#endif // CHARACTER_H
