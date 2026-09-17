#pragma once
#include "../models/Song.hpp"

class IAudioPlayer
{
public:
    virtual void play(Song *song) = 0;
    virtual ~IAudioPlayer() = default;
};