#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <map>
#include <iostream>
#include <SFML/Graphics.hpp>

class TextureManager
{
    public:
        TextureManager();
        virtual ~TextureManager();

        sf::Texture* getTexture(std::string filename);

    protected:

    private:
        static std::map<std::string, sf::Texture*> m_textures;
};

#endif // TEXTUREMANAGER_H
