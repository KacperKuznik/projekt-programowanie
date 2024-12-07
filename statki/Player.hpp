#pragma once

#include <iostream>

class Player {
private:
    short int tilesCount;
    bool playerTurn;

public:
    Player() = default;
    Player(short int count);

    void hit();
    short int getTilesCount() const;
    void setTilesCount(short int count);
    void changeTurn();
    void setTurn(bool turn);
    bool isPlayerTurn() const;
};
