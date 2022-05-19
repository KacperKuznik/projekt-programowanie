#pragma once
#include <SFML/Audio.hpp>
#include <iostream>
class SoundManager
{
private:
    sf::SoundBuffer shoot_buffer;
    sf::Sound shoot_sound;
public:
    SoundManager() {
        shoot_buffer.loadFromFile("sound/sus.wav");
    }
    void shoot() {
        shoot_sound.setBuffer(shoot_buffer);
        shoot_sound.play();
    }
};