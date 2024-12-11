#pragma once

#include <iostream>

class Player
{
private:
	short int tiles_count;
	bool player_turn;
public:
	Player();
	Player(short int _count);
	void hit();
	short int getTilesCount();
	void setTilesCount(short int _count);
	void changeTurn();
	void setTurn(bool _player_turn);
	bool isPlayerTurn();
};
