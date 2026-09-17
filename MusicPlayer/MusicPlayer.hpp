#include "./core/AudioPlayerFacade.hpp"
#include "./managers/PlaylistManager.hpp"
#include <map>

class MusicPlayer
{
    std::map<std::string, Song *> library;

public:
    void addSong(const std::string title, std::string artist, std::string path)
    {
        library[title] = new Song(title, artist, path);
    }
    void connectDevice(PlayerType type)
    {
        AudioPlayerFacade::getInstance()->connectDevice(type);
    }
    void switchPlayingStrategy(PlayStrategyType type)
    {
        AudioPlayerFacade::getInstance()->setStrategy(type);
    }
    void loadPlayList(std::string name)
    {
        AudioPlayerFacade::getInstance()->loadPlaylist(name);
    }
    void play(std::string title)
    {
        if (library.find(title) == library.end())
        {
            throw std::runtime_error("No song available with the title: " + title);
        }
        AudioPlayerFacade::getInstance()->play(library[title]);
    }
    void pause()
    {
        AudioPlayerFacade::getInstance()->pause();
    }
    void playAllSongsFromPlaylist()
    {
        AudioPlayerFacade::getInstance()->playAll();
    }
    void selectPlayList(std::string name)
    {
        AudioPlayerFacade::getInstance()->loadPlaylist(name);
    }
    void next()
    {
        AudioPlayerFacade::getInstance()->playNext();
    }
    void previous()
    {
        AudioPlayerFacade::getInstance()->playPrev();
    }
    void addToCustome(std::string title)
    {

        if (library.find(title) == library.end())
        {
            throw std::runtime_error("No song available with the title: " + title);
        }
        AudioPlayerFacade::getInstance()->addSongToCustom(library[title]);
    }
    void createPlayList(std::string name)
    {
        PlayListManager::getInstance()->createPlayList(name);
    }
    void addSongToPlaylist(std::string title, std::string playListName)
    {
        if (library.find(title) == library.end())
        {
            throw std::runtime_error("No song available with the title: " + title);
        }
        PlayListManager::getInstance()->addSongToPlayList(playListName, library[title]);
    }
    ~MusicPlayer()
    {
        for (auto &it : library)
        {
            delete it.second;
        }
        delete AudioPlayerFacade::getInstance();
        delete PlayListManager::getInstance();
    }
};