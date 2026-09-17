#include <iostream>
#include "./models/Song.hpp"
#include "./core/AudioPlayerFacade.hpp"
int main()
{
    AudioPlayerFacade *apf = AudioPlayerFacade::getInstance();

    Song *song = new Song("Sun raha hain na tu", "Jubbin Natiyal", "tseries/jubbin/core");
    PlayerType type = BLUETOOTH;
    apf->connectDevice(type);
    apf->play(song);
    apf->pause();
    apf->play(song);
    




    delete song;

    delete apf;

    return 0;
}