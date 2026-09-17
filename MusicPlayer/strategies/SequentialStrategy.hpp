#pragma once
#include "IPlayingStrategy.hpp"
#include <vector>
class SequentialStrategy : public IPlayingStrategy
{
    PlayList *playlist;
    int curIndex;

public:
    SequentialStrategy()
    {
        curIndex = -1;
        playlist = nullptr;
    }
    void setPlayList(PlayList *playList)
    {
        this->playlist = playList;
        curIndex = -1;
    }
    bool hasNextSong()
    {
        return curIndex + 1 < playlist->getSize();
    }
    bool hasPrevSong()
    {
        return curIndex != -1;
    }

    Song *nextSong()
    {
        if (!hasNextSong())
        {
            throw std::runtime_error("No next song available for the playlist" + playlist->getName());
        }
        return this->playlist->getSongs()[++curIndex];
    }
    Song *prevSong()
    {
        if (!hasPrevSong())
        {
            throw std::runtime_error("No previous song available for the playlist" + playlist->getName());
        }
        return this->playlist->getSongs()[--curIndex];
    }
    ~SequentialStrategy()
    {
    }
};