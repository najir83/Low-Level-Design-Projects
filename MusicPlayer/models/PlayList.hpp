#pragma once
#include "Song.hpp"
#include <string>
#include <vector>
#include <stdexcept>

class PlayList
{
    std::string name;
    std::vector<Song *> songs;

public:
    PlayList(const std::string &name)
        : name(name) {}
    void addSong(Song *song)
    {
        songs.push_back(song);
    }
    std::vector<Song *> getSongs() const
    {
        return songs;
    }
    std::string getName()
    {
        return name;
    }
    int getSize()
    {
        return (int)songs.size();
    }
};