#pragma once
#include <iostream>
class Player 
{
private:
	short int tiles_count;
	bool player_move;
public:
	Player(short int _count) {
		player_move = false;
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
};