#include "Player.hpp"

Player::Player() = default;

Player::Player(short int _count) {
	player_turn = false;
	tiles_count = _count;
}

void Player::hit() {
	tiles_count--;
}

short int Player::getTilesCount() {
	return tiles_count;
}

void Player::setTilesCount(short int _count) {
	tiles_count = _count;
}

void Player::changeTurn() {
	player_turn = !player_turn;
}

void Player::setTurn(bool _player_turn) {
	player_turn = _player_turn;
}

bool Player::isPlayerTurn() {
	return player_turn;
}
