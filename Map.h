#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>
#include "Room.h"
#include "Random.h"
#include "Character.h"
#include "Enemy.h"
#include "MapRandomizer.h"
#include "GameEnvironment.h"

enum Event{
    None,
    Healer,
    Chest
};

class Map : public sf::Drawable, public sf::Transformable
{
    public:
        Map(GameEnvironment* gameEnvironment, std::string tileset, int floorMax);
        virtual ~Map();

        void moveRoom(Dir d);
        void drawMapDebug();
        void updateZombie(Character& c);
        void drawMiniMap();

        bool isValidMove(Character& c);
        bool isEngagingFight(Character& c);
        bool isChangingTile(Character& c);
        bool isChangingFloor(Character& c);
        bool isValidMoveZombie(Enemy& c);

        sf::Vector2i getTP(Dir d);
        Room* getCurrentRoom();
        Point currentRoom();

        void openChest();
        bool update(Character& c);
        void nextFloor();
        Event checkEvent(Character& c);

    protected:
        void generateMap();
        void freeTab(int** t);
        void createRooms();
        void freeRooms();
        void getNbRoom();

    private:
        int m_nbRoom;
        int m_floor;
        std::string m_tileset;
        int m_floorMax;
        int** m_tab;
        Room*** m_rooms;
        Point m_currentPos;
        MapRandomizer m_randomizer;
        GameEnvironment* m_gameEnvironment;
        bool m_done;


        virtual void draw(sf::RenderTarget& t, sf::RenderStates s) const;
};

#endif // MAP_H
