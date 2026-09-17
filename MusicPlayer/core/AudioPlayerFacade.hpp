#pragma once
#include "AudioPlayerEngine.hpp"
#include "../models/PlayList.hpp"
#include "../enums/PlayerType.hpp"
#include "../managers/DeviceManager.hpp"
#include "../managers/PlaylistManager.hpp"
#include "../strategies/IPlayingStrategy.hpp"
#include "../enums/PlayStrategyType.hpp"
#include "../strategies/IPlayingStrategy.hpp"
#include "../managers/StrategyManager.hpp"

class AudioPlayerFacade
{
    AudioPlayerEngine *engin;
    PlayList *currPlaylist;
    static AudioPlayerFacade *instance;
    IPlayingStrategy *strategy;

    AudioPlayerFacade()
    {
        engin = new AudioPlayerEngine();
        currPlaylist = nullptr;
        strategy = StrategyManager::getInstance()->getStrategy(PlayStrategyType::SEQUENTIAL);
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
    void setStrategy(PlayStrategyType type)
    {
        strategy = StrategyManager::getInstance()->getStrategy(type);
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
    void playNext()
    {
        if (!currPlaylist)
        {
            throw std::runtime_error("No playlist loaded.");
        }
        strategy->setPlayList(currPlaylist);

        if (!strategy->hasNextSong())
        {
            std::cout << "No songs are available\n";
            return;
        }
        engin->play(strategy->nextSong(), DeviceManager::getInstance()->getDevice());
    }
    void playPrev()
    {
        if (!currPlaylist)
        {
            throw std::runtime_error("No playlist loaded.");
        }

        strategy->setPlayList(currPlaylist);

        if (!strategy->hasPrevSong())
        {
            std::cout << "No songs are available\n";
            return;
        }
        engin->play(strategy->prevSong(), DeviceManager::getInstance()->getDevice());
    }
    void playAll()
    {
        if (!currPlaylist)
        {
            throw std::runtime_error("No playlist loaded.");
        }
        strategy->setPlayList(currPlaylist);

        while (strategy->hasNextSong())
        {
            Song *s = strategy->nextSong();
            engin->play(s, DeviceManager::getInstance()->getDevice());
        }
        std::cout << "Completed Playlist: " << currPlaylist->getName() << "\n";
    }
    void addSongToCustom(Song *s)
    {
        strategy->queueNextSong(s);
    }

    ~AudioPlayerFacade()
    {
        delete engin;
        delete DeviceManager::getInstance();
    }
};

AudioPlayerFacade *AudioPlayerFacade::instance = nullptr;