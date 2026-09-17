#pragma once
#include <iostream>
#include <string>

class WiredPlayer
{
public:
    void playSongViaWired(std::string &song)
    {
        std::cout << "[Playing song via wired player: " << song << "]\n";
    }
};