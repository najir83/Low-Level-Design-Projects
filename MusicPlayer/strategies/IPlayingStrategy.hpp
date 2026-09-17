#pragma once
#include "../models/Song.hpp"
#include "../models/PlayList.hpp"

class IPlayingStrategy
{
public:
    virtual Song *nextSong() = 0;
    virtual Song *prevSong() = 0;
    virtual bool hasNextSong() = 0;
    virtual bool hasPrevSong() = 0;
    virtual void setPlayList(PlayList* playlist) = 0;
    virtual void queueNextSong(Song *song)
    {
    }
};
