#pragma once
#include "../devices/BlutoothPlayerAdapter.hpp"
#include "../devices/WiredPlayerAdapter.hpp"
#include "../devices/IAudioPlayer.hpp"
#include "../externals/BlutoothPlayer.hpp"
#include "../externals/WiredPlayer.hpp"
#include <stdexcept>

#include "../enums/PlayerType.hpp"

class AudioPlayerFactory
{

public:
    static IAudioPlayer *create(PlayerType ptype)
    {
        if (ptype == PlayerType::BLUETOOTH)
        {
            return new BluetoothPlayerAdapter(new BluetoothPlayer());
        }
        else
        {
            return new WiredPlayerAdapter(new WiredPlayer());
        }
    }
};
