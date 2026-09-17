#pragma once
#include "IPlayingStrategy.hpp"
#include <vector>
#include <queue>
#include <ctime>
#include <algorithm>

class RandomPlayingStrategy : public IPlayingStrategy
{
    std::vector<Song *> songs;
    std::queue<Song *> history;

public:
    RandomPlayingStrategy()
    {
        srand((unsigned)time(nullptr));
    }
    void setPlayList(PlayList *playList)
    {
        this->songs = playList->getSongs();
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
        int id = (rand() % (unsigned)(songs.size()));
        Song *s = songs[id];
        history.push(s);
        songs.erase(find(songs.begin(), songs.end(), s));
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
    ~RandomPlayingStrategy()
    {
    }
};