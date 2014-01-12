#include <SFML/Graphics.hpp>
#include "Map.h"

int main()
{
    Map m;
    int frame = 0;
	int lol = 0;
	sf::Time delay = sf::seconds(0.025f);
	sf::Clock clock;
	enum Dir direction = Up;
	sf::Sprite s;
	sf::IntRect rect;
	sf::Texture t;


	if (!t.loadFromFile("rc/test_perso.png"))
		std::cout<<"Error! Incorrect input"<<std::endl;

	s.setTexture(t);

	rect.width = 32;
	rect.height = 32;

	rect.left = 0;
	rect.top = 0;

	s.setTextureRect(rect);
	s.setPosition(64, 64);

	srand(time(NULL));

    m.generateMap();

    sf::RenderWindow window(sf::VideoMode(512, 512, sf::Style::Fullscreen), "Generate Room");

    window.setFramerateLimit(60);

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

                default:
                break;
            }
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            direction = Down;
            if(m.isValidMove(s.getPosition().x, s.getPosition().y+32))
            {
                if (lol == 0)
                {
                    frame = 1;
                }
                if(frame == 2 && lol == 3)
                {
                    frame = 1;
                    lol = 0;
                }
                else if(frame == 1 && lol == 3)
                {
                    frame = 2;
                    lol = 0;
                }
                rect.width = 32;
                rect.height = 32;
                rect.left = frame * 32;
                rect.top = direction * 32;
                s.setTextureRect(rect);
                clock.restart();
                while(clock.getElapsedTime() < delay);
                s.move(0,4);
                clock.restart();
                lol++;
            }

            if(m.isChangingTile(s.getPosition().x, s.getPosition().y+32))
            {
                sf::Vector2i v;
                m.moveRoom(Down);
                v = m.getTP(Up);
                s.setPosition((v.x*32), 32);
            }
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            direction = Left;
            if(m.isValidMove(s.getPosition().x-32, s.getPosition().y))
            {
                if (lol == 0)
                {
                    frame = 1;
                }
                if(frame == 2 && lol == 3)
                {
                    frame = 1;
                    lol = 0;
                }
                else if(frame == 1 && lol == 3)
                {
                    frame = 2;
                    lol = 0;
                }
                rect.width = 32;
                rect.height = 32;
                rect.left = frame * 32;
                rect.top = direction * 32;
                s.setTextureRect(rect);
                clock.restart();
                while(clock.getElapsedTime() < delay);
                s.move(-4,0);
                clock.restart();
                lol++;
            }
            if(m.isChangingTile(s.getPosition().x-32, s.getPosition().y))
            {
                sf::Vector2i v;
                m.moveRoom(Left);
                v = m.getTP(Right);
                s.setPosition((v.x-1)*32, v.y*32);
            }
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            direction = Up;
            if(m.isValidMove(s.getPosition().x, s.getPosition().y-32))
            {
                if (lol == 0)
                {
                    frame = 1;
                }
                if(frame == 2 && lol == 3)
                {
                    frame = 1;
                    lol = 0;
                }
                else if(frame == 1 && lol == 3)
                {
                    frame = 2;
                    lol = 0;
                }
                rect.width = 32;
                rect.height = 32;
                rect.left = frame * 32;
                rect.top = direction * 32;
                s.setTextureRect(rect);
                clock.restart();
                while(clock.getElapsedTime() < delay);
                s.move(0,-4);
                clock.restart();
                lol++;
            }

            if(m.isChangingTile(s.getPosition().x, s.getPosition().y-32))
            {
                sf::Vector2i v;
                m.moveRoom(Up);
                v = m.getTP(Down);
                s.setPosition(v.x*32, (v.y-1)*32);
            }
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            direction = Right;
            if(m.isValidMove(s.getPosition().x+32, s.getPosition().y))
            {
                if (lol == 0)
                {
                    frame = 1;
                }
                if(frame == 2 && lol == 3)
                {
                    frame = 1;
                    lol = 0;
                }
                else if(frame == 1 && lol == 3)
                {
                    frame = 2;
                    lol = 0;
                }
                rect.width = 32;
                rect.height = 32;
                rect.left = frame * 32;
                rect.top = direction * 32;
                s.setTextureRect(rect);
                clock.restart();
                while(clock.getElapsedTime() < delay);
                s.move(4,0);
                clock.restart();
                lol++;
            }

            if(m.isChangingTile(s.getPosition().x+32, s.getPosition().y))
            {
                sf::Vector2i v;
                m.moveRoom(Right);
                v = m.getTP(Left);
                s.setPosition((v.x+1)*32, v.y*32);
            }
        }
        else
        {
            rect.left = 0;
            rect.width = 32;
            rect.height = 32;
            rect.top = direction * 32;
            s.setTextureRect(rect);
        }
        float y = s.getPosition().y;
        float x = s.getPosition().x;
        while (((int)y%32 != 0) || ((int)x%32 != 0))
        {
            if (direction == Up)
            {
                if (lol == 0)
                {
                    frame = 1;
                }
                if(frame == 2 && lol == 3)
                {
                    frame = 1;
                    lol = 0;
                }
                else if(frame == 1 && lol == 3)
                {
                    frame = 2;
                    lol = 0;
                }
                rect.width = 32;
                rect.height = 32;
                rect.left = frame * 32;
                rect.top = direction * 32;
                s.setTextureRect(rect);
                while(clock.getElapsedTime() < delay);
                s.move(0,-4);
                clock.restart();
                lol++;
            }
            else if (direction == Right)
            {
                if (lol == 0)
                {
                    frame = 1;
                }
                if(frame == 2 && lol == 3)
                {
                    frame = 1;
                    lol = 0;
                }
                else if(frame == 1 && lol == 3)
                {
                    frame = 2;
                    lol = 0;
                }
                rect.width = 32;
                rect.height = 32;
                rect.left = frame * 32;
                rect.top = direction * 32;
                s.setTextureRect(rect);
                clock.restart();
                while(clock.getElapsedTime() < delay);
                s.move(4,0);
                clock.restart();
                lol++;
            }
            else if (direction == Down)
            {
                if (lol == 0)
                {
                    frame = 1;
                }
                if(frame == 2 && lol == 3)
                {
                    frame = 1;
                    lol = 0;
                }
                else if(frame == 1 && lol == 3)
                {
                    frame = 2;
                    lol = 0;
                }
                rect.width = 32;
                rect.height = 32;
                rect.left = frame * 32;
                rect.top = direction * 32;
                s.setTextureRect(rect);
                clock.restart();
                while(clock.getElapsedTime() < delay);
                s.move(0,4);
                clock.restart();
                lol++;
            }
            else // direction == Left
            {
                if (lol == 0)
                {
                    frame = 1;
                }
                if(frame == 2 && lol == 3)
                {
                    frame = 1;
                    lol = 0;
                }
                else if(frame == 1 && lol == 3)
                {
                    frame = 2;
                    lol = 0;
                }
                rect.width = 32;
                rect.height = 32;
                rect.left = frame * 32;
                rect.top = direction * 32;
                s.setTextureRect(rect);
                clock.restart();
                while(clock.getElapsedTime() < delay);
                s.move(-4,0);
                clock.restart();
                lol++;
            }

            y = s.getPosition().y;
            x = s.getPosition().x;

            window.draw(m);
            window.draw(s);
            window.display();
            window.clear();
        }

        window.clear();
        window.draw(m);
        window.draw(s);
        window.display();
    }

    return 0;
}


