#pragma once
#include "../externals/BlutoothPlayer.hpp"
#include "IAudioPlayer.hpp"

class BluetoothPlayerAdapter : public IAudioPlayer
{
    BluetoothPlayer *player;

public:
    BluetoothPlayerAdapter(BluetoothPlayer *player) : player(player) {}
    void play(Song *song)
    {
        std::string buffer = "[Name:" + song->getName() + ", Artist: " + song->getArtist() + ", Path: " + song->getPath() + "]";
        player->playSongViaBluetooth(buffer);
    }
    ~BluetoothPlayerAdapter()
    {
        delete player;
    }
};