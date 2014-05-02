#include "SoundManager.h"

SoundManager::SoundManager()
{
    init();
}

SoundManager::SoundManager(std::string filename, bool loop)
{
    init();
    loadMusic(filename, loop);
}

SoundManager::~SoundManager()
{

}

void SoundManager::init()
{
    m_buffers[Channel1].loadFromFile("rc/sounds/footsteps1.wav");
    m_buffers[Channel2].loadFromFile("rc/sounds/door.wav");

    m_sounds[Channel2].setBuffer(m_buffers[Channel2]);
    m_sounds[Channel1].setBuffer(m_buffers[Channel1]);
    m_sounds[Channel1].setLoop(true);
}

bool SoundManager::isPlaying()
{
    return (m_music.getStatus() == sf::Music::Playing);
}

bool SoundManager::loadMusic(std::string filename, bool loop)
{
    if(m_music.openFromFile(filename))
    {
        m_music.setLoop(loop);
        m_music.setVolume(25);
        return true;
    }
    else
    {
        return false;
    }
}

void SoundManager::play()
{
    m_music.play();
}

void SoundManager::stop()
{
    m_music.stop();
}

void SoundManager::pause()
{
    m_music.pause();
}

void SoundManager::loopMusic(bool loop)
{
    m_music.setLoop(loop);
}

void SoundManager::playFootsteps()
{
    if(m_sounds[Channel1].getStatus() != sf::Sound::Playing)
    {
        m_sounds[Channel1].play();
    }
}

void SoundManager::stopFootsteps()
{
    m_sounds[Channel1].stop();
}

void SoundManager::playDoor()
{
    if(m_sounds[Channel2].getStatus() != sf::Sound::Playing)
    {
        m_sounds[Channel2].play();
    }
}
