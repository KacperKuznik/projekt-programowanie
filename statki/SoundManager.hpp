#pragma once

#include "SFML/Audio.hpp"
#include <iostream>

class SoundManager
{
private:
    sf::SoundBuffer shootBuffer;
    sf::Sound shootSound;
    sf::SoundBuffer clickBuffer;
    sf::Sound clickSound;
public:
    SoundManager();
    void shoot();
    void click();
};
