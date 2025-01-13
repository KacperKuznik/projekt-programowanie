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
#include "History.hpp"
#include <vector>
#include <iostream>
#include <string>
#include <cmath>
#include <sstream>
#include <fstream>
#include <filesystem>
#include <regex>

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

    std::vector<Ship<Tile>> ships;
    Player player;

    bool started = false;

    std::string history_file_name;

    enum paarameters {
        INIT_HOST_BTN_X_POS = 525,
        INIT_HOST_BTN_Y_POS = 200,
        INIT_JOIN_BTN_X_POS = 525,
        INIT_JOIN_BTN_Y_POS = 350,

        CHAR_SIZE = 50,

        INIT_IP_TEXT_X_POS = 400,
        INIT_IP_TEXT_Y_POS = 50,
        INIT_PORT_TEXT_X_POS = 400,
        INIT_PORT_TEXT_Y_POS = 150,
        INIT_JOIN_CONF_BTN_X_POS = 525,
        INIT_JOIN_CONF_BTN_Y_POS = 300,

        INIT_IP_BOX_X_POS = 395,
        INIT_IP_BOX_Y_POS = 50,
        INIT_IP_BOX_OUTLINE_THICKNESS = 5,

        INIT_PORT_BOX_X_POS = 395,
        INIT_PORT_BOX_Y_POS = 150,
        INIT_PORT_BOX_OUTLINE_THICKNESS = 5
    };
public:
    Game();
    void startMenu();
    void joinMenu();
    void hostMenu();
    void run();
    void displayTurnText(sf::RenderWindow& window, bool isPlayerTurn);
    short int createShips();
    bool allShipsPlaced();
    int shipSel(sf::Vector2f mouse);
    bool shipMove(sf::Vector2f mouse, int selShip, GridPlayer playerGrid);
    bool shipRotate(Ship<Tile> ship, GridPlayer playerGrid);
    void updateShips(GridPlayer playerGrid);
    int checkWin(Player& player, Player& enemy, sf::RenderWindow& window);
    bool chooseStartingPlayer();
    static void printState(GridPlayer playerGrid, std::string history_file_name);
};
