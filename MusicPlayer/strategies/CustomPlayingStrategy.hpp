#pragma once
#include "IPlayingStrategy.hpp"
#include <vector>
#include <queue>
#include <set>
#include <ctime>
#include <algorithm>

class CustomPlayingStrategy : public IPlayingStrategy
{
    std::queue<Song *> songs;
    std::queue<Song *> history;
    std::set<std::string> queuedSongs;

public:
    CustomPlayingStrategy()
    {
    }
    void setPlayList(PlayList *p)
    {

        for (Song *s : p->getSongs())
        {
            if (queuedSongs.count(s->getName()))
                continue;
            songs.push(s);
            queuedSongs.insert(s->getName());
        }
    }
    bool hasNextSong()
    {
        return !songs.empty();
    }
    bool hasPrevSong()
    {
        return !history.empty();
    }

    Song *nextSong()
    {
        if (!hasNextSong())
        {
            throw std::runtime_error("No next song available for the playlist");
        }

        Song *s = songs.front();
        songs.pop();

        history.push(s);

        return s;
    }
    Song *prevSong()
    {
        if (!hasPrevSong())
        {
            throw std::runtime_error("No previous song available for the playlist");
        }
        Song *s = history.front();
        history.pop();
        return s;
    }
    void queueNextSong(Song *s)
    {
        if (!s)
        {
            throw std::runtime_error("Invalid song");
        }

        queuedSongs.insert(s->getName());
        songs.push(s);
    }
    ~CustomPlayingStrategy()
    {
    }
};