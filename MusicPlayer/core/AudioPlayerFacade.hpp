#pragma once
#include "AudioPlayerEngine.hpp"
#include "../models/PlayList.hpp"
#include "../enums/PlayerType.hpp"
#include "../managers/DeviceManager.hpp"
#include "../managers/PlaylistManager.hpp"

class AudioPlayerFacade
{
    AudioPlayerEngine *engin;
    PlayList *currPlaylist;
    static AudioPlayerFacade *instance;

    AudioPlayerFacade()
    {
        engin = new AudioPlayerEngine();
        currPlaylist = nullptr;
    }

public:
    static AudioPlayerFacade *getInstance()
    {
        if (!instance)
            instance = new AudioPlayerFacade();
        return instance;
    }
    void connectDevice(PlayerType ptype)
    {
        DeviceManager::getInstance()->connect(ptype);
    }
    void loadPlaylist(std::string &name)
    {
        currPlaylist = PlayListManager::getInstance()->getPlayList(name);
    }
    void play(Song *song)
    {
        engin->play(song, DeviceManager::getInstance()->getDevice());
    }
    void pause()
    {
        engin->pause();
    }

    ~AudioPlayerFacade()
    {
        delete engin;
        delete DeviceManager::getInstance();
    }
};

AudioPlayerFacade *AudioPlayerFacade::instance = nullptr;