#include <SFML/Graphics.hpp>
#include "Map.h"
#include "Character.h"

enum GameState{
    Running,
    Pause
};

int main()
{
    srand(time(NULL));

	sf::Clock fadeC;
	sf::Time fadeDelay = sf::seconds(0.005f);
	bool done = true;
	sf::RectangleShape fade;
	Character c("rc/images/test_perso.png");
	sf::RenderWindow window(sf::VideoMode(512, 512, sf::Style::Fullscreen), "BLAH SEA 2");
	sf::Texture pauseScreenTexture;
	sf::Sprite pauseScreen;
	GameState state = Running;

	fade.setSize(sf::Vector2f(512,512));

    pauseScreenTexture.loadFromFile("rc/images/paused.png");
    pauseScreen.setTexture(pauseScreenTexture);

    c.setWindow(&window);

    Map m("rc/images/test.png", "rc/musics/test.ogg", 2);
    m.drawMapDebug();

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
            if(state == Running)
            {
                c.setDirection(Down);
                if(m.isValidMove(c))
                {
                    c.moveCharacter();
                }

                if(m.update(c))
                {
                    done = false;
                }
            }
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            if(state == Running)
            {
                c.setDirection(Left);
                if(m.isValidMove(c))
                {
                    c.moveCharacter();
                }

                if(m.update(c))
                {
                    done = false;
                }
            }
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            if(state == Running)
            {
                c.setDirection(Up);
                if(m.isValidMove(c))
                {
                    c.moveCharacter();
                }

                if(m.update(c))
                {
                    done = false;
                }
            }
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            if(state == Running)
            {
                c.setDirection(Right);
                if(m.isValidMove(c))
                {
                    c.moveCharacter();
                }

                if(m.update(c))
                {
                    done = false;
                }
            }
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::R))
        {
            if(state == Running)
            {
                if(c.getState() == Run)
                {
                    c.setState(Walk);
                }
                else
                {
                    c.setState(Run);
                }
            }
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::P))
        {
            if(state == Running)
            {
                state = Pause;
            }
            else
            {
                state = Running;
            }
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            if(state == Running)
            {
                switch(m.checkEvent(c))
                {
                    case Healer:
                        c.healParty();
                    break;

                    case Chest:
                        m.openChest();
                    break;

                    default:
                    break;
                }
            }
        }
        else
        {
            if(state == Running)
            {
                c.setDirection(Default);
                c.moveCharacter();
            }
        }

        int alpha = 255;
        while(!done)
        {
            while(fadeC.getElapsedTime() < fadeDelay);
            fade.setFillColor(sf::Color(0, 0, 0, alpha));
            fadeC.restart();
            alpha-=17;
            window.clear();
            window.draw(m);
            window.draw(c);
            window.draw(fade);
            window.display();
            if(alpha == 0)
            {
                done = true;
            }
        }

        window.clear();

        if(state == Running)
        {
            window.draw(m);
            window.draw(c);
        }
        if(state == Pause)
        {
            window.draw(pauseScreen);
        }

        window.display();
    }

    return 0;
}

