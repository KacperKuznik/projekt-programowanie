#pragma once

#include "SFML/Graphics.hpp"
#include "Grid.hpp"
#include "Network.hpp"
#include "Tile.hpp"
#include "Ship.hpp"
#include "GridPlayer.hpp"
#include "GridEnemy.hpp"
#include "Player.hpp"
#include "Button.hpp"
#include <vector>
#include <iostream>
#include <string>
#include <cmath>
#include <sstream>

class Game
{
private:
    int width = 1200;
    int height = 900;
    int gridWidth = 500;
    int tileWidth = gridWidth / 10;
    char columnLabels[10];

    int posX = 25;
    int posY = 10;
    int row, col;

    int selShip = -1;
    bool shipIsSelected = false;
    bool selfFound = false;

    unsigned short port;
    Network network;
    sf::Text text;
    sf::Text playerTurnText;
    sf::Font font;

    sf::Texture bgMenu;
    sf::Sprite bg;

    sf::String ipInput;
    sf::String portInput;

    std::vector< Ship > ships;
    Player player;

    bool started = false;
public:
    void startMenu();
    void joinMenu();
    void hostMenu();
    void run();
    void displayTurnText(sf::RenderWindow& window, bool isPlayerTurn);
    short int createShips();
    bool allShipsPlaced();
    int shipSel(sf::Vector2f mouse);
    bool shipMove(sf::Vector2f mouse, int selShip, GridPlayer playerGrid);
    bool shipRotate(Ship ship, GridPlayer playerGrid);
    void updateShips(GridPlayer playerGrid);
    void checkShips(GridPlayer playerGrid);
    void checkWin(Player& player, Player& enemy, sf::RenderWindow& window);
    bool chooseStartingPlayer();
};
