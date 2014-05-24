#include <SFML/Graphics.hpp>
#include "Map.h"
#include "Character.h"
#include "Interpreter.h"
#include "SoundManager.h"
#include "TextureManager.h"
#include "GameEnvironment.h"
#include "Enemy.h"

enum GameState{
    Running,
    Fight,
    Pause,
    Event
};

void threadFunc(Map* m)
{
    while(1)
    {
        if(!m->getCurrentRoom()->isEmpty())
        {
            Enemy* zomb = m->getCurrentRoom()->getRandomZombie();

            if(m->isValidMoveZombie(*zomb))
            {
                zomb->moveCharacter();
            }

            sf::sleep(sf::milliseconds(100/(m->getCurrentRoom()->getNbZombie())));
        }
    }
}


int main()
{
    srand(time(NULL));

    sf::Clock fadeC;
    SoundManager soundManager("rc/musics/test.ogg", true);
    sf::Time fadeDelay = sf::seconds(0.005f);
    bool done = true;
    sf::RectangleShape fade;
    TextureManager textureManager;
    Character c("rc/images/test_perso.png");
    sf::Sprite menuBackground;
    sf::Sprite pauseScreen;
    GameState state = Running;
    GameState oldState = state;
    GameEnvironment gameEnvironment;
    sf::RenderWindow window(sf::VideoMode(910, 512, sf::Style::Fullscreen), "Badass Lengendary Awesome Heroes : Squad Extrem Adventure 2");
    sf::View view(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y));

    Random::Initialize();


    view.setViewport(sf::FloatRect(0, 0, 1, 1));
    window.setView(view);

    gameEnvironment.window = &window;
    gameEnvironment.soundManager = &soundManager;
    gameEnvironment.textureManager = &textureManager;

    Interpreter i(&gameEnvironment);

    fade.setSize(sf::Vector2f(512,512));

    pauseScreen.setTexture(*textureManager.getTexture("rc/images/paused.png"));
    menuBackground.setTexture(*textureManager.getTexture("rc/images/blah.png"));
    menuBackground.setPosition(512,0);

    Map m(&gameEnvironment, "rc/images/test.png", 2);
    //m.drawMapDebug();

    sf::Thread moveZombie(&threadFunc, &m);
    moveZombie.launch();



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
                    moveZombie.terminate();
                    window.close();
                break;

                case sf::Event::Resized:
                {
                    /*view.setSize(event.size.width, event.size.height);
                    view.setViewport(sf::FloatRect(0.25f, 0.25f, 1, 1));
                    window.setView(view);*/
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
                            moveZombie.launch();
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

                if(m.isEngagingFight(c))
                {
                    moveZombie.terminate();
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

                if(m.isEngagingFight(c))
                {
                    moveZombie.terminate();
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

                if(m.isEngagingFight(c))
                {
                    moveZombie.terminate();
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

                if(m.isEngagingFight(c))
                {
                    moveZombie.terminate();
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
            window.draw(menuBackground);
            window.draw(c);
            window.draw(fade);
            window.display();
            if(alpha == 0)
            {
                done = true;
                //m.drawMiniMap();
            }
        }

        window.clear();

        if(state == Running || state == Fight)
        {
            window.draw(m);
            window.draw(menuBackground);
            window.draw(c);
        }
        if(state == Pause)
        {
            window.draw(pauseScreen);
        }
        if(state == Event)
        {
            window.draw(m);
            window.draw(menuBackground);
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

