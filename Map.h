#ifndef MAP_H
#define MAP_H

#include <vector>

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

    protected:
        void generateMap();
        void copyTab(int** src, int** dest);
        bool isCorner (int y, int x);
        void freeTab(int** t);
        bool isEmpty ();
        bool isOnEdge (int y, int x);
        void numberRoomCo(int x, int y);

    private:
        int m_nbRoom;
        int*** m_tab;

        virtual void draw(sf::RenderTarget& t, sf::RenderStates s) const;
};

#endif // MAP_H
