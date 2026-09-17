#include <bits/stdc++.h>
#include "MusicPlayer.hpp"
#include "./enums/PlayStrategyType.hpp"
using namespace std;

int main()
{

    try
    {
        MusicPlayer myPlayer;
        myPlayer.connectDevice(PlayerType::BLUETOOTH);
        myPlayer.addSong("Sun raha hain na tu", "Jubbin Natiyal", "/tseries/core/sun-raha-hai");
        // myPlayer.play("Sun raha hain na tu");
        // myPlayer.pause();
        // myPlayer.play("Sun raha hain na tu");

        myPlayer.addSong("Tum Hi Ho", "Arijit", "/music/tum-hi-ho");
        myPlayer.addSong("Apna Bana Le", "Arijit", "/music/apna-bana-le");
        myPlayer.addSong("Kesariya", "Arijit", "/music/kesariya");
        myPlayer.addSong("Heeriye", "Jasleen", "/music/heeriye");
        myPlayer.addSong("Chaleya", "Arijit", "/music/chaleya");
        myPlayer.addSong("Raabta", "Arijit", "/music/raabta");
        myPlayer.addSong("Satranga", "Arijit", "/music/satranga");
        myPlayer.addSong("Ilahi", "Arijit", "/music/ilahi");
        myPlayer.addSong("Hawayein", "Arijit", "/music/hawayein");
        myPlayer.addSong("Phir Se Ud Chala", "Mohan", "/music/phir-se-ud-chala");

        myPlayer.createPlayList("fav");

        myPlayer.addSongToPlaylist("Tum Hi Ho", "fav");
        myPlayer.addSongToPlaylist("Kesariya", "fav");
        myPlayer.addSongToPlaylist("Chaleya", "fav");
        myPlayer.addSongToPlaylist("Satranga", "fav");
        myPlayer.addSongToPlaylist("Phir Se Ud Chala", "fav");
        myPlayer.addSongToPlaylist("Hawayein", "fav");

        myPlayer.loadPlayList("fav");

        myPlayer.playAllSongsFromPlaylist();
        cout << endl;
        myPlayer.connectDevice(PlayerType::WIRED);

        myPlayer.switchPlayingStrategy(PlayStrategyType::RANDOM);

        myPlayer.playAllSongsFromPlaylist();
        cout << endl;
        myPlayer.connectDevice(PlayerType::BLUETOOTH);

        myPlayer.switchPlayingStrategy(PlayStrategyType::CUSTOM);

        myPlayer.addToCustome("Phir Se Ud Chala");
        myPlayer.addToCustome("Raabta");
        myPlayer.playAllSongsFromPlaylist();
    }
    catch (const exception &e)
    {
        cerr << "Error: " << e.what() << endl;
    }

    return 0;
}