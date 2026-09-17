#pragma once
#include <string>

class Song
{
    std::string name;
    std::string artist;
    std::string path;

    public:
    Song(const std::string name, const std::string artist, const std::string path)
        : name(name), artist(artist), path(path) {}
    const std::string& getName() const
    {
        return name;
    }

    void setName(const std::string& name)
    {
        this->name = name;
    }

    const std::string& getArtist() const
    {
        return artist;
    }

    void setArtist(const std::string& artist)
    {
        this->artist = artist;
    }

    const std::string& getPath() const
    {
        return path;
    }

    void setPath(const std::string& path)
    {
        this->path = path;
    }
};