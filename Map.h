#ifndef MAP_H
#define MAP_H

#include <vector>
#include <SFML/Graphics.hpp>

#define SIZE_MAX 20

typedef struct Point
{
    int x;
    int y;
}Point;


class Map : public sf::Drawable, public sf::Transformable
{
    public:
        Map();
        virtual ~Map();
        void generateMap();

    protected:
        void initTab(int** t);
        void freeTab(int** t);
        void insertTab(int** src, int** dst);
        void copyTab(int** src, int** dest);
        bool isCorner(int y, int x);
        bool isEmpty(int** t);
        bool isOnEdge(int y, int x);
        int numberRoomCo(int x, int y, int** t);
        std::vector<Point> coordRoomCo(int x, int y, int** grille);
        void createRoomCo (int x, int y);
        bool setEvent ();
        int packNumber (int** t);
        int** extractPack();
        void linkPacks();
        bool joinPack();
        Point findStart();
        int distanceRoom(Point a, Point b);

    private:
        int m_nbRoom;
        int** m_tab;

        virtual void draw(sf::RenderTarget& t, sf::RenderStates s) const;
};

#endif // MAP_H
