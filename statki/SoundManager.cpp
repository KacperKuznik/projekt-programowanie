#include "SoundManager.hpp"

SoundManager::SoundManager() {
    shootBuffer.loadFromFile("sound/sus.wav");
    clickBuffer.loadFromFile("sound/click.wav");
}

void SoundManager::playShoot() {
    shootSound.setBuffer(shootBuffer);
    shootSound.play();
}

void SoundManager::playClick() {
    clickSound.setBuffer(clickBuffer);
    clickSound.play();
}
