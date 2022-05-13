#pragma once
#include <iostream>
class Player 
{
private:
	short int tiles_count;
	bool player_turn;
public:
	Player(short int _count) {
		player_turn = false;
		tiles_count = _count;
	}
	void hit() {
		tiles_count--;	
	}
	short int getTilesCount() {
		return tiles_count;
	}
	void setTilesCount(short int _count) {
		tiles_count = _count;
	}
	void changeTurn() {
		player_turn = !player_turn;
	}
	bool isPlayerTurn() {
		return player_turn;
	}
};