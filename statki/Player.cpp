#include "Player.hpp"

Player::Player(short int count) {
    playerTurn = false;
    tilesCount = count;
}

void Player::hit() {
    tilesCount--;
}

short int Player::getTilesCount() const {
    return tilesCount;
}

void Player::setTilesCount(short int count) {
    tilesCount = count;
}

void Player::changeTurn() {
    playerTurn = !playerTurn;
}

void Player::setTurn(bool turn) {
    playerTurn = turn;
}

bool Player::isPlayerTurn() const {
    return playerTurn;
}
