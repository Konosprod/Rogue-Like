#include <SFML/Graphics.hpp>
#include "Map.h"
#include "Character.h"
#include "Interpreter.h"
#include "SoundManager.h"

enum GameState{
    Running,
    Fight,
    Pause,
    Event
};

int main()
{
    srand(time(NULL));

    sf::Clock fadeC;
    SoundManager soundManager("rc/musics/test.ogg", true);
    sf::Time fadeDelay = sf::seconds(0.005f);
    bool done = true;
    sf::RectangleShape fade;
    Character c("rc/images/test_perso.png");
    sf::RenderWindow window(sf::VideoMode(1024, 768, sf::Style::Fullscreen), "Badass Lengendary Awesome Heroes : Squad Extrem Adventure 2", sf::Style::Close);
    sf::View view(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y));
    view.setViewport(sf::FloatRect(0.25f, 0.25f, 1, 1));
    window.setView(view);
    sf::Texture pauseScreenTexture;
    sf::Sprite pauseScreen;
    GameState state = Running;
    GameState oldState = state;

    fade.setSize(sf::Vector2f(view.getSize().x,view.getSize().y));

    pauseScreenTexture.loadFromFile("rc/images/paused.png");
    pauseScreen.setTexture(pauseScreenTexture);

    c.setWindow(&window);
    Interpreter i(&window, &soundManager);

    Map m(&soundManager, "rc/images/test.png", 2);
    m.drawMapDebug();

    window.setFramerateLimit(60);

    soundManager.play();

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

                case sf::Event::Resized:
                {
                    view.setSize(event.size.width, event.size.height);
                    view.setViewport(sf::FloatRect(0.25f, 0.25f, 1, 1));
                    window.setView(view);
                }
                break;

                case sf::Event::LostFocus:
                    oldState = state;
                    state = Pause;
                    soundManager.pause();
                break;

                case sf::Event::GainedFocus:
                    state = oldState;
                    soundManager.play();
                break;

                case sf::Event::KeyReleased:
                    if(event.key.code == sf::Keyboard::R)
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

                    if(event.key.code == sf::Keyboard::P)
                    {
                        if(state == Running)
                        {
                            state = Pause;
                            soundManager.pause();
                            soundManager.stopFootsteps();
                        }
                        else
                        {
                            state = Running;
                            soundManager.play();
                        }
                    }

                    if(event.key.code == sf::Keyboard::A)
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

                        if(state == Fight)
                        {
                            state = Running;
                            m.updateZombie(c);
                        }

                        if(state == Event)
                        {
                            i.nextDialog();
                        }
                    }

                    if(event.key.code == sf::Keyboard::M)
                    {
                        soundManager.stop();
                    }

                    if(event.key.code == sf::Keyboard::E)
                    {
                        state = Event;
                        i.loadScript("rc/scripts/script_test");
                    }
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
                    soundManager.playFootsteps();
                }
                else if(m.isEngagingFight(c))
                {
                    soundManager.stopFootsteps();
                    state = Fight;
                }

                done = !(m.update(c));
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
                    soundManager.playFootsteps();
                }

                else if(m.isEngagingFight(c))
                {
                    soundManager.stopFootsteps();
                    state = Fight;
                }


                done = !(m.update(c));
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
                    soundManager.playFootsteps();
                }
                else if(m.isEngagingFight(c))
                {
                    soundManager.stopFootsteps();
                    state = Fight;
                }


                done = !(m.update(c));
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
                    soundManager.playFootsteps();
                }
                else if(m.isEngagingFight(c))
                {
                    soundManager.stopFootsteps();
                    state = Fight;
                }

                done = !(m.update(c));
            }
        }
        else
        {
            if(state == Running)
            {
                c.setDirection(Default);
                c.moveCharacter();
                soundManager.stopFootsteps();
            }
        }

        int alpha = 255;
        while(!done)
        {
            soundManager.playDoor();
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

        if(state == Running || state == Fight)
        {
            window.draw(m);
            window.draw(c);
        }
        if(state == Pause)
        {
            window.draw(pauseScreen);
        }
        if(state == Event)
        {
            window.draw(m);

            if(i.isEmpty())
            {
                i.clear();
                window.draw(c);
                state = Running;
            }
            else
            {
                i.update();
            }
        }

        window.display();
    }

    return 0;
}

