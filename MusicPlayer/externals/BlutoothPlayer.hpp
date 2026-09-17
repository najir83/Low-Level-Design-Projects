#pragma once
#include <iostream>
#include <string>

class BluetoothPlayer
{
public:
    void playSongViaBluetooth(std::string &song)
    {
        std::cout << "[Playing song via bluetooth: " << song << "]\n";
    }

    ~BluetoothPlayer(){
        std::cout<<"Bluetooth speaker deleted\n";
    }
};