#include <SFML/Graphics.hpp>
#include "Room.h"

int main()
{
    bool connexions[4];

    for(int i = 0; i < 4; i++)
    {
        connexions[i] = true;
    }

    srand(time(NULL));

    Room r(connexions);

    r.generateRoom();

    sf::RenderWindow window(sf::VideoMode(r.getX()*32, r.getY()*32), "Generate Room");

    window.setFramerateLimit(60);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(r);
        window.display();
    }

    return 0;
}


