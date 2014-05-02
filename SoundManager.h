#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <SFML/Audio.hpp>

enum Channels
{
    Channel1,
    Channel2,
    Channel3,
    Channel4,
    Channel5,
    ChannelMax
};

class SoundManager
{
    public:
        SoundManager();
        SoundManager(std::string filename, bool loop = false);

        bool loadMusic(std::string filename, bool loop = false);
        bool isPlaying();

        void loopMusic(bool loop);
        void play();
        void stop();
        void pause();

        void playDoor();

        void playFootsteps();
        void stopFootsteps();

        virtual ~SoundManager();

    protected:
        void init();

    private:
        sf::Music m_music;
        sf::SoundBuffer m_buffers[ChannelMax];
        sf::Sound m_sounds[ChannelMax];
};

#endif // SOUNDMANAGER_H
