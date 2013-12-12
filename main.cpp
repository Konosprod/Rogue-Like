#include <SFML/Graphics.hpp>
#include "Map.h"

int main()
{
    srand(time(NULL));

    Map m;

    m.generateMap();

    sf::RenderWindow window(sf::VideoMode(512, 512, sf::Style::Fullscreen), "Generate Room");

    window.setFramerateLimit(60);

    m.drawMapDebug();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch(event.type)
            {
                case sf::Event::Closed:
                    window.close();
                break;

                case sf::Event::KeyReleased:
                    if(event.key.code == sf::Keyboard::Left)
                    {
                        m.moveRoom(0, -1);
                    }
                    else if(event.key.code == sf::Keyboard::Right)
                    {
                        m.moveRoom(0, 1);
                    }
                    else if(event.key.code == sf::Keyboard::Up)
                    {
                        m.moveRoom(-1, 0);
                    }
                    else if(event.key.code == sf::Keyboard::Down)
                    {
                        m.moveRoom(1, 0);
                    }
                break;

                default:
                break;
            }

        }

        window.clear();
        window.draw(m);
        window.display();
    }

    return 0;
}


