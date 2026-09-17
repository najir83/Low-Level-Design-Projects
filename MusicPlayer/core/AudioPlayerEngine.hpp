#pragma once
#include "../models/Song.hpp"
#include "../devices/IAudioPlayer.hpp"
#include <stdexcept>
#include <iostream>
class AudioPlayerEngine
{
    Song *song;
    bool isPause;

public:
    AudioPlayerEngine()
    {
        isPause = false;
        song = nullptr;
    }
    void play(Song *song, IAudioPlayer *player)
    {
        if (!song)
        {
            throw std::runtime_error("Cannot play a null song.");
        }
        if (isPause or this->song == song)
        {
            std::cout << "Resuming song: " << song->getName() << std::endl;
            player->play(song);
            isPause = false;
        }
        else
        {
            this->song = song;
            isPause = false;
            std::cout << "Playing song: " << song->getName() << std::endl;
            player->play(song);
        }
    }
    void pause()
    {
        if (song == nullptr)
        {
            throw std::runtime_error("No song is currently playing to pause.");
        }

        if (isPause)
        {
            throw std::runtime_error("Song is already paused.");
        }
        isPause = true;
        std::cout << "Pausing song: " << song->getName() << "\n";
    }
};