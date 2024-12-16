#include "SoundManager.hpp"

SoundManager::SoundManager() {
    if (!shootBuffer.loadFromFile("sound/sus.wav")) {
        std::cerr << "Failed to load shoot sound" << std::endl;
    }
    if (!clickBuffer.loadFromFile("sound/click.wav")) {
        std::cerr << "Failed to load click sound" << std::endl;
    }
}

SoundManager::~SoundManager() {
    shootSound.stop();
    clickSound.stop();
}

void SoundManager::shoot() {
    shootSound.setBuffer(shootBuffer);
    shootSound.play();
}

void SoundManager::click() {
    clickSound.setBuffer(clickBuffer);
    clickSound.play();
}
