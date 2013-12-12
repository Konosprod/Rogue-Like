#ifndef MAP_H
#define MAP_H

#include <vector>

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
        int initTab(int** t);
        void freeTab(int** t);
        void insertTab(int** src, int** dst);
        void copyTab(int** src, int** dest);
        bool isCorner(int y, int x);
        bool isEmpty();
        bool isOnEdge(int y, int x);
        void numberRoomCo(int x, int y);
        vector<Point> coordRoomCo(int x, int y);
        void createRoomCo (int x, int y);
        bool setEvent ();
        int packNumber ();
        int** extractPack();
        void linkPacks();
        void joinPack();

    private:
        int m_nbRoom;
        int*** m_tab;

        virtual void draw(sf::RenderTarget& t, sf::RenderStates s) const;
};

#endif // MAP_H
