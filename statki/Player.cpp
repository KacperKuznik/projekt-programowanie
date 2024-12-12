#include "Player.hpp"

Player::Player() = default;

Player::Player(short int count) {
    playerTurn = false;
    tilesCount = count;
}

void Player::hit() {
    tilesCount--;
}

short int Player::getTilesCount() {
    return tilesCount;
}

void Player::setTilesCount(short int count) {
    tilesCount = count;
}

void Player::changeTurn() {
    playerTurn = !playerTurn;
}

void Player::setTurn(bool playerTurn) {
    this->playerTurn = playerTurn;
}

bool Player::isPlayerTurn() {
    return playerTurn;
}
