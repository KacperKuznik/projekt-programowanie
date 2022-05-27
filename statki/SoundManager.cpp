#pragma once
#include <SFML/Audio.hpp>
#include <iostream>
class SoundManager
{
private:
    sf::SoundBuffer shoot_buffer;
    sf::Sound shoot_sound;
    sf::SoundBuffer click_buffer;
    sf::Sound click_sound;
public:
    SoundManager() {
        shoot_buffer.loadFromFile("sound/sus.wav");
        click_buffer.loadFromFile("sound/click.wav");
    }
    void shoot() {
        shoot_sound.setBuffer(shoot_buffer);
        shoot_sound.play();
    }
    void click() {
        click_sound.setBuffer(click_buffer);
        click_sound.play();
    }
};