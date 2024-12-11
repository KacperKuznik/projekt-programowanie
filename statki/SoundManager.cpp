#include "SoundManager.hpp"

SoundManager::SoundManager() {
    if (!shoot_buffer.loadFromFile("sound/sus.wav")) {
        std::cerr << "Failed to load shoot sound" << std::endl;
    }
    if (!click_buffer.loadFromFile("sound/click.wav")) {
        std::cerr << "Failed to load click sound" << std::endl;
    }
}

void SoundManager::shoot() {
    shoot_sound.setBuffer(shoot_buffer);
    shoot_sound.play();
}

void SoundManager::click() {
    click_sound.setBuffer(click_buffer);
    click_sound.play();
}
