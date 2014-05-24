#ifndef GAMEENVIRONEMENT_H_INCLUDED
#define GAMEENVIRONEMENT_H_INCLUDED

#include <SFML/Graphics.hpp>
#include "SoundManager.h"
#include "TextureManager.h"

typedef struct GameEnvironment
{
    public :
        sf::RenderWindow* window;
        SoundManager* soundManager;
        TextureManager* textureManager;
}GameEnvironment;



#endif // GAMEENVIRONEMENT_H_INCLUDED
