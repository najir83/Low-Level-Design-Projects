#pragma once
#include "../externals/WiredPlayer.hpp"
#include "IAudioPlayer.hpp"

class WiredPlayerAdapter : public IAudioPlayer
{
    WiredPlayer *player;

public:
    WiredPlayerAdapter(WiredPlayer *player) : player(player) {}
    void play(Song *song)
    {
        std::string buffer = "[Name:" + song->getName() + ", Artist: " + song->getArtist() + ", Path: " + song->getPath() + "]";
        player->playSongViaWired(buffer);
    }

    ~WiredPlayerAdapter()
    {
        delete player;
    }
};