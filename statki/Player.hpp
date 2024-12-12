#pragma once

#include <iostream>

class Player
{
private:
	short int tilesCount;
	bool playerTurn;
public:
	Player();
	Player(short int _count);
	void hit();
	short int getTilesCount();
	void setTilesCount(short int _count);
	void changeTurn();
	void setTurn(bool _playerTurn);
	bool isPlayerTurn();
};
