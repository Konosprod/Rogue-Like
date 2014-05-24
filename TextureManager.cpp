#include "TextureManager.h"

TextureManager::TextureManager()
{
    //ctor
}

std::map<std::string, sf::Texture*> TextureManager::m_textures;

sf::Texture* TextureManager::getTexture(std::string filename)
{
    if(m_textures.find(filename) != m_textures.end())
    {
        return m_textures[filename];
    }

    sf::Texture* texture = new sf::Texture();

    if(texture->loadFromFile(filename))
    {
        m_textures[filename] = texture;
        return m_textures[filename];
    }
    else
    {
        //delete texture;
        return NULL;
    }
}

TextureManager::~TextureManager()
{
    sf::Texture* texture;
    std::map<std::string, sf::Texture*>::iterator itBegin = m_textures.begin();

    while(itBegin != m_textures.end())
    {
        texture = itBegin->second;
        delete texture;
        ++itBegin;
    }

}

