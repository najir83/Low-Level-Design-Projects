#pragma once
#include "../factories/AudioPlayerFactory.hpp"
#include "../devices/IAudioPlayer.hpp"
#include <stdexcept>

class DeviceManager
{
    static DeviceManager *instance;
    IAudioPlayer *currPlayer;
    DeviceManager()
    {
        currPlayer = nullptr;
    }

public:
    static DeviceManager *getInstance()
    {
        if (instance == nullptr)
        {
            instance = new DeviceManager();
        }
        return instance;
    }
    void connect(PlayerType ptype)
    {
        if (currPlayer)
        {
            delete currPlayer;
        }
        currPlayer = AudioPlayerFactory::create(ptype);
        switch (ptype)
        {
        case PlayerType::BLUETOOTH:
            std::cout << "Bluetooth device connected\n";
            break;
        case PlayerType::WIRED:
            std::cout << "Wired device connected\n";
            break;
        default:
            break;
        }
    }
    IAudioPlayer *getDevice()
    {
        if (currPlayer == nullptr)
        {
            throw std::runtime_error("Device not found");
        }
        return currPlayer;
    }
    ~DeviceManager()
    {
        delete currPlayer;
    }
};

DeviceManager *DeviceManager::instance = nullptr;
