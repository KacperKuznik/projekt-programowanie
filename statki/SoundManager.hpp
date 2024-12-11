#pragma once

#include "SFML/Audio.hpp"
#include <iostream>

class SoundManager
{
private:
    sf::SoundBuffer shoot_buffer;
    sf::Sound shoot_sound;
    sf::SoundBuffer click_buffer;
    sf::Sound click_sound;
public:
    SoundManager();
    void shoot();
    void click();
};
