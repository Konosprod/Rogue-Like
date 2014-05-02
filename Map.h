#ifndef MAP_H
#define MAP_H

#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Room.h"
#include "Character.h"
#include "MapRandomizer.h"
#include "SoundManager.h"

enum Event{
    None,
    Healer,
    Chest
};

class Map : public sf::Drawable, public sf::Transformable
{
    public:
        Map(SoundManager* soundManager, std::string tileset, int floorMax);
        virtual ~Map();

        void moveRoom(Dir d);
        void drawMapDebug();
        void updateZombie(Character& c);

        bool isValidMove(Character& c);
        bool isEngagingFight(Character& c);
        bool isChangingTile(int x, int y);
        bool isChangingFloor(int x, int y);

        sf::Vector2i getTP(Dir d);
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
        SoundManager* m_soundManager;
        bool m_done;


        virtual void draw(sf::RenderTarget& t, sf::RenderStates s) const;
};

#endif // MAP_H
