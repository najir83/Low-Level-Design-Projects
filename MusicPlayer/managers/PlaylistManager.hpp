#pragma once
#include <map>
#include "../models/PlayList.hpp"
#include <string>

class PlayListManager
{
    static PlayListManager *instance;
    std::map<std::string, PlayList *> playlists;
    PlayListManager()
    {
    }
public:
    static PlayListManager *getInstance()
    {
        if (instance == nullptr)
        {
            instance = new PlayListManager();
        }
        return instance;
    }
    void createPlayList(const std::string &name)
    {
        if (playlists.find(name) == playlists.end())
        {
            playlists[name] = new PlayList(name);
        }
    }
    void addSongToPlayList(const std::string &playlistName, Song *song)
    {
        if (playlists.find(playlistName) != playlists.end())
        {
            playlists[playlistName]->addSong(song);
        }
    }
    PlayList *getPlayList(const std::string &name) const
    {
        if (playlists.find(name) != playlists.end())
        {
            return playlists.at(name);
        }
        else
        {
            throw std::runtime_error("Playlist not found");
        }
    }
    ~PlayListManager()
    {
        
        for (auto &[name, playlist] : playlists)
        {
            delete playlist;
        }
    }
};

PlayListManager *PlayListManager::instance = nullptr;