#ifndef ENEMY_H
#define ENEMY_H


#include "Character.h"

class Room;


class Enemy : public Character
{
    public:
        Enemy(GameEnvironment* gameEnvironment, std::string tileset, int id);
        virtual ~Enemy();

        int getId(){return m_id;};

        bool collision(sf::FloatRect r);
        int getPercentage(){return m_percentage;};
        void setPercentage(int p){m_percentage = p;};


    protected:
    private:
        int m_id;
        int m_percentage;
};

#endif // ENEMY_H
