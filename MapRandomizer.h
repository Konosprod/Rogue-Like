#ifndef MAPRANDOMIZER_H
#define MAPRANDOMIZER_H

#include <iostream>
#include <vector>
#include "Room.h"

#define SIZE_MAX_TAB 20
#define START_ROOM 2
#define EVENT_ROOM 3
#define CHEST_ROOM 4
#define HEAL_ROOM 5
#define END_ROOM 6

typedef struct Point
{
    int x;
    int y;
}Point;

class MapRandomizer
{
    public:
        MapRandomizer();
        MapRandomizer(int** t, int floor, int floorMax);
        virtual ~MapRandomizer();

        void generateMap();
        void setTab(int**t){m_tab = t;};
        void setFloor(int f){m_floor = f;};
        void setFloorMax(int f){m_floorMax = f;};
        bool* dirRoomCo (int x, int y);
        Point findStart ();


    protected:
        void initTab(int** t);
        void copyTab(int** src, int** dest);
        bool isCorner (unsigned int y, unsigned int x);
        bool isEmpty (int** t);
        bool isOnEdge (unsigned int y, unsigned int x);
        int numberRoomCo (unsigned int x, unsigned int y, int** grille);
        std::vector<Point> coordRoomCo (unsigned int x, unsigned int y, int** grille);
        void createRoomCo (unsigned int x, unsigned int y);
        bool setEvent();
        int packNumber (int** t);
        int distanceRoom(Point a, Point b);
        int** extractPack();
        void insertTab(int** src, int** dst);
        void linkPacks();
        bool joinPack ();
        void setHeal ();
        void setChest ();
        void freeTab(int** t);

    private:
        int** m_tab;
        int m_floor;
        int m_floorMax;
};

#endif // MAPRANDOMIZER_H
