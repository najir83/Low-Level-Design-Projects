#pragma once
#include "../externals/BlutoothPlayer.hpp"
#include "IAudioPlayer.hpp"
#include <thread>
#include <chrono>

class BluetoothPlayerAdapter : public IAudioPlayer
{
    BluetoothPlayer *player;

public:
    BluetoothPlayerAdapter(BluetoothPlayer *player) : player(player) {}
    void play(Song *song)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        std::string buffer = "[Name:" + song->getName() + ", Artist: " + song->getArtist() + ", Path: " + song->getPath() + "]";
        player->playSongViaBluetooth(buffer);
    }
    ~BluetoothPlayerAdapter()
    {
        delete player;
    }
};